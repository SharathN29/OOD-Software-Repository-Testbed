
/////////////////////////////////////////////////////////////
// TestExecutive.cpp - Tests all the test requirements	   //
// ver 1.0												   //
// Author - Sharath Nagendra							   //
// CSE 687 - Object Oriented Design, Spring 2018		   //
////////////////////////////////////////////////////////////

#include "../CoreRepository/CoreRepository.h"
#include "../PayLoad/PayLoad.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include "../Utilities/StringUtilities/StringUtilities.h"

using namespace NoSqlDb;

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

class test {
public:
	test(DbCore<PayLoad>& db_) :db(db_){}
	bool test1();
	bool test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void test7();
	void test8();

private:
	DbCore<PayLoad> db;
};


//----< Demonstrating Requirement #1 >--------------------------

bool test::test1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();
	return true; // would  not compile unless C++11
}

//----< Demonstrating Requirement #2 >--------------------------

bool test::test2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//----< Demonstrating Requirement #2 >---------------------------

void test::test3()
{
	Utilities::title("Demostrating Requirement #3 - All the required packages has been provided");
	std::cout << "\n All the required packages has been created in the following locations: \n";
	CoreRepository<PayLoad>::identify();
	CheckIn<PayLoad>::identify();
	CheckOut::identify();
	Version<PayLoad>::identify();
	Browse<PayLoad>::identify();
	putLine();
}

void test::test4()
{
	Utilities::title("Demostrating Requirement #4 - Check-In of files");
	CoreRepository<PayLoad> repocore(db);
	Path_ srcpath = "../PayLoad/PayLoad.h";
	Namespace_ name = "NoSqlDb";
	Keys key;
	Keys child;
	key.push_back("cat1");
	key.push_back("cat2");
	Filename_ file = "PayLoad.h";
	std::cout << "\nThe file ../PayLoad/PayLoad.h is being checked-in to the Repository";
	std::cout << "\n-------------------------------------------------------------------\n";
	repocore.CheckIn(srcpath, name, child, key);
	showDb(db);
	putLine();

	std::cout << "\n Closing the status of PayLoad.h.1";
	std::cout << "--------------------------------------";
	repocore.CloseStatus(name, file);
	showDb(db);

	std::cout << "\n A new version of PayLoad.h is being checked-in. The new key for new version will be Persist.h.2";
	std::cout << "\n -----------------------------------------------------------------------------------------------";
	repocore.CheckIn(srcpath, name, child, key);
	showDb(db);
	putLine();

	std::cout << "\n Trying to check-in a new version of PayLoad.h, while keeping the old previous checkin status as Open";
	std::cout << "\n ----------------------------------------------------------------------------------------------------";
	repocore.CheckIn(srcpath, name, child, key);
	showDb(db);
	std::cout << "\n Since the old version is still open, new version will not be checked-in";
	putLine();

	std::cout << "\n Checking-in ../DbCore/DbCore.h with PayLoad.h.2 as its children";
	std::cout << "\n--------------------------------------------------------------";
	child.push_back("NoSqlDb::PayLoad.h.2");
	srcpath = "../DbCore/DbCore.h";
	file = "DbCore.h";
	repocore.CheckIn(srcpath, name, child, key);
	showDb(db);
	putLine();

	std::cout << "\n Trying to close DbCore.h";
	std::cout << "\n -------------------------";
	repocore.CloseStatus(name, file);
	showDb(db);
	key.clear();
	std::cout << "\n Unable to close DbCore.h, as its child PayLoad.h.2 is still Open";
	putLine();

	std::cout << "\n Checking-In more files";
	std::cout << "\n ----------------------";
	srcpath = "../PayLoad/PayLoad.cpp";
	file = "PayLoad.cpp";
	key.push_back("cat4");
	repocore.CheckIn(srcpath, name, child, key);

	srcpath = "../DbCore/DbCore.cpp";
	child.clear();
	child.push_back("NoSqlDb::DbCore.h.1");
	file = "DbCore.cpp";
	repocore.CheckIn(srcpath, name, child, key);
	putLine();
}

void test::test5()
{
	Utilities::title("Checking-In files to a new namespace called DB");
	CoreRepository<PayLoad> repocore(db);
	Namespace_ name = "DB";
	Path_ srcpath = "../Process/Process.h";
	Keys key;
	Keys child;
	key.push_back("cat2");
	Filename_ filename = "Process.h";
	repocore.CheckIn(srcpath, name, child, key);
	repocore.CloseStatus(name, filename);
	repocore.CheckIn(srcpath, name, child, key);

	srcpath = "../Process/Process.cpp";
	child.push_back("DB::Process.h.1");
	key.push_back("cat4");
	repocore.CheckIn(srcpath, name, child, key);

	srcpath = "../Browse/Browse.h";
	repocore.CheckIn(srcpath, name, child, key);

	srcpath = "../Browse/Browse.cpp";
	repocore.CheckIn(srcpath, name, child, key);
	showDb(db);
	putLine();

	std::cout << "\n Displaying all the .cpp files in the namespace";
	std::cout << "\n ----------------------------------------------";
	repocore.getQueryFiles("cpp");
	putLine();
}

void test::test6()
{
	Utilities::title("Demonstrating Requirement #4 - CheckOut - Copying a partiular file");
	CoreRepository<PayLoad> repocore(db);
	Namespace_ namespace_ = "NoSqlDb";
	Filename_ filename = "DbCore.cpp";
	std::cout << "\n The file DbCore.cpp is checkedout with all its children";
	repocore.CheckOut(namespace_, filename, 1);
	putLine();
}

void test::test7()
{
	Utilities::title("Demonstrating Requirement #5 - Querying the database based on a condition");
	CoreRepository<PayLoad> repocore(db);
	std::cout << "\n The files that belong to the namespace DB are :";
	std::cout << "\n -----------------------------------------------";
	repocore.getQueryFiles("DB");

	std::cout << "\n\n Different versions of Process.h files in the namespace DB are: ";
	std::cout << "\n ---------------------------------------------------------------";
	repocore.getQueryFiles("Process.h");

	std::cout << "\n\n The dependencies of the file Browse.h";
	std::cout << "\n ---------------------------------------";
	std::string file = "DB::Browse.h.1";
	repocore.show_dependency(file);

	std::cout << "\n Query to display all the header files ";
	std::cout << "\n --------------------------------------";
	repocore.getQueryFiles(".h");

	std::cout << "\n Displaying all the files that belong to cat 2";
	std::cout << "\n ---------------------------------------------";
	repocore.getCatQueryFiles("cat2");

	Namespace_ namespace_ = "NoSqlDb";
	Filename_ filename = "DbCore.cpp";
	std::cout << "\nDisplaying the DbCore.cpp in a notepad file";
	std::cout << "\n---------------------------------------------";
	repocore.showDbFile(namespace_, filename, 1);
	putLine();
}

void test::test8()
{
	std::cout << "\n Demostrating parent-child relationship between a key and its child field";
	std::cout << "\n ------------------------------------------------------------------------";
	CoreRepository<PayLoad> repocore(db);
	Namespace_ name = "Relationship";
	Path_ srcpath = "../Browse/Browse.h";
	Keys key;
	Keys child;
	Key key1 = "Relationship::Browse.h.1";
	Key key2 = "Relationship::Query.h.1";
	Key filename = "Browse.h";
	std::cout << "\n\n Checkin-In Browse.h";
	std::cout << "\n ---------------------\n";
	repocore.CheckIn(srcpath, name, child, key);
	putLine();


	srcpath = "../Query/Query.h";
	child.push_back(key1);
	std::cout << "\n Checking-In Query.h";
	std::cout << "\n -------------------";
	repocore.CheckIn(srcpath, name, child, key);
	putLine();
	child.clear();

	srcpath = "../Browse/Browse.h";
	child.push_back(key2);
	repocore.CheckIn(srcpath, name, child, key);
	repocore.getQueryFiles("Relationship");
	putLine();

	std::cout << "\n Closing the file Browse.h.1 which has a relationship with Query.h.1";
	std::cout << "\n --------------------------------------------------------------------";
	repocore.CloseStatus(name, filename);
	putLine();

	std::cout << "\n Dependency has been handled ";
	repocore.getQueryFiles("Relationship");
	srcpath = "../Browse/Browse.h";
	std::cout << "\n\n Trying to check-in new version of Browse.h";
	repocore.CheckIn(srcpath, name, child, key);
	putLine();
	repocore.getQueryFiles("Relationship");
	putLine();

	std::cout << "\n Displaying the files in all the namespaces in the DB";
	std::cout << "\n ----------------------------------------------------";
	showDb(db);
}


int main()
{
	DbCore<PayLoad> db;
	test t(db);
	t.test1();
	t.test2();
	t.test3();
	t.test4();
	t.test5();
	t.test6();
	t.test7();
	t.test8();
	getchar();
    return 0;
}


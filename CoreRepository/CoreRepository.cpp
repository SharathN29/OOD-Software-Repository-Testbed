//////////////////////////////////////////////////////
// CoreRepository.cpp                               //
// ver 1.0					                        //
// Author - Sharath Nagendra                        //
// CSE 687 - Object Oriented Design, Spring 2018    //
//////////////////////////////////////////////////////


#include "../CoreRepository/CoreRepository.h"

using namespace NoSqlDb;


#ifdef Test_CoreRepository

void repositorytest() {
	DbCore<PayLoad> db;
	Path_ srcpath = "../PayLoad/PayLoad.h";
	Namespace_ namespace_ = "NoSqlDb";
	CoreRepository<PayLoad> repocore(db);
	repocore.CheckIn(srcpath,namespace_);
	std::string x = "xxxx";
	repocore.CheckOut(namespace_,x,1);

	showDb(db);
}

int main() 
{
	repositorytest();
	getchar();
}

#endif // Test_DBCORE



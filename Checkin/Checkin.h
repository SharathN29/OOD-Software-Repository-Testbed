#pragma once
//////////////////////////////////////////////////////////////////
// CheckIn.h - Handles checking-in of files to Repository		//
// ver 1.0														//
// Author - Sharath Nagendra									//
// CSE 687 - Object Oriented Design, Spring 2018				//
//////////////////////////////////////////////////////////////////

/*
Operations Handled:
-------------------
- A file will be checked in and it'll be copied to the repository

Required Files for the Operation:
---------------------------------
- FileSysytem.h, FileSystem.cpp
- DbCore.h, DbCore.cpp
- CheckIn.cpp

Maintainance history:
----------------------
ver 1.0 - March 14 2018 - first release
*/

#include "../FileSystemDemo/FileSystem.h"
#include "../DbCore/DbCore.h"
using namespace FileSystem;

namespace NoSqlDb {


	template <typename T>
	class CheckIn 
	{
		
	public:
		CheckIn() {}
		bool filePush(Path_& srcpath_, Filename_& finalname);
		bool file_copy(Path_& srcpath,std::string);
		static void identify(std::ostream& out = std::cout);
	private:
		
		
	};

	// Function to check in a file from a path to repository 

	template <typename T>
	inline bool CheckIn<T>::filePush(Path_& srcpath_, Filename_& finalname)
	{
		if (file_copy(srcpath_, finalname))
		{
			std::cout << std::endl<< "  file copied to Repository"<<finalname;
			return true;
		}
		else
		{
			std::cout << std::endl <<  finalname<< "  file not copied";
			return false;
		}	
	    return false;
	}

	// Function to copy the checkin file to the repository

	template<typename T>
	inline bool CheckIn<T>::file_copy(Path_ & srcpath,std::string finalname)
	{
		std::string dstn = "../Repository/"+ finalname;
		std::string sourceName = FileSystem::Path::getFullFileSpec(srcpath);
		std::string dstnName = FileSystem::Path::getFullFileSpec(dstn);
		if (FileSystem::File::copy(sourceName,dstnName))
		{
			return true;
		}
		return false;
	}

	//Function to show the name of the file

	template<typename T>
	inline void CheckIn<T>::identify(std::ostream & out)
	{
		out << "\n  \"" << __FILE__ << "\"";
	}
}

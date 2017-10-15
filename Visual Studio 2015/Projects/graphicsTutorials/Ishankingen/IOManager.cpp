#include "IOManager.h"
#include <fstream>
using namespace std;


	bool IOManager::readFileToBuffer(string filepath, vector<unsigned char> &buffer) {
		ifstream file(filepath, ios::binary);
		if (file.fail()) {
			perror(filepath.c_str());
			return false;
		}

		//seek to end 
		file.seekg(0, ios::end);

		int filesize = file.tellg();

		file.seekg(0, ios::beg);

		filesize -= file.tellg();//remove header (date of modification) size

		buffer.resize(filesize);

		file.read((char*)&buffer[0], filesize);
		file.close();

		return true;
	}

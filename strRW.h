#ifndef __STR_RW__
#define __STR_RW__

#include <fstream>
#include <string>
#include <io.h>
using namespace std;

void saveStr(string path,string content)
{
	ofstream fout;
	fout.open(path.c_str());
	fout<<content;
	fout.close();
}

string readStr(string path){
	ifstream ifile(path.c_str());
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch)){
		buf.put(ch);
	}
	return buf.str();
}

bool isDirExist(string path){
	return !_access(path.c_str(),0);
}

bool isFileExist(string path){
	fstream _file;
    _file.open(path.c_str(),ios::in);
	return !_file ? false : true;
}

int sizeofFile(FILE* file){
	int len;
	if(!file) return -1;
	rewind(file);
	fseek(file, 0L, SEEK_END);
	len = ftell(file);
	rewind(file);
	return len;
}

#endif

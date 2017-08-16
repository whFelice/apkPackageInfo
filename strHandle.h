#ifndef __STR_HANDLE__
#define __STR_HANDLE__
#include <string>
#include <vector>
#include <sstream>

using namespace std;

std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;
    unsigned int size=str.size();

    for(unsigned int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

string getMiddleStr(string str,string left,string right){
	vector<string> tmpList1=split(str,left);
	if(tmpList1.size()<2){
		return "";
	}
	string tmpStr=tmpList1[1];
	vector<string> tmpList2=split(tmpStr,right);
	if(tmpList2.size()<2){
		return "";
	}
	return tmpList2[0];
}

string getLeftStr(string str,string line){
	vector<string> tmpList=split(str,line);
	if(tmpList.size()<2){
		return "";
	}
	return tmpList[0];
}

string getRightStr(string str,string line){
	vector<string> tmpList=split(str,line);
	if(tmpList.size()<2){
		return "";
	}
	return tmpList[1];
}

vector<string> getMiddleStrArr(string str,string left,string right){
	vector<string> arr=split(str,left);
	int max=arr.size();
	if(max<1){
		return arr;
	}
	for(int i=1;i<max;i++){
		arr[i-1]=getLeftStr(arr[i],right);
	}
	arr.pop_back();
	return arr;
}

string intToStr(int num){
	stringstream ss;
	string str;
	ss<<num;
	ss>>str;
	return str;
}

int strToInt(string s){
	return atoi(s.c_str());
}

string RewriteTrim(string &str){
	int nLength = str.size();
	for (int i = 0; i < nLength; ++i){
		if (str[i] == '\n'){
			str.erase(i);
		}
	}
	string::size_type pos = str.find_last_not_of(' ');
	if(pos != string::npos){
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if(pos != string::npos) {
			str.erase(0, pos);
		}
	}else{
		str.erase(str.begin(), str.end());
	}
	return str;
}

void string_replace(string&s1,const string &find,const string &rep)
{
	string::size_type pos=0;
	string::size_type a=find.size();
	string::size_type b=rep.size();
	while((pos=s1.find(find,pos))!=string::npos)
	{
		s1.replace(pos,a,rep);
		pos+=b;
	}
}


#endif

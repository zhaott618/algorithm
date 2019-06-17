#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;

int main(){
        ifstream in;
        in.open("in.txt",ios::in);
        vector<vector<char> > strs;
	while(!in.eof()){
                char buffer[50];
                in.getline(buffer,100);
                vector<char> str;
                for(int i=0;i<strlen(buffer);i++){
                        str.push_back(buffer[i]);
               	}
		strs.push_back(str);
        }
	for(int i=0;i<strs.size();i++){
		for(int j=0;j<strs[0].size();j++){
			cout<<strs[i][j];	
		}
		cout<<endl;
	}
	in.close();
        return 0;
}


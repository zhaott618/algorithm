#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class PostmanTest{
	cout<<"-----from txt file input the map-----"<<endl;
	ifstream in;
	in.open("test1.txt",ios::in);
	if(!in.is_open()){
		cout<<"error openning file"<<endl;
	} 
	
	//define input map as MAP
	vector<vector<int> > MAP;
	while(!in.eof()){
		char buffer[50];
		in.getline(buffer,100);
		vector<char> str;
		for(int i=0;i<strlen(buffer);i++){
			str.push_back(buffer[i]);
		}
		MAP.push_back(str);
	}
	cout<<"------------INPUT MAP------------"<<endl;
	for(int i=0;i<MAP.size();i++){
		for(int j=0;j<MAP[0].size();j++){
			cout<<MAP[i][j];
		}
		cout<<endl;
	}
	cout<<"-----compute shortest paths from input map----"<<endl;
	
	
}

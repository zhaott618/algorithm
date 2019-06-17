#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
	vector<vector<char> > MAP;
	for(int j=0;j<2;j++){
		vector<char> map;
		for(int i=0;i<3;i++){
			char ch;
			ch=cin.get();
			map.push_back(ch);
		}
		MAP.push_back(map);
	}
	for(int j=0;j<2;j++){
	for(int i=0;i<3;i++){
		cout<<MAP[j][i]<<endl;
	}}
	return 0;	
}

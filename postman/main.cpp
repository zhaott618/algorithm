#include<iostream>
#include<TSP.h>
#include<BFS.h>
#include<vector>
#include<string>
using namespace std;
#define N_MAX 100;
#define M_MAX 100;
int main(){
	//input MAP to query route:
	int X,N,M;
	cout<<"please input the number of X, rows, cols:"<<endl;
	cin>>X>>N>>M;
	//char MAP[N][5];
	vector<vector<char> > MAP;
	//input USER-defined MAP
	cout<<"please enter every elements of the user-defined map:"<<endl;
	for(int i=0;i<N;i++){
		vector<char> map;
		for(int j=0;j<M;j++){
			char ch;
			ch=cin.get();
			/*if(ch!='#'&&ch!='.'&&ch!='X'){
				cout<<"undefined str inputed!"<<endl;
				return -1;
			}*/

			map.push_back(ch);
		}
		MAP.push_back(map);
	}
	for(int i=0;i<MAP.size();i++){
		for(int j=0;j<MAP[i].size();j++){
			cout<<MAP[i][j];
		}
		cout<<endl;
	}
	cout<<MAP[0].size()<<endl;
	cout<<MAP[0][7]<<endl;
	cout<<"hello, there!"<<endl;
	//static int C;
	vector<vector<int>> COST;
	f_bfs* b=new f_bfs();
	cout<<"hello, there!"<<endl;
	COST=b->BFS(N,M,MAP);
	cout<<"hello, there!"<<endl;
	int NC=COST[0].size();
	cout<<"size of table is:"<<NC<<endl;
	//vector<vector<int>> route;
	int route;
	tsp* t=new tsp();
	route=t->TSP(COST,NC);
	//plot(MAP,route);
	return 0;
}



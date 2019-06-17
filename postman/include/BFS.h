#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdio>
#include<cstring>
#define EAST MAZE[x][y+1]
#define WEST MAZE[x][y-1]
#define NORTH MAZE[x-1][y]
#define SOUTH MAZE[x+1][y]
#define EAST_VIS vis[x][y+1]
#define WEST_VIS vis[x][y-1]
#define NORTH_VIS vis[x-1][y]
#define SOUTH_VIS vis[x+1][y]
#define MAX_H 100
#define MAX_W 100
using namespace std;
//声明MAP数组
char MAZE[5][8] = { '#','#','#','#','#','#','#','#',
		    '#','.','.','.','G','.','X','#',
		    '#','.','#','#','.','X','.','#',
		    '#','S','X','X','.','.','.','#',
		    '#','#','#','#','#','#','#','#'};


class f_bfs{

private:
	char** MAZE;
	int vis[MAX_W][MAX_H];
	int path[MAX_W][MAX_H][2];
	struct node {
		int x; 
		int y;
		int par_x=0;
		int par_y=0;
		//struct node* next;
		//int parent[2];
		/*node(int a, int b) {
			x = a;
			y = b;
		}*/
	};
	typedef node* link;


	int bfs(vector<int>p1,vector<int>p2) {
		memset(vis,0,sizeof(vis));
		memset(path,0,sizeof(path));
		queue<node> q;
		node* start = new node;
		start->x = p1[0];
		start->y = p1[1];
		q.push(*start);

		while (!q.empty()) {
			link tmp = &(q.front());
			q.pop();
			int x = tmp->x;
			int y = tmp->y;
			path[x][y][0] = tmp->par_x;
			path[x][y][1] = tmp->par_y;
			vis[x][y] = 1;
			//将出队节点上下左右可走的节点压入队，记录其父节点

			if ((EAST == '.'||EAST=='X' || EAST == 'G')&& !EAST_VIS) {
				link newnode = new node;
				newnode->x = x;
				newnode->y = y+1;
				newnode->par_x = tmp->x;
				newnode->par_y = tmp->y;
				q.push(*newnode);
				EAST_VIS = 1;
			}

			if ((WEST == '.' || WEST == 'X' || WEST == 'G') && !WEST_VIS) {
				link newnode = new node;
				newnode->x = x;
				newnode->y = y - 1;
				newnode->par_x = tmp->x;
				newnode->par_y = tmp->y;
				q.push(*newnode);
				WEST_VIS = 1;
			}

			if ((NORTH == '.' || NORTH == 'X' || NORTH == 'G') && !NORTH_VIS) {
				link newnode = new node;
				newnode->x = x - 1;
				newnode->y = y;
				newnode->par_x = tmp->x;
				newnode->par_y = tmp->y;
				q.push(*newnode);
				NORTH_VIS = 1;
			}

			if ((SOUTH == '.' || SOUTH == 'X' || SOUTH == 'G') && !SOUTH_VIS) {
				link newnode = new node;
				newnode->x = x + 1;
				newnode->y = y;
				newnode->par_x = tmp->x;
				newnode->par_y = tmp->y;
				q.push(*newnode);
				SOUTH_VIS = 1;

			}

		}

		//use map to store path
		vector<vector<int>> route;

		vector<int> des;

		des.push_back(p2[0]);
		des.push_back(p2[1]);
		while (des[1]!=0) {
			route.push_back(des);
			des[0] = path[des[0]][des[1]][0];
			des[1] = path[des[0]][des[1]][1];
		}
		/*for (int i = route.size()-1; i >= 0;i--) {
			cout << setw(3)<<"["<<route[i][0]<<","<<route[i][1]<<"]";
			}
		cout << endl;*/
		return route.size();

	}
	
	static int M,N;

public:
	//int bfs(vector<int>p1,vector<int>p2);
	vector<vector<int>> BFS(int N,int M,vector<vector<char>>MAP);
};

//FUNCTION TO RETURN NEIGHBOUR MATRIX TABLE
vector<vector<int>> f_bfs::BFS(int N,int M,vector<vector<char>>MAP) {
	/*for(int i=0;i<MAP.size();i++){
		for(int j=0;j<MAP[i].size();j++){
			MAZE[i][j]=MAP[i][j];
		}	
	}*/
	for(int i=0;i<MAP.size();i++){
		for(int j=0;j<MAP[i].size();j++){
			cout<<MAZE[i][j];
		}
		cout<<endl;	
	}

	//MAZE=MAP;
	int n;
	vector<vector<int>> X_POS(4);

	X_POS={{1,6},{2,5},{3,2},{3,3}};
	vector<int> S_POS = { 3,1 };
	vector<int> G_POS = { 1,4 };

	vector<vector<int>> Table_Pos;
	//填入起点S坐标
	Table_Pos.push_back(S_POS);
	//填入各邮递点坐标
	for (int i = 0; i < X_POS.size(); i++)
	{
		Table_Pos.push_back(X_POS[i]);
	}
	//填入终点坐标
	Table_Pos.push_back(G_POS);
	int TOTAL = Table_Pos.size();
	/*int **COST;
	COST=(int **)malloc(N*sizeof(int*));
	for(int i=0;i<N;i++)
		COST[i]=(int*)malloc(M*sizeof(int));
	COST[0][1]=bfs(S_POS,X_POS[0]);
	COST[0][2]=bfs(S_POS,X_POS[1]);
	COST[0][3]=bfs(S_POS,X_POS[2]);
	COST[0][4]=bfs(S_POS,X_POS[3]);
	COST[0][5]=bfs(S_POS,G_POS);
	COST[1][2]=bfs(X_POS[0],X_POS[1]);
	COST[1][3]=bfs(X_POS[0],X_POS[2]);
	COST[1][4]=bfs(X_POS[0],X_POS[3]);
	COST[2][3]=bfs(X_POS[1],X_POS[2]);
	COST[2][4]=bfs(X_POS[1],X_POS[3]);
	COST[3][4]=bfs(X_POS[2],X_POS[3]);
	for(int i=1;i<TOTAL-1;i++){
		COST[i][5]=bfs(X_POS[i-1],G_POS);
	}
	for (int i = 0; i < TOTAL; i++) {
		for (int j = 0; j < TOTAL; j++) {
			if (i==j)
			{
				COST[i][j] = 0;
			}
			COST[j][i] = COST[i][j];
		}
	}*/
	

	//COST[TOTAL-1][0]=0;
	vector<vector<int>> cost(TOTAL);
	for(int i=0;i<S_POS.size();i++){
		cost[0].push_back(bfs(S_POS,X_POS[i]));	
	}
	cost[1]={bfs(S_POS,X_POS[0]),0,bfs(X_POS[0],X_POS[1]),bfs(X_POS[0],X_POS[2]),bfs(X_POS[0],X_POS[3])};
	cost[2]={bfs(S_POS,X_POS[1]),bfs(X_POS[0],X_POS[1]),0,bfs(X_POS[1],X_POS[2]),bfs(X_POS[1],X_POS[3])};
	cost[3]={bfs(S_POS,X_POS[2]),bfs(X_POS[0],X_POS[2]),bfs(X_POS[1],X_POS[2]),0,bfs(X_POS[2],X_POS[3])};
	cost[4]={bfs(S_POS,X_POS[3]),bfs(X_POS[0],X_POS[3]),bfs(X_POS[1],X_POS[3]),bfs(X_POS[2],X_POS[3]),0};
	cost[5]={bfs(S_POS,G_POS),bfs(X_POS[0],G_POS),bfs(X_POS[1],G_POS),bfs(X_POS[2],G_POS),bfs(X_POS[3],G_POS),0};
	for(int i=1;i<TOTAL-1;i++){
		cost[i].push_back(bfs(X_POS[i-1],G_POS));
	}
	cost[0].push_back(bfs(S_POS,G_POS));
	//print the neighborhood matrix table
	cout<<"-------邻接矩阵表为---------"<<endl;
	cout<<cost[0][3]<<endl;
	for(int i=0;i<cost.size();i++){
		cout<<cost[i].size()<<endl;
		/*for(int j=0;j<cost[0].size();j++){
			cout<<cost[i][j]<<endl;		
		}*/
	}
	/*for (int i = 0; i < TOTAL; i++) {
		for (int j = 0; j < TOTAL; j++) {
			cout << setw(3) << COST[i][j];
		}
		cout << endl;
	}*/
	
	return cost;
}



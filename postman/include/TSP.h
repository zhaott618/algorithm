//#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

const int INF = 0x3f3f3f3f;
#define sqr(x) ((x)*(x))


class tsp{
private:
	string file_name;

	int N;
	int init_point;
	int **dp; 
	int **dis;
	int ans;

	struct vertex {
		int x, y; 
		int id; 
		int input(FILE *fp) {
			return fscanf(fp, "%d %lf %lf", &id, &x, &y);
		}
	}*node;

	void io() { 
		printf("input file_name\n");
		cin >> file_name;
		FILE *fp = fopen(file_name.c_str(), "r");
		fscanf(fp, "%d", &N);
		node = new vertex[N + 5];
		dis = new int*[N + 5];
	
		for (int i = 0; i < N; i++) {
			dis[i] = new int[N];
			for (int j = 0; j < N; j++)
				fscanf(fp, "%lf", &dis[i][j]);
		
		}
		fclose(fp);
		return;
	}

	void init() { 
		dp = new int*[(1 << N) + 5];
		for (int i = 0; i < (1 << N); i++) {
			dp[i] = new int[N + 5];
			for (int j = 0; j < N; j++)
				dp[i][j] = INF;
		} 
		ans = INF;
		return;
	}

	int solve() {
		int M = (1 << N);

		dp[1][0] = 0;

		for (int i = 1; i < M; i++) {

			for (int j = 1; j < N; j++) {

				if (i & (1 << j)) continue;

				if (!(i & 1)) continue;

				for (int k = 0; k < N; k++) {

					if (i & (1 << k)) {

						dp[(1 << j) | i][j] = dp[(1 << j) | i][j]>(dp[i][k] + dis[k][j])? (dp[i][k] + dis[k][j]): dp[(1 << j) | i][j]; 
					} 
				}
			}
		}
		for (int i = 0; i < N; i++)
			ans = (dp[M - 1][i] + dis[i][0])>ans?ans: (dp[M - 1][i] + dis[i][0]);
		return ans;
	}

public:
	int TSP(vector<vector<int>>,int);

};


int tsp::TSP(vector<vector<int>> cost,int N) {
	for(int i=0;i<cost.size();i++){
		for(int j=0;j<cost[0].size();j++){
			dis[i][j]=cost[i][j];
		}	
	}
	init();
	string tmp = file_name + ".sol";
	FILE *fp = fopen(tmp.c_str(), "w");
	fprintf(fp, "%.2lf\n", solve());
	delete[] dp;
	delete[] node;
	delete[] dis;
	fclose(fp);
	return ans;
}


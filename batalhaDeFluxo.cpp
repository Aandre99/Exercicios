#include <iostream> 
#include <string.h> 
#include <vector>
#include <stdlib.h>
#include <utility>
#include <limits.h>

#define MAX(x,y) (x > y) ? (x):(y)

using namespace std; 

int* visited;
vector<pair<int,pair<int,int>>> components;
typedef vector<int> vi;
typedef vector<vi> Adj;

int cont_pd = 0, cont_prism = 0, money_comp, T=0;
int Memo[10000][10000];

void dfs(Adj g, int u, int size_pd, int* money_pd, int* money_prism){

	int i;

	if(u < size_pd){
		money_comp += money_pd[u];
		cont_pd+=1;
	}
	else{
		money_comp += money_prism[u-2];
		cont_prism+=1;
	}

	visited[u] = 1;
	
	for (i = 0; i < g[u].size(); i++)
	{
		if(!visited[g[u][i]]){
			dfs(g,g[u][i],size_pd,money_pd,money_prism);
		}
	}
}

void m(int money){

	int i,j;

	for(i=0;i<components.size();++i)
	{
		for(j=0;j<money+1;j++){
			cout << Memo[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
int dp(int money, int i, int p){
	
	if(i == components.size()){
		return 0;
	}
	if(Memo[i][money] != -1){
		cout << "USando dp..." << endl;
		return Memo[i][money];
	}
	else{
		if(components[i].first > money){
			Memo[i][money] = dp(money,i+1,p);
		}
		else{
			if(p)
				Memo[i][money] = MAX(components[i].second.second + dp(money-components[i].first,i+1,p),dp(money,i+1,p));
			else
				Memo[i][money] = MAX(components[i].second.first + dp(money-components[i].first,i+1,p),dp(money,i+1,p));
		}
	}
	return Memo[i][money];
}
int main() 
{ 
	Adj g;
	int n_pd, n_prism, n, money, i, j;
	cin >> n_pd >> n_prism >> n >> money;

	int price_pd[n_pd], price_prism[n_prism];
	
	g.resize(n_pd+n_prism);
	visited = (int*)calloc(n_pd+n_prism,sizeof(int));

	for (i = 0; i < n_pd; i++){
		cin >> price_pd[i];
	}
	for (i = 0; i < n_prism; i++){
		cin >> price_prism[i];
	}
	
	int u, v;

	for (i = 0; i < n; i++){
		cin >> u >> v;
		--u;
		--v;

		g[u].push_back(v+n_pd);
		g[v+n_pd].push_back(u);
	}
	for (i = 0; i < (n_pd+n_prism); i++)
	{
		money_comp = 0;
		cont_prism = 0;
		cont_pd = 0;

		if(visited[i] != 1){
			dfs(g,i,n_pd,price_pd,price_prism);
			components.push_back(make_pair(money_comp, make_pair(cont_prism,cont_pd)));
		}
	}
	
	memset(Memo,-1,sizeof(Memo));
	cout << dp(money,0,0);

	return 0; 
} 

#include <iostream> 
#include <string.h> 
#include <vector>
#include <stdlib.h>
#include <utility>

#define MAX(x,y) (x > y) ? (x):(y)

using namespace std; 

vector<pair<int,pair<int,int>>> Comp;
typedef vector<int> vi;
typedef vector<vi> Graph;

int* price_suborn = NULL;
int* visited = NULL;
int pd_cont = 0, prism_cont = 0, value_component = 0;

void dfs(Graph graph, int size_pd, int u){

	int i;
	visited[u] = 1;

	value_component += price_suborn[u-1];

	if(u <= size_pd){
		pd_cont+=1;
	}else{
		prism_cont+=1;
	}
	
	for (i = 0; i < graph[u].size(); i++)
	{
		if(!visited[graph[u][i]]){
			dfs(graph,size_pd,graph[u][i]);
		}
	}
}
int dp(int money, int i, int p, int Memo[][10001])
{
	cout << money << i << endl;
	if(i == Comp.size() || money == 0){
		Memo[i][money] = 0;
	}
	else if(Memo[i][money] != -1){
		return Memo[i][money];
	}
	else if(Comp[i].first > money){
		Memo[i][money] = dp(money,i+1,p,Memo);
	}else{

		if(p){
			Memo[i][money] = MAX(Comp[i].second.second - Comp[i].second.first + 
			dp(money - Comp[i].first,i+1,p,Memo),dp(money,i+1,p,Memo));
		}else{

			Memo[i][money] = MAX(Comp[i].second.first - Comp[i].second.second + 
			dp(money - Comp[i].first,i+1,p,Memo),dp(money,i+1,p,Memo));
		}
	}

	return Memo[i][money];
}
int main() 
{ 
	int politics_PD, politics_PRISM, number_discontent, initial_money;
	int size_graph = 0, politic_pd, politic_prism,i,j;

	cin >> politics_PD >> politics_PRISM >> number_discontent >> initial_money;

	size_graph = politics_PRISM + politics_PD + 1;


	visited = (int*)calloc(size_graph,sizeof(int));
	price_suborn = (int*)calloc(size_graph-1,sizeof(int));
	Graph graph_component(size_graph);

	for (i = 0; i < politics_PRISM + politics_PD;++i){
		cin >> price_suborn[i];
	}

	for (i = 0; i < number_discontent ; ++i)
	{
		cin >> politic_pd >> politic_prism;
		graph_component[politic_pd].push_back(politic_prism + politics_PD);
		graph_component[politic_prism + politics_PD].push_back(politic_pd);	
	}

	for (i = 1; i < graph_component.size() ; ++i)
	{
		pd_cont = prism_cont = value_component = 0;
		if(!visited[i]){
			dfs(graph_component,politics_PD,i);
			Comp.push_back(make_pair(value_component,make_pair(pd_cont,prism_cont)));
		}
	}

	int Memo[Comp.size()][10001];
	memset(Memo,-1,sizeof(Memo));

	cout << Comp.size() << initial_money << endl;
	int answer = dp(initial_money,0,1,Memo);
	cout << answer+politics_PD;
	memset(Memo,-1,sizeof(Memo));
	answer = dp(initial_money,0,0,Memo);
	cout << " " << answer+politics_PRISM;

	for (i=0;i<Comp.size();++i){
		printf("%d %d %d\n", Comp[i].first, Comp[i].second.first,Comp[i].second.second);
	}

	cout << Comp.size();
	return 0;
} 
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <limits.h>

#define Min(x,y) (x < y) ? (x):(y)

using namespace std;

typedef struct aresta{
	int destino, reversa,fluxo;
}Aresta;

typedef vector<Aresta> Arestas;
vector<Arestas> Grafo;

void mostrarGrafo(){

	int i;
	for (i = 0; i < Grafo.size(); i++)
	{
		Arestas :: iterator it = Grafo[i].begin();

		cout << '[' << i << ']';
		while(it != Grafo[i].end()){
			cout << '{' << (*it).destino << ','<<(*it).fluxo << ','<< (*it).reversa << '}' << "->";
			it = it + 1;
		}
		cout << endl;
	}
	
}
void AdicionarAresta(int v1, int v2, int cap){

	Grafo[v1].push_back(Aresta{v2,(int) Grafo[v2].size(),cap});
	Grafo[v2].push_back(Aresta{v1,(int) Grafo[v1].size()-1,0});
}
bool BFS(int s, int t, int* pais, int* pos_filhos){

	int vis[Grafo.size()];
	memset(vis,0,sizeof(vis));
	
	pais[s] = -1;
	pos_filhos[s] = -1;
	vis[s] = 1;
	queue<int> q;

	q.push(s);

	while(!q.empty()){

		int u = q.front();
		q.pop();

		if(u == t)break;

		Arestas :: iterator it = Grafo[u].begin();
		int i = 0;

		while(it != Grafo[u].end()){

			if(!vis[(*it).destino] && (*it).fluxo > 0){
	
				vis[(*it).destino] = 1;
				q.push((*it).destino);

				pais[(*it).destino] = u;
				pos_filhos[(*it).destino] = i;
			}
			++i;
			it = it + 1;
		}
	}
	return (vis[t]) ? true : false;
}
int Ford_Fulkerson(int s, int t){

	int n = Grafo.size(),i;

	int pai[n], pos_filhos[n];

	memset(pai,0,sizeof(pai));
	memset(pos_filhos,0,sizeof(pos_filhos));

	int max_flow = 0,u = 0,v = 0;

	while(BFS(s,t,pai,pos_filhos)){

		int flow = INT_MAX;
		
		for (i=t;i!=-1;i = pai[i]){
			u = pai[i];
			v = pos_filhos[i];
			if(u == -1) break;
			flow = Min(flow,Grafo[u][v].fluxo);
		}
		
		for (i = t; i != -1; i = pai[i])
		{
			u = pai[i];
			v = pos_filhos[i];
			if(u ==-1) break;

			Grafo[u][v].fluxo -= flow;
			Grafo[i][Grafo[u][v].reversa].fluxo += flow;
		}
		
		if(flow == 0)break;
		max_flow += flow;

		memset(pai,0,sizeof(pai));
		memset(pos_filhos,0,sizeof(pos_filhos));

	}
	return max_flow;
}
int main()
{
	int n, n_test, n_words, i, j, k;
	char word[1000];
	cin >> n;
	
	Grafo.resize(n+26);

	for (i = 0; i < n; ++j){

		scanf("%d", &n_test);
		cout << n_test;

		for (j = 0; j < n_test; ++j)
		{
			scanf("%d", &n_words);
			cout << n_words;
			for (k = 0; k < n_words; ++k)
			{
				scanf("%s", word);
				cout << word;
			}
			break;
		}
		
	}
	

	return 0;
}

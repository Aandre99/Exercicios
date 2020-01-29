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

	int i, j;

	for(i=0;i<Grafo.size();++i){
		cout << '['<<i<<']';
		for(j=0;j<Grafo[i].size();++j){
			cout << "{" << Grafo[i][j].destino << " "<<Grafo[i][j].fluxo << " } ->";
		}
		cout << endl;
	}
}
void AdicionarAresta(int v1, int v2, int cap){

	Grafo[v1].push_back(Aresta{v2,(int) Grafo[v2].size(),cap});
	Grafo[v2].push_back(Aresta{v1,(int) Grafo[v1].size()-1,0});
}

bool BFS(int s, int t, int* pais, int* pos_pais){

	int vis[Grafo.size()], v;
	memset(vis,0,sizeof(vis));
	
	pais[s] = -1;
	vis[s] = 1;
	queue<int> q;

	q.push(s);
	while(!q.empty()){

		int u = q.front(), dest=0,i=0;
		q.pop();

		for (v = 0; v < Grafo[u].size(); ++v)
		{
			dest = Grafo[u][v].destino;
			
			if(!vis[dest] && Grafo[u][v].fluxo > 0){

				cout << "u = " << u << "dest = " << dest <<" -> ";
				q.push(dest);
				pais[dest] = u;
				pos_pais[dest] = i;
				vis[dest] = 1;
			}
			++i;
		}
		cout << endl;
	}
	return (vis[t]) ? true : false;
}
int Edmonds_Karp(int s, int t){

	int turn = 0;

	int n = Grafo.size(), v,k,cont=0;
	int pai[n],pos_pai[n];
	memset(pai,-1,sizeof(pai));
	memset(pos_pai,-1,sizeof(pos_pai));

	int max_flow = 0,u = 0;
	
	while(BFS(s,t,pai,pos_pai)){

		turn += 1;
		int flow = INT_MAX;

		for (k = t ; k != 0; k = pai[k]){
			u = pai[k];
			v = pos_pai[k];
			flow = Min(flow,Grafo[u][v].fluxo);
		}

		for (k = t; k != 0; k = pai[k])
		{
			u = pai[k];
			v = pos_pai[k];

			Grafo[u][v].fluxo -= flow;
			Grafo[k][Grafo[u][v].reversa].fluxo += flow;
		}
		if(flow == 0)break;
		max_flow += flow;

		memset(pai,-1,sizeof(pai));
	}

	cout << max_flow;
	return max_flow;
}
int main()
{
	int n, i, j,health, power, n_cards, card;
	cin >> n;

	Grafo.resize(n*2+2);
	
	for (i = 0; i < (2*n); i++)
	{
		cin >> health >> power >> n_cards;

		for (j = 0; j < n_cards; ++j)
		{
			cin >> card;
			if(i+1 < n+1){
				AdicionarAresta(0,i+1,power);
				AdicionarAresta(i+1,card+1+n,health);
				AdicionarAresta(i+2,2*n+1,health);
			}else{
				AdicionarAresta(n*2+1,i+1,power);
				AdicionarAresta(card+1,0,health);
				AdicionarAresta(i+1,card+1,health);
			}
		}
	}

	mostrarGrafo();

	int entity  = Edmonds_Karp(0,n*2+1);
	int x ;//= Edmonds_Karp(n*2+1,0);

	if(entity < x){
		cout << "Entity wins in " << entity << " turns" << endl;
	}else{
		cout << "X wins in " << x << " turns" << endl;
	}
	return 0;
}

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>

using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vi;
typedef vector<vi> Adj;

bool Bellman_Ford(Adj graph, int edges, int source){

  int distance[graph.size()], i, j;
  for (i = 0; i < graph.size(); i++){
    distance[i] = INT_MAX;
  }
  distance[source] = 0;

  for (i = 0; i < graph.size()-1; i++)
  {
      for (j = 0; j < graph.size(); j++)
      {
          vi :: iterator it = graph[j].begin();

          while(it != graph[j].end()){

            if(distance[j] != INT_MAX && distance[j] + (*it).second < distance[(*it).first]){
              distance[(*it).first] = distance[j] + (*it).second;
            }
            it = it + 1;
          }
      }
  }
  
  for (j = 0; j < graph.size(); j++)
    {
        vi :: iterator it = graph[j].begin();
        while(it != graph[j].end()){

          if(distance[j] != INT_MAX && distance[j] + (*it).second < distance[(*it).first]){
            return true;
          }
          it = it + 1;
        }
    }
    return false;
}
void clear_Graph(Adj g){

    int i;
    for (i = 0; i < g.size(); ++i){
        g[i].clear();
    }
}
int main(){

  Adj Graph;
  int n, v1, v2, width, i, size, edges, j, source;

  cin >> n;

  for (i = 0; i < n; i++){
    
    cin >> size >> edges;

    Graph.resize(size);
    clear_Graph(Graph);

    for (j = 0; j < edges; j++)
    {
      cin >> v1 >> v2 >> width;
      v1;
      v2;
      Graph[v1].push_back(ii(v2,width));
    }

    if(Bellman_Ford(Graph,edges,v1)){
      cout << "possible";
    }else{
      cout << "not possible";
    }
    cout << endl;
    Graph.clear();
  }

  Graph.
  
  return 0;
}
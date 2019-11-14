#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vii;

void mostrarGrafo(vii Grafo, int n){

    int i;

    for (i = 0; i < n; i++){

        vi :: iterator it = Grafo[i].begin();
        cout << "[" << i << "]";
        while(it != Grafo[i].end()){
            cout << (*it) << "->";
            it = it + 1;
        }  
        cout << endl;
    }
}

void mostrarFila(priority_queue<ii> filaTempos){

        while(!filaTempos.empty()){
        cout << filaTempos.top().first << " "<<filaTempos.top().second << endl;
        filaTempos.pop();
    }
    cout << endl;
}
int DesmontarBoneco(vii Grafo, priority_queue<ii> FilaPrio, int* tempoApagar, int* temposPeca, int n_pecas){

    int cont = n_pecas,tempoTotal = 0;
    int indiceAtual = 0, tempoAtualApagar = 0;

    while(cont > 0){

        cout << cont;
        mostrarFila(FilaPrio);

        indiceAtual = FilaPrio.top().first;
        tempoAtualApagar = FilaPrio.top().second;
        tempoTotal += FilaPrio.top().second;
        cont-= 1;

        vi :: iterator it = Grafo[indiceAtual].begin();

        while(it != Grafo[indiceAtual].end()){
            tempoApagar[*it]-= tempoAtualApagar;
            FilaPrio.push(ii(*it,tempoApagar[*it]));
        }
        tempoApagar[indiceAtual] = 0;
    }

    return tempoTotal;
}
int main(){

    priority_queue<ii,vector<ii>,greater<ii>> filaTempos;

    int n, m, t, x, y, i;

    cin >> n >> m;
    cout << n << m;
    cout << endl;
    vii Grafo(n);
    Grafo.resize(n);
    
    int temposFixos[n];
    int temposApagar[n];

    for (i = 0; i < n; i++){

        temposApagar[i] = 0;
        cin >> temposFixos[i];
    }

    for (i = 0; i < m; i++){
        
        scanf("%d%d", &x, &y);

        Grafo[x-1].push_back(y);
        Grafo[y-1].push_back(x);

        temposApagar[x-1] += temposFixos[y-1];
        temposApagar[y-1] += temposFixos[x-1];

    }

    for (i = 0; i < n; i++){
        filaTempos.push(ii(i+1,temposApagar[i]));
    }
    
    mostrarGrafo(Grafo,n);

    cout << DesmontarBoneco(Grafo,filaTempos,temposApagar,temposFixos,n);
    return 0;
}

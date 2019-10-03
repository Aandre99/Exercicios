#include <stdio.h>
#include <stdlib.h>

typedef struct adj_list{
	int value;
	struct adj_list* next;
}Adj_list;

typedef struct graph{
	Adj_list** vertices;
	int *visited;
}Graph;

typedef struct queue{
	Adj_list* Head;
	Adj_list* Tail;
}Queue;
//-------------------------------------------

Adj_list* create_AdjList(int vertex){

	Adj_list* new_AdjList = (Adj_list*)malloc(sizeof(Adj_list));
	new_AdjList->value = vertex;
	new_AdjList->next = NULL;

	return new_AdjList;
}
Graph* createGraph(int size){

	Graph* newGraph = (Graph*)malloc(sizeof(Graph));
	newGraph->vertices = (Adj_list**)malloc(size * sizeof(Adj_list*));
	newGraph->visited = (int*)calloc(size+1,sizeof(int));

	int i;

	for (i = 0; i < size; ++i){
		newGraph->visited[i] = 0;
		newGraph->vertices[i] = (Adj_list*)malloc(sizeof(Adj_list));
		newGraph->vertices[i] = NULL;
	}
	return newGraph;
}

Queue* createQueue(){

	Queue* newQueue = (Queue*)malloc(sizeof(Queue));
	newQueue->Head = NULL;
	newQueue->Tail = NULL;

	return newQueue;
}
//---------------------------------------------

Adj_list* add_List(Adj_list* list, Adj_list* vertex){

	if(list == NULL){
		list = vertex;
	}else{

		Adj_list* Aux = list;

		while(Aux->next != NULL){
			Aux = Aux->next;
		}

		Aux->next = vertex;
	}

	return list;
}
void Enqueue(Queue* queue, int item){

	Adj_list* enqueued = create_AdjList(item);

	if(queue->Head == NULL){
		queue->Head = queue->Tail = enqueued;
	}else{
		queue->Tail->next = enqueued;
	}
		queue->Tail = enqueued;
}
void Add_Edge(Graph* graph, int vertex1, int vertex2){

	if(graph == NULL){
		printf("Error\n");
	}else{

		Adj_list* vertex = create_AdjList(vertex2);
		vertex->next = graph->vertices[vertex1];
		graph->vertices[vertex1] = vertex;
	}
}
//---------------------------------------------
 int Dequeue(Queue* queue){

 	int dequeued = queue->Head->value;
 	Adj_list* Aux = queue->Head;

 	if(queue->Head == queue->Tail){
 		queue->Head = queue->Tail = NULL;
 	}else{
 		queue->Head = Aux->next;
 	}
 	free(Aux);

 	return dequeued;
 } 
int EmptyQueue(Queue* queue){
	return (queue->Head == NULL) ? 1:0;
}
void BFS(Graph* graph, int source){

	int dequeued = 0;
	Queue* queue = createQueue();
	graph->visited[source] = 1;

	Enqueue(queue,source);
	Adj_list* Aux = graph->vertices[source];

	while(!EmptyQueue(queue)){

		dequeued  = Dequeue(queue);
		Aux = graph->vertices[dequeued];

		while(Aux != NULL){

			if(!graph->visited[Aux->value]){

				printf("%d\n", Aux->value);
				graph->visited[Aux->value] = 1;
				Enqueue(queue, Aux->value);
			}
			Aux = Aux->next;
		}
	}
}
int main()
{
	int quantity, vertex1, vertex2, source, i;
	scanf("%d%d", &quantity, &source);

	Graph* graph = createGraph(quantity);

	for(i=0;i<quantity+1;i++){
		graph->visited[i] = 0;
	}

	while(scanf("%d%d", &vertex1, &vertex2) != EOF){
		Add_Edge(graph,vertex1,vertex2);
	}
	printf("%d\n", source);
	BFS(graph,source);

	return 0;
}

void dijkstra(int begin, graph* grafo)
{
  queue* new_queue = create_queue();
  
  adj* aux;
  
  int v, i=0;
  
  grafo->distance[begin] = 0;
  
  enqueue(new_queue, begin, grafo->distance[begin]);
  
  while(!is_empty(new_queue))
  {
  
    v = dequeue(new_queue);
  
    if(!grafo->visited[v])
    {
    
      grafo->visited[v] = 1;
    
      aux = grafo->vertices[v];
    
      while(aux != NULL)
      {
    
        if(grafo->distance[v] + aux->peso < grafo->distance[aux->item])
        {
    
          grafo->distance[aux->item] = grafo->distance[v] + aux->peso;
    
          enqueue(new_queue, aux->item, grafo->distance[aux->item]);
        }
        aux = aux->next; 
      }
    }
  }
}
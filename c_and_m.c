#include <stdio.h>
#include <stdlib.h>

int chamadas = 0;

typedef struct node{

	int c, m, b;
	struct node* child_one;
	struct node* child_two;
	struct node* child_three;
	struct node* child_four;
	struct node* father;
}Node;

void show_state(Node* current){

	if(current != NULL){
		printf("m = %d, c = %d , b = %d\n", current->m,current->c,current->b);
	}else{
		printf("é nulo\n");
	}
}
int already_Created(Node* current_ft, Node* current){
	
	if(current_ft == NULL){
		return 0;
	}else{

		if(current->c == current_ft->c && current->m == current_ft->m){
			return 1;
		}
		return already_Created(current_ft->father, current);
	}
}
Node* create_Node(int c, int m, int b, Node* current){

	if(current != NULL && already_Created(current->father,current)){
		printf("Ja encontrado\n");
		return NULL;
	}
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->c = c;
	new_Node->m = m;
	new_Node->b = b;
	new_Node->father = current;

	return new_Node;
}
Node* operator_M(Node* current){

	if(current->m > 0){
		if(current->m - 1 >= current->c && (3 - current->m) + 1 >=  (3 - current->c)){
			return create_Node(3 - current->c, (3-current->m) + 1,!current->b,current);
		}else{
			return NULL;
		}
	}else
		return NULL;
}
Node* operator_C(Node* current){

	if(current->c > 0){
		
		if(current->m >= (current->c - 1)){
			return create_Node((3 - current->c) + 1, 3 - (current->m),!current->b, current);
		}
	}
	return NULL;
}
Node* operator_CC(Node* current){
	
	if(current->c >= 2){
		
		if((3 - current->m) == 0 ||  (3 - current->m) >= (3-current->c) + 2){
			return create_Node((3 - current->c) + 2, 3 - (current->m),!current->b,current);
		}
		return NULL;
	}else
		return NULL;
}

Node* operator_MM(Node* current){
	
	if(current->m >= 2){
		
		if(((3 - current->m + 2) >= (3 - current->c)) && (current->m - 2 >= current->c)){
			return create_Node((3 - current->c), (3 - current->m) + 2,!current->b,current);
		}
		return NULL;
	}
}

void dfs(Node* Three, int* flag, int c){

	printf("CHA = %d\n", chamadas++);
	if(Three == NULL || *flag){
		return;
	}
	if(Three->c = 3 && Three->m == 3 && Three->b == 1){
		*flag = 1;
		printf("Passou!!!\n");
		return;
	}else{
		Three->child_one = operator_C(Three);
		show_state(Three->child_one);
		Three->child_two = operator_M(Three);		
		show_state(Three->child_two);
		Three->child_three = operator_CC(Three);
		show_state(Three->child_three);
		Three->child_four = operator_MM(Three);
		show_state(Three->child_four);

		dfs(Three->child_one,flag,c+1);
		dfs(Three->child_two,flag,c+1);
		dfs(Three->child_three,flag,c+1);
		dfs(Three->child_four,flag,c+1);
	}
}
void free_Three(Node* Three){

	if(Three != NULL)
	{
		
		free_Three(Three->child_one);
		free_Three(Three->child_two);
		free_Three(Three->child_three);
		free_Three(Three->child_four);

		free(Three);
	}
}
int main(){

	int finded = 0;
	Node* initial_State = create_Node(3,3,0,NULL);

	dfs(initial_State, &finded,0);

	free_Three(initial_State);
	return 0;
}

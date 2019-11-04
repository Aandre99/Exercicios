#include <stdio.h>
#include <stdlib.h>

int chamadas = 0;

typedef struct node{

	int c, m, b;
	struct node* child_one;
	struct node* child_two;
	struct node* child_three;
	struct node* child_four;
    struct node* child_five;
	struct node* father;
}Node;

void show_state(Node* current){

	if(current != NULL){
		printf("m = %d, c = %d , b = %d\n", current->m,current->c,current->b);
	}
}
int already_Created(Node* current_ft, int c, int m){
	
	if(current_ft == NULL){
		return 0;
	}else{

		if(c == current_ft->c && m == current_ft->m){
			return 1;
		}
		return already_Created(current_ft->father, c,m);
	}
}
Node* create_Node(int c, int m, int b, Node* current){

	if(current != NULL){
        if(already_Created(current->father,c,m)){
            return NULL;
        }
	}
	Node* new_Node = (Node*)malloc(sizeof(Node));
    if(new_Node == NULL){
        printf("Sem espaço em memória! :(");
    }
	new_Node->c = c;
	new_Node->m = m;
	new_Node->b = b;
    new_Node->child_one = NULL;
    new_Node->child_two = NULL;
    new_Node->child_three = NULL;
    new_Node->child_four = NULL;
    new_Node->child_five = NULL;
    new_Node->father = current;
	return new_Node;
}
Node* operator_M(Node* current){

    int m_left = current->m;
    int m_right = 3 - m_left;

    int c_left = current->c;
    int c_right = 3 - c_left;

	if(m_left > 0){
		if((m_left - 1 >= c_left ) && (m_right + 1 >=  c_right)){
			return create_Node(c_right,m_right + 1,!current->b,current);
		}else{
			return NULL;
		}
	}else{
		return NULL;
    }
}
Node* operator_C(Node* current){

    int m_left = current->m;
    int m_right = 3 - m_left;

    int c_left = current->c;
    int c_right = 3 - c_left;
    
	if(c_left > 0){
		
		if(m_right == 0 || m_right >= c_right + 1){
			return create_Node(c_right+ 1, m_right,!current->b, current);
		}else{
            return NULL;
        }
	}else{
	    return NULL;
    }
}
Node* operator_CC(Node* current){
	
    int m_left = current->m;
    int m_right = 3 - m_left;

    int c_left = current->c;
    int c_right = 3 - c_left;
    
	if(c_left >= 2){
		
		if((m_right == 0) ||  (m_right >= c_right + 2)){
			return create_Node(c_right + 2,m_right,!current->b,current);
		}else{
		    return NULL;
        }
	}else{
		return NULL;
    }
}

Node* operator_MM(Node* current){
	
    int m_left = current->m;
    int m_right = 3 - m_left;

    int c_left = current->c;
    int c_right = 3 - c_left;
    
	if(m_left >= 2){
		if((m_right + 2 >= c_right) && (m_left - 2 >= c_left)){
			return create_Node((c_right), (m_right) + 2,!current->b,current);
		}
		return NULL;
	}else{
        return NULL;
    }
}
Node* operator_MC(Node* current){

    int m_left = current->m;
    int m_right = 3 - m_left;

    int c_left = current->c;
    int c_right = 3 - c_left;

    if(m_left >= 1 && c_left >= 1){

        if(c_right - m_right == 0 || m_right + 1 >= c_right + 1){
            return create_Node(c_right + 1, m_right + 1, !current->b, current);
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

void  dfs(Node* Three, int* flag){

	if(Three == NULL || *flag){
		return;
	}
	if(Three->c == 3 && Three->m == 3 && Three->b == 1){
		*flag = 1;
		printf("Passou!!!\n");
		return;
	}else{
        
        printf("Estado Atual: \n");
        show_state(Three);
        printf("Seus filhos: \n\n");
		Three->child_one = operator_C(Three);
        show_state(Three->child_one);
		Three->child_two = operator_M(Three);
        show_state(Three->child_two);		
		Three->child_three = operator_CC(Three);
        show_state(Three->child_three);
		Three->child_four = operator_MM(Three);
        show_state(Three->child_four);
        Three->child_five  = operator_MC(Three);
        show_state(Three->child_five);
		
        dfs(Three->child_one,flag);
		dfs(Three->child_two,flag);
		dfs(Three->child_three,flag);
		dfs(Three->child_four,flag);
        dfs(Three->child_five,flag);

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
	dfs(initial_State, &finded);
	free_Three(initial_State);
    return 0;
}

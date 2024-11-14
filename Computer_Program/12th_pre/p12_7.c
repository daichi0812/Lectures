/*
 *p12_7.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int num1;
	int num2;
} my_data;

typedef struct node{
	my_data data;
	struct node *next;
}list_node;

list_node *new_node(my_data d);
list_node *push_node(list_node *root, my_data d);
list_node *pop_node(list_node *root, my_data *d);
void print_data(my_data d);
void print_list(list_node *root);

int main(int argc, char **argv){
	list_node *root, *tail;
	my_data d[5]={{1, 10},{2, 20}, {3, 30}, {4, 40}, {5, 50}};
	my_data popped_data;
	int i;
	
	root=NULL;
	for(i=0; i<5; i++){
		root=push_node(root, d[i]);
	}
	print_list(root);
	while(root != NULL){
		root = pop_node(root, &popped_data); 	//手順 3
		printf("List after popping");
		print_data(popped_data);
		print_list(root);
	}
	
	return 0;
}

list_node *new_node(my_data d){
	list_node *new_p;
	
	if((new_p=(list_node *)calloc(1, sizeof(list_node)))==NULL){
		printf("Memory allocation error!\n");
		exit(1);
	}
	new_p ->data = d;
	new_p -> next = NULL;
	return new_p;
}

list_node *push_node(list_node *root, my_data d){
	list_node *new_p = new_node(d);		//手順 1 と 2
	new_p->next=root;		//手順 3
	return new_p;
}

list_node *pop_node(list_node *root, my_data *d){
	list_node *tmp;
	
	tmp=NULL;	//リストがカラの時のために初期化
	if(root!=NULL){
		*d=root->data;	//削除するノードのデータ値の取得
		tmp=root->next;	//手順　1
		free(root);		//手順 2
	}
	return 0;
}

void print_data(my_data d){
	printf("(%d, %d)\n", d.num1, d.num2);
}

void print_list(list_node *root){
	list_node *np;
	
	for(np=root; np!=NULL; np=np->next){
		print_data(np->data);
	}
}

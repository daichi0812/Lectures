/*
 *p12_5.c 15822108 情報テクノロジー 堀田大智
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
void print_data(my_data d);

int main(int argc, char **argv){
	list_node *root;
	my_data d={1, 10};
	
	root=new_node(d);
	print_data(root->data);
	
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

void print_data(my_data d){
	printf("(%d, %d)\n", d.num1, d.num2);
}

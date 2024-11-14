/*
 *ex13_3.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

typedef struct stack {
    char *string;
    struct stack *next;
} stack_node;

void remove_nl(char *s);
stack_node *get_strings(char *buf);
stack_node *new_node(char *s);
stack_node *push_node(stack_node *root, char *s);
void print_stack(stack_node *np);


int main() {
    char buf[BUFSIZE];
    stack_node *root;
	
    printf("カンマで区切った文字列を入力してください：");
    fgets(buf, sizeof(buf), stdin);
    remove_nl(buf);
    root = get_strings(buf);
    print_stack(root);

    return 0;
}

void remove_nl(char *s){
    int i;

    for(i=0; i<1024||s[i]=='\0'; i++){
        if(s[i]==10){
            s[i]='\0';
            break;
        }
    }
}

stack_node *new_node(char *s){
	stack_node *new_p;
	
	if((new_p=(stack_node *)calloc(1, sizeof(stack_node)))==NULL){
		printf("Memory allocation error!\n");
		exit(1);
	}
	new_p ->data = d;
	new_p -> next = NULL;
	return new_p;
}

stack_node *push_node(stack_node *root, char *s){
	list_node *new_p = new_node(d);		
	new_p->next=root;		
	return new_p;
}

void print_list(list_node *root){
	list_node *np;
	
	for(np=root; np!=NULL; np=np->next){
		print_data(np->data);
	}
}
/*
 *ex12_3.c 15822108 情報テクノロジー 堀田大智
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
list_node *append_node(list_node *tail, my_data d);
list_node *remove_node(list_node *root, list_node *tail, my_data *d);
void print_data(my_data d);
void print_list(list_node *root);

int main(int argc, char **argv){
	list_node *root, *tail;
	my_data d[5]={{1, 10},{2, 20}, {3, 30}, {4, 40}, {5, 50}};
	my_data removed_data;
	int i;
	
	root=tail=NULL;
	for(i=0; i<5; i++){
		//root=push_node(root, d[i]);
		tail=append_node(tail, d[i]); 	//手順5
		if(root==NULL){
			root=tail;
		}
	}
	print_list(root);
	while(root != NULL){
		/*
		root = pop_node(root, &popped_data); 	
		printf("List after popping");
		print_data(popped_data);
		*/
		tail = remove_node(root, tail, &removed_data);
		if(tail == NULL){
			root = NULL;
		}
		printf("LIst after removing");
		print_data(removed_data);
		print_list(root);
	}
	
	return 0;
}

//新しい箱(構造体)の領域確保
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

//古い箱から新しい箱へ移動する
//今回は使わない
list_node *push_node(list_node *root, my_data d){
	list_node *new_p = new_node(d);		
	new_p->next=root;		
	return new_p;
}

//今回は使わない
list_node *pop_node(list_node *root, my_data *d){
	list_node *tmp;
	
	tmp=NULL;	
	if(root!=NULL){
		*d=root->data;	
		tmp=root->next;	
		free(root);		
	}
	return tmp;
}

//古い箱から新しい箱へ移動する
//順番は尻尾から
list_node *append_node(list_node *tail, my_data d){
	list_node *new_p=new_node(d);
	if(tail!=NULL){
		tail->next=new_p;
	}
	return new_p;
}

//今回使う
list_node *remove_node(list_node *root, list_node *tail, my_data *d){
	list_node *tmp;
	
	tmp=NULL;
	if(root!=NULL){
		*d=tail->data;
		tmp=tail->next;
		free(tail);
	}
	return tmp;
}

//除外するデータを表示
void print_data(my_data d){
	printf("(%d, %d)\n", d.num1, d.num2);
}

//リストを表示
void print_list(list_node *root){
	list_node *np;
	
	for(np=root; np!=NULL; np=np->next){
		print_data(np->data);
	}
}
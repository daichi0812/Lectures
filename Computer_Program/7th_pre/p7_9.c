/*
 *p7_9.c 構造体配列の利用　15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
 
typedef struct{
	char name[30];
	int age;
	int grade;
	double gpa;
} personal_data;

void print_data(personal_data d[], int n);

int main(){
	personal_data data[]={{"Aoyama Taro", 20, 2, 3.0},
						  {"Aoyama Hanako", 19, 2, 3.2},
	{"Aoyama Jiro", 22, 3, 1.2}};
	
	print_data(data, 3);
	
	return 0;
}

void print_data(personal_data d[], int n){
	int i;
	
	for(i=0; i<n; i++){
		printf("%d人目\n", i+1);
		printf("氏名 : %s\n", d[i].name);
		printf("年齢 : %d\n", d[i].age);
		printf("学年 : %d\n", d[i].grade);
		printf("GPA : %.2f\n", d[i].gpa);
	}
}
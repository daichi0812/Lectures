/*
 *p7_8.c typedefを使った構造体の定義(タグ名の省略) 158220108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

typedef struct{
	char name[30];
	int age;
	int grade; 
	double gpa;
} personal_data;

void print_data(personal_data d);

int main(){
	personal_data data={"Aoyama Taro", 20, 2, 3.0};
	
	print_data(data);
	return 0;
}

void print_data(personal_data d){
	printf("氏名 : %s\n", d.name);
	printf("年齢 : %d\n", d.age);
	printf("学年 : %d\n", d.grade);
	printf("GPA : %.2f\n", d.gpa);
}
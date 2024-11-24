/*
 *p7_4.c 構造体を引数にとる関数　15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

struct personal_data{
	char name[30];
	int age;
	int grade;
	double gpa;
};

void print_data(struct personal_data d);

int main(){
	struct personal_data data={"Aoyama Taro", 20, 2, 3.0};
	
	print_data(data);
	return 0;
}

void print_data(struct personal_data d){
	printf("氏名 : %s\n", d.name);
	printf("年齢 : %d\n", d.age);
	printf("学年 : %d\n", d.grade);
	printf("GPA : %.2f\n", d.gpa);
}
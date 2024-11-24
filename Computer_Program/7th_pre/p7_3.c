/*
 *p7_3.c 構造多変数間の代入　15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

struct personal_data{
	char name[30];
	int age;
	int grade;
	double gpa;
};

int main(){
	struct personal_data data={"Aoyama Taro", 20, 2, 3.0};
	struct personal_data data2;
	
	data2=data;	//構造体変数の代入
	printf("氏名 : %s\n", data2.name);
	printf("年齢 : %d\n", data2.age);
	printf("学年 : %d\n", data2.grade);
	printf("GPA : %.2f\n", data2.gpa);
	
	return 0; 
}
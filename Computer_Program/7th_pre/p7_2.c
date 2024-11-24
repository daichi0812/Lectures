/*
 *p7_2.c 構造体変数の初期値設定　15822108 情報テクノロジー 堀田大智
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
	
	printf("氏名 : %s\n", data.name);
	printf("年齢 : %d\n", data.age);
	printf("学年 : %d\n", data.grade);
	printf("GPA : %.2f\n", data.gpa);
	
	return 0;
}
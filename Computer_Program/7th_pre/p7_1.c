/*
 *p7_1.c 構造体の利用　15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 256

struct personal_data{	//構造体の定義
	char name[30];
	int age;
	int grade;
	double gpa;
};

int main(){
	struct personal_data data;	//構造体変数の宣言
	char buf[BUFSIZE];
	
	printf("名前を入力してください(最大29文字) : ");
	gets(data.name);
	printf("年齢を入力してください: ");
	gets(buf);
	data.age=atoi(buf);
	printf("学年を入力してください : ");
	gets(buf);
	data.grade=atoi(buf);
	printf("GPAを入力してください : ");
	gets(buf);
	data.gpa=atof(buf);
	
	printf("氏名 : %s\n", data.name);
	printf("年齢 : %d\n", data.age);
	printf("学年 : %d\n", data.grade);
	printf("GPA :  %.2f\n", data.gpa);
	
	return 0;
}
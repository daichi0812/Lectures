/*
 *ex7_1.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNUM 10
#define BUFSIZE 256

typedef struct{
	char name[30];
	int age;
	int grade;
	double gpa;
	
}personal_data;

void print_data(personal_data d[]);
personal_data get_data(void);

int main(){
	int i;
	personal_data data[MAXNUM];
	
	for(i=0; i<MAXNUM; i++){
		data[i]=get_data();
		if(!strcmp(data[i].name, "end")) break;
	}
	
	print_data(data);
	
	return 0;
}

void print_data(personal_data d[]){
	int i;
	
	for(i=0; i<MAXNUM; i++){
		
		if(!strcmp(d[i].name, "end")){
		return 0;
		}
		
		printf("%d人目\n", i+1);
		printf("氏名 : %s\n", d[i].name);
		printf("年齢 : %d\n", d[i].age);
		printf("学年 : %d\n", d[i].grade);
		printf("GPA :  %.2f\n", d[i].gpa);
	}
	
	return 0;
}

personal_data get_data(void){
	int i;
	personal_data d;
	char buf[BUFSIZE];
	
	printf("名前を入力してください(最大29文字, \"end\"で入力終了) : ");
	gets(d.name);
	
	if(!strcmp(d.name, "end")){
		return d;
	}
	
	printf("年齢を入力してください : ");
	gets(buf);
	d.age=atoi(buf);
	printf("学年を入力してください : ");
	gets(buf);
	d.grade=atoi(buf);
	printf("GPAを入力してください : ");
	gets(buf);
	d.gpa=atoi(buf);
	
	return d;
}
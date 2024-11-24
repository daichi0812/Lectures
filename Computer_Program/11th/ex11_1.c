/*
 *ex11_1.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

#define MAXLENGH 20 //名前を表す文字列の最大長(終端文字を含む)

char **name; //名前を保存する2次元配列
int *id; 	 //ID を保存する1次元配列

int read_data(char *fname);

int main(){
	int i, num;
	
	num=read_data("data_ex11_1.txt");
	
	//読み込んだデータの確認
	for(i=0; i<num; i++){
		printf("%d %s\n", id[i], name[i]);
	}
		
	return 0;
}

int read_data(char *fname){
	int i, n;
	FILE *fin;
	
	//ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		exit(1);
	}
	
	//人数の入力
	fscanf(fin, "%d", &n);
	
	//id の領域確保
	id=(int *)malloc(n*sizeof(int));
	if(id==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	
	//name　の領域確保
	name=(char **)malloc(n*sizeof(char *));
	if(name==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	for(i=0; i<n; i++){
		name[i]=(char *)malloc(MAXLENGH*sizeof(char));
		if(name[i]==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	//学生番号と名前の入力
	for(i=0; i<n; i++){
		fscanf(fin, "%d,%s", &id[i], name[i]);
	}
	
	return n;
}
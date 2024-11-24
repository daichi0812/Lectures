/*
 *ex11_2.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256     // 文字列読み込み用の配列のサイズ
#define MAXLENGTH 20    // 名前を表す文字列の最大長（終端文字を含む）

char **name;    // 名前を保存する2次元配列
int *id;        // ID を保存する1次元配列

int read_data(char *fname);

int main() {
    int i, num;

    num = read_data("data_ex11_2.txt");

    // 読み込んだデータの確認
    for (i = 0; i < num; i++)
        printf("%d: %s\n", id[i], name[i]);

    return 0;
}

int read_data(char *fname){
	int i, j, k, n, t;
	j=0;
	char c;
	FILE *fin;
	
	//ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		exit(1);
	}
	
	//人数の入力
	char n2[BUFSIZE];
	fgets(n2, BUFSIZE, fin);
	n=atoi(n2);
	
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
		name[i]=(char *)malloc(MAXLENGTH*sizeof(char));
		if(name[i]==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	//学生番号と名前の入力
	char buf[5][BUFSIZE];
	char num[5][BUFSIZE];
	char user[5][BUFSIZE];
	
	for(i=0; i<5; i++){
		j=0;
	
		fgets(buf[i], BUFSIZE, fin);
		
		while(1){
			if(buf[i][j]==','){
				for(t=0; t<j; t++){
					num[i][t]=buf[i][t];
				}
				id[i]=atoi(num[i]);
				break;
			}else{
				j++;
			}
		}
		
		while(1){
			if(buf[i][j]=='"'){
				for(t=j+1, k=0; t<BUFSIZE && buf[i][t]!='"'; t++, k++){
					name[i][k]=buf[i][t];
				}
				break;
			}else{
				j++;
			}
		}
	}
	
	return n;
}
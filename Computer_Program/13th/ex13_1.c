/*
 *ex13_1.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

//行列の内容を読み取る関数
int **read_matrix(char *fname, int *s);
//コマンドライン引数を正確に機能させる関数
void check_argnum(int min, int max, int arg_num, char *cmd);
//コマンドライン引数の使い方を表示する関数
void print_usage(char *cmd);

int main(int argc, char **argv) {
    int **m, size, i, j;

    check_argnum(2, 2, argc, argv[0]);
    m = read_matrix(argv[1], &size);
    printf("  ");
    for (i = 0; i < size; i++)
        printf(" %2d", i + 1);
    printf("\n");
    for (i = 0; i < size; i++) {
        printf("%2d", i+1);
        for (j = 0; j < size; j++)
            printf(" %2d", m[i][j]);
        printf("\n");
    }

    return 0;
}

//行列の内容を読み取る関数
int **read_matrix(char *fname, int *s){
	int i, n;
	FILE *fin;
	int **matrix;
	int **reader;
	char buf[1024];
	int k, l;
	
	//ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		exit (1);
	}
	
	//行数、列数の入力
	fgets(buf, sizeof(buf), fin);
	sscanf(buf, "%d", s);
	
	//行数、列数の代入
	n=*s;
	
	//領域確保
	if((matrix=(int **)calloc(n, sizeof(int *)))==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	for(i=0; i<n; i++){
		if((matrix[i]=(int *)calloc(n, sizeof(int)))==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	if((reader=(int **)calloc(n*n/2, sizeof(int *)))==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	for(i=0; i<n*n/2; i++){
		if((reader[i]=(int *)calloc(3, sizeof(int)))==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	//行列の要素の読み取り、各要素をmatに代入
	int row, col, value;
	
	while(fgets(buf, sizeof(buf), fin)!=NULL){
		sscanf(buf, "%d %d %d", &row, &col, &value);
		matrix[row][col]=value;
		matrix[col][row]=value;
	}
	
	return matrix;
}

//コマンドライン引数を正確に機能させる関数
void check_argnum(int min, int max, int arg_num, char *cmd){
	if(!(min<=arg_num&&arg_num<=max)){
		printf("Too %s arguments!\n", (arg_num < min)? "few" : "many");
		print_usage(cmd);
		exit(1);
	}
}

//コマンドライン引数の使い方を表示する関数
void print_usage(char *cmd){
	printf("Usage\n");
	printf("%s 'input_file'\n", cmd);
}
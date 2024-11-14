/*
 *ex13_2.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>

//ヒストグラムの横
#define bin_size 10
//ヒストグラムの縦
#define max_size 20
//データ数
#define d_size 100
//バフサイズ
#define BUFSIZE 1024

//データをファイルから読み込む関数
void input_data(char *fname, int d[]);
//2次元配列hist[][]に値を設定する関数
void make_hist(int d[], int h[][max_size]);
//hist[][]の情報に従って実際にヒストグラムを作成する関数
void print_vhist(char *fname, int h[][max_size]);
//コマンドライン引数を正確に機能させる関数
void check_argnum(int min, int max, int arg_num, char *cmd);
//コマンドライン引数の使い方を表示する関数
void print_usage(char *cmd);

int main(int argc, char **argv) {
    int data[d_size] = {};
    int hist[bin_size][max_size] = {};

    check_argnum(3, 3, argc, argv[0]);
    input_data(argv[1], data);
    make_hist(data, hist);
    print_vhist(argv[2], hist);

    return 0;
}

//データをファイルから読み込む関数
void input_data(char *fname, int d[]){
	int i;
	FILE *fin;
	char buf[1024];
	 
	 //ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		exit(1);
	}
	
	//データの読み取り
	for(i=0; i<d_size; i++){
		fgets(buf, sizeof(buf), fin);
		sscanf(buf, "%d", &d[i]);
	}
	
	//確認用出力
	 printf("Data\n");
	 for(i=0; i<d_size; i++){
		 printf("%2d",d[i]);
		 if(!((i+1)%10)){
			 printf("\n");
		 }
	 }
	 printf("\n");
 }
 
  //2次元配列hist[][]に値を設定する関数
 void make_hist(int d[], int h[][max_size]){
	 int t=19;
	 
	 //dataがi(0<=i<=9)のとき
	 for(int i=0; i<bin_size; i++){
		 for(int j=0; j<d_size; j++){
			 if(d[j]==i){
				h[i][t]=1;
				t=t-1;
			 }
		 }
		 t=19;
	 }
 }
  
 //hist[][]の情報に従って実際にヒストグラムをファイルに作成する関数
void print_vhist(char *fname, int h[][max_size]){
	 int i, j;
	 FILE *fout;
	 
	 //ファイルのオープン
	if((fout=fopen(fname, "w"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		exit(1);
	}
	 
	 fprintf(fout, "Histogram\n");
	 
	 for(j=0; j<max_size; j++){
		 if(j==0){
			 fprintf(fout, "20|");
		 }else if(j==10){
			 fprintf(fout, "10|");
		 }else{
			 fprintf(fout, "  |");
		 }
		 
		 for(i=0; i<bin_size; i++){
			 if(h[i][j]==1){
				 fprintf(fout, "* ");
			 }else{
				 fprintf(fout, "  ");
			 }
		 }
		 fprintf(fout, "\n");
	 }
	 
	 for(i=0; i<2*bin_size+2; i++){
		 if(i==0||i==1){
			 fprintf(fout, " ");
		 }else if(i==2){
			 fprintf(fout, "+");
		 }else{
			 fprintf(fout, "-");
		 }
	 }
	 fprintf(fout, "\n");
	 
	 for(i=0; i<bin_size+2; i++){
		 if(i==0||i==1){
			 fprintf(fout, " ");
		 }else{
			 fprintf(fout, "%2d", i-2);
		 }
	 }
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
	printf("%s 'input_file' 'output_file\n", cmd);
}
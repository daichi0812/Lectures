/*
 * ex6_2.c 15822108 情報テクノロジー　堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 
 //ヒストグラムの横
 #define BIN_SIZE 10
 //ヒストグラムの縦
 #define MAX_SIZE 20
 //データ数
 #define D_SIZE 100
 
 //データをファイルから読み込む関数
 int input_data(char fname[], int d[]);
 //2次元配列hist[][]に値を設定する関数
 void make_hist(int d[], int h[][MAX_SIZE]);
 //hist[][]の情報に従って実際にヒストグラム作成する関数
 int print_vhistf(int h[][MAX_SIZE]);
 
 int main(){
	 int data[D_SIZE]={};
	 int hist[BIN_SIZE][MAX_SIZE]={};
	 char fname[100];
	 
	 printf("入力ファイル名を入力してください: ");
	 scanf("%s", fname);
	 if (input_data(fname, data) == 1)
        return 1;
     make_hist(data, hist);
     if (print_vhistf(hist) == 1)
        return 1;
	 
	 return 0;
 }
 
//データをファイルから読み込む関数
int input_data(char fname[], int d[]){
	 int i;
	 FILE *fin;
	 
	 //ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		return 1;
	}
	
	//データの読み取り
	for(i=0; i<100; i++){
		fscanf(fin, "%d", &d[i]);
	}
	
	//確認用出力
	 printf("Data\n");
	 for(i=0; i<D_SIZE; i++){
		 printf("%2d",d[i]);
		 if(!((i+1)%10)){
			 printf("\n");
		 }
	 }
	 printf("\n");
	 
	 return 0;
 }
 
 //2次元配列hist[][]に値を設定する関数
 void make_hist(int d[], int h[][MAX_SIZE]){
	 int t=19;
	 
	 //dataがi(0<=i<=9)のとき
	 for(int i=0; i<BIN_SIZE; i++){
		 for(int j=0; j<D_SIZE; j++){
			 if(d[j]==i){
				h[i][t]=1;
				t=t-1;
			 }
		 }
		 t=19;
	 }
 }
 
 //hist[][]の情報に従って実際にヒストグラムをファイルに作成する関数
 int print_vhistf(int h[][MAX_SIZE]){
	 int i, j;
	 FILE *fout;
	 char fname[]="result.txt";
	 
	 //ファイルのオープン
	if((fout=fopen(fname, "w"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		return 1;
	}
	 
	 fprintf(fout, "Histogram\n");
	 
	 for(j=0; j<MAX_SIZE; j++){
		 if(j==0){
			 fprintf(fout, "20|");
		 }else if(j==10){
			 fprintf(fout, "10|");
		 }else{
			 fprintf(fout, "  |");
		 }
		 
		 for(i=0; i<BIN_SIZE; i++){
			 if(h[i][j]==1){
				 fprintf(fout, "* ");
			 }else{
				 fprintf(fout, "  ");
			 }
		 }
		 fprintf(fout, "\n");
	 }
	 
	 for(i=0; i<2*BIN_SIZE+2; i++){
		 if(i==0||i==1){
			 fprintf(fout, " ");
		 }else if(i==2){
			 fprintf(fout, "+");
		 }else{
			 fprintf(fout, "-");
		 }
	 }
	 fprintf(fout, "\n");
	 
	 for(i=0; i<BIN_SIZE+2; i++){
		 if(i==0||i==1){
			 fprintf(fout, " ");
		 }else{
			 fprintf(fout, "%2d", i-2);
		 }
	 }
 }
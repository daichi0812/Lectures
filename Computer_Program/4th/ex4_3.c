/*
 * ex4_3.c 15822108 情報テクノロジー　堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 
 //ヒストグラムの横
 #define BIN_SIZE 10
 //ヒストグラムの縦
 #define MAX_SIZE 20
 //データ数
 #define D_SIZE 100
 
 //データを乱数で生成する関数
 void get_data(int d[]);
 //2次元配列hist[][]に値を設定する関数
 void make_hist(int d[], int h[][MAX_SIZE]);
 //hist[][]の情報に従って実際にヒストグラム作成する関数
 void print_vhist(int h[][MAX_SIZE]);
 
 int main(){
	 int data[D_SIZE]={};
	 int hist[BIN_SIZE][MAX_SIZE]={};
	 
	 get_data(data);
	 make_hist(data, hist);
	 
	 
	 print_vhist(hist);
	 
	 return 0;
 }
 
 //データを乱数で生成する関数
 void get_data(int d[]){
	 int i;
	 
	 srand(1);
	 
	 printf("Data\n");
	 for(i=0; i<D_SIZE; i++){
		 //0~9の整数値の生成と保存
		 d[i]=rand()%BIN_SIZE; //ここでの配列値の変更はmain()関数のdata[]にも反映
		 //確認用出力
		 printf("%2d",d[i]);
		 if(!((i+1)%10)){
			 printf("\n");
		 }
	 }
	 printf("\n");
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
 
 //hist[][]の情報に従って実際にヒストグラム作成する関数
 void print_vhist(int h[][MAX_SIZE]){
	 int i, j;
	 
	 printf("Histogram\n");
	 
	 for(j=0; j<MAX_SIZE; j++){
		 if(j==0){
			 printf("20|");
		 }else if(j==10){
			 printf("10|");
		 }else{
			 printf("  |");
		 }
		 
		 for(i=0; i<BIN_SIZE; i++){
			 if(h[i][j]==1){
				 printf("* ");
			 }else{
				 printf("  ");
			 }
		 }
		 printf("\n");
	 }
	 
	 for(i=0; i<2*BIN_SIZE+2; i++){
		 if(i==0||i==1){
			 printf(" ");
		 }else if(i==2){
			 printf("+");
		 }else{
			 printf("-");
		 }
	 }
	 printf("\n");
	 
	 for(i=0; i<BIN_SIZE+2; i++){
		 if(i==0||i==1){
			 printf(" ");
		 }else{
			 printf("%2d", i-2);
		 }
	 }
 }
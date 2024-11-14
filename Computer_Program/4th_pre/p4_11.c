/*
 * p4_11.c 15822108 堀田大智
 */
 
 #include<stdio.h>
 #include<stdlib.h>
 
 #define BIN_SIZE 10 //ヒストグラムの分割数
 #define D_SIZE 100 //データ数
 
 //データを乱数で生成する関数
 void get_data(int d[]);
 //データ値の出現回数(frequency)をカウントする関数
 void count_freq(int d[], int c[]);
 //ヒストグラムを表示する関数
 void print_hhist(int c[]);
 
 int main(){
	 int data[D_SIZE]; //データ用の配列
	 int count[BIN_SIZE]={}; //データ値の出現回数を保持する配列
	 
	 get_data(data);
	 count_freq(data, count);
	 print_hhist(count);
	 
	 return 0;
 }
 
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
 
 void count_freq(int d[], int c[]){
	 for(int i=0; i<D_SIZE; i++){
		 for(int j=0; j<BIN_SIZE; j++){
			 if(d[i]==j){
				 c[j]=c[j]+1;
			 }
		 }
	 }
 }
 
 void print_hhist(int c[]){
	 for(int i=0; i<BIN_SIZE; i++){
		 printf("%2d|",9-i);
		 for(int j=0; j<c[9-i]; j++){
			 printf("*");
		 }
		 printf("\n");
	 }
 }
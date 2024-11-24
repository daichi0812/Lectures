/*
 * program4_11 15822108 堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 #include <errno.h>
 #include<math.h>
 
 //ベクトルの入力
 double *input_dvector(int *size, char *filename);
 //ベクトルの領域確保
 double *dvector(int i, int j);
 //ベクトルの領域開放
 void free_dvector(double *a, int i);
 //ノルム1=絶対値の和
 double one_vector_norm(double *a, int n){
	 double norm=0.0;
	 int i;
	 
	 for(i=1; i<=n; i++){
		 norm=norm+fabs(a[i]); //math.h によって、fabsは絶対値を返す
	 }
	 
	 return norm;
 }
 
  //aの2ノルム=二乗和の平方根
 double two_vector_norm(double *a, int n){
	 double norm=0.0;
	 int i;
	 
	 for(i=1; i<=n; i++){
		 norm=norm+a[i]*a[i];
	 }
	 
	 norm=sqrt(norm); /*平方根*/
	 
	 return norm;
 }
 
 //aの∞ノルム=各ノルムの絶対値の最大値
 double inf_vector_norm(double *a, int n){
	 double norm=0.0;
	 int i;
	 
	 for(i=1; i<=n; i++){
		 if(norm<fabs(a[i])){
			 norm=fabs(a[i]);
		 }
	 }
	 
	 return norm;
 }
 
 int main(){
	 char *fname="vector1.dat";
	 int n,i;
	 double *a, one_norm, two_norm, inf_norm;
	 
	 //
	 if((a=input_dvector(&n, fname))==(double*)NULL){
		 printf("ベクトル%sの読み込みに失敗しました\n", fname);
		 exit(1);
	 }
	 
	 printf("ベクトル%sの内容は次の通りです。\n", fname);
	 
	 for(i=1; i<=n; i++){
		 printf("%6.2f", a[i]);
	 }
	 printf("\n");
	 
	 one_norm=one_vector_norm(a,n);
	 two_norm=two_vector_norm(a,n);
	 inf_norm=inf_vector_norm(a,n);
	 
	 printf("ベクトルの各ノルムは次の通りです。\n");
	 printf("%6.2lf, %6.2lf, %6.2lf\n", one_norm, two_norm, inf_norm);
	 
	 //領域の開放
	 free_dvector(a, 1);
	 
	 return 0;
 }
 
 //ベクトルaの入力
 double *input_dvector(int *n, char *fname){
	 double *a;
	 int i;
	 FILE *fin;
	 
	 if((fin=fopen(fname,"r"))==(FILE*)NULL){
		 printf("ファイル%sをオープンできません \n", fname);
		 
		 return (double*)NULL;
	 }
	 
	 //要素数の取得
	 fscanf(fin, "%d", &n);
	 if(n<=0){
		 printf("ベクトルのサイズが間違っています\\n");
		 fclose(fin);
		 return(double*)NULL;
	 }
	 
	 //aの領域をdvectorで確保
	 if((a=dvector(1,*n))==(double*)NULL){
		 printf("dvectorが失敗しました\n");
		 fclose(fin);
		 return(double*)NULL;
	 }
	 
	 for(i=1; i<=*n; i++){
		 fscanf(fin, "%lf", &a[i]);
	 }
	 fclose(fin);
	 return a;
 }
 
 //ベクトルの領域確保
 double *dvector(int i, int j){
	 double *a;
	 
	 if((a=(double*)malloc(((j-i+1)*sizeof(double))))==NULL){
		 printf("メモリが確保できません\n");
		 exit(1);
	 }
	 
	 return(a-i);
 }
 
 //領域の解放
 void free_dvector(double *a, int i){
	 free((void*)(a+i));
 }
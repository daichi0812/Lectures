/*
 *p5_13.c 文字列の加工　15822108 堀田大智
 */
 #include<stdio.h>
 
 #define MAXLENGTH 40
 
 int main(){
	 int i;
	 char fname[MAXLENGTH];
	 
	 printf("ファイル名を入力してください(最大%d文字) : ", MAXLENGTH-1);
	 gets(fname);
	 for(i=0; fname[i]!='\0'&&i<MAXLENGTH; i++){
		 if(fname[i]=='.'){
			 fname[i]='\0';
			 break;
		 }
	 }
	 printf("ファイル名(拡張子を除く) :%s\n", fname);
	 
	 return 0;
 }
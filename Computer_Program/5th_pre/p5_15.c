/*
 *p5_15.c 15822108 堀田大智
 */
 #include<stdio.h>
 #include<string.h>
 
 #define MAXLENGTH 40
 #define ENDWORD "end"
 
 void get_fname(char fn[]);
 void remove_ext(char fn[]);
 
 int main(){
	 int i;
	 char fname[MAXLENGTH];
	 
	 while(1){
		 get_fname(fname);
		 if(!strcmp(fname, ENDWORD)){
			 break;
		 }
		 remove_ext(fname);
		 printf("拡張子なしファイル名 : %s\n", fname);
	 }
	 printf("終了します\n");
	 return 0;
 }
 
 void get_fname(char fn[]){
	 int limit=MAXLENGTH/2;
	 
	 while(1){
		 printf("ファイル名を入力してください(最大%d文字, \"end\"で終了)", limit);
		 gets(fn);
		 if(strlen(fn)>limit){
			 printf("長すぎます\n");
		 }else{
			 return;
		 }
	 }
 }
 
 void remove_ext(char fn[]){
	 int i;
	 
	 for(i=strlen(fn)-1; i>=0; i--){
		 if(fn[i]=='.'){
			 fn[i]='\0';
			 break;
		 }
	 }
 }
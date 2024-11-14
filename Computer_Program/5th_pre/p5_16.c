/*
 *p5_16.c 15822108 堀田大智
 */
 #include<stdio.h>
 #include<string.h>
 
 #define MAXLENGTH 40
 #define ENDWORD "end"
 
 void get_fname(char fn[]);
 void remove_ext(char fn[]);
 void get_ext(char fn[], char ext[]);
 
 int main(){
	 int i;
	 char fname[MAXLENGTH], fname2[MAXLENGTH], ext[MAXLENGTH];
	 
	 while(1){
		 get_fname(fname);
		 if(!strcmp(fname, ENDWORD)){
			 break;
		 }
		 
		 for(int i=0; i<MAXLENGTH; i++){
			 fname2[i]=fname[i];
		 }
		 
		 remove_ext(fname);
		 printf("拡張子なしファイル名 : %s\n", fname);
		 get_ext(fname2, ext);
		 printf("拡張子 : %s\n", ext);
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
 
 void get_ext(char fn[], char ext[]){
	 int i, j;
	 j=1;
	 
	 for(i=strlen(fn)-1; i>=0; i--){
		 if(i==0){
			 ext[0]='\0';
		 }
		if(fn[i]=='.'){
		 ext[0]='.';
		 ext[j+1]='\0';
		 break;
		}else{
			ext[j]=fn[i];
			j++;
		}
	 }
 }
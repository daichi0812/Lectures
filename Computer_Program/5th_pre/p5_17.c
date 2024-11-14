/*
 *p5_17.c バックアップ用ファイル名の生成
 */
 #include<stdio.h>
 #include<string.h>
 
 #define MAXLENGTH 40
 #define ENDWORD "end"
 #define SUFFIX "_back"
 
 void get_fname(char fn[]);
 void remove_ext(char fn[]);
 void get_ext(char fn[], char exr[]);
 
 int main(){
	 int i;
	 char fname[MAXLENGTH];
	 char ext[MAXLENGTH];
	 char backup_name[MAXLENGTH];
	 
	 while(1){
		 get_fname(fname);
		 if(!strcmp(fname, ENDWORD)){
			 break;
		 }
		 strcpy(backup_name, fname);
		 get_ext(backup_name, ext);
		 remove_ext(backup_name);
		 strcat(strcat(backup_name,SUFFIX),ext);
		 printf("バックアップ用ファイル名 : %s\n", backup_name);
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
/*
 *p5_14.c 15822108 堀田大智
 */
 #include<stdio.h>
 #include<ctype.h>
 
 #define MAXLENGTH 40
 
 int main(){
	 char ss[MAXLENGTH];
	 char tt[MAXLENGTH];
	 
	 printf("空白を含む文字列を入力してください(最大%d文字) : \n", MAXLENGTH-1);
	 gets(ss);
	 
	 for(int i=0; i<MAXLENGTH; i++){
		 tt[i]=ss[i];
	 }
	 
	 for(int i=0; ss[i]!='\0'&&i<MAXLENGTH; i++){
		 if(ss[i]!=' '){
			 if(isalnum(ss[i])==0){
				 ss[i]='*';
			 }
		 }
		 
		 if(isupper(ss[i])){
			 ss[i]=tolower(ss[i]);
		 }else{
			 ss[i]=toupper(ss[i]);
		 }
	 }
	 
	 puts(ss);
	 
	 printf("元の文字列\n");
	 puts(tt);
	 
	 return 0;
 }
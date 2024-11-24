/*
 *p5_12.c 文字列で初期化した配列の確認　15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	 int i;
	 char agu[]="Aoyama Gakuin University";
	 char day_of_week[][4]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	 
	 printf("大学名 : %s\n", agu);
	 for(i=0; i<7; i++){
		 printf("%s ", day_of_week[i]);
	 }
	 puts("");
	 for(i=0; i<4; i++){
		 if(day_of_week[0][i]=='\0'){
			 printf("終端文字\n");
		 }else{
			 printf("%c\n", day_of_week[0][i]);
		 }
	 }
	 
	 return 0;
 }
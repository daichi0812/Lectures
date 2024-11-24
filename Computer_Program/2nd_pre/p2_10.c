/*
 *p2_10.c
 */
 #include <stdio.h>
 
 int main(){
	 
	 int score;
	 
	 printf("成績を入力してください:");
	 
	 scanf("%d", &score);
	 
	 if(score>=90){
		 printf("AA\n");
	 }else if(score>=80){
		 printf("A\n");
	 }else if(score>=70){
		 printf("B\n");
	 }else if(score>=60){
		 printf("C\n");
	 }else{
		 printf("来年頑張ってください\n");
	 }
	 
	 return(0);
 }
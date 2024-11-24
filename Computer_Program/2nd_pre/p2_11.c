/*
 *p2_11.c
 */
 #include <stdio.h>
 
 int main(){
	 
	 int score;
	 
	 printf("成績を入力してください:");
	 
	 scanf("%d", &score);
	 
	 if((100>=score)&&(score>=90)){
		 printf("AA\n");
	 }else if((90>score)&&(score>=80)){
		 printf("A/n");
	 }else if((80>score)&&(score>=70)){
		 printf("B\n");
	 }else if((70>score)&&(score>=60)){
		 printf("C\n");
	 }else if((60>score)&&(score>=0)){
		 printf("不合格/n");
	 }else{
		 printf("入力が正しくありません/n");
	 }
	 
	 return(0);
 }
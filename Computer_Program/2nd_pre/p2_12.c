/*
 *p2_12.c
 */
 #include <stdio.h>
 
 int main(){
	 
	 int month;
	 
	 printf("月を入力してください:");
	 
	 scanf("%d", &month);
	 
	 switch(month){
		 
		 case 1: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 2: printf("日数は%d日です\n", 28);
		 break;
		 
		 case 3: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 4: printf("日数は%d日です\n", 30);
		 break;
		 
		 case 5: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 6: printf("日数は%d日です\n", 30);
		 break;
		 
		 case 7: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 8: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 9: printf("日数は%d日です\n", 30);
		 break;
		 
		 case 10: printf("日数は%d日です\n", 31);
		 break;
		 
		 case 11: printf("日数は%d日です\n", 30);
		 break;
		 
		 case 12: printf("日数は%d日です\n", 31);
		 break;
		 
		 default: printf("入力が正しくありません\n");
	 }
	 
	 return(0);
 }
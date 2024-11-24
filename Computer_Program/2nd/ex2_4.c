/*
 * 15822108 堀田大智
 */
 #include <stdio.h>
 
 int is_leap_year(int y);
 
 int main(){
	 
	 int year, month;
	 
	 printf("年を入力");
	 scanf("%d", &year);
	 
	 printf("月を入力");
	 scanf("%d", &month);
	 
	 if(is_leap_year(year)){
		 switch(month){
		 
		 case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		 printf("%d年%d月の日数は%d日です\n", year, month, 31);
		 break;
		 
		 case 2: printf("%d年%d月の日数は%d日です\n", year, month, 29);
		 break;
		 
		 case 4: case 6: case 9: case 11:
		 printf("%d年%d月の日数は%d日です\n", year, month, 30);
		 break;
		 
		 default: printf("入力が正しくありません\n");
	 }
		 
	 }else{
		 switch(month){
		 
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		 printf("%d年%d月の日数は%d日です\n", year, month, 31);
		 break;
		 
		 case 2: printf("%d年%d月の日数は%d日です\n", year, month, 28);
		 break;
		 
		 case 4: case 6: case 9: case 11:
		 printf("%d年%d月の日数は%d日です\n", year, month, 30);
		 break;
		
		 default: printf("入力が正しくありません\n");
		 }
	 }
		 
	 return(0);
 }
 
 int is_leap_year(int y){
	 
	 int judge;
	 
	 if(y%100==0&&y%400==0){
		 judge=1;
		 
	 }else if(y%100==0){
		 judge=0;
		 
	 }else if(y%4==0){
		 judge=1;
		 
	 }else{
		 judge=0;
	 }
		 
	 
	 return judge;
 }
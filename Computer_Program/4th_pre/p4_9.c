/*
 *p4_9.c 配列の利用(二次元配列、行ごとの参照と列ごとの参照)
 */
 
 #include<stdio.h>
 
 void print_line(void);
 
 int main(){
	 int team, game, scores[2][4];
	 
	 for(team=0; team<2; team++){
		 for(game=0; game<4; game++){
			printf("チーム%dの%d試合目の得点を入力 : ", team+1, game+1);
			scanf("%d",&scores[team][game]);
		 }
	 }
	 printf("チーム1とチーム2の対戦結果(0は引き分け)\n");
	 print_line();
	 for(team=0; team<2; team++){
		 printf("| Team %d ", team+1);
		 for(game=0; game<4; game++){
			 printf("| %d ", scores[team][game]);
		 }
		printf("|\n");
		print_line();
	 }
	 printf("| Winner ");
	 for(game=0; game<4; game++){
		 if(scores[0][game]>scores[1][game]){
			 printf("| 1 ");
		 }else if(scores[0][game]<scores[1][game]){
			 printf("| 2 ");
		 }else{
			 printf("| 0 ");
		 }
		 printf("|\n");
		 print_line();
		 
		 return 0;
	 }
 }

void print_line(void){
	int i;
	
	printf("+--------");
	for(i=0; i<4; i++){
		printf("+---");
	}
	printf("+\n");
}
	
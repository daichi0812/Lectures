/*
 *ex12_2.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 256

//行列の領域確保
int **get_2d_array(int n, int m);
//行列の要素を表示
void print_2d_array(int **p, int n, int m);
//行列の要素を入力
void set_2d_array(int **p, int n, int m);

//ex12_2で追加した自作関数
//コマンドラインが多いか少ないかの判別する関数
void check_argnum(int min, int max, int arg_num, char *cmd);
//プログラムの使用方法を表示
void print_usage(char *cmd);
//正の整数の文字列を数値に変換する
int get_posi_int (char *n);
//valがmin以上，max以下の範囲であれば1を返し，それ以外の場合は0を返す
int in_range(int min, int max, int val);

int main(int argc, char **argv){
	int **d;
	int n, m;
	
	check_argnum(2, 3, argc, argv[0]);
	n=get_posi_int(argv[1]);
	m=(argc==3)? get_posi_int(argv[2]) : n;
	
	if(!in_range(1, 20, n) || !in_range(1, 20, m)){
		printf("The argument should be a positive integer\n");
		exit(1);
	}
	
	d=get_2d_array(n, m);
	set_2d_array(d, n, m);
	print_2d_array(d, n, m);
	
	return 0;
}

//行列の要素を表示
void print_2d_array(int **p, int n, int m){
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("(%2d, %2d)=%2d\n", i, j, p[i][j]);
		}
	}
}

//行列の領域確保
int **get_2d_array(int n, int m){
	int **p, i;
	
	if((p=(int **)calloc(n, sizeof(int *)))==NULL){
		printf("Memory allocation error!\n");
		exit(1);
	}
	for(i=0; i<n; i++){
		if((p[i]=(int *)calloc(m, sizeof(int)))==NULL){
			printf("Memory allocation erro!\n");
			exit(1);
		}
	}
	return p;
}

//行列の要素を入力
void set_2d_array(int **p, int n, int m){
	int i, j, c =0;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			p[i][j]=c++;
		}
	}
}
//コマンドラインが多いか少ないかの判別する関数
void check_argnum(int min, int max, int arg_num, char *cmd){
	if(!(min<=arg_num&&arg_num<=max)){
		printf("Too %s arguments!\n", (arg_num < min)? "few" : "many");
		print_usage(cmd);
		exit(1);
	}
}

//プログラムの使用方法を表示
void print_usage(char *cmd){
	printf("Usage\n");
	printf("%s 'n_row' ['n_col']\n", cmd);
	printf("n_row: number of rows (1 - 20)\n");
	printf("n_col: number of columns (1 - 20) (optional)\n");
	printf("  If the parameter n_col is omitted, the value of n_row is used insted of it.");
}

//正の整数の文字列を数値に変換する
int get_posi_int (char *n){
	int i=0;
	int ans, num=0;
	
	while(1){
		if(n[0]=='-'){
			ans=0;
			break;
		}
		if(47<n[i]&&n[i]<58){
			if(n[i+1]=='\0'){
				ans=1;
				break;
			}
			i++;
		}else if(n[i]=='.'){
			for(int j=0; j<i; j++){
				if(47<n[j]&&n[j]<58){
					ans=1;
				}else{
					ans=0;
					break;
				}
			}
			for(int k=i+1; n[k]!='\0'&&k<BUFSIZE; k++){
				if(n[k]=='0'){
					ans=1;
				}else{
					ans=0;
					break;
				}
			}
			break;
		}else{
			ans=0;
			break;
		}
	}
	
	if(ans==1){
		num=atoi(n);
	}
	
	return num;
}

//valがmin以上，max以下の範囲であれば1を返し，それ以外の場合は0を返す
int in_range(int min, int max, int val){
	int ans=0;
	
	if(min<=val&&val<=max){
		ans=1;
	}
	
	return ans;
}
/*
 *15822108 堀田大智
 */
 
 #include <stdio.h>

int in_range(int n, int min, int max);
int get_sorted_number(int x, int y, int z, int n);

int main() {
    int a, b, c, n;

    printf("3つの整数値をカンマで区切って入力してください：");
    scanf("%d,%d,%d", &a, &b, &c);

    printf("1～3のいずれかの値を入力してください：");
    scanf("%d", &n);

    if (in_range(n, 1, 3))
        printf("%d, %d, %d を昇順に並べた場合の %d 番目の数値は %d です\n",
                a, b, c, n, get_sorted_number(a, b, c, n));
    else
        printf("%d は1～3のいずれかの値ではありません\n", n);
	
    return 0;
}

int in_range(int n, int min, int max){
	
	int ans;
	
	if(n>=min&&max>=n){
		ans=1;
		
	}else{
		ans=0;
	}
	
	return ans;
}

int get_sorted_number(int x, int y, int z, int n){
	
	int temp;
	
	if(x>y){
		temp=x;
		x=y;
		y=temp;
	}
	
	if(x>z){
		temp=x;
		x=z;
		z=temp;
	}
	
	if(y>z){
		temp=y;
		y=z;
		z=temp;
	}
	
	switch(n){
		case 1:
			return x;
		case 2:
			return y;
		case 3:
			return z;
		default:
			return 0;
	}
}
	
/*
 * 15822108 情報テクノロジー　堀田大智
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 行列の入力 */ 
int input_matrix( double ***a, char c, FILE *fin, FILE *fout);
/* 行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* 部分ピボット選択付きガウス消去法 */
double gauss1( double **a, int n); 

int main(void)
{
  FILE *fin, *fout;
  double **a, ans; 
  int i, n;

  /* ファイルのオープン */
  if ( (fin = fopen( "matrix1.txt", "r")) == NULL )
  {
    printf("ファイルが見つかりません : matrix1.txt \n");
    exit(1);
  }
  if( (fout = fopen( "matrix1.dat", "w")) == NULL )
  {
    printf("ファイルが作成できません : matrix1.dat \n");
    exit(1);
  }

  n = input_matrix( &a, 'A', fin, fout );    //行列Aの入出力、サイズ取得  
  
  ans = gauss1( a, n);             /* ガウス消去法 */

  /* 結果の出力 */
  fprintf( fout, "行列式の値は次の通りです\n");
  fprintf(fout, "%f\n", ans);

  fclose(fin); fclose(fout);  /* ファイルのクローズ */

  /* 領域の解放 */
  free_dmatrix( a, 1, n, 1, n );

  return 0;
}

/* 部分ピボット選択付きガウス消去法 */
double gauss1( double **a, int n )
{
  int i, j, k, ip;
  int count = 0;  //ピボット選択の回数を数えマイナスをかける
  double alpha, tmp, ans = 1.0;
  double amax, eps=pow(2.0, -50.0); /* eps = 2^{-50}とする */

  for( k = 1; k <= n-1; k++)
  {
    /* ピボットの選択 */
    amax = fabs(a[k][k]); ip = k;
    for( i = k+1; i <= n; i++)
    {
      if ( fabs(a[i][k]) > amax )
      {
        amax = fabs(a[i][k]); ip = i;
      }
    }
    /* 正則性の判定 */
    if ( amax < eps ) printf("入力した行列は正則ではない!!\n");
    /* 行交換 */
    if ( ip != k)
    {
      for( j = k; j <= n; j++)
      {
        tmp = a[k][j]; a[k][j]=a[ip][j]; a[ip][j]=tmp;
      }
      count++;  //ピボット選択の回数を数える
    }
      /* 前進消去 */
    for( i = k+1; i <= n; i++)
    {
      alpha = - a[i][k]/a[k][k];
      for( j = k+1; j <= n; j++)
      {
        a[i][j] = a[i][j] + alpha * a[k][j];
      }
    }
  }

  //前進消去後の対角成分の積が行列式の値になる
  for(i=1; i<=n; i++)
    ans *= a[i][i];
  ans = ans * pow(-1, count);  //ピボット選択の回数だけ-1をかける

  return ans;
}

/* a[1...N][1...N]の入力 */
int input_matrix( double ***a, char c, FILE *fin, FILE *fout)
{
  int i,j;
  int n;

  fscanf(fin, "%d", &n); //行列の大きさを読み込む
  //行列の領域確保
  *a = dmatrix(1, n, 1, n); /* 行列 a[1...n][1...n] */

  fprintf( fout, "行列%cは次の通りです\n", c);
  for( i = 1 ; i <= n ; i++)
  {
    for( j = 1 ; j <= n ; j++)
    {
      fscanf(fin, "%lf", &(*a)[i][j]);
      fprintf(fout, "%5.2f\t", (*a)[i][j]);
    }
    fprintf( fout, "\n");
  }
  return n;
}

double **dmatrix(int nr1, int nr2, int nl1, int nl2)
{
  int i, nrow, ncol; 
  double **a; 

  nrow = nr2 - nr1 + 1 ; /* 行の数 */
  ncol = nl2 - nl1 + 1 ; /* 列の数 */

  /* 行の確保 */
  if ( ( a=(double **)malloc( nrow*sizeof(double *) ) ) == NULL ) 
  {
    printf("メモリが確保できません(行列a)\n");
    exit(1);
  }
  a = a - nr1; /* 行をずらす */
  /* 列の確保 */
  for( i=nr1; i<=nr2; i++) a[i] = (double *)malloc(ncol*sizeof(double)); 
  for( i=nr1; i<=nr2; i++) a[i] = a[i]-nl1;             /* 列をずらす */
  
  return(a);
}

void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2)
{
  int i;

  /* メモリの解放  */
  for ( i = nr1 ; i <= nr2 ; i++) free((void *)(a[i]+nl1));
  free((void *)(a+nr1));
}

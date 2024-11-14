/*
　* 15822108 情報テクノロジー　堀田大智
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 行列の入力 */ 
int input_matrix( double ***a, double ***b, char c, FILE *fin, FILE *fout);
/* 行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* 部分ピボット選択付きガウス消去法 */
double **gauss2( double **a, double **b, int n); 
//行列の積(検算用)
void matrix_product(double **a, double **b, double **c, int n);

int main(void)
{
  FILE *fin, *fout;
  double **a, **b, **ans, **c, **check; 
  int i, j, n;

  // ファイルのオープン 
  if ( (fin = fopen( "matrix1.txt", "r")) == NULL )
  {
    printf("ファイルが見つかりません : matrix1.txt \n");
    exit(1);
  }
  if( (fout = fopen( "matrix1-2.txt", "w")) == NULL )
  {
    printf("ファイルが作成できません : matrix1-2.txt \n");
    exit(1);
  }

  n = input_matrix( &a, &b, 'A', fin, fout );    //行列Aの入出力、サイズ取得  
  
  //領域確保
  check = dmatrix(1, n, 1, n);
  c = dmatrix(1, n, 1, n);

  //aの値の避難
  for(i=1; i<=n; i++)
  {
    for(j=1; j<=n; j++)
    {
      check[i][j] = a[i][j];
    }
  }

  //Bの初期化
  for(i=1; i<=n; i++)
  {
    for(j=1; j<=n; j++)
    {
      if(i==j) 
        b[i][j] = 1.0;
      else
        b[i][j] = 0.0;
    }
  }
  ans = gauss2( a, b, n);             // ガウス消去法

  matrix_product(check, ans, c, n);   //行列の積(検算)

  /* 結果の出力(foutには逆行列、画面には検算の結果を出力)*/
  fprintf( fout, "逆行列は次の通りです\n");
  for(i=1; i<=n; i++)
  {
    for(j=1; j<=n; j++)
    { 
      fprintf(fout, "%6.3f ", ans[i][j]);
      printf("%6.3f",c[i][j]);
    }
    fprintf(fout, "\n");
    printf("\n");
  }

  fclose(fin); fclose(fout);  /* ファイルのクローズ */

  /* 領域の解放 */
  free_dmatrix( a, 1, n, 1, n );
  free_dmatrix( b, 1, n, 1, n );
  free_dmatrix( c, 1, n, 1, n );
  free_dmatrix( check, 1, n, 1, n );

  return 0;
}

/* 部分ピボット選択付きガウス消去法を利用して逆行列を求める */
double **gauss2( double **a, double **b, int n )
{
  int i, j, k, ip;
  double alpha, tmp;
  double amax, eps=pow(2.0, -50.0); /* eps = 2^{-50}とする */

  for( k = 1; k <= n; k++)
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
        tmp = b[k][j]; b[k][j]=b[ip][j]; b[ip][j]=tmp;
      }
    }
      /* 前進消去 1行目からk行目を除いた全ての行に */
    for( i = 1; i <= n; i++)
    {
      if(i != k)
      {
        alpha = - a[i][k]/a[k][k];
        for( j = 1; j <= n; j++)
        {
        a[i][j] = a[i][j] + alpha * a[k][j];
        b[i][j] = b[i][j] + alpha * b[k][j];
        }
      }
    }
  }

  //対角成分が１になるように
  for(i=1; i<=n; i++)
  {
    for(j=1; j<=n; j++)
    {
      b[i][j] = b[i][j] / a[i][i];
      printf("%6.3f", a[i][j]);  //計算がうまくいっているか確認用の出力
    }                           //成功なら対角以外０
    printf("\n");
  }

  return b;
}

/* a[1...N][1...N]の入力 */
int input_matrix( double ***a, double ***b, char c, FILE *fin, FILE *fout)
{
  int i,j;
  int n;

  fscanf(fin, "%d", &n); //行列の大きさを読み込む
  //行列の領域確保
  *a = dmatrix(1, n, 1, n); /* 行列 a[1...n][1...n] */
  *b = dmatrix(1, n, 1, n); /* 行列 a[1...n][1...n] */

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

void matrix_product(double **a, double **b, double **c, int n)
{
  int i,j,k;
  for(i=1; i<=n; i++)
  {
    for(j=1; j<=n; j++)
    {
      c[i][j] = 0.0;  //変数の初期化
      for(k=1; k<=n; k++)
      {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
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

/*
 *program32n.c 15822108 堀田大智
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 行列の入力 */ 
int input_matrix( double ***a, char c, FILE *fin, FILE *fout);
/* ベクトルの入力 */
int input_vector( double **b, char c, FILE *fin, FILE *fout);
/* 行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* ベクトル領域の確保 */
double *dvector(int i, int j);  
/* 領域の解放 */
void free_dvector(double *a, int i); 
/* 部分ピボット選択付きガウス消去法 */
double *gauss( double **a, double *b, int n); 

int main(void)
{
  FILE *fin, *fout;
  double **a, *b; 
  int i, n, n2;
  char finame[]="test_01_input.dat";
  char foname[]="test_01_output.dat";

  /* ファイルのオープン */
  if ( (fin = fopen( finame, "r")) == NULL )
  {
    printf("ファイルが見つかりません : %s \n", finame);
    exit(1);
  }
  if( (fout = fopen( foname, "w")) == NULL )
  {
    printf("ファイルが作成できません : %s \n", foname);
    exit(1);
  }
  
  //行列のサイズ入力
  fprintf(fin, "%d", &n);

  n = input_matrix( &a, 'A', fin, fout );    //行列Aの入出力、サイズ取得  
  n2 = input_vector( &b, 'b', fin, fout );    //ベクトルbの入出力、サイズ取得
  if( n != n2){
    fprintf( fout, "行列のサイズとベクトルのサイズが合わない\n");
    return 1;
  }
  b = gauss( a, b, n);             /* ガウス消去法 */

  /* 結果の出力 */
  fprintf( fout, "Ax=bの解は次の通りです\n");
  for( i = 1 ; i <= n ; i++)
  {
    fprintf(fout, "%f\n", b[i]);
  }

  fclose(fin); fclose(fout);  /* ファイルのクローズ */

  /* 領域の解放 */
  free_dmatrix( a, 1, n, 1, n );  free_dvector( b, 1 );

  return 0;
}

/* 部分ピボット選択付きガウス消去法 */
double *gauss( double **a, double *b, int n )
{
  int i, j, k, ip;
  double alpha, tmp;
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
        tmp = b[k] ; b[k]=b[ip]; b[ip]=tmp;
    }
      /* 前進消去 */
    for( i = k+1; i <= n; i++)
    {
      alpha = - a[i][k]/a[k][k];
      for( j = k+1; j <= n; j++)
      {
        a[i][j] = a[i][j] + alpha * a[k][j];
      }
      b[i] = b[i] + alpha * b[k];
    }
  }

  /* 後退代入 */
  b[n] = b[n]/a[n][n];
  for( k = n-1; k >= 1; k--)
  {
    tmp = b[k];
    for( j = k+1; j <= n; j++)
    {
      tmp = tmp - a[k][j] * b[j];
    }
    b[k] = tmp/a[k][k];
  }

  return b;
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

/* b[1...N]の入力 */
int input_vector( double **b, char c, FILE *fin, FILE *fout)
{
  int i;
  int n;

  fscanf( fin, "%d", &n);
  /* ベクトルの領域確保 */
  *b = dvector(1,n);  /* b[1...n] */

  fprintf( fout, "ベクトル%cは次の通りです\n", c);
  for( i = 1 ; i <= n ; i++)
  {
    fscanf(fin, "%lf", &(*b)[i]);
    fprintf(fout, "%5.2f\t", (*b)[i]);
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

double *dvector(int i, int j) /* a[i]〜a[i+j]の領域を確保 */
{
  double *a;

  if ( (a=(double *)malloc( ((j-i+1)*sizeof(double))) ) == NULL )
  {
    printf("メモリが確保できません(from dvector) \n");
    exit(1);
  }  

  return(a-i);
}

void free_dvector(double *a, int i)
{
  free( (void *)(a + i) );  /* (void *)型へのキャストが必要 */
}


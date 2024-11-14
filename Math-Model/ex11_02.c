/*
 *ex11_02.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ベクトルの入力 */
void input_vector2( double *b, char c, int n, FILE *fin, FILE *fout);
/*  行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* ベクトル領域の確保 */
double *dvector(int i, int j);  
/* ベクトル領域の解放 */
void free_dvector(double *a, int i); 
/* 部分ピボット選択付きガウス消去法 */
double *gauss2( double **a, double *b, int n ); 
/* 最小2乗近似 */
void least_square( double *x, double *y, FILE *fout, int M, int N );

int main(void)
{
  FILE *fin, *fout;
  double *x, *y; 
  int M, N;
  char finame[]="ex11_02_input.dat";
  char foname[]="ex11_02_output.dat";
  
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
   
   //要素数 mと　n次多項式の入力
   fscanf(fin, "%d %d", &M, &N);
  
  /* ベクトルの領域確保 */
  x = dvector(1,M); /* x[1...M] */
  y = dvector(1,M); /* y[1...M] */

  input_vector2( x, 'x', M, fin, fout );    /* ベクトルxの入出力 */
  input_vector2( y, 'y', M, fin, fout );    /* ベクトルyの入出力 */

  least_square( x, y, fout, M, N );  /* 最小2乗近似 */

  fclose(fin); fclose(fout);  /* ファイルのクローズ */

  /* 領域の解放 */
  free_dvector( x, 1 );  free_dvector( y, 1 );

  return 0;
}

void least_square( double *x, double *y, FILE *fout, int M, int N )
{
  double *a, **p;
  int i, j, k;

  p = dmatrix(1, N+1, 1, N+1);  /* p[1...N+1][1...N+1] */
  a = dvector(1, N+1);          /* a[1...N+1] */

  /* 右辺ベクトルの作成 */
  for(i=1; i <= N+1; i++)
  {
    a[i]=0.0;
    for( j = 1; j <= M; j++)
    {
      a[i] +=  y[j]*pow(x[j],(double)(i-1)) ;
    }
  }

  /* 係数行列の作成 */
  for( i = 1; i <= N+1; i++)
  {
    for( j = 1; j <= i;  j++ )
    {
      p[i][j]=0.0;
      for( k =1; k <= M; k++)
      {
        p[i][j] += pow( x[k], (double)(i+j-2) );
      }
      p[j][i] = p[i][j];
    } 
}
  /* 連立1次方程式を解く. 結果はaに上書き */
   a = gauss2( p, a, N+1 );            

  /* 結果の出力 */
  fprintf( fout, "最小2乗近似式はy=\n");
  for( i = N+1 ; i >= 1 ; i--)
  {
    fprintf(fout, "+ %5.2f x^%d ", a[i],i-1);
  }
  fprintf(fout, "\n"); 

  /* 領域の解放 */
 free_dmatrix( p, 1, N+1, 1, N+1 ); free_dvector( a, 1 );  
}

/* 部分ピボット選択付きガウス消去法 */
double *gauss2( double **a, double *b, int n )
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

/* b[1...n]の入力 */
void input_vector2( double *b, char c, int n, FILE *fin, FILE *fout)
{
  int i;

  fprintf( fout, "ベクトル%cは次の通りです\n", c);
  for( i = 1 ; i <= n ; i++)
  {
    fscanf(fin, "%lf", &b[i]);
    fprintf(fout, "%5.2f\t", b[i]);
  }
  fprintf( fout, "\n");
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

/* ベクトルa[m...n]とb[m...n]の内積を計算する */
double inner_product( int m, int n, double *a, double *b)
{
  int i;
  double s = 0.0; 

  for( i = m; i <= n; i++) s += a[i]*b[i];

  return s ;
}

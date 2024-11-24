/*
 *ex13_03.c 15822108 IT HOTTA DAICHI
 */
/********************************************************************/
/* Householder - QR法で行列の固有値と固有ベクトルを求めるプログラム */
/* eigen_jacobi.c written by Kazuhiko Sumi on June 30 2012          */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define EPS pow(10.0, -15.0)
#define N 1000

/* 行列の入力 */
double **input_dmatrix( FILE *fin, int *n );
/* 行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* 行列の表示 */
void print_dmatrix( double **a, int r1, int r2, int l1, int l2, FILE *fout );
/* ベクトル領域の確保 */
double *dvector(int i, int j);  
/* ベクトル領域の解放 */
void free_dvector(double *a, int i); 
/* ハウスホルダー法 */
void householder( double **a, int n );
/* qr法 */
void qr( double **a, double eps, int n );
/* LU分解 */
void lu_decomp( double **a, int *p, int n );
/* LU分解を利用して連立1次方程式を解く */
double *lu_solve( double **a, double *b, int *p, int n );
/* ベクトルa[m...n]とb[m...n]の内積を計算する */
double inner_product( int m, int n, double *a, double *b);
/* 逆反復法 */
void inverse_iteration( double **ao, double **a, double eps, int n );

int main( int argc, char* argv[] )
{
  FILE *fin, *fout;
  double **a, **ao, eps=pow(10.0,-8.0);
  int i, j, n;

  /* ファイルのオープン */
  if ( argc != 3 ) {
      fprintf(stderr, "usage: %s input_data_file output_data_file\n", argv[0] );
      return(1);
  }
  if (( fin = fopen( argv[1], "r")) == NULL ) {
    fprintf(stderr, "%s: cannot open input file %s\n", argv[0], argv[1]);
    return(1);
  }
  if(( fout = fopen( argv[2], "w")) == NULL ) {
    fprintf(stderr, "%s: cannot open output file %s\n", argv[0], argv[2]);
    return(1);
  }

  a = input_dmatrix( fin, &n );    /* 行列Aの入出力 */  
  if ( n == 0 || a == (double**)NULL ){
    fprintf( stderr, "%s: fail to read input matrix\n", argv[0] );
    return(1);
  }
  ao = dmatrix( 1, n, 1, n ); /* 行列領域の確保(行列保存用) */
  for( i = 1; i <= n; i++){   /* 行列のコピー */
    for( j = 1; j <= n; j++)
      ao[i][j] = a[i][j]; 
  }

  householder( a, n );                 /* ハウスホルダー法 */
  qr( a, eps, n );                     /* QR法 */

  fprintf( fout, "Eigen values\n" );
  for( i = 1; i <= n; i++ ) fprintf( fout, "%10.7f\t", a[i][i] ); 
  fprintf( fout, "\n" );

  inverse_iteration( ao, a, eps, n );     /* 逆反復法 */
  fprintf( fout, "Eigen Vectors\n");
  for ( i = 1; i <= n; i++) {
    fprintf( fout, "["); 
    for( j = 1; j <= n; j++) { 
      fprintf( fout, "%10.7f\t", a[j][i]); 
    }
    fprintf( fout, "]\n" );
  }

  /* 領域の解放 */
  free_dmatrix( a, 1, n, 1, n ); free_dmatrix( ao, 1, n, 1, n );

  /* ファイルのクローズ */
  fclose(fin); fclose(fout);

  return 0;
}

/* 逆反復法 */
void inverse_iteration( double **ao, double **a, double eps, int n )
{
  int i, j, k, *p;    /* p[1...n-1]を利用, p[0]は未使用 */
  double v2, v2s, *v, *y, **lu, lambda, mu=0.0, muo;

  if (( p = (int*)malloc( n * sizeof(int))) == (int*)NULL ) {
    fprintf(stderr,"inverse_iteration: fail to allocate %d words\n", n );
    exit(1);
  }
  v = dvector( 1, n ); y = dvector( 1, n );  /* ベクトル領域の確保 */
  lu = dmatrix( 1, n, 1, n );

  for ( i = 1; i <= n; i++)
  { 
    lambda = a[i][i];  /* 近似固有値の代入 */
    for( j = 1; j <= n; j++) y[j] = 0.0; y[i] = 1.0; /* 初期値設定 */

    /* 行列の作成およびLU分解 */
    for ( k = 1; k <= n; k++)
    {
      for ( j = 1; j <= n; j++ ) lu[k][j] = ao[k][j];
      lu[k][k] = ao[k][k] - lambda;
    }    
    lu_decomp( lu, p, n ); /* LU分解 */

    /* 逆反復法 */
    do
    {
      muo = mu;
      for ( j = 1; j <= n; j++ ) v[j] = y[j]; 
      v = lu_solve( lu, v, p, n );  /* 固有ベクトルの計算 */     
      mu = inner_product( 1, n, v, y );  /* 補正 */
      v2 = inner_product( 1, n, v, v );
      v2s = sqrt(v2);
      for( j = 1; j <= n ; j++) y[j]=v[j]/v2s;
    }while( fabs((mu-muo)/mu) >= eps );  

    /* 結果の代入(固有ベクトルはaのi列に) */
    for ( j = 1; j <= n; j++ ) a[j][i] = y[j];      
  }

  free_dvector( v, 1 ); free_dvector( y, 1 ); free_dmatrix( lu, 1, n, 1, n );
  free( p );
}

/* QR法 */
void qr( double **a, double eps, int n )
{
  int i, j, k, m;
  double **q, *work, r, s, sint, cost, tmp;

  /* 領域の確保 */
  q = dmatrix( 1, n, 1, n ); work = dvector( 1, n );

  m = n; 
  while ( m > 1 )
  {
    /* 収束判定 */
    if ( fabs(a[m][m-1]) < eps ) 
    {
      m = m - 1; continue;
    }
    
    /* 原点移動 */
    s = a[n][n];
    if ( m == n ) s = 0.0;   /* m=nのときは原点移動なし */
    for ( i = 1; i <= m; i++) a[i][i] -= s ;

    /* QR法 */
     
    for ( i = 1; i <= m; i++)
    {
      for( j = 1; j <= m; j++ )
      {
        q[i][j] = 0.0;         /* Qを m x m単位行列で初期化 */
      }
      q[i][i] = 1.0;
    }

    /* RとQの計算 */ 
    for ( i = 1; i <= m-1; i++)
    {
      r = sqrt( a[i][i]*a[i][i] + a[i+1][i]*a[i+1][i] );
      if ( r == 0.0 )
      {
        sint = 0.0; cost = 0.0;
      }
      else
      {
        sint = a[i+1][i]/r; cost = a[i][i]/r; 
      }
      for ( j = i+1; j <= m; j++)
      {
        tmp = a[i][j]*cost + a[i+1][j]*sint;
        a[i+1][j] = -a[i][j]*sint + a[i+1][j]*cost;
        a[i][j] = tmp;
      }
      a[i+1][i] = 0.0;
      a[i][i] = r; 
      for ( j = 1;  j <= m; j++ )
      {                          /* QはPの転置 */
        tmp = q[j][i]*cost + q[j][i+1]*sint;
        q[j][i+1] = -q[j][i]*sint + q[j][i+1]*cost;
        q[j][i] = tmp;
      }
    }

    /* RQの計算 */
    for ( i = 1; i <= m; i++)
    {
      for ( j = i; j <= m ; j++ ) work[j] = a[i][j];
      for ( j = 1; j <= m ; j++ ) 
      {
        tmp = 0.0;
        for( k = i; k <= m; k++ ) tmp += work[k]*q[k][j];
        a[i][j] = tmp;
      }
    }

    /* 原点移動後の処理 */
    for ( i = 1; i <= m; i++ ) a[i][i] = a[i][i] + s;
  }
  
  /* 領域の解放 */
  free_dmatrix( q, 1, n, 1, n ); free_dvector( work, 1 );
}

/* ハウスホルダー法 */
void householder( double **a, int n )
{
  int i, j, k;                  
  double *u, *f, *g, gamma, s, ss, uu; 

  /* ベクトル領域の確保 */
  u = dvector( 1, n ); f = dvector( 1, n ); g = dvector( 1, n );               

  for ( k = 1; k <= n-2; k++)
  { 
    /* vの計算 */
    for ( i = 1; i <= k; i++) u[i] = 0.0;
    for ( i = k+1; i <= n; i++) u[i] = a[i][k];

    /* sの計算 */
    ss = 0.0;
    for ( i = k+2; i <= n; i++ ) ss += u[i]*u[i];
    if ( fabs(ss) < EPS ) continue; /* 消去が必要ない場合の処理 */
    s = sqrt( ss + u[k+1]*u[k+1] );
    if ( u[k+1] > 0.0 ) s = -s;

    /* uの計算 */
    u[k+1] -= s; 
    uu = sqrt( ss + u[k+1]*u[k+1] );
    for ( i = k+1; i <= n; i++) u[i] /= uu;

    /* f, gの計算 */
    for ( i = 1; i <= n; i++)
    {
      f[i] = 0.0; g[i] = 0.0;
      for ( j = k+1; j <= n; j++ )
      {
        f[i] += a[i][j]*u[j];
        g[i] += a[j][i]*u[j];
      }
    }

    /* gammaの計算 */
    gamma = 0.0;
    for ( j = 1; j <= n; j++) gamma += u[j]*g[j];

    /* f, gの計算 */
    for ( i = 1; i <= n; i++) 
    {
      f[i] -=  gamma * u[i];
      g[i] -=  gamma * u[i];
    }

    /* Aの計算 */
    for ( i = 1; i <= n; i++)
    {
      for ( j = 1; j <= n; j++ )
      {
        a[i][j] = a[i][j] - 2.0*u[i]*g[j] - 2.0*f[i]*u[j];
      }
    }

  }

  /* ベクトル領域の解放 */
  free_dvector( u, 1 ); free_dvector( f, 1 ); free_dvector( g, 1 ); 
}

#define LBUFSIZE 1024

double** input_dmatrix( FILE *fin, int *n )
{
  int i, j;
  char buf[LBUFSIZE];
  char *ch, *s ;
  double **a ;

  /* 最初の行には、行列のサイズが書いてあると仮定 */
  if ( fgets( buf, LBUFSIZE, fin ) == (char*)NULL ){
    fprintf(stderr,"input_matrix: nothing can be read\n");
    return(0);
  }
  sscanf( buf, "%d", n );
  if ( *n < 2 || *n > N ) {
    fprintf(stderr, "input_matrix: matrix size %d should be 1 < n < %d\n",
	    *n, N );
    return(0);
  }

  a = dmatrix( 1, *n, 1, *n ); /* *n x *n 行列を確保 */

  /* 一行には、行列の１行分のデータが空白で区切られて書いてあると仮定 */
  for( i = 1 ; i <= *n ; i++ ) {
    if ( fgets( buf, LBUFSIZE, fin ) == (char*)NULL ) {
      fprintf(stderr, "input_matrix: not enough line at %d\n", i );
      free_dmatrix( a, 1, *n, 1, *n );
      return(0);
    }
    ch = buf ;
    for ( j = 1; j <= *n; j++ ) {
      s = ch ;
      if ( *s == '\0' ){
	fprintf(stderr, 
		"input_matrix: not enough digits in line %d at %d of %s\n", 
		i, j, buf );
	free_dmatrix( a, 1, *n, 1, *n );
	return(0);
      }
      /* 最初の空白は読み飛ばす */
      while ( *ch != '\0' &&  isspace(*ch) ) ch++ ;
      /* 次に見つかった空白までが数値と仮定する */
      while ( *ch != '\0' && !isspace(*ch) ) ch++ ;
      /* 空白を終了文字 '\0' に置き換え */
      *ch ++ = '\0';
      a[i][j] = atof(s); /* 数字として解釈する */
    }
  }
  return(a);
}

char *format = "%10.6f";

void print_dmatrix( double **a, int nr1, int nr2, int nl1, int nl2, FILE *fout )
{
  int i, j;
  extern char *format;

  for ( i = nr1; i <= nr2; i++ ) {
    for ( j = nl1; j <= nl2 ; j++ ) {
      fprintf( fout, format, a[i][j] );
    }
    fprintf( fout, "\n" );
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
    fprintf( stderr, "メモリが確保できません(行列a)\n");
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
    fprintf( stderr, "メモリが確保できません(from dvector) \n");
    exit(1);
  }  

  return(a-i);
}

void free_dvector(double *a, int i)
{
  free( (void *)(a + i) );  /* (void *)型へのキャストが必要 */
}


/* 行列a[1...N][1...N]とベクトルb[1...N]との積 c <- Ab */
void matrix_vector_product(double **a, double *b , double *c)
{
  double wk;
  int i, j;

  for ( i = 1; i <= N; i++)
  {
    wk = 0.0;
    for ( j = 1; j <= N; j++ )
    {
      wk += a[i][j]*b[j];
    }
    c[i] = wk;
  }
}


/* ベクトルa[m...n]とb[m...n]の内積を計算する */
double inner_product( int m, int n, double *a, double *b)
{
  int i;
  double s = 0.0; 

  for( i = m; i <= n; i++) s += a[i]*b[i];

  return s ;
}


void lu_decomp( double **a, int *p, int n )
{
  int i, j, k, ip;
  double alpha, tmp;
  double amax, eps = pow(2.0, -50.0); /* eps = 2^{-50}とする */

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
    if ( amax < eps ) fprintf( stderr, "入力した行列は正則ではない!!\n");
    /* ipを配列pに保存 */
    p[k]=ip;
    /* 行交換 */
    if ( ip != k)
    {
      for( j = k; j <= n; j++)
      {
        tmp = a[k][j]; a[k][j]=a[ip][j]; a[ip][j]=tmp;
      }
    }
      /* 前進消去 */
    for( i = k+1; i <= n; i++)
    {
      alpha = - a[i][k]/a[k][k];
      a[i][k] = alpha;
      for( j = k+1; j <= n; j++)
      {
        a[i][j] = a[i][j] + alpha * a[k][j];
      }
    }
  }
}

double *lu_solve( double **a, double *b, int *p, int n )
{
  int i, j, k;
  double tmp;

  /* 右辺の行交換 */
  for( k = 1; k <= n-1; k++)
  {
    tmp=b[k]; b[k]=b[p[k]]; b[p[k]]=tmp;
    /* 前進代入 */
    for( i=k+1; i <= n; i++)
    {
      b[i] = b[i] + a[i][k]*b[k];
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

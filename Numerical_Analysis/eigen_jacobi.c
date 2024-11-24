/*
 *ex13_02.c 15822108 ���e�N�m���W�[ �x�c��q
 */
/**************************************************************/
/* ���R�r�@�ōs��̌ŗL�l�ƌŗL�x�N�g�������߂�v���O����     */
/* eigen_jacobi.c written by Kazuhiko Sumi on June 26 2011    */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define  N 1000
#define  ITMAX 1500

/* �s��̓��� */
double **input_dmatrix( FILE *fin, int *n );
/* �s��̕\�� */
void print_dmatrix( double **a, int r1, int r2, int l1, int l2, FILE *fout );
/* �s��̗̈�m�� */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* �s��̗̈��� */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* �x�N�g���̈�̊m�� */
double *dvector(int i, int j);  
/* �x�N�g���̈�̉�� */
void free_dvector(double *a, int i); 
/* ���R�r�@ */
void jacobi_method( int n, double **a, double **r, FILE *fout);  

int main(int argc, char *argv[] )
{
  double  **a, **r; 
  FILE *fin, *fout;
  int n;

  /* �t�@�C���̃I�[�v�� */
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

  /* a[][]:���͍s��i�����l�j���@�ŗL�l�Ίp�s��i�������ʁj,
     r[][]:�P�ʍs��i�����l�j���@�ŗL�x�N�g���i�������ʁj  */
  a = input_dmatrix( fin, &n );            /*  �s��A�̓��� */  
  if ( n == 0 || a == (double**)NULL ){
    fprintf( stderr, "%s: fail to read input matrix\n", argv[0] );
    return(1);
  }
  r = dmatrix( 1, n, 1, n );  /* �ŗL�x�N�g���s�� R �̊m��  */
  fprintf( fout, "%s: input matrix A\n", argv[0] );
  print_dmatrix( a, 1, n, 1, n, fout ) ; /* ���͍s�� A ���o�� */

  jacobi_method( n, a, r, fout );   /* Jacobi �@�ŌŗL�x�N�g�������߂� */ 

  { /* �������ʂ̏o�� */
    int i;
    fprintf( fout, "%s: eigen values\n", argv[0] );
    for( i = 1; i <= n; i++ ) fprintf( fout, "%f\n", a[i][i]);
    fprintf( fout, "%s: engen vectors\n", argv[0]);
    print_dmatrix( r, 1, n, 1, n, fout );
  }
      
  /* �t�@�C���̃N���[�Y */
  fclose(fin);
  fclose(fout);
  /* �̈�̉�� */
  free_dmatrix( a, 1, n, 1, n );
  free_dmatrix( r, 1, n, 1, n );
  return(0);
}

void jacobi_method( int n, double** a, double**r, FILE *fout )
{
  int m,k; /* index of rotated elements */
  int it;  /* iteration counter */
  int i,j;

  double s; /* the maximum element */
  double eps = 1.0E-10;
  double t, u;
  double *a_row_k, *a_row_m, *a_col_k, *a_col_m;
  double xkk, xkm, xmk, xmm, cos_t, sin_t;

  a_row_m = dvector(1, n);
  a_row_k = dvector(1, n);
  a_col_m = dvector(1, n);
  a_col_k = dvector(1, n);

  /* initialize eigenvalues x and eigenvector R */
  for(i=1; i<=n; i++){
    for(j=1; j<=n; j++){
      r[i][j] = 0.0;
    }
    r[i][i] = 1.0;
  }

  /* repeat until all no diagonal elements are zero */
  for(it=1; it<=ITMAX; it++){
    /* check ending condition (whether A*x is zero or not),
       and find the maximum element a[m][k] */
    s = eps;
    for(i=1; i<=n; i++){ 
      for(j=i+1; j<=n; j++){
	if ( fabs( a[i][j] ) > s ){
	  s = fabs( a[i][j] ), k = i, m = j;
	}
      }
    }
    if ( s == eps ) {
      if ( fout ) 
	fprintf( fout, "jacobi: finished after %d cycles s=%f\n", it, a[k][m] );
      return ;
    }
    else if ( fout )
      fprintf( fout, 
	       "jacobi: cycle %d, found non-orthogonral max a[%d][%d]=%f\n", 
	       it, k, m, s );

    /* calcurate rotation parameter t(theta), cos(t), and sin(t) */
    if ( fabs( a[k][k] - a[m][m] ) < eps ) { /* theta is PI */
      cos_t = 1/sqrt(2.0); 
      sin_t = a[k][m] > 0.0 ? 1.0/sqrt(2.0) : -1.0/sqrt(2.0);
    }
    else {
      t = ( 2.0 * a[k][m] )/( a[k][k] - a[m][m] );
      u = sqrt( 1.0 + t * t );
      cos_t = sqrt(( 1.0 + u)/(2.0 * u)) ;
      sin_t = sqrt((-1.0 + u)/(2.0 * u)) * ( t > 0.0 ? 1.0 : -1.0 ) ;
    }
    if ( fout )
      fprintf( fout, "jacobi: cos_t=%f, sin_t=%f\n", cos_t, sin_t );
    
    /* apply R'*A*R */
    for ( j = 1; j <= n; j++ ){
      a_row_k[j] =        a[k][j] * cos_t + a[m][j] * sin_t;
      a_row_m[j] = -1.0 * a[k][j] * sin_t + a[m][j] * cos_t;
    }
    for ( i = 1; i <= n; i++ ){
      a_col_k[i] =        a[i][k] * cos_t + a[i][m] * sin_t;
      a_col_m[i] = -1.0 * a[i][k] * sin_t + a[i][m] * cos_t;
    }
    a_col_k[k] = a[k][k] * cos_t * cos_t 
      + a[k][m] * cos_t * sin_t 
      + a[m][k] * cos_t * sin_t 
      + a[m][m] * sin_t * sin_t;
    a_col_m[m] = a[k][k] * sin_t * sin_t 
      - a[m][k] * cos_t * sin_t 
      - a[k][m] * cos_t * sin_t 
      + a[m][m] * cos_t * cos_t;
    a_col_k[m] = 0.0;
    a_col_m[k] = 0.0;
    for ( j = 1; j <= n; j++ ){
      a[k][j] = a_row_k[j];
      a[m][j] = a_row_m[j];
    }
    for ( i = 1; i <= n; i++ ){
      a[i][k] = a_col_k[i];
      a[i][m] = a_col_m[i];
    }
    if ( fout ) {
      fprintf( fout, "jacobi: A(%d)\n", it );
      print_dmatrix( a, 1, n, 1, n, fout );
    }

    /* apply X*R */
    for ( i = 1; i <= n; i++ ){
      a_col_k[i] =        r[i][k] * cos_t + r[i][m] * sin_t ;
      a_col_m[i] = -1.0 * r[i][k] * sin_t + r[i][m] * cos_t ;
    }
    for ( i = 1; i <= n; i++ ){
      r[i][k] = a_col_k[i] ;
      r[i][m] = a_col_m[i] ;
    }

    if ( fout ) {
      fprintf( fout, "jacobi: R(%d)\n", it );
      print_dmatrix( r, 1, n, 1, n, fout );
    }
  }

  free_dvector( a_row_m, 1 );
  free_dvector( a_row_k, 1 );
  free_dvector( a_col_m, 1 );
  free_dvector( a_col_k, 1 );
}

#define LBUFSIZE 1024

double** input_dmatrix( FILE *fin, int *n )
{
  int i, j;
  char buf[LBUFSIZE];
  char *ch, *s ;
  double **a ;

  /* �ŏ��̍s�ɂ́A�s��̃T�C�Y�������Ă���Ɖ��� */
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

  a = dmatrix( 1, *n, 1, *n ); /* *n x *n �s����m�� */

  /* ��s�ɂ́A�s��̂P�s���̃f�[�^���󔒂ŋ�؂��ď����Ă���Ɖ��� */
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
      /* �ŏ��̋󔒂͓ǂݔ�΂� */
      while ( *ch != '\0' &&  isspace(*ch) ) ch++ ;
      /* ���Ɍ��������󔒂܂ł����l�Ɖ��肷�� */
      while ( *ch != '\0' && !isspace(*ch) ) ch++ ;
      /* �󔒂��I������ '\0' �ɒu������ */
      *ch ++ = '\0';
      a[i][j] = atof(s); /* �����Ƃ��ĉ��߂��� */
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
  int i, nrow, ncol, s; 
  double **a; 

  nrow = nr2 - nr1 + 1 ; /* �s�̐� */
  ncol = nl2 - nl1 + 1 ; /* ��̐� */

  /* �s�̊m�� */
  s = nrow * sizeof(double*);
  if (( a=(double**)malloc( s )) == (double**)NULL ){
    fprintf(stderr, "dmatrix: cannot allocate index memory (%d)\n", nrow);
    exit(1);
  }
  a = a - nr1; /* �s�����炷 */
  /* ��̊m�� */
  s = ncol * sizeof(double);
  for( i=nr1; i<=nr2; i++) {
    if (( a[i] = (double *)malloc( s )) == (double*)NULL ){
      fprintf(stderr,"dmatrix: cannot allocate data memory (%dx%d)\n", 
	      nrow, ncol);
      exit(1); 
    }
  }
  for( i=nr1; i<=nr2; i++) a[i] = a[i]-nl1;             /* ������炷 */
  return(a);
}

void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2)
{
  int i;

  /* �������̉��  */
  for ( i = nr1 ; i <= nr2 ; i++) free((void *)(a[i]+nl1));
  free((void *)(a+nr1));
}

double *dvector(int i, int j) /* a[i]�`a[i+j]�̗̈���m�� */
{
  double *a;
  int s = j-1+1;
  if (( a = (double *)malloc( s * sizeof(double))) == NULL )
  {
    fprintf(stderr,"dvector: cannot allocate memory %d\n", s );
    exit(1);
  }  
  return(a-i);
}

void free_dvector(double *a, int i)
{
  free( (void *)(a + i) );  /* (void *)�^�ւ̃L���X�g���K�v */
}

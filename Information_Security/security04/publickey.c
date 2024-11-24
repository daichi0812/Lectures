/*
15822108 堀田大智
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int binary_mod(int a, int b, int n){
    int ans = 1;
    int tmp = a;

    while(1){
        if(b == 0){
            break;
        }
        else if(b % 2 == 1){
            ans = (ans * tmp) % n;
        }
        
        b = b / 2;
        tmp = (tmp * tmp) & n;
    }

    return ans;
}

int gcd1(int a, int b){
  int c = 0;

  if (b <= 0){
    return (-1);
  }

  while (b != 0){
    c = a % b;
    a = b;
    b = c;
  }

  return a;
}

int gcd2(int a, int b, int *x, int *y){
  int q, r0, r1, r2, x0, x1, x2, y0, y1, y2;

  if (a < b){
    int c;
    c = a;
    a = b;
    b = c;
  }

  if (b <= 0){
    return (-1);
  }
  
  r0 = a;
  r1 = b;
  x0 = 1;
  x1 = 0;
  y0 = 0;
  y1 = 1;
  q = 0;
  r2 = 0;
  x2 = 0;
  y2 = 0;

  while (r1 > 0){
    q = floor(r0 / r1);
    r2 = r0 % r1;
    x2 = x0 - q * x1;
    y2 = y0 - q * y1;
    r0 = r1;
    r1 = r2;
    x0 = x1;
    x1 = x2;
    y0 = y1;
    y1 = y2;
  }

  *x = x0;
  *y = y0;
}

int main(int argc, char *argv[]){
  int p, q, l, n, e, d, m, c, i, x, y;
  int e_list[256], ne;
  double r;

  srand((unsigned int)time(NULL));

  if (argc != 4){
    fprintf(stderr, "Usage: %s prime_number_1 prime_number_2 message_number\n", argv[0]);

    return (1);
  }

  p = atoi(argv[1]);
  q = atoi(argv[2]);
  m = atoi(argv[3]);

  // p, q は自然数
  if (p <= 0 || q <= 0){
    fprintf(stderr,
            "%s: number1(%d) and number2(%d) must be prime numbers\n",
            p, q);

    return (1);
  }

  do{
    n = p * q;
    l = (p - 1) * (q - 1);

    ne = 1;
    e = 1;

    while (1){
      if (ne == 255)
        break;

      e++;
      if (gcd1(l, e) == 1)
      {
        e_list[ne - 1] = e;
        ne++;
      }
    }

    e = e_list[(int)((rand() / (double)RAND_MAX) * ne)] % l;

    printf("p = %d, q = %d --> e = %d\n", p, q, e);
    gcd2(l, e, &x, &y);
    printf("extended gcd(%d,%d) = %d * %d + %d * %d = %d\n", l, e, l, x, e, y, l * x + e * y);

    if (y < 0)
      d = y + l;
    else
      d = y;

  } while (d == e); 

  printf("pubclic key is (%d,%d), private key is %d\n", n, e, d);

  c = binary_mod(m, e, n);

  printf("input message is %d, crypted message is %d\n", m, c);

  y = binary_mod(c, d, n);

  printf("decrypted message is %d\n", y);

  return (0);
}
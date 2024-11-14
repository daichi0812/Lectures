/*
 * 15822108
 * ほった だいち
 * 堀田 大智
 */
/* Very simple grammar  */

%{
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double real;
    double imag;
} Complex;

#define YYSTYPE Complex

#define YYDEBUG 0

int yylex (void);
void yyerror (char const *);
%}

%token NUM IMAGINARY PLUS HYPHEN ASTERISK SLASH
%token SEMICOLON OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET COMMA IMAGINARYUNIT

%%

statement_list:     statement {}
        |    statement statement_list {}
;

statement: exp SEMICOLON   { 
                if($1.imag == 0){
                    printf("Result is %g\n", $1.real); 
                }else if($1.real == 0 && $1.imag == 1){
                    printf("Result is i\n"); 
                }else if($1.real == 0){
                    printf("Result is %gi\n", $1.imag); 
                }else if($1.imag > 0){
                    printf("Result is %g+%gi\n", $1.real, $1.imag); 
                }else{
                    printf("Result is %g%gi\n", $1.real, $1.imag);
                }
            }
        |   error SEMICOLON { yyerror("Statement Error!"); yyerrok; }
;

exp:    exp PLUS term { $$.real = $1.real + $3.real; $$.imag = $1.imag + $3.imag; }
    |   exp HYPHEN term { $$.real = $1.real - $3.real; $$.imag = $1.imag - $3.imag; }
    |   term { $$ = $1; }
;

term:   term ASTERISK factor {
            $$.real = $1.real * $3.real - $1.imag * $3.imag;
            $$.imag = $1.real * $3.imag + $1.imag * $3.real;
        } 
    |   term SLASH factor {
            double denom = $3.real * $3.real + $3.imag * $3.imag;
            $$.real = ($1.real * $3.real + $1.imag * $3.imag) / denom;
            $$.imag = ($1.imag * $3.real - $1.real * $3.imag) / denom;
        } 
    |   factor { $$ = $1; }
;

factor: NUM { $$.real = $1.real; $$.imag = 0; }
      | IMAGINARY { $$.real = 0; $$.imag = $1.real; }
      | OPENPAREN exp CLOSEPAREN { $$ = $2; }
      | OPENBRACKET exp COMMA exp CLOSEBRACKET { if($2.imag || $4.imag) { YYERROR; } $$.real = $2.real; $$.imag = $4.real; }
      | OPENBRACKET exp COMMA exp CLOSEBRACKET NUM { $$.real = $2.real * $6.real; $$.imag = $4.real * $6.real; }
      | OPENBRACKET exp COMMA exp CLOSEBRACKET IMAGINARY { $$.real = -($4.real * $6.real); $$.imag = $2.real * $6.real; }
      | OPENBRACKET exp COMMA exp CLOSEBRACKET IMAGINARYUNIT { $$.real = -$4.real; $$.imag = $2.real; }
      | HYPHEN factor { $$.real = -$2.real; $$.imag = -$2.imag; }
      | IMAGINARYUNIT { $$.real = 0; $$.imag = 1; }
;

%%

int main (void)
{
#if YYDEBUG != 0
    yydebug = YYDEBUG; /* for debugging */
#endif
    return yyparse();
}

void yyerror (char const *s)
{
    fprintf(stderr, "%s\n", s);
}
/*
 * 15822108
 * ほった だいち
 * 堀田 大智
 */
/*
 * flex
 */

%{
#define YYSTYPE double
#include "complex.tab.h"
#undef yywrap
#define yywrap() 1
%}
%option noyywrap
%%

(\.)?[0-9]+(\.[0-9]*)?([eE][-+]?[0-9]+)? {
            yylval = atof(yytext);
            return NUM;
        }
(\.)?[0-9]+(\.[0-9]*)?[(" ")*]?([eE][-+]?[0-9]+)?i {
    yylval = atof(yytext);
    return IMAGINARY;
}

"+"     return PLUS;

"-"     return HYPHEN;

"*"     return ASTERISK;

"/"     return SLASH;

";"     return SEMICOLON;

"("     return OPENPAREN;

")"     return CLOSEPAREN;

"["     return OPENBRACKET;

"]"     return CLOSEBRACKET;

","     return COMMA;

"i"     return IMAGINARYUNIT;

[ \t\r\n]    ;

%%
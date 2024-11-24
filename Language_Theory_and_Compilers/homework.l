/*
 15822108
 堀田大智
 ほっただいち
 */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*アンダーバーを除外する*/
int yytextToNumber(char* text, int base)
{
    char c, *from = text, *to = text;

    while (c = (*to++=*from++))  // remove '_'
        if (c=='_')
            to--;
    return strtol(text, NULL, base);
}
    
%}

%%
"BEGIN"|"class"|"ensure"|"nil"|"self"|"when"|"END"|"def"|"false"|"not"|"super"|"while"|"alias"|"defined?"|"for"|"or"|"then"|"yield"|"and"|"do"|"id"|"redo"|"true"|"__LINE__"|"begin"|"else"|"in"|"rescure"|"undef"|"__FILE__"|"break"|"elsif"|"module"|"retry"|"unless"|"__ENCODING__"|"case"|"end"|"next"|"return"|"until"                               {printf("Keywords: %s\n", yytext);}
@[a-zA-Z_][a-zA-Z0-9_]*                      {printf("Instance variable: %s\n", yytext);}
@@[a-zA-Z_][a-zA-Z0-9_]*                     {printf("Class variable: %s\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]*[!?=]                  {printf("Mehod: %s\n", yytext);}
[a-z_][a-zA-Z0-9_]*                          {printf("Method or variable: %s\n", yytext);}
"$"[a-zA-Z0-9_]*                             {printf("Global variable: %s\n", yytext);}
[A-Z][a-zA-Z0-9_]*                           {printf("Constant: %s\n", yytext);}

[1-9][0-9_]*|0[dD][1-9][0-9_]                {printf("Decimal Integer: %d\n", yytextToNumber(yytext, 10));}
0[0-7][0-7_]*                                {printf("Octal Integer: %d\n", yytextToNumber(yytext, 8));}
0[xX][0-9a-fA-F][0-9a-fA-F_]*                {printf("Hex Integer: %d\n", yytextToNumber(yytext, 16));}
0[bB][01][01_]*                              {printf("Binary Integer: %d\n", yytextToNumber(yytext, 2));}

["+""-""*""/""%""(**)"]+                     {printf("Arithmetic Operators: %s\n", yytext);}
[(==)(!=)<>(<=)(>=)]+                        {printf("Comparison Operators: %s\n", yytext);}

[0-9][0-9_]*"."[0-9]+                        {printf("Floating Point Number: %s\n", yytext);}

"#".*                                        {printf("Comment: %s\n", yytext);}
[ \t]+
[\n]
.                                            {printf("Error: '%s'\n", yytext);}
    
%%
    int main(void)
    {
        yylex();
        
    }
    
    int yywrap () { return 1; }

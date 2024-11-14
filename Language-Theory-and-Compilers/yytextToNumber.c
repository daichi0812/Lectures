#include <stdlib.h>

/* Convert numbers with underscores to decimal notation */
/* examples of how to call:
 *     yytextToNumber(yytext, 8);  // for octal numbers
 *     yytextToNumber(yytext, 16); // for hexadecimal numbers
 */
int yytextToNumber(char* text, int base)
{
    char c, *from = text, *to = text;

    while (c = (*to++=*from++))  // remove '_'
        if (c=='_')
            to--;
    return strtol(text, NULL, base);
}

/*
    15822108
    ほっただいち
    堀田大智
*/
/* parser for simple expressions */
/* Grammar:
   Statement -> Expression ';'
   Expression -> Expression '+' Term
              | Expression '-' Term
              | Term
   Term -> Element
        | Term '*' Element
        | Term '/' Element
   Element -> Primary
           | Element '&' Primary
           | Element '|' Primary
   Primary -> '(' Expression ')'
            | '~' Primary
            | number
*/

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

token nextToken;

int Statement();  // forward declarations
int Expression(); // (also needed for
int Term();       //  mutual recursion)
int Element();
int Primary();

int main()
{
    initScanner();
    nextToken = getNextToken(); // get first token
    Statement();

    return 0;
}

int Statement()
{
    int value = Expression();

    if (nextToken.type == semicolon)
    {
        printf("Result is %d\n", value);
        // semicolon is last token, so we do not need a next one,
        // but this needs to be uncommented if we have multiple statements
        // nextToken = getNextToken();
    }
    else
        printf("Error: Missing semicolon!\n"), exit(1);
}

int Expression()
{
    int r = Term();

    while (nextToken.type == plus || nextToken.type == hyphen)
    {
        if (nextToken.type == plus)
        {
            nextToken = getNextToken();
            r += Term();
        }
        else if (nextToken.type == hyphen)
        {
            nextToken = getNextToken();
            r -= Term();
        }
    }

    return r;
}

int Term()
{
    int r = Element();

    while (nextToken.type == asterisk || nextToken.type == slash)
    {
        if (nextToken.type == asterisk)
        {
            nextToken = getNextToken();
            r *= Element();
        }
        else if (nextToken.type == slash)
        {
            nextToken = getNextToken();
            int denominator = Element();
            if (denominator != 0)
                r /= denominator;
            else
            {
                printf("Error: Division by zero!\n");
                exit(1);
            }
        }
    }

    return r;
}

int Element()
{
    int r = Primary();

    while (nextToken.type == ampersand || nextToken.type == pipe)
    {
        if (nextToken.type == ampersand)
        {
            nextToken = getNextToken();
            r &= Primary();
        }
        else if (nextToken.type == pipe)
        {
            nextToken = getNextToken();
            r |= Primary();
        }
    }

    return r;
}

int Primary()
{
    int r;

    if (nextToken.type == openpar)
    {
        nextToken = getNextToken();
        r = Expression();
        if (nextToken.type == closepar)
        {
            nextToken = getNextToken();
        }
        else
        {
            printf("Error: Missing closing parenthesis!\n");
            exit(1);
        }
    }
    else if (nextToken.type == tilde)
    {
        nextToken = getNextToken();
        r = Primary();
        r = r ? 0 : 1;
    }
    else if (nextToken.type == number)
    {
        r = nextToken.val.iv;
        nextToken = getNextToken();
    }
    else
    {
        printf("Error: Number, '(' or '~' expected but not found!\n");
        exit(1);
    }

    return r;
}
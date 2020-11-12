/////////////////////////
// Keith Kirtfield
// CMSC 403
// Sept. 25, 2020
// Project 1
////////////////////////
//Parser.c Parser.c will implement a recursive decent parser based upon a
// provided EBNF grammar
#include "Parser.h"
// Token initialization
int currtok = 0;
//checks if it is valid IDENTIFIER or NUMBER as defined by the given EBNF
_Bool parseTerm(struct lexics *someLexics)
{
    //term  --> IDENTIFIER | NUMBER
    if (someLexics[currtok].token == IDENTIFIER || someLexics[currtok].token == NUMBER)
    {
        currtok++;
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}
// checks if it has valid syntax for expression as defined by the given EBNF
_Bool parseExpression(struct lexics *someLexics)
{
    _Bool code = FALSE;
    //expression    --> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
    if (someLexics[currtok].token == LEFT_PARENTHESIS)
    {
        currtok++;
        if (parseExpression(someLexics) && someLexics[currtok++].token == RIGHT_PARENTHESIS)
        {
            return (TRUE);
        }
    }
    if (parseTerm(someLexics))
    {
        if (someLexics[currtok].token == BINOP)
        {
            currtok++;
            if (parseTerm(someLexics))
            {
                code = TRUE;
            }
        }
        else
        {
            code = TRUE;
        }
    }
    return (code);
}

//checks if it has valid syntax while loop as defined by the given EBNF
_Bool parseWhileLoop(struct lexics *someLexics)
{
    //while-loop    --> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
    if (someLexics[currtok++].token == WHILE_KEYWORD && someLexics[currtok++].token == LEFT_PARENTHESIS)
    {
        if (parseExpression(someLexics) && someLexics[currtok++].token == RIGHT_PARENTHESIS)
        {
            return (parseStatement(someLexics));
        }
    }
    return (FALSE);
}

//checks if it has valid syntax for return as defined by the given EBNF
_Bool parseReturn(struct lexics *someLexics)
{
    //return    --> RETURN_KEYWORD expression EOL
    if (someLexics[currtok++].token == RETURN_KEYWORD)
    {
        if (parseExpression(someLexics) && someLexics[currtok++].token == EOL)
        {
            return (TRUE);
        }
    }
    return (FALSE);
}

// checks if it has valid syntax for assignment as defined by the given EBNF
_Bool parseAssigment(struct lexics *someLexics)
{
    // assignment   --> IDENTIFIER EQUAL expression EOL
    if (someLexics[currtok++].token == IDENTIFIER && someLexics[currtok++].token == EQUAL)
    {
        if (parseExpression(someLexics) && someLexics[currtok++].token == EOL)
        {
            return (TRUE);
        }
    }
    return (FALSE);
}

//checks if it has valid syntax for statement
//statement --> while-loop | return | assignment | body
_Bool parseStatement(struct lexics *someLexics)
{
    _Bool code;
    switch (someLexics[currtok].token)
    {

    case WHILE_KEYWORD:
        code = parseWhileLoop(someLexics);
        break;
    case RETURN_KEYWORD:
        code = parseReturn(someLexics);
        break;
    case IDENTIFIER:
        code = parseAssigment(someLexics);
        break;
    case LEFT_BRACKET:
        code = parseBody(someLexics);
        break;
    default:
        code = FALSE;
    }
    return (code);
}

//checks if it has valid syntax for statement-list as defined by the given EBNF
//statement-list    --> statement {statement}
_Bool parseStatementList(struct lexics *someLexics)
{
    while (someLexics[currtok].token == WHILE_KEYWORD ||
           someLexics[currtok].token == RETURN_KEYWORD ||
           someLexics[currtok].token == IDENTIFIER ||
           someLexics[currtok].token == LEFT_BRACKET)
    {

        if (!parseStatement(someLexics))
        {
            return (FALSE);
        }
    }
    return (TRUE);
}

//checks if it has valid syntax for body as defined by the given EBNF
//body  --> LEFT_BRACKET [statement-list] RIGHT_BRACKET
_Bool parseBody(struct lexics *someLexics)
{
    if ((someLexics[currtok++].token == LEFT_BRACKET))
    {
        if (someLexics[currtok].token == RIGHT_BRACKET)
        {
            currtok++;
            return (TRUE);
        }
        else if ((parseStatementList(someLexics)) &&
                 (someLexics[currtok++].token == RIGHT_BRACKET))
        {
            return (TRUE);
        }
    }
    return (FALSE);
}

//checks if it has valid syntax for parseArgDecl as defined by the given EBNF
//arg-decl  --> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
_Bool parseArgDecl(struct lexics *someLexics)
{
    if ((someLexics[currtok++].token == VARTYPE) &&
        (someLexics[currtok++].token == IDENTIFIER))
    {
        if (someLexics[currtok].token == COMMA)
        {
            currtok++;
            return (parseArgDecl(someLexics));
        }
        return (TRUE);
    }
    return (FALSE);
}

//checks if it has valid syntax for header as defined by the given EBNF
_Bool parseHeader(struct lexics *someLexics)
{
    if ((someLexics[currtok++].token == VARTYPE) &&
        (someLexics[currtok++].token == IDENTIFIER) &&
        (someLexics[currtok++].token == LEFT_PARENTHESIS))
    {
        if ((someLexics[currtok].token == VARTYPE) && !(parseArgDecl(someLexics)))
        {
            return (FALSE);
        }
        if (someLexics[currtok++].token == RIGHT_PARENTHESIS)
        {
            return (TRUE);
        }
    }
    return (FALSE);
}

// Main func in Parser file
// Given by assigment req
_Bool parser(struct lexics *someLexics, int numberOfLexics)
{
    //function  --> header body
    return (parseHeader(someLexics) && parseBody(someLexics) && (numberOfLexics == currtok));
}

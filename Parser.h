
/////////////////////////
// Keith Kirtfield
// CMSC 403
// Sept. 25, 2020
// Project 1
////////////////////////
#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool parser(struct lexics *someLexics, int numberOfLexics);

_Bool parseTerm(struct lexics *someLexics);
_Bool parseExpression(struct lexics *someLexics);
_Bool parseWhileLoop(struct lexics *someLexics);
_Bool parseReturn(struct lexics *someLexics);
_Bool parseAssignment(struct lexics *someLexics);
_Bool parseStatement(struct lexics *someLexics);
_Bool parseStatementList(struct lexics *someLexics);
_Bool parseBody(struct lexics *someLexics);
_Bool parseArgDecl(struct lexics *someLexics);
_Bool parseHeader(struct lexics *someLexics);

#endif

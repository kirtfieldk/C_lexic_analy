/////////////////////////
// Keith Kirtfield
// CMSC 403
// Sept. 25, 2020
// Project 1
////////////////////////

//  read characters from a given FILE variable and convert
//	them into tokens.
#include "Tokenizer.h"

// Gets single character at a time from the input file.
char characterPoint(FILE *inf)
{
    char character;
    fpos_t curpos;
    fgetpos(inf, &curpos);        // saves the position
    character = (char)fgetc(inf); // gets a character
    fsetpos(inf, &curpos);        // resets the position
    return character;
}

//	tokenizer reads character by character from the given input file, creates
//				  lexemes and the associated tokens. Each time a lexeme is generated, a new
//				  lexics struct is created and the lexeme added. The generated lexeme is then
//				  tokenized, the token is added to the generated lexics struct, the lexics
//				  struct is then added to the end of the given lexics array. Whitespaces are
//				  ignored while processing the input file. Two functions provided in the
//				  Givens.c is used to validate IDENTIFIER and NUMBER.
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf)
{
    int i;
    char character;
    struct lexics *lexic;
    while ((character = (char)fgetc(inf)) != EOF) // read next char until end of file
    {
        if ((lexic = (struct lexics *)malloc(sizeof(struct lexics))) == NULL)
        {
            printf("ERROR allocating memory with malloc. \n\n");
            return FALSE;
        }
        lexic->token = FALSE;

        // Creates lexemes and the associated tokens
        // Switches through all possible terminal cases
        switch (character)
        {
        case '(':
            lexic->token = LEFT_PARENTHESIS;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case ')':
            lexic->token = RIGHT_PARENTHESIS;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case '{':
            lexic->token = LEFT_BRACKET;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case '}':
            lexic->token = RIGHT_BRACKET;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case '+':
        case '*':
        case '%':
            lexic->token = BINOP;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case '=':
            lexic->lexeme[0] = character;
            if (characterPoint(inf) == '=') //Incase ==
            {
                lexic->token = BINOP;
                lexic->lexeme[1] = fgetc(inf);
                lexic->lexeme[2] = '\0'; // Ends all with terminal
            }
            else
            {
                lexic->token = EQUAL;
                lexic->lexeme[1] = '\0'; // Ends all with terminal
            }
            break;
        case ',':
            lexic->token = COMMA;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case ';':
            lexic->token = EOL;
            lexic->lexeme[0] = character;
            lexic->lexeme[1] = '\0'; // Ends all with terminal
            break;
        case '!':
            lexic->lexeme[0] = character;
            if (characterPoint(inf) == '=') // Incase !=
            {
                lexic->token = BINOP;
                lexic->lexeme[1] = fgetc(inf);
                lexic->lexeme[2] = '\0'; // Ends all with terminal
            }
            else
            {
                lexic->token = FALSE;
                lexic->lexeme[1] = '\0'; // Ends all with terminal
                return FALSE;
            }
            break;
        default: // while, return, var type, identifier, and number processing
            if (isspace(character))
            {
                while (isspace(characterPoint(inf))) // Ignore whitespaces
                {
                    fgetc(inf);
                }
            }
            else if (isalpha(character) || isdigit(character)) // processing alphanumeric data and create associated tokens
            {
                i = 1;
                lexic->lexeme[0] = character;
                character = characterPoint(inf);
                while (isalpha(character) || isdigit(character))
                {
                    lexic->lexeme[i++] = fgetc(inf);
                    character = characterPoint(inf);
                }
                lexic->lexeme[i] = '\0';
                if (strcmp(lexic->lexeme, "while") == 0)
                {
                    lexic->token = WHILE_KEYWORD;
                }
                else if (strcmp(lexic->lexeme, "return") == 0)
                {
                    lexic->token = RETURN_KEYWORD;
                }
                else if (strcmp(lexic->lexeme, "int") == 0 || strcmp(lexic->lexeme, "void") == 0)
                {
                    lexic->token = VARTYPE;
                }
                else if (validIdentifier(lexic->lexeme)) // Validate IDENTIFIER using function from Givens.c
                {
                    lexic->token = IDENTIFIER;
                }
                else if (validNumber(lexic->lexeme)) // Validate NUMBER using function from Givens.c
                {
                    lexic->token = NUMBER;
                }
                else
                {
                    lexic->token = FALSE;
                    return FALSE; // Tokenization is unsuccessful returns FALSE
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////////
        // lexics struct is added to the lexics array
        //Bechase LEFT_PEREN == 0 its false, so we need to account for that
        ///////////////////////////////////////////////////////////////////////////////////////////
        if (lexic->token != FALSE || lexic->lexeme[0] == '(')
        {
            aLex[(*numLex)] = *lexic;
            (*numLex)++;
        }
    }
    return TRUE; // Tokenization is successful returns TRUE
}
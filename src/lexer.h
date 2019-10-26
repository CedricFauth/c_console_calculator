#ifndef LEXER
#define LEXER

#include <stdbool.h>
#include "token.h"

bool generate_tokens(TokenList* list, char* input_str);

#endif
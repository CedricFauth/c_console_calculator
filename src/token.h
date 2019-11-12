#ifndef TOKEN
#define TOKEN
#include <stdbool.h>

typedef enum TokenType{
    LEFT_P,
    RIGHT_P,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    DOUBLE,
    ENDOFLINE
} TokenType;

typedef struct TokenNode{

    TokenType type;
    double value;
    struct TokenNode* next;

} TokenNode;

typedef struct TokenList {

    TokenNode* head;
    TokenNode* tail;

} TokenList; 

TokenNode* new_token(TokenType type, double value);

TokenList* new_token_list();

void token_append(TokenList* list, TokenType type, double value);

void print_token_list(TokenList* list);

void free_token_list(TokenList* list);

int size(TokenList* list);

TokenNode* get_token(TokenList* l, int index);

#endif

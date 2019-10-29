#ifndef EXPRESSION
#define EXPRESSION

#include "token.h"

typedef struct ExprNode ExprNode;

typedef enum ExprType {
    BINARY,
    GROUP,
    UNARY,
    NUMBER
} ExprType;

typedef struct ExprBinary {
    TokenType op;
    ExprNode* left;
    ExprNode* right;
} ExprBinary;

typedef struct ExprGroup {
    ExprNode* next;
} ExprGroup;

typedef struct ExprUnary {
    /*
    TODO: implement NEGATION OPERATOR
    */
    ExprNode* next;
} ExprUnary;

typedef struct ExprNumber {
    double value;
} ExprNumber;


struct ExprNode {

    ExprType type;

    union
    {
        ExprBinary binary;
        ExprGroup group;
        ExprUnary unary;
        ExprNumber number;
    };

};

void print_ast(ExprNode* node);
void free_ast(ExprNode* node);

#endif

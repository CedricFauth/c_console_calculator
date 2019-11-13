#ifndef EXPRESSION
#define EXPRESSION

#include "../utils/token.h"

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

ExprNode* new_expr_binary(ExprNode* left, TokenType op, ExprNode* right);
ExprNode* new_expr_group(ExprNode* node);
ExprNode* new_expr_unary(ExprNode* node);
ExprNode* new_expr_number(double value);

#endif

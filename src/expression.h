#ifndef EXPRESSION
#define EXPRESSION

#include "token.h"

struct ExprNode;

typedef struct Expr {
    struct ExprNode* next;
} Expr;

typedef struct ExprBin {
    TokenType op;
    struct ExprNode* left;
    struct ExprNode* right;
} ExprBin;

// TODO: ExprGrouping, ExprUnary, ExprLiteral

typedef struct ExprNode {

    TokenType type;

    union
    {
        Expr ex;
        ExprBin bin;
        // ...
    };
    

} ExprNode;







#endif

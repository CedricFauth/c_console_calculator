#ifndef EXPRESSION
#define EXPRESSION

#include "token.h"

typedef struct ExprNode ExprNode;

typedef struct Expr {
    ExprNode* next;
} Expr;

typedef struct ExprBin {
    TokenType op;
    ExprNode* left;
    ExprNode* right;
} ExprBin;

// TODO: ExprGrouping, ExprUnary, ExprLiteral

struct ExprNode {

    TokenType type;

    union
    {
        Expr ex;
        ExprBin bin;
        // ...
    };

};



#endif

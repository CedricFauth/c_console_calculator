#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "logger.h"

extern TokenList* list;
int i = 0;

bool next_token(TokenType type){
    TokenType real_type = ENDOFLINE;
    if(get_token(list, i)->type == ENDOFLINE) return false;

    real_type = get_token(list, i+1)->type;
    //printf("Next TokenType: %d\n", real_type);
    return real_type == type? true : false;
}

ExprNode* primary(){
    ExprNode* expr = new_expr_number(23);
    return expr;
}

ExprNode* unary(){
    ExprNode* expr = primary();
    return expr;
}

ExprNode* multiplication(){
    ExprNode* expr = unary();
    return expr;
}

ExprNode* addition(){
    ExprNode* expr = multiplication();

    log_info("call next_token");
    while (next_token(MINUS) || next_token(PLUS)){
        ++i;
        // get operator here
        ++i;
        // get right mult here 
        log_info("addition detected");
    }
    
    // maybe do ++i;

    return expr;
}

// AKA expression
ExprNode* build_ast(){
    log_info("call build_ast");
    i = 0;
    return addition();
}

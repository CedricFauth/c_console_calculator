#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "logger.h"

extern TokenList* list;

bool next_token(TokenType type, int* i_ptr){
           
    TokenType real_type = ENDOFLINE;
    if(get_token(list, *i_ptr)->type == ENDOFLINE) return false;

    real_type = get_token(list, (*i_ptr)+1)->type;
    return real_type == type? true : false;
}

ExprNode* primary(int* i_ptr){
    log_info("Primary detected");
    ExprNode* expr = new_expr_number(get_token(list, *(i_ptr))->value);
    //++(*i_ptr);
    return expr;
}

ExprNode* unary(int* i_ptr){
    ExprNode* expr;
    TokenType op;

    if((op = get_token(list, *i_ptr)->type) == MINUS){
        log_info("Unary detected");
        ++(*i_ptr);
        expr = unary(i_ptr);
        expr = new_expr_unary(expr);
    }else{
        expr = primary(i_ptr);
    }

    return expr;
}

ExprNode* multiplication(int* i_ptr){

    ExprNode* expr = unary(i_ptr);

    while (next_token(STAR, i_ptr) || next_token(SLASH, i_ptr)){
        log_info("Multiplication/division detected");
        ++(*i_ptr);
        // get operator here
        TokenType op = get_token(list, *i_ptr)->type;
        ++(*i_ptr);
        ExprNode* right = unary(i_ptr);
        expr = new_expr_binary(expr, op, right);
    } 

    return expr;
}

ExprNode* addition(int* i_ptr){
    ExprNode* expr = multiplication(i_ptr);

    while (next_token(MINUS, i_ptr) || next_token(PLUS, i_ptr)){
        log_info("Addition/substraction detected");
        ++(*i_ptr);
        // get operator here
        TokenType op = get_token(list, *i_ptr)->type;
        printf("OP is: %d\n", op);
        ++(*i_ptr);
        ExprNode* right = multiplication(i_ptr);
        expr = new_expr_binary(expr, op, right);
    }

    return expr;
}

// AKA expression
ExprNode* build_ast(){
    log_info("Building ast");
    int i = 0;
    return addition(&i);
}

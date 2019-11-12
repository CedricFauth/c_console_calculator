#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "logger.h"

ExprNode* addition(int* i_ptr);

extern TokenList* list;
extern bool error;

bool next_token(TokenType type, int* i_ptr){
           
    TokenType real_type = ENDOFLINE;
    if(get_token(list, *i_ptr)->type == ENDOFLINE) return false;

    real_type = get_token(list, (*i_ptr)+1)->type;
    return real_type == type? true : false;
}

ExprNode* primary(int* i_ptr){
    ExprNode* expr;
    switch (get_token(list, *i_ptr)->type){
        case DOUBLE:
            log_info("Primary detected");
            expr = new_expr_number(get_token(list, *(i_ptr))->value);
            break;
        case LEFT_P:
            log_info("Group detected");
            ++(*i_ptr);
            expr = addition(i_ptr);
            if(next_token(RIGHT_P,i_ptr)){
                ++(*i_ptr);
                return new_expr_group(expr);
            }else{
                log_err("')' not found\n");
                error = true;
            }
            break;
        default:
            expr = NULL;
            log_err("Equation invalid\n");
            error = 1;
            break;
    }
    
    return expr;
}

ExprNode* unary(int* i_ptr){
    ExprNode* expr;

    if(get_token(list, *i_ptr)->type == MINUS){
        log_info("Unary detected");
        ++(*i_ptr);
        expr = unary(i_ptr);
        expr = new_expr_unary(expr);
    }else {
        log_info("Running primary");
        printf("TOKEN: %d\n", get_token(list, *i_ptr)->type);
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
    ExprNode* expr = addition(&i);

    ++i;
    
    if(get_token(list, i)->type == ENDOFLINE){
        log_warn("EOF");
    }else
    {
        log_err("Next token not ENDOFLINE\n");
        error = true;
    }
    
    return expr;

}

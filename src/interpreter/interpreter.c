#include <stdlib.h>
#include "../logger/logger.h"
#include "../utils/token.h"
#include "../utils/expression.h"
#include "interpreter.h"

double interpret(ExprNode* node){

    if(node == NULL) {
        log_err("Node is null\n"); 
        return -1;
    }

    if(node->type == BINARY){
        log_info("binary");
        double num1 = interpret(node->binary.left);
        double num2 = interpret(node->binary.right);

        switch (node->binary.op)
        {
        case PLUS:
            log_info("+");
            return num1 + num2;
        case MINUS:
            log_info("-");
            return num1 - num2;
        case SLASH:
            log_info("/");
            return num1 / num2;
        case STAR:
            log_info("*");
            return num1 * num2;
        default:
            return -1;
        }
        
    }else if(node->type == GROUP){
        log_info("group");
        return interpret(node->group.next);
    }else if(node->type == UNARY){
        log_info("unary");
        return -(interpret(node->unary.next));
    }else if(node->type == NUMBER){
        log_info("number");
        return node->number.value;
    }else{
        log_err("undefined op");
        return -1;
    }

}

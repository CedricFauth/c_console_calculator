#include <stdlib.h>
#include <stdio.h>
#include "expression.h"
#include "logger.h"

ExprNode* new_expr_binary(ExprNode* left, TokenType op, ExprNode* right){
    ExprNode* expr = malloc(sizeof(ExprNode));
    expr->type = BINARY;
    expr->binary.left = left;
    expr->binary.op = op;
    expr->binary.right = right;
    return expr;
}

ExprNode* new_expr_group(ExprNode* node){
    ExprNode* expr = malloc(sizeof(ExprNode));
    expr->type = GROUP;
    expr->group.next = node;
    return expr;
}

ExprNode* new_expr_unary(ExprNode* node){
    ExprNode* expr = malloc(sizeof(ExprNode));
    expr->type = UNARY;
    expr->unary.next = node;
    return expr;
}

ExprNode* new_expr_number(double value){
    ExprNode* expr = malloc(sizeof(ExprNode));
    expr->type = NUMBER;
    expr->number.value = value;
    return expr;
}

void free_ast(ExprNode* node){
    if(node == NULL) return;
    if(node->type == BINARY){
        log_info("free left, right");
        free_ast(node->binary.left);
        free_ast(node->binary.right);
        log_info("free bin node");
        free(node);
    }else if(node->type == GROUP){
        log_info("free group next");
        free_ast(node->group.next);
        log_info("free group");
        free(node);
    }else if(node->type == UNARY){
        log_info("free unary next");
        free_ast(node->unary.next);
        log_info("free unary");
        free(node);
    }else if(node->type == NUMBER){
        log_info("free number");
        free(node);
    }
}

void print_ast_rec(ExprNode*);

void print_ast(ExprNode* node){
    print_ast_rec(node);
    printf("\n");
}

void print_ast_rec(ExprNode* node){

    if(node == NULL) return;

    printf("(");

    if(node->type == BINARY){
        print_ast_rec(node->binary.left);
        switch (node->binary.op)
        {
        case PLUS:
            printf(" + ");
            break;
        case MINUS:
            printf(" - ");
            break;
        case SLASH:
            printf(" / ");
            break;
        case STAR:
            printf(" * ");
            break;
        default:
            break;
        }
        print_ast_rec(node->binary.right);
    }else if(node->type == GROUP){
        printf(" group: ");
        print_ast_rec(node->group.next);
    }else if(node->type == UNARY){
        printf(" - ");
        print_ast_rec(node->unary.next);
    }else if(node->type == NUMBER){
        printf("%f", node->number.value);
    }else{
        printf("UNDEFINED");
    }

    printf(")");

}

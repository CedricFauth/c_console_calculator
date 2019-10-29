#include <stdlib.h>
#include <stdio.h>
#include "expression.h"

void free_ast(ExprNode* node){
    if(node == NULL) return;
    if(node->type == BINARY){
        printf("free left, right\n");
        free_ast(node->binary.left);
        free_ast(node->binary.right);
        printf("free bin node\n");
        free(node);
    }else if(node->type == GROUP){
        printf("free group next\n");
        free_ast(node->group.next);
        printf("free group\n");
        free(node);
    }else if(node->type == UNARY){
        printf("free unary next\n");
        free_ast(node->unary.next);
        printf("free unary\n");
        free(node);
    }else if(node->type == NUMBER){
        printf("free number\n");
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

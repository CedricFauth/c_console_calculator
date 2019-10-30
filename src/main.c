#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "logger.h"
#include "token.h"
#include "expression.h"

int main(){

    set_log_level(INFO);

    int BUFFER_SIZE = 128;

    char* input = malloc(sizeof(char) * BUFFER_SIZE);

    bool error = false;

    
    ExprNode* a = malloc(sizeof(ExprNode));
    ExprNode* b = malloc(sizeof(ExprNode));
    ExprNode* c = malloc(sizeof(ExprNode));
    ExprNode* d = malloc(sizeof(ExprNode));
    ExprNode* e = malloc(sizeof(ExprNode));
    ExprNode* f = malloc(sizeof(ExprNode));
    ExprNode* g = malloc(sizeof(ExprNode));

    g->type = NUMBER;
    g->number.value = 123.0;

    f->type = NUMBER;
    f->number.value = -2.25;

    e->type = NUMBER;
    e->number.value = 1000.0;

    d->type = BINARY;
    d->binary.op = MINUS;
    d->binary.left = e;
    d->binary.right = f;

    c->type = GROUP;
    c->group.next = d;

    b->type = UNARY;
    b->unary.next = c;

    a->type = BINARY;
    a->binary.op = STAR;
    a->binary.right = b;
    a->binary.left = g;

    print_ast(a);

    /*
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);*/

    free_ast(a);

    do {

        fgets(input, BUFFER_SIZE, stdin);

        printf("strlen: %lu\nstring: %s", strlen(input), input);

        TokenList* list = new_token_list();
        error = generate_tokens(list, input);
        print_token_list(list);

        if(size(list) > 1 && !error){
            log_info("Continue parsing.");
            //parser call
        }
        /*else{
            log_warn("Error or list empty.");
        }*/

        free_token_list(list);

    } while(strcmp(input, "q\n"));

    free(input);

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "logger.h"
#include "token.h"
#include "expression.h"
#include "parser.h"

const int BUFFER_SIZE = 256;

TokenList* list;
char input[256];
bool error = false;

int main(){

    set_log_level(INFO);

    do {
        error = false;

        // step 1: input
        fgets(input, BUFFER_SIZE, stdin);

        printf("strlen: %lu\nstring: %s", strlen(input), input);

        // step 2: lexing
        list = generate_tokens();
        print_token_list(list);

        if(size(list) <= 1 || error){
            free_token_list(list);
            continue;
        }

        // step 3: parsing
        log_info("Continue with parsing.");
        ExprNode* ast = build_ast();

        if(error){
            free_ast(ast);
            free_token_list(list);
            continue;
        }

        log_info("Continue with evaluating.");

        print_ast(ast);
        free_ast(ast);
        free_token_list(list);

    } while(strcmp(input, "q\n"));

    exit(EXIT_SUCCESS);

}

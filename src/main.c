#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer/lexer.h"
#include "logger/logger.h"
#include "utils/token.h"
#include "utils/expression.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

const int BUFFER_SIZE = 256;
char input[256];

TokenList* list;

bool error = false;

int main(){

    set_log_level(ERROR);

    do {
        error = false;

        // step 1: input
        fgets(input, BUFFER_SIZE, stdin);

        //printf("strlen: %lu\nstring: %s", strlen(input), input);

        // step 2: lexing
        list = generate_tokens();
            //print_token_list(list);

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

        // step 4: interpretation
        log_info("Continue with interpretation.");
        double result = interpret(ast);
            //print_ast(ast);
        printf(" = %f\n", result);
        
        free_ast(ast);
        free_token_list(list);

    } while(strcmp(input, "q\n"));

    exit(EXIT_SUCCESS);

}

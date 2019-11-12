#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "logger.h"
#include "token.h"
#include "expression.h"
#include "parser.h"

const int BUFFER_SIZE = 128;

TokenList* list;
char input[128];

int main(){

    set_log_level(INFO);

    bool error = false;

    do {

        fgets(input, BUFFER_SIZE, stdin);

        printf("strlen: %lu\nstring: %s", strlen(input), input);

        list = new_token_list();
        error = generate_tokens();
        print_token_list(list);

        if(size(list) > 1 && !error){
            log_info("Continue parsing.");
            ExprNode* ast = build_ast();
            print_ast(ast);
            free_ast(ast);
        }
        /*else{
            log_warn("Error or list empty.");
        }*/

        free_token_list(list);

    } while(strcmp(input, "q\n"));

    exit(EXIT_SUCCESS);

}

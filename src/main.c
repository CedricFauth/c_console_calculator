#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "logger.h"
#include "token.h"

#include "expression.h"

int main(){

    int BUFFER_SIZE = 128;

    char* input = malloc(sizeof(char) * BUFFER_SIZE);

    bool error = false;

    /*
    ExprNode a;
    ExprNode b;
    ExprNode c;
    ExprNode d;

    a.bin.op = PLUS;
    a.bin.left = &b;
    a.bin.right = &c;

    a.bin.right->ex.next = &d;
    */

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

int main(){

    int BUFFER_SIZE = 128;

    char* input = malloc(sizeof(char) * BUFFER_SIZE);

    do {

        fgets(input, BUFFER_SIZE, stdin);

        printf("strlen: %lu\nstring: %s", strlen(input), input);

        TokenList* list = new_token_list();
        generate_tokens(list, input);
        print_token_list(list);
        free_token_list(list);

    } while(strcmp(input, "q\n"));

    free(input);

}
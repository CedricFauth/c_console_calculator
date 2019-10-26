#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "logger.h"

bool isDigit(char c){
    return c >= '0' && c <= '9';
}

double number(char* string, int *i_ptr){
    int start = *i_ptr;
    do{
        (*i_ptr)++;
    }while(isDigit(string[*i_ptr]) || string[(*i_ptr)] == '.');
        
    
    printf("stop is: %d\n", *i_ptr);
    int stop = *i_ptr;

    char sub_string[stop-start+1];
    for(int k = 0; k < (stop-start); k++){
        sub_string[k] = string[start + k];
    }
    sub_string[stop-start] = '\0';

    //test print
    /*for(int i = 0; i < stop-start+1; i++){
        printf("Char: %d\n", (int)sub_string[i]);
    }*/

    (*i_ptr)--;
    return atof(sub_string);
}

bool generate_tokens(TokenList* list, char* input_str){
    
    for(int i = 0; i < strlen(input_str); i++){ //until \n linebreak
        //token_append(list, PLUS, 0.0);

        switch (input_str[i])
        {
        case '+':
            token_append(list, PLUS, 1.0);
            break;
        case '-':
            token_append(list, MINUS, 2.0);
            break;
        case '*':
            token_append(list, STAR, 3.0);
            break;
        case '/':
            token_append(list, SLASH, 4.0);
            break;
        case '\n':
            token_append(list, ENDOFLINE, 5.0);
            break;
        case 'q':
            return false;
        default:
            if(isDigit(input_str[i])){
                printf("is number\n");
                token_append(list, DOUBLE, number(input_str, &i));
            }else{
                log_err_detail(input_str, "Unknown character", i);
                return true;
            }
        }
        //printf("%d\n", (int) *(input_str+i));

    }

    return false;

}

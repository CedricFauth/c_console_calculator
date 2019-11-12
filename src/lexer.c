#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "logger.h"

extern TokenList* list;
extern char input[];

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

bool generate_tokens(){
    
    for(int i = 0; i < strlen(input); i++){ //until \n linebreak
        //token_append(list, PLUS, 0.0);

        switch (input[i])
        {
        case '(':
            token_append(list, LEFT_P, 0.0);
            break;
        case ')':
            token_append(list, RIGHT_P, 0.0);
            break;
        case '+':
            token_append(list, PLUS, 0.0);
            break;
        case '-':
            token_append(list, MINUS, 0.0);
            break;
        case '*':
            token_append(list, STAR, 0.0);
            break;
        case '/':
            token_append(list, SLASH, 0.0);
            break;
        case '\n':
            token_append(list, ENDOFLINE, 0.0);
            break;
        case ' ':
            break;
        case 'q':
            return true;
        default:
            if(isDigit(input[i])){
                log_info("Lexer detects a number");
                token_append(list, DOUBLE, number(input, &i));
            }else{
                log_err_detail(input, "Unknown character", i);
                return true;
            }
        }
        //printf("%d\n", (int) *(input+i));

    }

    return false;

}

#include <stdlib.h>
#include <stdio.h>

#include "../utils/token.h"
#include "../logger/logger.h"

TokenNode* new_token(TokenType type, double value){
    TokenNode* token = malloc(sizeof(TokenNode));
    if(token == NULL) {
        log_err("Could not allocate token memory.");
        return NULL;
    }
    token->type = type;
    token->value = value;
    token->next = NULL;
    return token;
}

TokenList* new_token_list(){
    TokenList* list = malloc(sizeof(TokenList));
    if(list == NULL) {
        log_err("Could not allocate token_list memory.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void token_append(TokenList* list, TokenType type, double value){

    TokenNode* token = new_token(type, value);
    if(token == NULL) return;

    if(list->head == NULL){
        list->head = token;
        list->tail = token;
    }else{
        list->tail->next = token;
        list->tail = token;
    }
}

void print_token_list(TokenList* list){

    if(list == NULL){
        log_err("Null instead of list.");
        return;
    }

    printf("{ ");
    if(list->head != NULL){
        for(TokenNode* node = list->head; node != NULL; node = node->next){

            switch (node->type)
            {
            case LEFT_P:
                printf("[TOKEN: LEFT_P] ");
                break;
            case RIGHT_P:
                printf("[TOKEN: RIGHT_P] ");
                break;
            case PLUS:
                printf("[TOKEN: PLUS] ");
                break;
            case MINUS:
                printf("[TOKEN: MINUS] ");
                break;
            case STAR:
                printf("[TOKEN: STAR] ");
                break;
            case SLASH:
                printf("[TOKEN: SLASH] ");
                break;
            case DOUBLE:
                printf("[TOKEN: DOUBLE -> VALUE: %f] ", node->value);
                break;
            case ENDOFLINE:
                printf("[TOKEN: EOL] ");
                break;
            
            default:
                printf("[TOKEN:%d  VALUE:%f] ",node->type, node->value);
                break;
            }
        }
    }
    printf("}\n");
}

void free_token_list(TokenList* list){
    log_info("Free token list");
    TokenNode* token = list->head;
    TokenNode* tmp;

    while(token != NULL){
        tmp = token;
        token = token->next;
        free(tmp);
    }

    free(list);

}

int size(TokenList* list){
    int c = 0;
    for(TokenNode* node = list->head; node != NULL; node = node->next, c++);
    return c;
}

TokenNode* get_token(TokenList* l, int index){
    TokenNode* node = l->head;
    for(int i = 0; node->next != NULL && i < index; node = node->next, i++);

    return node;
}

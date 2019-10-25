#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "logger.h"

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
            printf("[TOKEN:%d  VALUE:%f] ",node->type, node->value);
        }
    }
    printf("}\n");
}

void free_token_list(TokenList* list){

    TokenNode* token = list->head;
    TokenNode* tmp;

    while(token != NULL){
        tmp = token;
        token = token->next;
        free(tmp);
    }

    free(list);

}



#include <string.h>
#include <stdlib.h>
#include "../include/rules.h"
#include "../include/checkout.h"

struct s_match {
        rulematcher_p func;
        void* data;
};

int match_client_name(checkout_p co, item_p item, void* param) {
        char* client_name = (char*)param;
        if(strcmp(client_name, checkout_get_client_name(co)) == 0) {
                return 1;
        }
        return 0;
}

int match_product_id(checkout_p co, item_p item, void* param) {
        int product_id = *((int*)param);
        return item_get_product_id(item) == product_id;
}

int match_product_quantity(checkout_p co, item_p item, void* param) {
        int product_quantity = *((int*)param);
        return item_get_quantity(item) >= product_quantity;
}

match_p match_new(char *key, char *val) {
        match_p match = (match_p)malloc(sizeof(match_t));
        if(strcmp(key,"client") == 0) {
                match->func = match_client_name;
                match->data = malloc(sizeof(char)*(strlen(val)+1));
                strcpy((char*)match->data, val);
        } else if(strcmp(key, "product") == 0) {
                match->func = match_product_id;
                match->data = malloc(sizeof(int));
                *((int*)match->data) = atoi(val);
        } else if(strcmp(key, "quantity") == 0) {
                match->func = match_product_quantity;
                match->data = malloc(sizeof(int));
                *((int*)match->data) = atoi(val);
        }

        return match;
}

void match_del(match_p match) {
        free(match->data);
        free(match);
}

int match_execute(match_p match, checkout_p co, item_p item) {
        return match->func(co, item, match->data);
}

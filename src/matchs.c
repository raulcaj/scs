#include <string.h>
#include <stdlib.h>
#include "../include/matchs.h"
#include "../include/checkout.h"
#include "../include/parsers.h"

#define MATCH_FUNC_COUNT 3

struct s_match {
        rulematcher_p func;
        void* data;
};

static const char* match_keywords[MATCH_FUNC_COUNT] = {
        "client",
        "product",
        "quantity"
};
static const rulematcher_p match_funcs[MATCH_FUNC_COUNT]  = {
            match_client_name,
            match_product_id,
            match_product_quantity
};
static const parser_func_p match_parsers[MATCH_FUNC_COUNT] = {
        parser_copychar,
        parser_parseint,
        parser_parseint
};

match_p match_new(const char *key, const char *val) {
        int i = 0;
        match_p match = (match_p)malloc(sizeof(match_t));
        for(i = 0; i < MATCH_FUNC_COUNT; ++i) {
                if(strcmp(key, match_keywords[i]) == 0) {
                        match->func = match_funcs[i];
                        match->data = match_parsers[i](val);
                        break;
                }
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


/* generic matching function */

int match_client_name(checkout_p co, item_p item, void* param) {
        char* client_name = (char*)param;
        return strcmp(client_name, checkout_get_client_name(co)) == 0;
}

int match_product_id(checkout_p co, item_p item, void* param) {
        int product_id = *((int*)param);
        return item_get_product_id(item) == product_id;
}

int match_product_quantity(checkout_p co, item_p item, void* param) {
        int product_quantity = *((int*)param);
        return item_get_quantity(item) >= product_quantity;
}

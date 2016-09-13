#ifndef RULES_H
#define RULES_H

#include "checkout.h"
#include "item.h"

typedef int (*rulematcher_p)(checkout_p, item_p, void*);

typedef struct s_match match_t, *match_p;

int match_client_name(checkout_p co, item_p item, void* param);
int match_product_id(checkout_p co, item_p item, void* param);
int match_product_quantity(checkout_p co, item_p item, void* param);
match_p match_new(const char *key, const char *val);
int match_execute(match_p match, checkout_p co, item_p item);
void match_del(match_p match);
#endif

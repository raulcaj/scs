#ifndef CHECKOUT_H
#define CHECKOUT_H

#include "item.h"
#include "client.h"

typedef struct s_checkout checkout_t, *checkout_p;

typedef int (*rulematcher_p)(checkout_p, item_p, void*);
typedef void(*rulesaction_p)(checkout_p, item_p, void*);

int checkout_total(checkout_p checkout);
void checkout_add(checkout_p checkout, item_p item);
char *checkout_get_client_name(checkout_p co);
int checkout_get_items_count(checkout_p co);
item_p checkout_get_item(checkout_p co, int index);

#include "pricingrules.h"
pricingrules_p checkout_get_pricingrules(checkout_p co);
checkout_p checkout_new(pricingrules_p pricingrules, client_p client);
#endif

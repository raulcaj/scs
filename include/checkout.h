#ifndef CHECKOUT_H
#define CHECKOUT_H

#include "item.h"
#include "client.h"
#include "list.h"

typedef struct s_checkout checkout_t, *checkout_p;

checkout_p checkout_new(list_p prs, client_p client);
int checkout_total(checkout_p checkout);
void checkout_add(checkout_p checkout, item_p item);
char *checkout_get_client_name(checkout_p co);
void checkout_del(checkout_p co);
list_p checkout_get_items(checkout_p co);
list_p checkout_get_pricingrules(checkout_p co);
#endif

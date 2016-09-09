#ifndef RULES_H
#define RULES_H

#include "checkout.h"
#include "item.h"

int match_client_name(checkout_p co, item_p item, void* param);
int match_product_id(checkout_p co, item_p item, void* param);
int match_product_quantity(checkout_p co, item_p item, void* param);
#endif

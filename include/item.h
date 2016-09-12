#ifndef ITEM_H
#define ITEM_H

#include "product.h"

typedef struct s_item item_t, *item_p;

item_p item_new(product_p product, int quantity);
void item_del(item_p item);
int item_eq(item_p item1, item_p item2);
int item_get_price(item_p item);
void item_set_price(item_p item, int price);
int item_get_quantity(item_p item);
void item_set_quantity(item_p item, int quantity);
int item_get_product_id(item_p item);
product_p item_get_product(item_p item);

#endif

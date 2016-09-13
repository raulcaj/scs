#include "../include/item.h"
#include <stdlib.h>
#include <string.h>

struct s_item {
        product_p product;
        int quantity;
};

item_p item_new(product_p product, int quantity) {
        item_p item = (item_p)malloc(sizeof(item_t));
        item->product = product;
        item->quantity = quantity;
        return item;
}

void item_del(item_p item) {
        product_del(item->product);
        free(item);
}

int item_eq(item_p item1, item_p item2) {
        return strcmp(product_get_id(item1->product), product_get_id(item2->product)) == 0 &&
                product_get_price(item1->product) == product_get_price(item2->product);
}

int item_get_price(item_p item) {
        return product_get_price(item->product);
}

void item_set_price(item_p item, int price) {
        product_set_price(item->product, price);
}

int item_get_quantity(item_p item) {
        return item->quantity;
}

void item_set_quantity(item_p item, int quantity) {
        item->quantity = quantity;
}

char* item_get_product_id(item_p item) {
        return product_get_id(item->product);
}

product_p item_get_product(item_p item) {
        return item->product;
}

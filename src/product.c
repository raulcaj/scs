#include "../include/product.h"
#include <string.h>
#include <stdlib.h>

struct s_product {
        int id;
        char *name;
        int price;
};

static product_t products[3];
void product_init() {
        product_t p_classic;
        p_classic.id  = classic;
        p_classic.name = "Classic Ad";
        p_classic.price = 26999;


        product_t p_standout;
        p_standout.id  = standout;
        p_standout.name = "Standout Ad";
        p_standout.price = 32299;

        product_t p_premium;
        p_premium.id  = premium;
        p_premium.name = "Premium Ad";
        p_premium.price = 39499;

        products[classic]  = p_classic;
        products[standout] = p_standout;
        products[premium]  = p_premium;
}

product_p product_get_by_id(int id) {
        return &products[id];
}

product_p product_cpy(product_p product) {
        product_p cpy = (product_p)malloc(sizeof(product_t));
        memcpy(cpy, product, sizeof(product_t));
        return cpy;
}

void product_del(product_p product) {
        free(product);
}


int product_get_id(product_p product) {
        return product->id;
}

char* product_get_name(product_p product) {
        return product->name;
}

int product_get_price(product_p product) {
        return product->price;
}

void product_set_price(product_p product, int price) {
        product->price = price;
}

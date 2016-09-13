#include "../include/product.h"
#include "../include/parsers.h"
#include "../include/db.h"
#include <string.h>
#include <stdlib.h>

struct s_product {
        char *id;
        char *name;
        int price;
};

product_p product_get_by_id(const char* id) {
        product_p product = (product_p)malloc(sizeof(product_t));
        product->id = parser_copychar(id);
        db_retrieve_product_by_id(product->id, &product->name, &product->price);
        return product;
}

product_p product_copy(product_p product) {
        product_p copy = (product_p)malloc(sizeof(product_t));
        copy->id = parser_copychar(product->id);
        copy->name = parser_copychar(product->name);
        copy->price = product->price;
        return copy;
}

void product_del(product_p product) {
        free(product->id);
        free(product->name);
        free(product);
}

char* product_get_id(product_p product) {
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

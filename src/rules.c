#include <string.h>
#include "../include/rules.h"
#include "../include/checkout.h"

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

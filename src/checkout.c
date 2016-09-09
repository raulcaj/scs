#include "../include/checkout.h"
#include <stdlib.h>

struct s_checkout {
        pricingrules_p pricingrules;
        client_p client;
        item_p *items;
        int items_count;
        int items_size;
};

checkout_p checkout_new(pricingrules_p pricingrules, client_p client) {
        checkout_p co = (checkout_p)malloc(sizeof(checkout_t));
        co->items = (item_p*)calloc(10, sizeof(item_p));
        co->pricingrules = pricingrules;
        co->client = client;
        co->items_count = 0;
        co->items_size = 10;
        return co;
}

int checkout_total(checkout_p co) {
        int sum = 0, i = 0;
        pricingrules_execute(co);
        for(i = 0; i < co->items_count; ++i) {
                sum += item_get_quantity(co->items[i]) * item_get_price(co->items[i]);
        }
        return sum;
}

void checkout_add(checkout_p co, item_p item) {
        int i = 0;
        for(i = 0; i < co->items_count; ++i) {
                if(item_eq(co->items[i], item)) {
                        item_set_quantity(co->items[i], item_get_quantity(co->items[i])+item_get_quantity(item));
                        return;
                }
        }
        co->items[co->items_count] = item;
        co->items_count++;
}

char *checkout_get_client_name(checkout_p co) {
        return client_get_name(co->client);
}

item_p checkout_get_item(checkout_p co, int index) {
        return co->items[index];
}

int checkout_get_items_count(checkout_p co) {
        return co->items_count;
}

pricingrules_p checkout_get_pricingrules(checkout_p co) {
        return co->pricingrules;
}

#include "../include/checkout.h"
#include "../include/list.h"
#include "../include/pricingrules.h"

#include <stdlib.h>

struct s_checkout {
        list_p pricingrules;
        client_p client;
        list_p items;
};

checkout_p checkout_new(list_p pricingrules, client_p client) {
        checkout_p co = (checkout_p)malloc(sizeof(checkout_t));
        co->pricingrules = pricingrules;
        co->client = client;
        co->items = list_new();
        return co;
}


void list_pricingrules_del(void* ptr) {
        pricingrules_p pr = ptr;
        pricingrules_del(pr);
}

void list_item_del(void* ptr) {
        item_p item = ptr;
        item_del(item);
}

void checkout_del(checkout_p co) {
        client_del(co->client);
        list_del(co->pricingrules, list_pricingrules_del);
        list_del(co->items, list_item_del);
        free(co);
}

void checkout_sumitems(void *sum_param, void* item_param) {
        int* sum = sum_param;
        item_p item = item_param;
        *sum += item_get_quantity(item) * item_get_price(item);
}

int checkout_total(checkout_p co) {
        int sum = 0;
        pricingrules_execute(co);
        list_foreach(co->items, checkout_sumitems, &sum);
        return sum;
}

void checkout_incquantity(void *newitem_param, void* item_param) {
        item_p newitem = newitem_param;
        item_p item = item_param;
        if(item_eq(item, newitem)) {
                item_set_quantity(item, item_get_quantity(item)+item_get_quantity(newitem));
                item_set_quantity(newitem, 0);
        }
}

void checkout_add(checkout_p co, item_p newitem) {
        list_foreach(co->items, checkout_incquantity, newitem);
        if(item_get_quantity(newitem) > 0) {
                list_add(co->items, newitem);
        } else {
                item_del(newitem);
        }
}

char *checkout_get_client_name(checkout_p co) {
        return client_get_name(co->client);
}

list_p checkout_get_pricingrules(checkout_p co) {
        return co->pricingrules;
}

list_p checkout_get_items(checkout_p co) {
        return co->items;
}

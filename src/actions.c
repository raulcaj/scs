#include "../include/checkout.h"

void action_set_price(checkout_p co, item_p item, void *param) {
        int price = *((int*)param);
        item_set_price(item, price);
}

void action_add_bonus(checkout_p co, item_p item, void *param) {
        int x4y = *((int*)param);
        int bonus_quantity = item_get_quantity(item) / x4y;
        item_p bonus_item = item_new(item_get_product(item), bonus_quantity);
        item_set_price(bonus_item, 0);
        checkout_add(co, bonus_item);
        item_set_quantity(item, item_get_quantity(item)-bonus_quantity);
}

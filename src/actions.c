#include "../include/checkout.h"
#include "../include/actions.h"

#include <stdlib.h>
#include <string.h>


struct s_action {
        rulesaction_p func;
        void* data;
};

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

action_p action_new(char *key, char *val) {
        action_p action = (action_p)malloc(sizeof(action_t));
        if(strcmp(key, "add_bonus") == 0) {
                action->func = action_add_bonus;
                action->data = malloc(sizeof(int));
                *((int*)action->data) = atoi(val);
        } else if(strcmp(key, "set_price") == 0) {
                action->func = action_set_price;
                action->data = malloc(sizeof(int));
                *((int*)action->data) = atoi(val);
        }
        return action;
}

void action_del(action_p action) {
        free(action->data);
        free(action);
}

void action_execute(action_p action, checkout_p co, item_p item) {
        action->func(co, item, action->data);
}

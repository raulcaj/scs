#include "../include/checkout.h"
#include "../include/actions.h"
#include "../include/parsers.h"

#include <stdlib.h>
#include <string.h>

#define ACTION_FUNC_COUNT 2

struct s_action {
        rulesaction_p func;
        void* data;
};

static const char* action_keywords[ACTION_FUNC_COUNT] = {
        "add_bonus",
        "set_price"
};
static const rulesaction_p action_funcs[ACTION_FUNC_COUNT] = {
        action_add_bonus,
        action_set_price
};
static const parser_func_p action_parsers[ACTION_FUNC_COUNT] = {
        parser_parseint,
        parser_parseint
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

action_p action_new(const char *key, const char *val) {
        int i = 0;
        action_p action = (action_p)malloc(sizeof(action_t));
        for(i = 0; i < ACTION_FUNC_COUNT; ++i) {
                if(strcmp(key, action_keywords[i]) == 0) {
                        action->func = action_funcs[i];
                        action->data = action_parsers[i](val);
                        break;
                }
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

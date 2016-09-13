#ifndef ACTION_H
#define ACTION_H

#include "checkout.h"

typedef struct s_action action_t, *action_p;

typedef void(*rulesaction_p)(checkout_p, item_p, void*);

void action_set_price(checkout_p co, item_p item, void *param);
void action_add_bonus(checkout_p co, item_p item, void *param);
action_p action_new(const char *key, const char *val);
void action_execute(action_p action, checkout_p co, item_p item);
void action_del(action_p action);
#endif

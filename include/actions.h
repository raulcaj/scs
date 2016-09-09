#ifndef ACTION_H
#define ACTION_H

#include "checkout.h"

void action_set_price(checkout_p co, item_p item, void *param);
void action_add_bonus(checkout_p co, item_p item, void *param);
#endif

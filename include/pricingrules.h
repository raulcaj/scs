#ifndef PRICINGRULES_H
#define PRICINGRULES_H

#include "item.h"

typedef struct s_match match_t, *match_p;
typedef struct s_action action_t, *action_p;
typedef struct s_pricingrules pricingrules_t, *pricingrules_p;

pricingrules_p pricingrules_from_file(char *filename);
void pricingrules_execute(checkout_p co);

match_p create_match(char *key, char *val);
void append_match(pricingrules_p pr, match_p match);
action_p create_action(char *key, char *val);
void append_action(pricingrules_p pr, action_p action);
pricingrules_p  append_pricingrules(pricingrules_p root, pricingrules_p pr);
#endif

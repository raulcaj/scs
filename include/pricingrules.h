#ifndef PRICINGRULES_H
#define PRICINGRULES_H

#include "item.h"
#include "list.h"

typedef struct s_pricingrules pricingrules_t, *pricingrules_p;

pricingrules_p pricingrules_new(void);
list_p pricingrules_from_file(char *filename);
void pricingrules_execute(checkout_p co);
void pricingrules_del(pricingrules_p pr);

#endif

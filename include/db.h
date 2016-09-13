#ifndef DB_H
#define DB_H

#include "list.h"

void db_init(void);
void db_retrieve_product_by_id(const char* id, char* *name, int *price);
void db_retrieve_pricingrules(list_p *prs);
void db_free(void);

#endif

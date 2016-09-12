#ifndef PRODUCT_H
#define PRODUCT_H

#define  classic  0
#define  standout 1
#define  premium  2

typedef struct s_product product_t, *product_p;

product_p product_cpy(product_p product);
product_p product_get_by_id(int id);
void product_init(void);

void product_del(product_p product);
int product_get_id(product_p product);
char* product_get_name(product_p product);
int product_get_price(product_p product);
void product_set_price(product_p product, int price);

#endif

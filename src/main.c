#include <stdio.h>
#include "../include/checkout.h"
#include "../include/pricingrules.h"
#include "../include/product.h"

void process_order() {
        int total = 0;
        int quantity = 0;
        int product_id = 0;
        char client_name[128] = "";
        client_p client = NULL;
        fscanf(stdin, "%s", client_name);
        client = client_new(client_name);
        list_p prs = pricingrules_from_file("./conf/pricingrules.data");
        checkout_p co = checkout_new(prs, client);
        item_p item = NULL;
        fscanf(stdin, "%d", &quantity);
        while(quantity-- > 0) {
                fscanf(stdin, "%d", &product_id);
                item = item_new(product_get_by_id(product_id), 1);
                checkout_add(co, item);
        }
        total = checkout_total(co);
        fprintf(stderr, "total: %d.%d\n", total/100, total%100);
        checkout_del(co);
}


int main(int argc, char *argv[]) {
        product_init();
        process_order();
        return 0;
}

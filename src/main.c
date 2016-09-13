#include <stdio.h>
#include "../include/checkout.h"
#include "../include/pricingrules.h"
#include "../include/product.h"
#include "../include/client.h"
#include "../include/db.h"

#define CONF_FILE "./conf/pricingrules.data"

void process_order() {
        int total = 0;
        int quantity = 0;
        char product_id[128] = "";
        char client_name[CLIENT_MAX_NAME] = "";
        client_p client = NULL;
        fscanf(stdin, "%s", client_name);
        client = client_new(client_name);
        //list_p prs = pricingrules_from_file(CONF_FILE);
        list_p prs = pricingrules_from_db();
        checkout_p co = checkout_new(prs, client);
        item_p item = NULL;
        fscanf(stdin, "%d", &quantity);
        while(quantity-- > 0) {
                fscanf(stdin, "%s", product_id);
                item = item_new(product_get_by_id(product_id), 1);
                checkout_add(co, item);
        }
        total = checkout_total(co);
        fprintf(stderr, "total: %d.%d\n", total/100, total%100);
        checkout_del(co);
}


int main(int argc, char *argv[]) {
        db_init();
        process_order();
        db_free();
        return 0;
}

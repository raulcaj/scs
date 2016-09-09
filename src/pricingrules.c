#include "../include/checkout.h"
#include "../include/rules.h"
#include "../include/actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void try_match_and_execute(pricingrules_p pr, checkout_p co, item_p item);

struct s_match {
        rulematcher_p func;
        void* data;
        match_p next;
};

struct s_action {
        rulesaction_p func;
        void* data;
        action_p next;
};

struct s_pricingrules {
        match_p rule;
        action_p action;
        pricingrules_p next;
};

pricingrules_p pricingrules_from_file(char *filename) {
        pricingrules_p root_pr;
        int match_count = 0;
        int action_count = 0;
        char key[128] = "";
        char val[128] = "";
        FILE* db = fopen(filename, "r");
        pricingrules_p pr = NULL;
        while(!feof(db)) {
                pr = (pricingrules_p)malloc(sizeof(pricingrules_t));
                pr->next = NULL;
                fscanf(db,"\tmatch\t%d", &match_count);
                while(match_count-- > 0) {
                        fscanf(db, "\t%s\t%s", key, val);
                        append_match(pr, create_match(key,val));
                }
                fscanf(db,"\taction\t%d", &action_count);
                while(action_count-- > 0) {
                        fscanf(db, "\t%s\t%s", key, val);
                        append_action(pr, create_action(key,val));
                }
                root_pr = append_pricingrules(root_pr, pr);
        }
        return root_pr;
}

void pricingrules_execute(checkout_p co) {
        int i = 0;
        for(i = 0; i < checkout_get_items_count(co); ++i) {
                item_p item = checkout_get_item(co, i);
                try_match_and_execute(checkout_get_pricingrules(co), co, item);
        }
}

void try_match_and_execute(pricingrules_p pr, checkout_p co, item_p item) {
        int allmatching = 0;
        match_p match;
        action_p action;
        while(pr) {
                match = pr->rule;
                allmatching = 1;
                while(allmatching && match) {
                        allmatching = match->func(co, item, match->data);
                        match = match->next;
                }
                if(allmatching && !match) {
                        action = pr->action;
                        while(action) {
                                action->func(co, item, action->data);
                                action = action->next;
                        }
                        return;
                }
                pr = pr->next;
        }
}

match_p create_match(char *key, char *val) {
        match_p match = (match_p)malloc(sizeof(match_t));
        match->next = NULL;
        if(strcmp(key,"client") == 0) {
                match->func = match_client_name;
                match->data = malloc(sizeof(char)*(strlen(val)+1));
                strcpy((char*)match->data, val);
        } else if(strcmp(key, "product") == 0) {
                match->func = match_product_id;
                match->data = malloc(sizeof(int));
                *((int*)match->data) = atoi(val);
        } else if(strcmp(key, "quantity") == 0) {
                match->func = match_product_quantity;
                match->data = malloc(sizeof(int));
                *((int*)match->data) = atoi(val);
        }

        return match;
}

void append_match(pricingrules_p pr, match_p match) {
        match_p last = NULL;
        if(pr->rule == NULL) {
                pr->rule = match;
        }
        else {
                last = pr->rule;
                while(last->next != NULL) {
                        last = last->next;
                }
                last->next = match;
        }
}

action_p create_action(char *key, char *val) {
        action_p action = (action_p)malloc(sizeof(action_t));
        action->next = NULL;
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

void append_action(pricingrules_p pr, action_p action) {
        action_p last = NULL;
        if(pr->action == NULL) {
                pr->action = action;
        }
        else {
                last = pr->action;
                while(last->next != NULL) {
                        last = last->next;
                }
                last->next = action;
        }
}

pricingrules_p append_pricingrules(pricingrules_p root, pricingrules_p pr) {
        pricingrules_p last = NULL;
        if(root == NULL) {
                root = pr;
        } else {
                last = root;
                while(last->next != NULL) {
                        last = last->next;
                }
                last->next = pr;
        }
        return root;
}

#include "../include/checkout.h"
#include "../include/matchs.h"
#include "../include/actions.h"
#include "../include/list.h"
#include "../include/pricingrules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct s_pricingrules {
        list_p matchs;
        list_p actions;
};

pricingrules_p pricingrules_new() {
        pricingrules_p pr = (pricingrules_p)calloc(1,sizeof(pricingrules_t));
        pr->matchs = list_new();
        pr->actions = list_new();
        return pr;
}

list_p pricingrules_from_file(char *filename) {
        list_p prs = list_new();
        pricingrules_p pr = NULL;
        int match_count = 0;
        int action_count = 0;
        char key[128] = "";
        char val[128] = "";
        FILE* db = fopen(filename, "r");
        while(!feof(db)) {
                pr = pricingrules_new();
                fscanf(db,"\tmatch\t%d", &match_count);
                while(match_count-- > 0) {
                        fscanf(db, "\t%s\t%s", key, val);
                        list_add(pr->matchs, match_new(key,val));
                }
                fscanf(db,"\taction\t%d", &action_count);
                while(action_count-- > 0) {
                        fscanf(db, "\t%s\t%s", key, val);
                        list_add(pr->actions, action_new(key,val));
                }
                list_add(prs, pr);
        }
        fclose(db);
        return prs;
}

void list_match_del(void* ptr) {
        match_p match = ptr;
        match_del(match);
}

void list_action_del(void* ptr) {
        action_p action = ptr;
        action_del(action);
}

void pricingrules_del(pricingrules_p pr) {
        list_del(pr->matchs, list_match_del);
        list_del(pr->actions, list_action_del);
        free(pr);
}

void try_match_and_execute(void* co_param, void* item_param) {
//        checkout_p co = co_param;
//        item_p item = item_param;
//        list_p prs = checkout_get_pricingrules(co);
//        void match_all(void* result_param, void* match_param) {
//                int* result = result_param;
//                match_p match = match_param;
//                if(*result) {
//                        *result = match_execute(match, co, item);
//                }
//        }
//        void do_actions(void* data, void* action_param) {
//                action_p action = action_param;
//                action_execute(action, co, item);
//        }
//        void each_rule(void* data, void* pr_param) {
//                int result = 1;
//                pricingrules_p pr = pr_param;
//                list_foreach(pr->matchs, match_all, &result);
//                if(result) {
//                        list_foreach(pr->actions, do_actions, NULL);
//                }
//        }
//        list_foreach(prs, each_rule, NULL);
}


void pricingrules_execute(checkout_p co) {
        list_foreach(checkout_get_items(co), try_match_and_execute, co);
}


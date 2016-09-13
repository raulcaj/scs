#include <stdio.h>
#include <stdlib.h>
#include "../include/sqlite3.h"
#include "../include/parsers.h"
#include "../include/list.h"
#include "../include/pricingrules.h"
#include "../include/matchs.h"
#include "../include/actions.h"

#define DB_PATH "./db/scs.sqlite3"

static sqlite3 *db;

void db_init() {
        sqlite3_open(DB_PATH, &db);
}

void db_free() {
        sqlite3_close(db);
}

void db_retrieve_product_by_id(const char* id, char* *name, int *price) {
        char query[512] = "";
        const char *sql = "SELECT name, price FROM PRODUCTS WHERE ID = '%s';";
        sprintf(query, sql, id);
        int callback(void *data, int argc, char* *argv, char* *cols) {
                *name = (char*)parser_copychar(argv[0]);
                *price = atoi(argv[1]);
                return 0;
        }
        sqlite3_exec(db, query, callback, NULL, NULL);
}


void db_retrieve_pricingrules(list_p *prs) {
        const char *query= "SELECT PRICINGRULES.ID" \
                           " FROM PRICINGRULES" \
                           " WHERE PRICINGRULES.ENABLED = 1;";
        *prs = list_new();
        int each_rule(void *data, int argc, char* *argv, char* *cols) {
                pricingrules_p pr = pricingrules_new();
                char* id = argv[0];
                char query[512] = "";
                const char *sql_match = "SELECT MATCHINGRULES.MATCH_KEY, MATCHINGRULES.MATCH_VALUE" \
                        " FROM PRICINGRULES" \
                        " INNER JOIN PR2MATCH ON PRICINGRULES.ID = PR2MATCH.PR_ID" \
                        " INNER JOIN MATCHINGRULES ON MATCHINGRULES.ID = PR2MATCH.MATCH_ID" \
                        " WHERE PRICINGRULES.ID = %s;";
                const char *sql_action = "SELECT ACTIONRULES.ACTION_KEY, ACTIONRULES.ACTION_VALUE" \
                        " FROM PRICINGRULES" \
                        " INNER JOIN PR2ACTION ON PRICINGRULES.ID = PR2ACTION.PR_ID" \
                        " INNER JOIN ACTIONRULES ON ACTIONRULES.ID = PR2ACTION.ACTION_ID" \
                        " WHERE PRICINGRULES.ID = %s;";
                sprintf(query, sql_match, id);
                int each_match(void *data, int argc, char* *argv, char* *cols) {
                        list_add(pricingrules_get_matchs(pr), match_new(argv[0], argv[1]));
                        return 0;
                }
                sqlite3_exec(db, query, each_match, NULL, NULL);
                sprintf(query, sql_action, id);
                int each_action(void *data, int argc, char* *argv, char* *cols) {
                        list_add(pricingrules_get_actions(pr), action_new(argv[0], argv[1]));
                        return 0;
                }
                sqlite3_exec(db, query, each_action, NULL, NULL);
                list_add(*prs, pr);
                return 0;
        }
        sqlite3_exec(db, query, each_rule, NULL, NULL);
}

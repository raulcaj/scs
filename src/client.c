#include "../include/client.h"
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 128

struct s_client {
        char* name;
};

char* client_get_name(client_p client) {
        return client->name;
}

client_p client_new(const char *name) {
        client_p client = (client_p)malloc(sizeof(client_t));
        client->name = (char*)malloc(sizeof(char)*MAX_NAME);
        strncpy(client->name, name, MAX_NAME);
        return client;
}

void client_del(client_p client) {
        free(client->name);
        free(client);
}

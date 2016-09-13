#include "../include/client.h"
#include <stdlib.h>
#include <string.h>


struct s_client {
        char* name;
};

char* client_get_name(client_p client) {
        return client->name;
}

client_p client_new(const char *name) {
        client_p client = (client_p)malloc(sizeof(client_t));
        client->name = (char*)malloc(sizeof(char)*CLIENT_MAX_NAME);
        strncpy(client->name, name, CLIENT_MAX_NAME);
        return client;
}

void client_del(client_p client) {
        free(client->name);
        free(client);
}

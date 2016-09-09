#include "../include/client.h"
#include <stdlib.h>

struct s_client {
        char* name;
};

char* client_get_name(client_p client) {
        return client->name;
}

client_p client_new(char *name) {
        client_p client = (client_p)malloc(sizeof(client_t));
        client->name = name;
        return client;
}

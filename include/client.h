#ifndef CLIENT_H
#define CLIENT_H

#define CLIENT_MAX_NAME 128

typedef struct s_client client_t, *client_p;

char* client_get_name(client_p client);
client_p client_new(const char *name);
void client_del(client_p client);
#endif

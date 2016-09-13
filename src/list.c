#include "../include/list.h"
#include <stdlib.h>

typedef struct node_s {
        void *data;
        struct node_s *next;
} node_t, *node_p;

struct list_s {
        node_p head;
        node_p tail;
        int count;
};


list_p list_new() {
        list_p list = (list_p)malloc(sizeof(list_t));
        list->head = list->tail = NULL;
        list->count = 0;
        return list;
}

void list_add(list_p list, void* data) {
        node_p node = (node_p)malloc(sizeof(node_t));
        node->next = NULL;
        node->data = data;

        if(list->head == NULL) {
                list->head = node;
        }
        if(list->tail != NULL) {
                list->tail->next = node;
        }
        list->tail = node;
        list->count++;
}

void list_del(list_p list, list_free_p func) {
        node_p tmp = NULL;
        while(list->head) {
                tmp = list->head->next;
                func(list->head->data);
                free(list->head);
                list->head = tmp;
        }
        free(list);
}

void list_foreach(list_p list, list_each_p func, void* data) {
        node_p node = list->head;
        while(node) {
                func(data, node->data);
                node = node->next;
        }
}

int list_count(list_p list) {
        return list->count;
}

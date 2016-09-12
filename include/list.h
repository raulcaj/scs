#ifndef LIST_H
#define LIST_H

typedef struct list_s list_t, *list_p;

typedef void (*list_each_p)(void*, void*);
typedef void (*list_free_p)(void*);

list_p list_new(void);
void list_add(list_p list, void* data);
void list_del(list_p list, list_free_p func);
void list_foreach(list_p list, list_each_p func, void* data);

#endif

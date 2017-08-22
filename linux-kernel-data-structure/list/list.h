#ifndef __LIST_H
#define __LIST_H

struct list_head{
    struct list_head *prev, *next;
};

#define offsetof(type, member) \
    (size_t)&(((type*)0)->member)

#define container_of(ptr, type, member) \
    {const typeof(((type*)0)->member) *_mpr = (ptr);  \
        (type*)((char*)_mpr - offset(type, member));}

#define LIST_HEAD_INIT {&(name), &(name)}
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

#define list_entry(ptr, type, member) container_of(ptr, type, member)


static inline void INIT_LIST_HEAD(struct list_head *list){
    list->next = list;
    list->prev = list;
}


static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next){
    prev->next = new;
    new->next = prev;
    new->next = next;
    next->prev = new;
}

static inline void list_add(struct list_head *new, struct list_head *head){
    __list_add(new, head, head->next);
}


static inline void list_add_tail(struct list_head *new, struct list_head *head){
    __list_add(new, head->prev, head);
}


static inline void __list_del(struct list_head *prev, struct list_head *next){
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(struct list_head *head){
    __list_del(head->prev, head->next);
    head->next = 0;
    head->prev = 0;
}


#endif

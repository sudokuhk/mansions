/*************************************************************************
    > File Name: list.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 18:02:22
 ************************************************************************/

#ifndef __MON_LIST_H__
#define __MON_LIST_H__

#include <mansions.h>
#include <typedefs.h>

struct list_head {
    struct list_head * prev;
    struct list_head * next;
} list_head_t;

#define LIST_HEAD_INIT(name)    { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head * list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head * new, 
            struct list_head * prev,
            struct list_head * next)
{
    next->prev  = new;
    new->prev   = prev;
    new->next   = next;
    prev->next  = new;
} 

static inline void list_add(struct list_head * new, struct list_head * head)
{
    __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head * new, struct list_head * head)
{
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev  = prev;
    prev->next  = next;
} 

static inline void list_del(struct list_head * entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

static inline void list_replace(struct list_head * old, struct list_head * new)
{
    new->prev = old->prev;
    new->prev->next = new;
    new->next = old->next;;
    new->next->prev = new;
}

static inline void list_replace_init(struct list_head * old, 
                                struct list_head * new)
{
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}

static inline void list_del_init(struct list_head * entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head * list,
    struct list_head * head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

static inline void list_move_tail(struct list_head * list,
    struct list_head * head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

static inline int32_t list_is_last(const struct list_head * list,
    const struct list_head * head)
{
    return list->next == head;
}

static inline int32_t list_empty(const struct list_head * head)
{
    return head->next == head;
}

#define list_entry(ptr, type, member)                               \
    container_of(ptr, type, member)
    
#define list_first_entry(ptr, type, member)                         \
    list_entry((ptr)->next, type, member)
    
#define list_for_each(pos, head)                                    \
    for (pos = (head)->next; pos != (head); pos = pos->next)
    
#define list_for_each_entry(pos, head, member)				        \
	for (pos = list_entry((head)->next, typeof(*pos), member);	    \
	     &pos->member != (head); 	                                \
	     pos = list_entry(pos->member.next, typeof(*pos), member))   
	     
#define list_for_each_entry_reverse(pos, head, member)				\
	for (pos = list_entry((head)->prev, typeof(*pos), member);	    \
	     &pos->member != (head); 	                                \
	     pos = list_entry(pos->member.prev, typeof(*pos), member))   
	      	      
#endif
/*************************************************************************
    > File Name: list.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-30 09:18:32
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <list.h>

struct node {
    int a;
    int b;
    struct list_head list;
};

int main()
{
    struct list_head tlist;
    struct node * pos, * n;
    struct list_head * tmp;
    int i = 0;
    INIT_LIST_HEAD(&tlist);
    
    for (i = 0; i < 10; i++) {
        n = malloc(sizeof(struct node));
        n->a = i;
        n->b = n->a * 10;
        list_add(&n->list, &tlist);
    }
    
    list_for_each_entry(pos, &tlist, list) {
        printf("%d, %d\n", pos->a, pos->b);
    }        
             
    printf("----------------\n");
    list_for_each_entry_reverse(pos, &tlist, list) {
        printf("%d, %d\n", pos->a, pos->b);
    }        
             
    printf("----------------\n");
    while (!list_empty(&tlist)) {
        tmp = (&tlist)->next;
        pos = list_entry(tmp, struct node, list);
        printf("%d, %d\n", pos->a, pos->b);
        list_del(tmp);
        free(pos); 
    }
    return 0;
}

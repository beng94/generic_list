#ifndef GLIST_H
#define GLIST_H

#include <stdlib.h>

typedef struct glist
{
    void* data;
    struct glist* next;
} glist;

typedef int (*gcompare)(void*, void*);
typedef void (*gdestroy)(void*);
typedef void* (*gcopy)(void*);
typedef void (*gfunc)(void* data, void* usr_data);

glist* glist_alloc(void);
glist* glist_append (glist* root, void* data);
glist* glist_prepend (glist* root, void* data);
glist* glist_insert (glist* root, void* data, int id);
glist* glist_insert_before(glist* root, glist* sibling, void* data);
glist* glist_insert_sorted(glist* root, void* data, gcompare);
glist* glist_remove(glist* root, void* data);
glist* glist_remove_link(glist* root, glist* link);
glist* glist_delete_link(glist* root, glist* link);
glist* glist_remove_all(glist* root, void* data);
void glist_free(glist* root);
void glist_free_full(glist* root, gdestroy free_func);
void glist_free_1(glist* item);
int glist_length(glist* root);
glist* glist_copy(glist* root);
glist* glist_copy_deep(glist* root, gcopy copy_func);
glist* glist_reverse(glist* root);
glist* glist_sort(glist* root, gcompare cmp_func);
glist* glist_concat(glist* list_a, glist* list_b);
void glist_foreach(glist* root, gfunc func, void* urs_data);
glist* glist_last(glist* root);
glist* glist_first(glist* root);
glist* glist_previous(glist* root, glist* item);
glist* glist_next(glist* item);
glist* glist_nth(glist* root, int id);
void* glist_nth_data (glist* root, int id);
glist* glist_nth_prev(glist* root, int id);
glist* glist_find(glist* root, void* data);
glist* glist_find_custom(glist* root, void* data, gcompare cmp_func);
int glist_position(glist* root, glist* item);
int glist_index(glist* root, void* data);

#endif

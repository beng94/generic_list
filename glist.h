#include <stdlib.h>

typedef struct glist
{
    void* data;
    struct glist* next;
} glist;

typedef int (*gcompare)(void*, void*);

glist* glist_append (glist* root, void* data);
glist* glist_prepend (glist* root, void* data);
glist* glist_insert (glist* root, void* data, int id);
glist* glist_insert_before(glist* root, glist* sibling, void* data);
glist* glist_insert_sorted(glist* root, void* data, gcompare);
glist* glist_remove(glist* root, void* data);
glist* glist_remove_link(glist *root, glist *link);
glist* glist_last(glist* root);
glist* glist_first(glist* root);
int glist_length (glist* root);
void* glist_nth_data (glist* root, int id);

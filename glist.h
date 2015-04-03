#include <stdlib.h>

typedef struct glist
{
    void* data;
    struct glist* next;
    //struct glist* prev;
} glist;

glist* glist_append (glist* root, void* data);
glist* glist_prepend (glist* root, void* data);
int glist_length (glist* root);
void* glist_nth_data (glist* root, int id);
//TODO: delete: first, id

#include "glist.h"

glist* glist_append(glist* root, void* data)
{
    glist *new = malloc(sizeof(glist));
    new->data = data;
    new->next = NULL;

    if(root == NULL) return new;

    else
    {
        glist *tmp = root;
        while(tmp->next != NULL) tmp = tmp->next;

        tmp->next = new;
    }

    return root;
}

glist* glist_prepend (glist* root, void* data)
{
    glist *new = (glist*)malloc(sizeof(glist));
    new->data = data;
    new->next = root;

    return new;
}

int glist_length(glist* root)
{
    glist* tmp = root;
    int cnt = 0;

    while(tmp != NULL)
    {
        tmp = tmp->next;
        cnt++;
    }

    return cnt;
}

void* glist_nth_data (glist* root, int id)
{
    if(id >= glist_length(root)) return NULL;

    glist* tmp = root;
    for(int i = 0; i<id; i++) tmp = tmp->next;

    return tmp->data;
}

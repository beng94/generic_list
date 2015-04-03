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

glist* glist_insert(glist* root, void* data, int id)
{
    //TODO: check glist_length -1 ?
    if(id < 0 || id > glist_length(root))
        root = glist_append(root, data);

    else
    {
        glist *tmp = root;
        for(int i = 0; i<id; i++) tmp = tmp->next;

        glist *new = (glist*)malloc(sizeof(glist));
        new->data = data;
        new->next = tmp->next;

        tmp->next = new;
    }

    return root;
}

glist* glist_insert_before(glist* root, glist* sibling, void* data)
{
    glist* tmp = root;
    while(tmp->next != sibling || tmp != NULL) tmp = tmp->next;

    if(tmp == NULL) root = glist_append(root, data);
    else
    {
        glist *new = (glist*)malloc(sizeof(glist));
        new->data = data;
        new->next = sibling;

        tmp->next = new;
    }

    return root;
}

glist* glist_insert_sorted(glist* root, void* data, gcompare cmp)
{
    if(cmp == NULL) root = glist_append(root, data);
    else
    {
        glist *tmp = root;
        while(tmp != NULL && cmp(tmp->data, data) < 0) tmp = tmp->next;

        root = glist_insert_before(root, tmp, data);
    }

    return root;
}

glist* glist_remove(glist* root, void* data)
{
    if(root == NULL) return root;
    else
    {
        if(root->data == data)
        {
            free(root);
            root = root->next;
        }
        else
        {
            glist *tmp = root;
            while(tmp->next->data != data && tmp->next->next != NULL)
                tmp = tmp->next;

            glist* del = tmp->next;
            tmp->next = del->next;
            free(del);
        }
    }
    return root;
}

glist* glist_remove_link(glist* root, glist* link)
{
    if(root == NULL) return root;
    else
    {
        if(root->next == link)
        {
            root->next = link->next;
        }
        else
        {
            glist *tmp = root;
            while(tmp->next->next != link && tmp->next->next != NULL)
                tmp = tmp->next;

            tmp->next = link->next;
        }
    }

    return root;
}

glist* glist_last(glist* root)
{
    glist *tmp = root;
    while(tmp->next != NULL) tmp = tmp->next;

    return tmp;
}

glist* glist_first(glist* root)
{
    return root;
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

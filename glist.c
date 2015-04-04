#include "glist.h"

glist* glist_alloc(void)
{
    return (glist*)malloc(sizeof(glist));
}

glist* glist_append(glist* root, void* data)
{
    glist *new = glist_alloc();
    new->data = data;
    new->next = NULL;

    if(root == NULL) return new;
    else
    {
        while(root->next != NULL) root = root->next;

        root->next = new;
    }

    return root;
}

glist* glist_prepend (glist* root, void* data)
{
    glist *new = glist_alloc();
    new->data = data;
    new->next = root;

    return new;
}

glist* glist_insert(glist* root, void* data, int id)
{
    if(id <=  0)
        return glist_prepend(root, data);

    if(id > glist_length(root))
        return glist_append(root, data);

    else
    {
        glist *prev = glist_nth(root, id-1);

        glist *new = glist_alloc();
        new->data = data;
        new->next = prev->next;

        prev->next = new;
    }

    return root;
}

glist* glist_insert_before(glist* root, glist* sibling, void* data)
{
    while(root->next != NULL && root->next != sibling) root = root->next;

    if(root->next == NULL) root = glist_append(root, data);
    else
    {
        glist *new = glist_alloc();
        new->data = data;
        new->next = sibling;

        root->next = new;
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

glist* glist_delete_link(glist* root, glist* link)
{
    if(root == NULL) return root;
    else
    {
        if(root->next == link)
        {
            root->next = link->next;
            free(link);
        }
        else
        {
            glist *tmp = root;
            while(tmp->next->next != link && tmp->next->next != NULL)
                tmp = tmp->next;

            tmp->next = link->next;
            free(link);
        }
    }

    return root;
}

glist* glist_remove_all(glist* root, void* data)
{
    if(root == NULL) return root;
    else
    {
        while(root->data == data)
        {
            glist* rm = root;
            root = root->next;
            free(rm);
        }

        glist* tmp = root;
        while(tmp->next->data == data && tmp->next != NULL)
        {
            tmp->next = tmp->next->next;
            free(tmp->next);
        }
    }

    return root;
}

void glist_free(glist* root)
{
    glist* rm = root;
    while(rm != NULL)
    {
        glist* next = rm->next;
        free(rm);
        rm = next;
    }
}

void glist_free_full (glist* root, gdestroy free_func)
{
    glist* rm = root;
    while(rm != NULL)
    {
        glist* next = rm->next;
        free_func(rm->data);
        free(rm);
        rm = next;
    }
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

void* glist_nth_data (glist* root, int id)
{
    if(id >= glist_length(root)) return NULL;

    glist* tmp = root;
    for(int i = 0; i<id; i++) tmp = tmp->next;

    return tmp->data;
}

void glist_free_1(glist* item)
{
    free(item);
}

glist* glist_copy(glist* root)
{
    glist* new_root = NULL;

    glist* ptr = root;
    while(ptr != NULL)
    {
        new_root = glist_append(new_root, ptr->data);
        ptr = ptr->next;
    }

    return new_root;
}

glist* glist_copy_deep(glist* root, gcopy copy_func)
{
    glist* new_root = NULL;

    glist* ptr = root;
    while(ptr != NULL)
    {
        void* new_data = copy_func(ptr->data);
        new_root = glist_append(new_root, new_data);
        ptr = ptr->next;
    }

    return new_root;
}

glist* glist_nth(glist* root, int id)
{
    glist* tmp = root;
    for(int i = 0; i<id; i++) tmp = tmp->next;

    return tmp;
}

glist* glist_reverse(glist* root)
{
    int len = glist_length(root);

    for(int i = 0; i<len/2; i++)
    {
        glist* chg_a = glist_nth(root, i);
        glist* chg_b = glist_nth(root, len-1-i);

        void* tmp = chg_a->data;
        chg_a->data = chg_b->data;
        chg_b->data = tmp;
    }

    return root;
}

glist* glist_sort(glist* root, gcompare cmp_func)
{
    int len = glist_length(root);

    glist* tmp_a = root;
    for(int i = 0; i<len; i++)
    {
        glist* tmp_b = root;
        for(int j = 0; j<len; j++)
        {
            if(cmp_func(tmp_a->data, tmp_b->data))
            {
                void* chg = tmp_a->data;
                tmp_a->data = tmp_b->data;
                tmp_b->data = chg;
            }
            tmp_b = tmp_b->next;
        }

        tmp_a = tmp_a->next;
    }

    return root;
}

glist* glist_concat (glist* list_a, glist* list_b)
{
    glist* last = glist_last(list_a);
    last->next = list_b;

    return list_a;
}

void glist_foreach(glist* root, gfunc func, void* usr_data)
{
    glist* ptr = root;
    while(ptr)
    {
        (*func)(ptr->data, usr_data);
        ptr = ptr->next;
    }
}

glist* glist_previous(glist* root, glist* item)
{
    glist* out = NULL;

    glist* ptr = root;
    if(ptr == NULL) return out;
    else
    {
        while(ptr->next != NULL || ptr->next != item) ptr = ptr->next;
        if(ptr->next != NULL) out = ptr;
    }

    return out;
}

glist* glist_next(glist* item)
{
    return item->next;
}

glist* glist_nth_prev(glist* root, int id)
{
    if(id <= 0) return NULL;

    return glist_nth(root, id-1);
}

glist* glist_find(glist* root, void* data)
{
    glist* out = NULL;

    while(root != NULL)
    {
        if(root->data == data)
        {
            out = root;
            break;
        }
        root = root->next;
    }

    return out;
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


glist* glist_find_custrom(glist* root, void* data, gcompare cmp_func)
{
    glist* out = NULL;

    glist* ptr = root;
    while(ptr!= NULL)
    {
        if(cmp_func(data, ptr->data) == 0)
        {
            out = ptr;
            break;
        }
        ptr = ptr->next;
    }

    return out;
}

int glist_position(glist* root, glist* item)
{
    int out = -1;

    int id = 0;
    glist* ptr = root;
    while(ptr != NULL)
    {
        if(ptr == item) return id;

        id++;
        ptr = ptr->next;
    }

    return out;
}

int glist_index(glist* root, void* data)
{
    int out = -1;

    int id = 0;
    glist* ptr = root;
    while(ptr != NULL)
    {
        if(ptr->data == data) return id;

        id++;
        ptr = ptr->next;
    }

    return out;
}

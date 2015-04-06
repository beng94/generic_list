#include "test.h"

int tst_glist_append()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_append:\n");
    printf("expected output: 1 2\n");

    printf("%d %d", *(int*)root->data, *(int*)root->next->data);

    return 1;
}

int tst_glist_prepend()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_prepend(root, (void*)&a);
    root = glist_prepend(root, (void*)&b);

    printf("tst_glist_prepend:\n");
    printf("expected output: 2 1\n");

    printf("%d %d", *(int*)root->data, *(int*)root->next->data);

    return 1;
}

int tst_glist_insert()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_insert(root, (void*)&a, -1);
    root = glist_insert(root, (void*)&a, 3);
    root = glist_insert(root, (void*)&b, 2);
    root = glist_insert(root, (void*)&c, 3);
    root = glist_insert(root, (void*)&a, 2);

    printf("tst_glist_insert:\n");
    printf("expected output: 1 1 1 2 3\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_insert_before()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&a);
    root = glist_insert_before(root, root->next, (void*)&b);
    root = glist_insert_before(root, root, (void*)&b);

    printf("tst_glist_insert_before:\n");
    printf("expected output: 2 1 2 1\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

static int cmp (void* a, void* b)
{
    int aa = *(int*)a;
    int bb = *(int*)b;

    if(aa > bb) return 1;
    if(aa == bb) return 0;
    return -1;
}


int tst_glist_insert_sorted()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_insert_sorted(root, (void*)&a, cmp);
    root = glist_insert_sorted(root, (void*)&b, cmp);
    root = glist_insert_sorted(root, (void*)&a, cmp);
    root = glist_insert_sorted(root, (void*)&a, cmp);

    printf("tst_glist_insert_sorted:\n");
    printf("expected output: 1 1 1 2\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_remove()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (int*)&a);
    root = glist_append(root, (int*)&b);
    root = glist_append(root, (int*)&a);
    root = glist_append(root, (int*)&a);
    root = glist_append(root, (int*)&b);

    root = glist_remove(root, (int*)&a);
    root = glist_remove(root, (int*)&a);
    root = glist_remove(root, (int*)&b);

    printf("tst_glist_remove\n");
    printf("expected output: 1 2\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_remove_link()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    root = glist_remove_link(root, root);
    root = glist_remove_link(root, root->next->next);

    printf("tst_glist_remove_link:\n");
    printf("expected output: 2 1\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_delete_link()
{
    //TODO: should check whether the memery is freed
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    root = glist_remove_link(root, root);
    root = glist_remove_link(root, root->next->next);

    printf("tst_glist_remove_link:\n");
    printf("expected output: 2 1\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_remove_all()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&a);

    root = glist_remove_all(root, (void*)&a);

    printf("tst_glist_remove_all:\n");
    printf("expected output: 2\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

//TODO: it doesnt work
int tst_glist_free()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    glist_free(root);
    root = glist_append(root, (void*)&a);

    printf("tst_glist_free\n");
    printf("expecte output: empty\n");
    if(root == NULL) printf("empty");
    else printf("not empty");

    printf("\n%d\n", *(int*)(root->data));

    return 1;
}

int tst_glist_last()
{
    int a = 1;
    int b = 2;

    glist* root= NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_last:\n");
    printf("expected output: 2\n");
    printf("%d",  *(int*)glist_last(root)->data);

    root = glist_append(root, (void*)&a);

    return 1;
}

int tst_glist_nth_data()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&c);

    printf("tst_list_nth_data:\n");
    printf("expected output: 1 2 3\n");
    printf("%d %d %d", *(int*)glist_nth_data(root, 0),
                       *(int*)glist_nth_data(root, 1),
                       *(int*)glist_nth_data(root, 2));

    return 1;
}

int tst_glist_copy()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&c);

    glist* new_list = glist_copy(root);

    printf("tst_glist_copy\n");
    printf("expected output: 1 2 3\n");

    while(new_list != NULL)
    {
        printf("%d ", *(int*)new_list->data);
        new_list = new_list->next; //modifies the list
    }

    return 1;
}

//TODO: cannot check until free functions checked
int tst_glist_copy_deep() { return 1;}

int tst_glist_nth()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&c);

    printf("tst_glist_nth\n");
    printf("expected output: 1 2 3\n");
    printf("%d %d %d", *(int*)glist_nth(root, 0)->data,
                       *(int*)glist_nth(root, 1)->data,
                       *(int*)glist_nth(root, 2)->data);

    root = glist_append(root, (void*)&a);
    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_reverse()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&c);

    root = glist_reverse(root);

    printf("tst_glist_reverse\n");
    printf("expected output: 3 2 1\n");

    glist* tmp = root;
    while(tmp != NULL)
    {
        printf("%d ", *(int*)tmp->data);
        tmp = tmp->next; //modifies the list
    }

    printf("\n");
    root = glist_append(root, (void*)&a);
    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_sort()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&d);
    root = glist_append(root, (void*)&d);
    root = glist_append(root, (void*)&c);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&a);

    root = glist_sort(root, cmp);

    printf("tst_glist_sort\n");
    printf("expected output: 1 1 2 3 4 4\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

int tst_glist_concat()
{
    int a = 1;
    int b = 2;
    //int c = 3;
    //int d = 4;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    glist* new_root = NULL;
    //new_root = glist_append(new_root, (void*)&c);
    //new_root = glist_append(new_root, (void*)&d);
    root = glist_concat(root, new_root);

    printf("tst_glist_concat\n");
    printf("expected output: 1 2\n");

    while(root != NULL)
    {
        printf("%d ", *(int*)root->data);
        root = root->next; //modifies the list
    }

    return 1;
}

static void func(void* data, void* usr_data)
{
    printf("%d ", *(int*)data);
}

int tst_glist_foreach()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_foreach\n");
    printf("expected output: 1 1 2\n");

    glist_foreach(root, func, NULL);

    return 1;
}

int tst_glist_previous()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_previous\n");
    printf("expected output: 1 NULL\n");

    printf("%d ", *(int*)glist_previous(root, root->next)->data);
    if(glist_previous(root, root) == NULL) printf("NULL");
    else printf("not NULL");

    return 1;
}

int tst_glist_nth_prev()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_nth_prev\n");
    printf("expected output: 1 2 NULL NULL\n");

    printf("%d ", *(int*)glist_nth_prev(root, 1)->data);
    printf("%d ", *(int*)glist_nth_prev(root, 2)->data);
    if(glist_nth_prev(root, 0) == NULL) printf("NULL ");
    else printf("not NULL ");
    if(glist_nth_prev(root, 3) == NULL) printf("NULL ");
    else printf("not NULL ");

    return 1;
}

int tst_glist_find()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_find\n");
    printf("expected output: 1 2 NULL\n");
    printf("%d ", *(int*)glist_find(root, (void*)&a)->data);
    printf("%d ", *(int*)glist_find(root, (void*)&b)->data);
    if(glist_find(root, (void*)&c) == NULL) printf("NULL");
    else printf("not NULL");

    return 1;
}

int tst_glist_length()
{
    int a = 1;
    int b = 2;

    glist* root = NULL;
    int len_a = glist_length(root);
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    int len_b = glist_length(root);

    printf("tst_glist_length\n");
    printf("expected output: 0 2\n");
    printf("%d %d", len_a, len_b);

    return 1;
}

int tst_glist_find_custom()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_find_custom\n");
    printf("expected output: 1 NULL\n");
    printf("%d ", *(int*)glist_find_custom(root, (void*)&a, cmp)->data);
    if(glist_find_custom(root, (void*)&c, cmp) == NULL) printf("NULL");
    else printf("not NULL");

    return 1;
}

int tst_glist_position()
{
    int a = 1;
    int b = 2;

    glist* tst = NULL;
    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_position\n");
    printf("expected output: 0 1 NULL\n");
    printf("%d ", glist_position(root, root));
    printf("%d ", glist_position(root, root->next));
    if(glist_position(root, tst) == -1) printf("NULL");
    else printf("not NULL");

    return 1;
}

int tst_glist_index()
{
    int a = 1;
    int b = 2;
    int c = 3;

    glist* root = NULL;
    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);

    printf("tst_glist_index\n");
    printf("expected output: 0 1 NULL\n");
    printf("%d ", glist_index(root, (void*)&a));
    printf("%d ", glist_index(root, (void*)&b));
    if(glist_index(root, (void*)&c) == -1) printf("NULL");
    else printf("not NULL");

    return 1;
}

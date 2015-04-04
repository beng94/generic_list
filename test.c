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

#include "glist.h"
#include <stdio.h>

int main()
{
    glist* root = NULL;

    int a = 10;
    int b = 20;
    int c = 30;

    root = glist_append(root, (void*)&a);
    root = glist_append(root, (void*)&b);
    root = glist_append(root, (void*)&c);

    printf("%d\n", glist_length(root));

    for(int i=0; i<5; i++)
    {
        int* tmp = glist_nth_data(root, i);
        if(tmp == NULL) printf("NULL\n");
        else
        {
            printf("%d\n", *tmp);
        }
    }


    return 0;
}

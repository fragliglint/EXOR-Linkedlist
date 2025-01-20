

#include <stdio.h>
#include <stdlib.h>


struct node
{
    int d;
    struct node* l;
};


struct node* XOR(struct node* p, struct node* q)
{
    return (struct node*)((uintptr_t)(p) ^ (uintptr_t)(q));
}


struct node* createnode(int d)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->d = d;
    node->l = NULL;
    return node;
}


struct node* createlist()
{
    int x;
    printf("Enter the size of the list: \n");
    scanf("%d", &x);

    struct node* h = NULL;
    struct node* t = NULL;

    for (int i = 0; i < x; i++)
    {
        int d;
        printf("Enter the element %d: ", i + 1);
        scanf("%d", &d);

        struct node* m = createnode(d);

        if (h == NULL)
        {
            h = m;
            t = m;
        }
        else
        {
            t->l = XOR(m, t->l);
            m->l = t;
            t = m;
        }
    }

    return h;
}


void display(struct node* h)
{
    struct node* c = h;
    struct node* prev = NULL;
    struct node* next;

    while (c != NULL)
    {
        printf("%d--> ", c->d);
        next = XOR(prev, c->l);
        prev = c;
        c = next;
    }
    printf("NULL\n");
}


void insertAtBeginning(struct node** h, int d)
{
    struct node* m = createnode(d);
    m->l = *h;
    if(*h!=NULL)
    {
        (*h)->l = XOR(m, (*h)->l);
    }

    *h = m;
}



void insertAtPosition(struct node** h, int d, int p)
{
    if (p <= 0)
    {
        insertAtBeginning(h, d);
        return;
    }

    struct node* m = createnode(d);

    if (*h == NULL)
    {
        m->l = NULL;
        *h = m;
        return;
    }

    struct node* c = *h;
    struct node* prev = NULL;
    struct node* next;
    int a= 1;

    while (c != NULL && a< p)
    {
        next = XOR(prev, c->l);
        prev = c;
        c = next;
        a++;
    }

    if (c == NULL)
    {

        prev->l = XOR(m, prev->l);
        m->l = prev;
    }
    else
    {

        m->l = XOR(prev, c);
        prev->l = XOR(XOR(prev->l, c), m);
        if (c->l != NULL)
        {
            c->l = XOR(m, XOR(prev, c->l));
        }
    }
}


void deleteAtBeginning(struct node** h)
{
    if (*h == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    struct node* next = XOR(NULL, (*h)->l);
    if (next != NULL)
    {
        next->l = XOR(NULL, XOR(*h, next->l));
    }

    free(*h);
    *h = next;
}



void deleteAtPosition(struct node** h, int p)
{
    if (p <= 0)
    {
        deleteAtBeginning(h);
        return;
    }

    if (*h == NULL)
    {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    struct node* c = *h;
    struct node* prev = NULL;
    struct node* next;
    int a= 1;

    while (c != NULL && a< p)
    {
        next = XOR(prev, c->l);
        prev = c;
        c = next;
        a++;
    }

    if (c == NULL)
    {
        printf("Position not found. Cannot delete.\n");
    }
    else
    {

        struct node* next = XOR(prev, c->l);
        if (next != NULL)
        {
            next->l = XOR(prev, XOR(c, next->l));
        }

        if (prev != NULL)
        {
            prev->l = XOR(XOR(prev->l, c), next);
        }

        free(c);
    }
}


struct node* searchByKey(struct node* h, int k)
{
    struct node* c = h;
    struct node* prev = NULL;
    struct node* next;

    while (c != NULL && c->d != k)
    {
        next = XOR(prev, c->l);
        prev = c;
        c = next;
    }


    if (c != NULL && c->d == k)
    {
        return c;
    }
    else
    {
        return NULL;
    }
}
void reverseList(struct node** h)
{
    struct node* c = *h;
    struct node* prev = NULL;
    struct node* next;

    while (c != NULL)
    {
        next = XOR(prev, c->l);
        prev = c;
        c = next;
    }


    *h = prev;
}

int main()
{
    struct node* h = NULL;
    int choice, d, p, k;

    do
    {
        printf("\nPlease choose one option from below:\n\n");
        printf("press (1) for Create XOR Linked List\n");
        printf("press (2) for Display the List\n");
        printf("press (3) for Insert at the Beginning.\n");
        printf("press (4) for Insert at any Position. \n");
        printf("press (5) for Delete at Beginning\n");
        printf("press (6) for Delete at any Position\n");
        printf("press (7) for Search Value using Key\n");
        printf("press (8) for reverse the list\n");
        printf("press (0) for Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            h = createlist();
            printf("XOR Linked List created successfully.\n");
            break;

        case 2:
            if (h == NULL)
            {
                printf("List is empty.\n");
            }
            else
            {
                printf("XOR Linked List: ");
                display(h);
            }
            break;

        case 3:
            printf("Enter the data to insert at the beginning of the list: ");
            scanf("%d", &d);
            insertAtBeginning(&h, d);
            printf("node inserted at the beginning of the list.\n");
            break;

        case 4:
            printf("Enter the data to insert at any position: ");
            scanf("%d", &d);
            printf("Enter the position to insert at: ");
            scanf("%d", &p);
            insertAtPosition(&h, d, p);
            printf("node inserted at position %d.\n", p);
            break;

        case 5:
            deleteAtBeginning(&h);
            printf("node deleted from the beginning.\n");
            break;

        case 6:
            printf("Enter position to delete from: ");
            scanf("%d", &p);
            deleteAtPosition(&h, p);
            printf("node deleted from position %d.\n", p);
            break;

        case 7:
            printf("Enter key to search: ");
            scanf("%d", &k);
            struct node* r = searchByKey(h, k);
            if (r != NULL)
            {
                printf("Key found in the list.\n");
            }
            else
            {
                printf("Key not found in the list.\n");
            }
            break;
        case 8:
            reverseList(&h);
            printf("XOR Linked List reversed successfully.\n");
            break;

        case 0:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 0);

    return 0;
}

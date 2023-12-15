#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node
{
    int element, npl;
    struct Node *left;
    struct Node *right;
};

struct LeftHeap
{
    struct Node *head;
};

struct Node *createNode(int element)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->npl = 0;
    return newNode;
}

struct LeftHeap *createLeftHeap()
{
    struct LeftHeap *heap = (struct LeftHeap *)malloc(sizeof(struct LeftHeap));
    if (heap == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    heap->head = NULL;
    return heap;
}

bool isEmpty(struct LeftHeap *heap)
{
    return heap->head == NULL;
}

void clear(struct LeftHeap *heap)
{
    heap->head = NULL;
}

struct Node *merge(struct Node *a, struct Node *b)
{
    if (a == NULL)
        return b;

    if (b == NULL)
        return a;

    if (a->element > b->element)
    {
        struct Node *temp = a;
        a = b;
        b = temp;
    }

    a->right = merge(a->right, b);

    if (a->left == NULL)
    {
        a->left = a->right;
        a->right = NULL;
    }

    else
    {

        if (a->left->npl < a->right->npl)
        {
            struct Node *temp = a->left;
            a->left = a->right;
            a->right = temp;
        }
        a->npl = a->right->npl + 1;
    }
    return a;
}

void mergeHeaps(struct LeftHeap *heap1, struct LeftHeap *heap2)
{
    if (heap1 == heap2)
        return;

    heap1->head = merge(heap1->head, heap2->head);
    heap2->head = NULL;
}

void insert(struct LeftHeap *heap, int element)
{
    heap->head = merge(createNode(element), heap->head);
}

int deleteMin(struct LeftHeap *heap)
{

    if (isEmpty(heap))
        return -1;

    int min = heap->head->element;
    heap->head = merge(heap->head->left, heap->head->right);
    return min;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->element);
    inorder(root->right);
}

int main()
{
    printf("LEFTIST HEAP\n");
    struct LeftHeap *h = createLeftHeap();
    bool askForAnother = true;
    char ch;
    while (askForAnother)
    {
        printf("Functions to do:\n1.Insert\n2.Delete minimum\n3.Checkn Empty\n4.Clear\n5.Exit\nEnter your choice:");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter integer element to insert:");
            int element;
            scanf("%d", &element);
            insert(h, element);
            break;

        case 2:
            deleteMin(h);
            break;

        case 3:
            printf("Empty status = %s\n", isEmpty(h) ? "true" : "false");
            break;

        case 4:
            clear(h);
            break;

        case 5:
            askForAnother = false;
            break;

        default:
            printf("Wrong Entry\n");
            break;
        }

        if (choice != 5)
        {
            printf("Inorder Traversal:");
            inorder(h->head);
            printf("\n");
        }
    }
    free(h);
    return 0;
}

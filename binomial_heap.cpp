#include <iostream>
#include <cstdlib>
using namespace std;
// Node Declaration
struct node
{
    int n;
    int degree;
    node *parent;
    node *child;
    node *sibling;
};
// Class Declaration
class BinomialHeap
{
private:
    node *H;
    node *Hr;
    int count;

public:
    node *Initializeheap();
    void Binomial_link(node *, node *);
    node *Create_node(int);
    node *Union(node *, node *);
    node *Insert(node *, node *);
    node *Merge(node *, node *);
    void Display(node *);
    node *Search(node *, int);
    BinomialHeap()
    {
        H = Initializeheap();
        Hr = Initializeheap();
        int count = 1;
    }
};
// Initialize Heap
node *BinomialHeap::Initializeheap()
{
    node *np;
    np = NULL;
    return np;
}
// Linking nodes in Binomial Heap
void BinomialHeap::Binomial_link(node *y, node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
// Create Nodes in Binomial Heap
node *BinomialHeap::Create_node(int k)
{
    node *p = new node;
    p->n = k;
    return p;
}
// Insert Nodes in Binomial Heap
node *BinomialHeap::Insert(node *H, node *x)
{
    node *H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}
// Union Nodes in Binomial Heap
node *BinomialHeap::Union(node *H1, node *H2)
{
    node *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    node *prev_x;
    node *next_x;
    node *x;

    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}
// Merge Nodes in Binomial Heap
node *BinomialHeap::Merge(node *H1, node *H2)
{
    node *H = Initializeheap();
    node *y;
    node *z;
    node *a;
    node *b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }

    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
void printTree(node *root, int depth)
{
    if (root == NULL)
        return;

    // Print the current node
    for (int i = 0; i < depth; i++)
        cout << "  "; // Adjust the spacing for each level of the tree
    cout << root->n << endl;

    // Recursively print the child and sibling nodes
    printTree(root->child, depth + 1);
    printTree(root->sibling, depth);
}

void BinomialHeap::Display(node *H)
{
    if (H == NULL)
    {
        cout << "The Heap is empty" << endl;
        return;
    }

    cout << "Binomial Heap:" << endl;
    printTree(H, 0);
    cout << endl;
}

int main()
{
    int n, m, l, i;
    BinomialHeap bh;
    node *p;

    node *H;
    H = bh.Initializeheap();
    char ch;
    while (1)
    {
        cout << "----------------------------" << endl;
        cout << " BINOMIAL HEAP" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Insert Element in the heap" << endl;
        cout << "2. Display Heap" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> l;
        switch (l)
        {
        case 1:
            cout << "Enter the element to be inserted: ";
            cin >> m;
            p = bh.Create_node(m);
            H = bh.Insert(H, p);
            break;
        case 2:
            cout << "The Heap is: " << endl;
            bh.Display(H);
            break;
        case 3:
            exit(1);
        default:
            cout << "Wrong Choice";
        }
    }
    return 0;
}

#include <iostream>
using namespace std;

struct Interval
{
    int low, high;
};

struct ITNode
{
    Interval *i;
    int max;
    ITNode *left, *right;
};

ITNode *newNode(Interval i)
{
    ITNode *temp = new ITNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = NULL;
    return temp;
};

ITNode *insert(ITNode *root, Interval i)
{
    if (root == NULL)
        return newNode(i);

    int l = root->i->low;

    if (i.low < l)
        root->left = insert(root->left, i);
    else
        root->right = insert(root->right, i);

    if (root->max < i.high)
        root->max = i.high;

    return root;
}

bool doOverlap(Interval i1, Interval i2)
{
    return (i1.low <= i2.high && i2.low <= i1.high);
}

Interval *overlapSearch(ITNode *root, Interval i)
{
    if (root == NULL)
        return NULL;

    if (doOverlap(*(root->i), i))
        return root->i;

    if (root->left != NULL && root->left->max >= i.low)
        return overlapSearch(root->left, i);

    return overlapSearch(root->right, i);
}

void inorder(ITNode *root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    cout << "[" << root->i->low << ", " << root->i->high << "]"
         << " max = " << root->max << endl;

    inorder(root->right);
}

int main()
{
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;

    Interval *ints = new Interval[n];

    cout << "Enter intervals in the format [low high]:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Interval " << i + 1 << ": ";
        cin >> ints[i].low >> ints[i].high;
    }

    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);

    cout << "Inorder traversal of constructed Interval Tree is\n";
    inorder(root);

    Interval x;
    cout << "\nEnter the interval to search [low high]: ";
    cin >> x.low >> x.high;

    cout << "Searching for interval [" << x.low << ", " << x.high << "]";
    Interval *res = overlapSearch(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";

    delete[] ints;
    return 0;
}

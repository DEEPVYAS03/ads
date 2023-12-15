#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int sum;
    pair<int, int> interval;
    Node *left;
    Node *right;
};

void build(vector<int> &array, Node *cur_node, int L, int R)
{
    cur_node->interval = make_pair(L, R);
    if (L == R)
    {
        cur_node->sum = array[L];
        cur_node->left = NULL;
        cur_node->right = NULL;
        return;
    }
    cur_node->left = new Node;
    cur_node->right = new Node;

    build(array, cur_node->left, L, (L + R) / 2);
    build(array, cur_node->right, (L + R) / 2 + 1, R);

    cur_node->sum = cur_node->left->sum + cur_node->right->sum;

    return;
}

int query(Node *cur_node, int start, int end)
{
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (R < start || L > end)
        return 0;

    if (start <= L && end >= R)
        return cur_node->sum;

    int left_index = query(cur_node->left, start, end);
    int right_index = query(cur_node->right, start, end);

    return left_index + right_index;
}

void clearMem(Node *cur_node)
{
    int L = cur_node->interval.first;
    int R = cur_node->interval.second;

    if (L != R)
    {
        clearMem(cur_node->left);
        clearMem(cur_node->right);
    }
    delete cur_node;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> array(n);
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> array[i];
    }

    Node *root = new Node();
    build(array, root, 0, n - 1);

    int numQueries;
    cout << "Enter the number of queries: ";
    cin >> numQueries;

    cout << "Enter the intervals for each query in the format [start end]:\n";
    for (int i = 0; i < numQueries; ++i)
    {
        int start, end;
        cout << "Query " << i + 1 << ": ";
        cin >> start >> end;

        cout << "The sum in the interval [" << start << ", " << end << "] is " << query(root, start, end) << '\n';
    }

    clearMem(root);
    return 0;
}

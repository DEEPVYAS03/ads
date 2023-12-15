#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int low;
    int high;
} Interval;

typedef struct Node {
    Interval *interval;
    int max;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(Interval *interval) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->interval = interval;
    node->max = interval->high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, Interval *interval) {
    if (root == NULL) {
        return newNode(interval);
    }
    int low = root->interval->low;
    if (interval->low < low) {
        root->left = insert(root->left, interval);
    } else {
        root->right = insert(root->right, interval);
    }
    if (root->max < interval->high) {
        root->max = interval->high;
    }
    return root;
}

void overlapSearch(Node *root, Interval *interval) {
    if (root == NULL) {
        return;
    }
    if (root->interval->low <= interval->high && interval->low <= root->interval->high) {
        printf("Overlapping interval: [%d, %d]\n", root->interval->low, root->interval->high);
    }
    if (root->left != NULL && root->left->max >= interval->low) {
        overlapSearch(root->left, interval);
    }
    overlapSearch(root->right, interval);
}

int main() {
    Interval intervals[] = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};
    int n = sizeof(intervals) / sizeof(intervals[0]);
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, &intervals[i]);
    }
    Interval x = {6, 7};
    overlapSearch(root, &x);
    return 0;
}
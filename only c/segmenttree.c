#include <stdio.h>
#include <limits.h>

#define MAX 1000

int segmentTreeSum[MAX];
int segmentTreeMin[MAX];
int segmentTreeMax[MAX];

void buildSegmentTree(int arr[], int node, int start, int end) {
    if (start == end) {
        segmentTreeSum[node] = arr[start];
        segmentTreeMin[node] = arr[start];
        segmentTreeMax[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(arr, 2 * node, start, mid);
        buildSegmentTree(arr, 2 * node + 1, mid + 1, end);
        segmentTreeSum[node] = segmentTreeSum[2 * node] + segmentTreeSum[2 * node + 1];
        segmentTreeMin[node] = (segmentTreeMin[2 * node] < segmentTreeMin[2 * node + 1]) ? segmentTreeMin[2 * node] : segmentTreeMin[2 * node + 1];
        segmentTreeMax[node] = (segmentTreeMax[2 * node] > segmentTreeMax[2 * node + 1]) ? segmentTreeMax[2 * node] : segmentTreeMax[2 * node + 1];
    }
}

int querySum(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return segmentTreeSum[node];
    }
    int mid = (start + end) / 2;
    return querySum(2 * node, start, mid, l, r) + querySum(2 * node + 1, mid + 1, end, l, r);
}

int queryMin(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MAX;
    }
    if (l <= start && end <= r) {
        return segmentTreeMin[node];
    }
    int mid = (start + end) / 2;
    return (queryMin(2 * node, start, mid, l, r) < queryMin(2 * node + 1, mid + 1, end, l, r)) ? queryMin(2 * node, start, mid, l, r) : queryMin(2 * node + 1, mid + 1, end, l, r);
}

int queryMax(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return INT_MIN;
    }
    if (l <= start && end <= r) {
        return segmentTreeMax[node];
    }
    int mid = (start + end) / 2;
    return (queryMax(2 * node, start, mid, l, r) > queryMax(2 * node + 1, mid + 1, end, l, r)) ? queryMax(2 * node, start, mid, l, r) : queryMax(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = 6;

    buildSegmentTree(arr, 1, 0, n - 1);

    printf("Sum of elements in range [2, 3] is %d\n", querySum(1, 0, n - 1, 2, 3));
    printf("Minimum of elements in range [1, 3] is %d\n", queryMin(1, 0, n - 1, 1, 3));
    printf("Maximum of elements in range [1, 5] is %d\n", queryMax(1, 0, n - 1, 1, 5));

    return 0;
}
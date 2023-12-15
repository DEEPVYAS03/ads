#include <algorithm>
#include <iostream>
#include <vector>

#define MAXN 11
#define ver 2

int hashtable[ver][MAXN];

int pos[ver];

void initTable()
{
    for (int j = 0; j < MAXN; j++)
        for (int i = 0; i < ver; i++)
            hashtable[i][j] = INT_MIN;
}

int hash(int function, int key)
{
    switch (function)
    {
    case 1:
        return key % MAXN;
    case 2:
        return (key / MAXN) % MAXN;
    }
}

void place(int key, int tableID, int cnt, int n)
{
    if (cnt == n)
    {
        printf("%d unpositioned\n", key);
        printf("Cycle present. REHASH.\n");
        return;
    }

    for (int i = 0; i < ver; i++)
    {
        pos[i] = hash(i + 1, key);
        if (hashtable[i][pos[i]] == key)
            return;
    }
    if (hashtable[tableID][pos[tableID]] != INT_MIN)
    {
        int dis = hashtable[tableID][pos[tableID]];
        hashtable[tableID][pos[tableID]] = key;
        place(dis, (tableID + 1) % ver, cnt + 1, n);
    }
    else
        hashtable[tableID][pos[tableID]] = key;
}

void printTable()
{
    printf("Final hash tables:\n");

    for (int i = 0; i < ver; i++, printf("\n"))
        for (int j = 0; j < MAXN; j++)
            (hashtable[i][j] == INT_MIN) ? printf("- ") : printf("%d ", hashtable[i][j]);

    printf("\n");
}

void cuckoo(std::vector<int> keys)
{
    initTable();
    for (int i = 0, cnt = 0; i < keys.size(); i++, cnt = 0)
        place(keys[i], 0, cnt, keys.size());

    printTable();
}

int main()
{
    int n;
    std::cout << "Enter the number of keys: ";
    std::cin >> n;

    std::vector<int> keys(n);
    std::cout << "Enter the keys:\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "Key " << i + 1 << ": ";
        std::cin >> keys[i];
    }

    cuckoo(keys);

    return 0;
}

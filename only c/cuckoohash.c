#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 11  // Choose a prime number for better performance

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry* table1;
    Entry* table2;
    int size;
} CuckooHashTable;

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Initialize cuckoo hash table
CuckooHashTable* initCuckooHashTable(int size) {
    CuckooHashTable* cuckooTable = (CuckooHashTable*)malloc(sizeof(CuckooHashTable));
    cuckooTable->size = size;
    cuckooTable->table1 = (Entry*)calloc(size, sizeof(Entry));
    cuckooTable->table2 = (Entry*)calloc(size, sizeof(Entry));
    return cuckooTable;
}

// Insert key-value pair into the cuckoo hash table
bool insert(CuckooHashTable* cuckooTable, int key, int value);

// Search for a key in the cuckoo hash table
int search(CuckooHashTable* cuckooTable, int key);

// Print the cuckoo hash table
void printCuckooTable(CuckooHashTable* cuckooTable);

// Main function
int main() {
    CuckooHashTable* cuckooTable = initCuckooHashTable(TABLE_SIZE);

    // Example usage
    insert(cuckooTable, 5, 50);
    insert(cuckooTable, 2, 20);
    insert(cuckooTable, 8, 80);
    insert(cuckooTable, 9, 90);

    printCuckooTable(cuckooTable);

    int searchResult = search(cuckooTable, 2);
    if (searchResult != -1) {
        printf("Value for key 2: %d\n", searchResult);
    } else {
        printf("Key 2 not found.\n");
    }

    // Clean up
    free(cuckooTable->table1);
    free(cuckooTable->table2);
    free(cuckooTable);

    return 0;
}

bool insert(CuckooHashTable* cuckooTable, int key, int value) {
    int currentKey = key;
    int currentValue = value;

    for (int i = 0; i < cuckooTable->size; i++) {
        // Try inserting into the first table
        int hashIndex1 = hash1(currentKey);
        if (cuckooTable->table1[hashIndex1].key == 0) {
            cuckooTable->table1[hashIndex1].key = currentKey;
            cuckooTable->table1[hashIndex1].value = currentValue;
            return true;
        }

        // Swap with the current table entry and move to the other table
        Entry temp = cuckooTable->table1[hashIndex1];
        cuckooTable->table1[hashIndex1].key = currentKey;
        cuckooTable->table1[hashIndex1].value = currentValue;

        currentKey = temp.key;
        currentValue = temp.value;

        // Try inserting into the second table
        int hashIndex2 = hash2(currentKey);
        if (cuckooTable->table2[hashIndex2].key == 0) {
            cuckooTable->table2[hashIndex2].key = currentKey;
            cuckooTable->table2[hashIndex2].value = currentValue;
            return true;
        }

        // Swap with the current table entry and move to the other table
        temp = cuckooTable->table2[hashIndex2];
        cuckooTable->table2[hashIndex2].key = currentKey;
        cuckooTable->table2[hashIndex2].value = currentValue;

        currentKey = temp.key;
        currentValue = temp.value;
    }

    // Rehash and try again if insertion fails
    return false;
}

int search(CuckooHashTable* cuckooTable, int key) {
    int hashIndex1 = hash1(key);
    if (cuckooTable->table1[hashIndex1].key == key) {
        return cuckooTable->table1[hashIndex1].value;
    }

    int hashIndex2 = hash2(key);
    if (cuckooTable->table2[hashIndex2].key == key) {
        return cuckooTable->table2[hashIndex2].value;
    }

    return -1;  // Key not found
}

void printCuckooTable(CuckooHashTable* cuckooTable) {
    printf("Table 1:\n");
    for (int i = 0; i < cuckooTable->size; i++) {
        printf("[%d] -> %d\n", cuckooTable->table1[i].key, cuckooTable->table1[i].value);
    }

    printf("Table 2:\n");
    for (int i = 0; i < cuckooTable->size; i++) {
        printf("[%d] -> %d\n", cuckooTable->table2[i].key, cuckooTable->table2[i].value);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILTER_SIZE 1000

typedef struct {
    char* array;
    int size;
} BloomFilter;

// Hash functions
unsigned int hash1(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash % FILTER_SIZE;
}

unsigned int hash2(const char* str) {
    unsigned int hash = 5381;
    while (*str) {
        hash = (hash * 33) ^ (*str++);
    }
    return hash % FILTER_SIZE;
}

unsigned int hash3(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 65599) + (*str++);
    }
    return hash % FILTER_SIZE;
}

BloomFilter* initializeFilter(int size) {
    BloomFilter* filter = (BloomFilter*)malloc(sizeof(BloomFilter));
    filter->array = (char*)calloc((size + 7) / 8, sizeof(char));
    filter->size = size;
    return filter;
}

void addElement(BloomFilter* filter, const char* element) {
    unsigned int index1 = hash1(element);
    unsigned int index2 = hash2(element);
    unsigned int index3 = hash3(element);

    filter->array[index1 / 8] |= (1 << (index1 % 8));
    filter->array[index2 / 8] |= (1 << (index2 % 8));
    filter->array[index3 / 8] |= (1 << (index3 % 8));
}

bool containsElement(BloomFilter* filter, const char* element) {
    unsigned int index1 = hash1(element);
    unsigned int index2 = hash2(element);
    unsigned int index3 = hash3(element);

    return (filter->array[index1 / 8] & (1 << (index1 % 8))) &&
           (filter->array[index2 / 8] & (1 << (index2 % 8))) &&
           (filter->array[index3 / 8] & (1 << (index3 % 8)));
}

int main() {
    BloomFilter* filter = initializeFilter(FILTER_SIZE);

    addElement(filter, "apple");
    addElement(filter, "orange");
    addElement(filter, "banana");

    printf("Contains 'apple': %s\n", containsElement(filter, "apple") ? "Yes" : "No");
    printf("Contains 'grape': %s\n", containsElement(filter, "grape") ? "Yes" : "No");
    printf("Contains 'banana': %s\n", containsElement(filter, "banana") ? "Yes" : "No");

    return 0;
}
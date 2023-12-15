#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ALPHABET_SIZE 26

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node)
    {
        node->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}
bool isLeafNode(struct TrieNode *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i])
            return false;
    return true;
}
void insert(struct TrieNode *root, const char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->isEndOfWord = true;
}
bool search(struct TrieNode *root, const char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
            return false;
        current = current->children[index];
    }
    return (current != NULL && current->isEndOfWord);
}
bool delete(struct TrieNode *root, const char *word, int depth)
{
    if (!root)
        return false;
    if (depth == strlen(word))
    {
        if (root->isEndOfWord)

        {
            root->isEndOfWord = false;
            return isLeafNode(root);
        }
        return false;
    }
    int index = word[depth] - 'a';
    if (delete (root->children[index], word, depth + 1))
    {
        free(root->children[index]);
        root->children[index] = NULL;
        return isLeafNode(root) && !root->isEndOfWord;
    }
    return false;
}
void menu()
{
    printf("\nTrie Menu:\n");
    printf("1.Insert a word\n");
    printf("2.Search for a word\n");
    printf("3.Delete a word\n");
    printf("4.Exit\n");
    printf("Enter your choice: ");
}
int main()
{
    struct TrieNode *root = createNode();
    int choice;
    char word[50];
    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a word to insert: ");
            scanf("%s", word);
            insert(root, word);
            printf("%s inserted into the Trie.\n", word);
            break;
        case 2:
            printf("Enter a word to search: ");
            scanf("%s", word);
            if (search(root, word))
                printf("%s found in the Trie.\n", word);
            else
                printf("%s not found in the Trie.\n", word);
            break;
        case 3:
            printf("Enter a word to delete: ");
            scanf("%s", word);
            if (delete (root, word, 0))
                printf("%s deleted from the Trie.\n", word);
            else
                printf("%s not found in the Trie.\n", word);
            break;
        case 4:

            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

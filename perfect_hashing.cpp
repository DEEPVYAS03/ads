#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <climits>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

typedef long long int long_int;
const int max_int = 1000000001; // value, that couldn't be in the table. Analog of NULL.

// function for calculation of hash
inline int hash(long_int a_prime, long_int b_prime, int p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}

// class for mini-hash table in cells of the main hash-table class Bucket
class Bucket
{
private:

public:
    vector<int> _cells;
    int size; // the size of the mini-table should be greater than 4
    long_int hash_a;
    long_int hash_b;
    int prime;
    Bucket() {}

    void Initialize()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b = 1 + std::rand() % (prime - 1);
    }

    // construct hash table from list of elements
    void Construct(list<int> &input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        // Calculate the size of the mini-table using a power of 2
        size = std::pow( std::ceil(input.size()), 2);

        _cells.assign(size, max_int);
        Initialize();
        bool flag = true;

        // while there are no collisions in the table
        while (flag)
        {
            list<int>::iterator elem = input.begin();
            flag = false; // Assume no collision

            while (elem != input.end())
            {
                int hashKey = hash(hash_a, hash_b, prime, size, *elem);
                if (_cells[hashKey] != max_int)
                {
                    // Collision occurred, reset and break
                    flag = true;
                    _cells.assign(size, max_int);
                    Initialize();
                    break;
                }
                _cells[hashKey] = *elem;
                ++elem;
            }
        }
    }

    bool Contains(int elem)
    {
        if (size == 0)
            return false;

        int hashKey = hash(hash_a, hash_b, prime, size, elem);
        if (_cells[hashKey] == elem)
            return true;

        return false;
    }
};

// class for main hash table class FixedSet
class FixedSet
{
private:
    int _tableSize;
    long_int _hashFuncA;
    long_int _hashFuncB;
    int _primeNumber;
    vector<list<int> > _elementsInCells;
    vector<Bucket> _buckets;

public:
    FixedSet()
    {
        _primeNumber = 100013; // the maximum prime number
        _hashFuncA = std::rand() % _primeNumber;
        _hashFuncB = 1 + std::rand() % (_primeNumber - 1);
    }

    void setTableSize(int size)
    {
        _tableSize = size;
        _buckets.resize(size);
    }

    void Initialize(const vector<int> &numbers)
    {
        _tableSize = numbers.size();
        _buckets.resize(numbers.size());
        _elementsInCells.resize(numbers.size());

        for (int i = 0; i < numbers.size(); ++i)
        {
            int hashKey = hash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, numbers[i]);
            _elementsInCells[hashKey].push_back(numbers[i]);
        }

        for (int i = 0; i < numbers.size(); ++i)
        {
            _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    void PrintHashTable() const
    {
        for (int i = 0; i < _tableSize; ++i)
        {
            cout << "Hash " << i << ": ";

            if (_buckets[i].size == 0)
            {
                cout << "/" << endl;  // Print "/" for an empty bucket
            }
            else
            {
                for (int j = 0; j < _buckets[i].size; ++j)
                {
                    if (_buckets[i]._cells[j] != max_int)
                    {
                        cout << _buckets[i]._cells[j] << " ";
                    }
                    else
                    {
                        cout << "/ ";
                    }
                }
                cout << endl;
            }
        }
    }

    bool Contains(int number)
    {
        int hashKey = hash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, number);
        return _buckets[hashKey].Contains(number);
    }
};

int main(int argc, char *argv[])
{
    clock_t begin, end;
    double time_spent;
    std::srand(time(NULL));

    int numberOfElements;
    printf("Number of elements\n");
    scanf("%d", &numberOfElements);

    FixedSet fs;
    begin = clock();

    vector<int> inputVector;
    fs.setTableSize(numberOfElements);

    printf("Enter Elements\n");
    for (int i = 0; i < numberOfElements; ++i)
    {
        int elemValue;
        scanf("%d", &elemValue);
        inputVector.push_back(elemValue);
    }

    fs.Initialize(inputVector);
    end = clock();


    fs.PrintHashTable();


    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Search for an Element\n";
        cout << "2. Print Hash Table\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            int elem;
            cout << "Enter element to search: ";
            cin >> elem;
            if (fs.Contains(elem))
            {
                cout << "Element " << elem << " present in the Hash Table.\n";
            }
            else
            {
                cout << "Element " << elem << " not present in the Hash Table.\n";
            }
            break;

        case 2:
            cout << "Hash Table:\n";
            fs.PrintHashTable();
            break;

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}

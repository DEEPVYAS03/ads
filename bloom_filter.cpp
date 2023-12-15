#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int h1(string s, int arrSize) {
    ll int hash = 0;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}

int h2(string s, int arrSize) {
    ll int hash = 1;
    for (int i = 0; i < s.size(); i++) {
        hash = hash + pow(19, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

int h3(string s, int arrSize) {
    ll int hash = 7;
    for (int i = 0; i < s.size(); i++) {
        hash = (hash * 31 + s[i]) % arrSize;
    }
    return hash % arrSize;
}

bool lookup(bool* bitarray, int arrSize, string s) {
    int a = h1(s, arrSize);
    int b = h2(s, arrSize);
    int c = h3(s, arrSize);

    return bitarray[a] && bitarray[b] && bitarray[c];
}

void insert(bool* bitarray, int arrSize, string s) {
    if (lookup(bitarray, arrSize, s))
        cout << s << " is Probably already present" << endl;
    else {
        int a = h1(s, arrSize);
        int b = h2(s, arrSize);
        int c = h3(s, arrSize);

        bitarray[a] = true;
        bitarray[b] = true;
        bitarray[c] = true;

        cout << s << " inserted" << endl;
    }
}

int main() {
    int arrSize;
    cout << "Enter the size of the array: ";
    cin >> arrSize;

    bool bitarray[100] = {false}; // Assuming a maximum size of 100 for simplicity

    int numStrings;
    cout << "Enter the number of strings to insert: ";
    cin >> numStrings;

    vector<string> sarray(numStrings);
    cout << "Enter the strings:\n";
    for (int i = 0; i < numStrings; ++i) {
        cout << "String " << i + 1 << ": ";
        cin >> sarray[i];
    }

    for (const string& s : sarray) {
        insert(bitarray, arrSize, s);
    }

    return 0;
}

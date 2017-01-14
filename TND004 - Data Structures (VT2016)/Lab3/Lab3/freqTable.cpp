#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <random>

#include "BinarySearchTree.h"
#include "WordEntry.h"

using namespace std;
const string PUNCT = ".,!?:\"();";


int main()
{
    BinarySearchTree<WordEntry> tree;

    string name;

    cout << "Enter file name: ";
    cin >> name;

    ifstream file_in(name);
    ofstream file_out("out_"+name);

    if (!file_in || !file_out)
    {
        cout << "Could not open a file!" << endl;

        return 0;
    }

    string s;
    int _count = 0;

    //Read words and load them in the hash table
    while (file_in >> s)
    {
        //transform all upper-case letters to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        string s1;

        copy_if(s.begin(), s.end(), back_inserter(s1), [](char c)
        {
            return (PUNCT.find(c) == string::npos);
        });

        // (tries to) insert s1, does nothing if already exists
        tree.insert(WordEntry(s1));
        auto iter = tree.contains(WordEntry(s1));
        (iter->counter)++;

        _count++;
    }

    cout << "\nNumber of words in the file = " << _count << endl;

    file_out << "Frequency table ..." << endl << endl;

    for(auto it = tree.begin(); it != tree.end(); ++it)
    {
        file_out << *it << endl;
    }

    //close the file streams
    file_in.close();
    file_out.close();

    return 0;
}


//Hash function for English words
//Polynomial accumulation
//the Horner's rule is used to compute the value
//See pag. 213 of course book
unsigned _hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal = 37 * hashVal + s[i];

    hashVal %= tableSize;

    return hashVal;
}

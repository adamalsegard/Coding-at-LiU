// =======================================================
// TNG033: Lesson 5, exercise 4
// Aida Nordman
// 2014/HT2
// =======================================================

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;


int main()
{

    set<string> S1;
    set<string> S2;

    ifstream file1 ("ex4_1.txt");
    ifstream file2 ("ex4_2.txt");

    if (!file1 || !file2)
    {
        cout << "Input files could not be opened!!" << endl;
        return 0;
    }

    //1. Read the words in file1 and store them in a set S1
    istream_iterator<string> in_it1(file1);
    istream_iterator<string> in_end;

    copy(in_it1, in_end, inserter(S1,S1.begin()));

    //2. Read the words in file2 and store them in a set S2
    istream_iterator<string> in_it2(file2);

    copy(in_it2, in_end, inserter(S2,S2.begin()));

    //3. Find common words and store them in a vector

   vector<string> common;

   set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(common));

    //4. Display the common words
    ostream_iterator<string> out_it(cout,"\n");

    cout << "Common words: " << endl;
    copy(common.begin(), common.end(), out_it);

    cout << endl;

    return 0;
}

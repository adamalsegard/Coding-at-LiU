/******************************
* TNG033: Lesson 4            *
* Exercise 1, set             *
*******************************/

#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    const int RAD_SIZE = 20;
    const int EXTRA_SIZE = 11;
    const int LIMIT = 95;


    set<int> rad;
    set<int> extra;


    while(rad.size() <= RAD_SIZE)
    {
        int value = rand() % LIMIT+1;

        rad.insert(value);
    }

    while(extra.size() <= EXTRA_SIZE)
    {
        int value = rand() % LIMIT+1;

        if(find(rad.begin(), rad.end(), value) == rad.end())
            extra.insert(value);
    }

    ostream_iterator<int> out_it(cout, " ");

    cout << "First: " << RAD_SIZE << " values: ";
    copy(rad.begin(), rad.end(), out_it);

    cout << endl << endl << "Last: " << EXTRA_SIZE << " values: ";
    copy(extra.begin(), extra.end(), out_it);

    return 0;
}

// =======================================================
// TNG033: Lesson 5, exercise 2
// Aida Nordman
// 2014/HT2
// =======================================================

#include <iostream>
#include <iterator>
#include <set>

using namespace std;

//ADD my_copy




/**************************************
* Main function                       *
***************************************/


int main()
{
    const int SIZE = 100;

    double D[] = {2.0, 3.0, 3.7, 5.0, 6.8};

    int Array[SIZE] = {0};
    int howMany = 0;

    //Copy the values in D to Array
    //At most SIZE values can be copied
    howMany = my_copy(Array, SIZE, D, D+5);

    //Display the Array
    ostream_iterator<int> out_it(cout," ");

    cout << "Array values: ";
    copy(Array, Array+howMany, out_it);

    cout << endl;

    /* ******************************************** */

    set<int> S {2, 4, 8, 9, -11, 33, 100, 88, 44, 2};

    //Copy the values in set S, from S.begin()+1 until S.end(), to Array
    //At most SIZE values can be copied
    howMany = my_copy(Array, SIZE, ++S.begin(), S.end());

    //Display the Array
    cout << "Array values: ";
    copy(Array, Array+howMany, out_it);

    cout << endl;


    return 0;
}

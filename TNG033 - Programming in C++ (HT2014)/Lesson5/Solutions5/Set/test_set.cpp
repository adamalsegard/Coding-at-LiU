/**************************************************
* TNG033, Lesson 2                                *
* Test class Set                                  *
* *************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

#include "set.h"


int main()
{
    int Array[] = {2, 3, 25, 7, 5, 8};

    Set s1(25);

    s1.add(Array, Array+6);

    cout << "S1: " << s1 << endl;  //s1 = {25}

    return 0;
}



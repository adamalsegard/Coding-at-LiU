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
    /*****************************************************
    * TEST PHASE 0                                       *
    * Set: constructors and operator<<                   *
    ******************************************************/
    cout << "\nTEST PHASE 0: constructors and operator<<\n";

    Set s1(25);
    Set s2(10);

    cout << "S1: " << s1 << endl;  //s1 = {25}
    cout << "S2: " << s2 << endl;  //s1 = {10}

    /*****************************************************
    * TEST PHASE 1                                       *
    * Set: copy constructor                              *
    ******************************************************/
    cout << "\nTEST PHASE 1: copy constructor\n";

    Set s3(s1);

    cout << "S3: " << s3 << endl; //s3 = {25}

    /*****************************************************
    * TEST PHASE 2                                       *
    * Set: operator=                                     *
    ******************************************************/
    cout << "\nTEST PHASE 2: assignment operator\n";

    s3 = s3;
    cout << "S3: " << s3 << endl; //s3 = {25}

    const Set s4(13);

    s1 = s1 = s4;
    cout << "S1: " << s1 << endl; //s3 = {13}

    /*****************************************************
    * TEST PHASE 3                                       *
    * Set: operator+                                     *
    ******************************************************/
    cout << "\nTEST PHASE 3: S1+S2\n";

    s3 = s1 + s2 + s4;
    cout << "S3: " << s3 << endl; //s3 = {10, 13}

    //(s1+s2) = s4;  //Good: strange stuff should not compile!!

    /*****************************************************
    * TEST PHASE 4                                       *
    * Set: operator-                                     *
    ******************************************************/
    cout << "\nTEST PHASE 4: S1-S2\n";

    s3 = s3 - (s3 - s3);
    cout << "S3: " << s3 << endl; //s3 = {10, 13}

    /*****************************************************
    * TEST PHASE 5                                       *
    * Set: operator+                                     *
    ******************************************************/
    cout << "\nTEST PHASE 5: S+i and S-i\n";

    cout << "S2 + 8: " << s2 + 8 << endl; //{8, 10}
    cout << "S2 - 8: " << s2 - 8 << endl; //{8}
    cout << "S4 - 8: " << s4 - 8 << endl; //{8}

    s2 = s2 + 8 - 20 - 4 + 100;

    cout << "S2: " << s2 << endl; //s2 = {8, 10, 100}

    /*****************************************************
    * TEST PHASE 6                                       *
    * Set: operator+                                     *
    ******************************************************/
    cout << "\nTEST PHASE 6: i+S and i-S\n";

    cout << "50 + S2: " << 50 + s2 << endl; //{8, 10, 50, 100}
    cout << "8 - S2: " << 8 - s2 << endl; //empty set

    /*****************************************************
    * TEST PHASE 7                                       *
    * Set: operator[]                                    *
    ******************************************************/
    cout << "\nTEST PHASE 7: subscript operator\n";

    s2[7] = true;

    cout << "S2: " << s2 << endl; //s2 = {7, 8, 10, 100}

    if (s2[7])
        cout << "7 belongs to set S2" << endl;

    if (!s4[10])
        cout << "10  does not belong to set S4" << endl;

    /*****************************************************
    * TEST PHASE 8                                       *
    * Set: conversion to string                          *
    ******************************************************/
    cout << "\nTEST PHASE 8: conversion to string\n";

    string s = s2;

    cout << "\"" << s << "\""<< endl;

    return 0;
}



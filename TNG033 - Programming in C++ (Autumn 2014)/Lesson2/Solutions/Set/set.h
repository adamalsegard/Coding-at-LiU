/***************************************************************************
* TNG033, Lesson 2                                                         *
* Defines a class Set represented as an array of booleans                  *
* header file set.h                                                        *
* **************************************************************************/


#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include <iostream>

using namespace std;

class Set
{
    public:

        //constructors
        Set(int n);        //conversion constructor
        Set(const Set& s); //copy constructor

        ~Set();

        const Set& operator=(const Set& s);

        operator string() const; //type conversion operator

        friend const Set operator+(const Set &s1, const Set &s2);
        friend const Set operator-(const Set &s1, const Set &s2);

        //subscript operators
        bool& operator[](int index);
        const bool& operator[] (int index) const; //a copy of the bool value stored in the Set is returned
        //Note:It is ok to have two different member functions for a class whose
        //declaration differs in whether they are declared const memeber function or not
        //the first operator[] is called for a "Set s(...);"
        //while the second operator[] is called for "const Set s(...);"


        //one kitten is going to be killed by god
        //bool& operator[](int index) const;
        //
        //Comment away both operator[] in lines 33 and 34
        //Uncomment the line 42
        //Try to compile:
        //const Set S(12);
        //S[5] = true;
        //cout << S << endl;
        //SURPRISE!! It compiles and set S is modified. But, how? Isn't S a constant?!!

        friend ostream& operator<<(ostream& os, const Set& s);

    private:
        int capacity;
        bool* V;

        static const int DEFAULT_SIZE = 10;  //C++11

};

#endif // SET_H_INCLUDED

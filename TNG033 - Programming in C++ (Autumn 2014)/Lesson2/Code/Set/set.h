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

        //Constructors
        //Create a Set with (i+1) slots
        Set(int n); //Conversion constructors
        //add explicit if you want to disable some things

        //copy constructor
        Set(const Set &s);

        //Destructor
        ~Set();

        const Set& operator=(const Set& s);

        operator string() const; //Type conversion operator

        friend const Set operator+(const Set &s1, const Set &s2);
        friend const Set operator-(const Set &s1, const Set &s2);

        friend ostream& operator<<(ostream& os, const Set& s);

        //subscript operators
        bool& operator[](int index); //s[25] = true;
        const bool& operator[](int index) const; // if([25]) ... ;
        //a copy of the bool value stored in the Set is returned
        //Note:It is ok to have two different member functions for a class whose
        //declaration differs in whether they are declared const memeber function or not
        //the first operator[] is called for a "Set s(...);"
        //while the second operator[] is called for "const Set s(...);"

    private:

        int capacity;
        bool *V;

        static const int DEFAULT_SIZE = 10; //C++ 11

};

#endif // SET_H_INCLUDED

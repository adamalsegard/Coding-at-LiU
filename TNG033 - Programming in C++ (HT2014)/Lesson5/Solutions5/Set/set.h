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

    //Lesson 5: exercise 3
    template <class Iterator>
    int add(Iterator start_it, Iterator end_it)
    {
        {
            int i = 0;

            for( ; start_it != end_it; ++i, ++start_it)
            {
                *this = *this + *start_it;
            }

            return i; //return number of values copied into *this
        }

    };

    operator string() const; //type conversion operator

    friend const Set operator+(const Set &s1, const Set &s2);
    friend const Set operator-(const Set &s1, const Set &s2);

    //subscript operators
    bool& operator[](int index);
    const bool& operator[] (int index) const; //a copy of the bool value stored in the Set is returned

    friend ostream& operator<<(ostream& os, const Set& s);

private:
    int capacity;
    bool* V;

    static const int DEFAULT_SIZE = 10;  //C++11

};

#endif // SET_H_INCLUDED

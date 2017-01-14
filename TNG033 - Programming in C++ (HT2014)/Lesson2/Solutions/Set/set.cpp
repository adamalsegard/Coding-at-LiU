/***************************************************************************
* TNG033, Lesson 2                                                         *
* Source file set.cpp                                                      *
* **************************************************************************/

#include "set.h"

#include <iomanip>
#include <new>
#include <cassert>
#include <sstream>

//constructors
Set::Set(int n)
{
    capacity = (n < 0)? DEFAULT_SIZE : n;

    V = new bool[capacity+1];

    for(int i = 0; i <= capacity; i++)
        V[i] = false;

    if (n >= 0)
        V[n] = true;

}


Set::Set(const Set& s)
 : capacity(s.capacity)
{
    V = new bool[s.capacity+1];

    for(int i = 0; i <= capacity; i++)
        V[i] = s.V[i];
}

Set::~Set()
{
    delete [] V;
}


Set::operator string() const
{
    ostringstream os;

    for(int i = 0; i <= capacity; i++)
        if (V[i])
            os << i << " ";

    return os.str();
}

const Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs) //test self-assignment
    {
      Set Acopy(rhs);  //call copy constructor

      swap(V, Acopy.V);
      capacity = Acopy.capacity;
    }

    return *this;
}


const Set operator+(const Set &s1, const Set &s2)
{
    int m = max(s1.capacity, s2.capacity);

    Set temp(m);

    for(int i = 0; i <= s1.capacity; i++)
        temp.V[i] = s1.V[i];

    for(int i = 0; i <= s2.capacity; i++)
        temp.V[i] = (s2.V[i] || temp.V[i]);

    return temp; //copy constructor is called
}


//Set difference
//Return a new set S1-S2
const Set operator-(const Set &s1, const Set &s2)
{
    Set temp(s1);

    int n = min(s1.capacity, s2.capacity);

    //remove the elements of S
    for(int i = 0; i <= n; i++)
        temp.V[i] = temp.V[i] && (!s2.V[i]);

    return temp;
}


//indexing operators
bool& Set::operator[](int index) //set capacity does not grow
{
    assert (index >= 0 && index <= capacity); //can be ignored

    return V[index]; //return a reference
}


const bool& Set::operator[] (int index) const
{
//    if (index < 0 || index > capacity)
//        return false;

    assert (index >= 0 && index <= capacity); //can be ignored

    return V[index]; //return a copy
}


ostream& operator<<(ostream& os, const Set& s)
{
    os << "{ ";

    for(int i = 0; i <= s.capacity; i++)
      if (s.V[i])
          os << i << " ";

      os << "}";

     return os;
}




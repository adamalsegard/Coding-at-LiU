/***************************************************************************
* TNG033, Lesson 2                                                         *
* Source file set.cpp                                                      *
* **************************************************************************/

#include "set.h"

#include <iomanip>
#include <sstream>
#include <new>
#include <cassert>


//Conversion constructor
//Create a Set with (n+1) slots
Set::Set(int n)
{
    if(n<=0)
        capacity = DEFAULT_SIZE;
    else
        capacity = n;
    //Same as:
    //capacity = (n<=0) ? DEFAULT_SIZE : n;

    V = new (nothrow) bool [capacity+1]; //could have try-catch instead!?

    if(!V)
        capacity = 0;

    for(int i = 0; i<= capacity; i++)
        V[i] = false;

    V[n] = true;

}

//copy constructor
Set::Set (const Set &s)
    : capacity(s.capacity)
{   //Same as:
    //capacity = s.capacity;

    //Allocate memory
    V = new (nothrow) bool [capacity+1]; //(nothrow) not needed

    if(!V)
        capacity = 0;

    for(int i=0; i<=capacity; i++)
        V[i] = s.V[i];
}

//Destructor
Set::~Set()
{
    if(V)
    {
        delete [] V; //delete array pointed by V!
    }

}

Set::operator string() const
{
    ostringstream os;

    for(int i = 0; i<=capacity; i++)
    {
        if(V[i])
            os << i << " ";
    }

    return os.str();
}

//Addition operator, friend function
const Set operator+(const Set &s1, const Set &s2)
{
    int m = max(s1.capacity, s2.capacity);

    Set temp(m);

    temp.V[m] = false;

    for(int i=0; i<=s1.capacity; i++)
    {
        temp.V[i] = s1.V[i];
    }
    for(int i=0; i<=s2.capacity; i++)
    {
        if(!temp.V[i])
        {
            temp.V[i] = s2.V[i];
        }
    }

    return temp; //copy constructor is called
}

//Set difference
//Return a new set S1-S2
const Set operator-(const Set &s1, const Set &s2)
{

    Set temp(s1);

    int n = min(s1.capacity, s2.capacity);

    //remove the elements of S2
    for(int i = 0; i <= n; i++)
        temp.V[i] = temp.V[i] && (!s2.V[i]);

    return temp;



}

//Assignment operator
const Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs) //test self-assignment
    {
        Set Acopy(rhs); // call copy constructor

        swap(V, Acopy.V);
        capacity = Acopy.capacity;
    }
    return *this;
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


//Cannot be a member function because of the stream, needs to be a friend function
ostream& operator<< (ostream& os, const Set& theSet)
{

    os << "{ ";

    for(int i=0; i<=theSet.capacity; i++)
    {
        if(theSet.V[i])
            os << i << " ";
    }
    os << "}";
    return os;
}

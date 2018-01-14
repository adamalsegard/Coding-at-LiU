#ifndef SET_H
#define SET_H

#include "node.h"

//DO NOT MODIFY the public interface of class Set

class Set
{
    public:

        //Constructors
       Set ();

       //Constructor creating a set
       //from n integers in a non-sorted array a
       Set (int a[], int n);

       //copy constructor
       Set (const Set& b);

       //destructor
       ~Set ();

       bool empty () const; //Test if the set is empty
       int cardinality() const; //Return number of elements in the set
       bool member (int x) const; //Test if x is an element of the set

        //Overloaded operators
       // A new set is returned by the operators
       Set operator+ (const Set& b) const; //Set union
       Set operator* (const Set& b) const; //Set intersection
       Set operator- (const Set& b) const; //Set difference
       Set operator+(int x) const; //set union with set {x}
       Set operator-(int x) const; //set difference with set {x}

       //Comparison operators
       bool operator<=(const Set& b) const;
       bool operator==(const Set& b) const;
       bool operator<(const Set& b) const;

        //assignment operator
       const Set& operator=(const Set& b);


    private:
       Node *head; //points to the first node
                   //Note: first node is a dummy node

        void insert(int &n);
        void remove(int &n);

       friend ostream& operator<< (ostream& os, const Set& b);
};


#endif

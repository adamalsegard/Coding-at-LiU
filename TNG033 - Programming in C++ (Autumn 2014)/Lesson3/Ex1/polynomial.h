/*************************
* Class Polynomial       *
* TNG033: Lab 3          *
**************************/

#ifndef POL_H
#define POL_H

#include <iostream>

using namespace std;

#include "expression.h"


class Polynomial : public Expression
{
public:

    //Constructors
    Polynomial(int n, double *V); //Default
    Polynomial(double n); //Conversion
    Polynomial(const Polynomial& p); //Copy

    //Destructor
    ~Polynomial();

    //Assignment operator
    const Polynomial& operator=(const Polynomial& p);


    friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2); //Not const?

    //subscript operators
    bool& operator[](int index);
    const bool& operator[] (int index) const; //a copy of the bool value stored in the Set is returned
    //Note:It is ok to have two different member functions for a class whose
    //declaration differs in whether they are declared const memeber function or not
    //the first operator[] is called for a "Set s(...);"
    //while the second operator[] is called for "const Set s(...);"


protected:
    int degree;
    double *coef; //array with coefficients

    void display(ostream& os);

};


#endif

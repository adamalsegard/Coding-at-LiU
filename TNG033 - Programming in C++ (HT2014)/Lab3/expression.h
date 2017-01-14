/*************************
* Class Expression       *
* TNG033: Lab 3          *
**************************/

#ifndef EXP_H
#define EXP_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include "math.h"

using namespace std;

const double EPSILON = 1.0e-5;


class Expression
{

    public:

    //Constructors (Don't need'em! Can't declare variables of abstract class)
    //Assignment operator don't needed as well?

    //Empty, virtual, Destructor
    virtual ~Expression(){}

    //Member functions
    bool isRoot(double x) const; //Doesn't need to be abstract, use () when you check!
    virtual double operator()(double d) const = 0; //Evaluate, needs to be abstract
    virtual Expression* clone() const = 0; //Make a copy of Expression

    //Friend functions
    friend ostream& operator<<(ostream& os, const Expression& e); // Can't be virtual, alas use display as helpfunction

protected:

    virtual void display(ostream& os) const = 0; //To be used in operator<<, needs to be abstract

};

#endif

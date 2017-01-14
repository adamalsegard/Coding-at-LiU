/*************************
* Class Expression       *
* TNG033: Lab 3          *
**************************/

#ifndef EXP_H
#define EXP_H

#include <iostream>

using namespace std;

const double EPSILON = 1.0e-5;


class Expression
{
public:

    //Constructors (Don't need'em! Can't declare variables of abstract class)
    //Assignment operator don't needed as well?
    //const Expression& operator=(const Expression& e);

    //Destructor
    virtual ~Expression();

    //Member functions
    bool isRoot(double x) const; //Doesn't need to be abstract, use () when you check!
    virtual double operator()(double d) const = 0; //Evaluate, needs to be abstract
    virtual Expression* clone() = 0; //Make a copy of Expression

    //Friend functions
    friend ostream& operator<<(ostream& os, const Expression& e);

protected:

    virtual void display(ostream& os) = 0; //To be used in operator<<



};


#endif

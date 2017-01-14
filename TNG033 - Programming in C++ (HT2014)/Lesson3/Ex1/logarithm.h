/*************************
* Class Log              *
* TNG033: Lab 3          *
**************************/


#ifndef LOG_H
#define LOG_H

#include <iostream>

using namespace std;

#include "expression.h"

class Log : public Expression
{

public:

    //Constructors
    Log(); //Default
    Log(Expression *E, double c1, double c2, int b); //E is a copy of the polynomial P
    // L = c1 + c2*Log'base(E)
    Log(const Log& l); //Copy

    //Destructor
    ~Log();

    //Assignment operator
    const Log& operator=(const Log& l);

    virtual Log* clone();



protected:
    double k1, k2;
    int base;
    Expression *ex; //A copy of the polynomial P


};

#endif

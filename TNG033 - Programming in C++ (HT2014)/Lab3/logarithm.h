/*************************
* Class Log              *
* TNG033: Lab 3          *
**************************/


#ifndef LOG_H
#define LOG_H

//#include <iostream>

using namespace std;

#include "expression.h"

class Log : public Expression
{
public:
    //Constructors
    Log(); //Default
    Log(const Expression &E, double c1, double c2, int b);
    Log(const Log& l); //Copy

    //Destructor
    ~Log();

    //Assignment operator
    const Log& operator=(const Log& l);

    //Inherited functions
    virtual Expression* clone() const;
    double operator()(double d) const;


protected:
    double k1, k2;
    int base;
    Expression *ex; //A copy of the polynomial P

    virtual void display(ostream& os) const;

};

#endif

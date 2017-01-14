/*************************
* Class Polynomial       *
* TNG033: Lab 3          *
**************************/

#ifndef POL_H
#define POL_H

//#include <iostream>
//#include <iomanip>
//#include <cmath>

using namespace std;

#include "expression.h"


class Polynomial : public Expression
{
public:

    //Constructors
    Polynomial(); //Default - without arguments
    Polynomial(int n, double *V); //Default - with arguments
    Polynomial(double n); //Conversion
    Polynomial(const Polynomial& p); //Copy

    //Destructor
    ~Polynomial();

    //Assignment operator
    const Polynomial& operator=(const Polynomial& p);

    //Friend functions
    friend const Polynomial operator+(const Polynomial &p1, const Polynomial &p2);

    //subscript operator
    double& operator[](int index);

    //Inherited functions
    virtual Expression* clone() const;
    double operator()(double d) const;


protected:
    int degree;
    double *coef; //array with coefficients

    virtual void display(ostream& os) const;
};

#endif

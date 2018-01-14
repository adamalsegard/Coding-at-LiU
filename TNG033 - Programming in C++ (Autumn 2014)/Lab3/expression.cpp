/*********************************************************
* Class Expression member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/

#include "expression.h"


ostream& operator<<(ostream& os, const Expression& e)
{
    e.display(os); //Call virtual function display() for dynamic binding
    return os;
}

bool Expression::isRoot(double x) const
{
    if(fabs((*this)(x)) < EPSILON) //since operator()
        return true;
    else
        return false;
}

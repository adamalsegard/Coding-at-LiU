/*********************************************************
* Class Log member functions implementation              *
* TNG033: Lab 3                                          *
**********************************************************/

#include "logarithm.h"
#include "polynomial.h"
//#include <iomanip>
//#include "math.h"

//Default
Log::Log()
{
    double V[2] = {0, 1};
    Expression *temp = new Polynomial(1, V);

    base = 2;
    k1 = 0;
    k2 = 1;
    ex = temp;
}

Log::Log(const Expression &E, double c1, double c2, int b)
{
    base = b;
    k1 = c1;
    k2 = c2;
    ex = E.clone(); //Borde funka som dynamic binding eftersom clone() är virtual och returnerar en pointer(lika väl som ->)

    //Får inte pointer (nedan) att funka
    //Log::Log(const Expression *E, double c1, double c2, int b)
    //ex = E->clone();

    //If you know E is either a polynomial or logarithm
    // ex = new Polynomial(*E);
    // ex = new Log(*E);
}

//Copy constructor
Log::Log(const Log& l)
{
    base = l.base;
    k1 = l.k1;
    k2 = l.k2;
    ex = l.ex->clone();
}

//Assignment operator
const Log& Log::operator=(const Log& l)
{
    if (this != &l) //test self-assignment
    {
        base = l.base;
        k1 = l.k1;
        k2 = l.k2;
        ex = l.ex->clone();
    }
    return *this;
}

//Destructor - Inte nödvändig eftersom Log inte allokerar nytt minne explicit!?
Log::~Log()
{
    //base = k1 = k2 = 0; //Isn't needed
    delete ex; //Kallar destructor för Polynomial!?
    ex = nullptr;
}

Expression* Log::clone() const
{
    Expression *temp = new Log(*ex, k1, k2, base);
    return temp;
}

double Log::operator()(double d) const
{
    double y;

    y = k1+k2*(log10((*ex)(d))/log10(base)); // Log_b(x) = Log_10(x)/Log_10(b)

    return y;
}


void Log::display(ostream& os) const
{
    if(fabs(k1) > EPSILON)
        os << fixed << setprecision(2) << k1 << " + ";

    if(fabs(k2) > EPSILON)
        os << fixed << setprecision(2) << k2 << "*Log_" << base << "(" << *ex << ")" ;
}

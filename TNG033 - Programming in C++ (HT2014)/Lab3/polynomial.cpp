/*********************************************************
* Class Polynomial member functions implementation       *
* TNG033: Lab 3                                          *
**********************************************************/

#include "polynomial.h"

//Default
Polynomial::Polynomial()
{
    degree = 0;
    coef = new (nothrow) double[degree+1];

    coef[degree] = 0.0;
}

Polynomial::Polynomial(int n, double *V)
{
    degree = n;
    coef = new (nothrow) double[degree+1];

    for(int i=0; i<=degree; i++)
        coef[i] = V[i];
}

//Conversion
Polynomial::Polynomial(double n)
{
    degree = 0;
    coef = new (nothrow) double[degree+1];

    coef[degree] = n;
}

//Copy
Polynomial::Polynomial(const Polynomial& p)
    :degree(p.degree)
{
    coef = new (nothrow) double[degree+1];

    for(int i=0; i<=degree; i++)
        coef[i] = p.coef[i];
}

//Destructor
Polynomial::~Polynomial()
{
    delete [] coef;
    coef = nullptr;
    //delete &degree; //Bad practise!
}

const Polynomial& Polynomial::operator=(const Polynomial& p)
{
    if (this != &p) //test self-assignment
    {
        degree = p.degree;

        //1. Delete old memory
        delete [] coef;

        //2. Allocate new memory
        coef = new (nothrow) double[p.degree+1];

        //3. Copy
        for(int i = 0; i <= degree; i++)
            coef[i] = p.coef[i];
    }
    return *this;
}

//Utskrift
void Polynomial::display(ostream& os) const
{
    //if(fabs(coef[0]) > EPSILON)
        os << fixed << setprecision(2) << coef[0];

    for(int i=1; i<=degree; i++)
    {
        if(fabs(coef[i]) > EPSILON)
            os << " + " << setprecision(2) << coef[i] << " * X^" << i;
    }
}

Expression* Polynomial::clone() const
{
    //Inte nödvändigt att ha Expression!?
    Expression *temp = new Polynomial(this->degree, this->coef);
    return temp;
}

//Overloading operator()
double Polynomial::operator()(double d) const
{
    double y = 0.0;

    for(int i=0; i<=degree; i++)
        y += coef[i]*pow(d, i); //Calculate expression

    return y;
}

//Overloading operator[]
double& Polynomial::operator[](int index)
{
    return coef[index]; //Smart return!? Hur känner den av vad den ska returna?
}

//Friend function
const Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{
    int deg = max(p1.degree, p2.degree);
    double V[deg];

    for(int i=0; i<=p1.degree; i++)
        V[i] = p1.coef[i];

    for(int i=0; i<=p2.degree; i++)
        V[i] += p2.coef[i];

    Polynomial temp(deg, V);

    return temp; //copy constructor is called
}

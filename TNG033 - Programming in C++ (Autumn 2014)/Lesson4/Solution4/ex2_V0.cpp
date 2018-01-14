/******************************
* TNG033: Lesson 4            *
* Exercise 2                  *
*******************************/

#include <iostream>
#include <string>

using namespace std;

/*******************************
* Class Instrument             *
********************************/

class Instrument
{
public:

    //Constructor
    Instrument(string b);


protected:
    string brand;

};


/**********************************
* Class Instrument                *
* Member functions implementation *
***********************************/


//Cosntructor
Instrument::Instrument(string b)
    : brand(b)
{

};


/*******************************
* Class Piano                  *
********************************/


class Piano : public Instrument
{
public:

    Piano(string b) : Instrument(b)
    { };

};


/*******************************
* Class Violin                 *
********************************/


class Violin : public Instrument
{
public:

    Violin(string b) : Instrument(b)
    { };

};


/*******************************
* Main                         *
********************************/


int main()
{
   Instrument I1("Bach");

    Piano P1("Yamaha");
    Piano P2("Yamaha");

    const Violin V1("Stradivarius");

    //Exercise a.ii
//    cout << I1.get_identification() << endl;
//    cout << P1.get_identification() << endl;
//    cout << P2.get_identification() << endl;
//    cout << V1.get_identification() << endl;

    //Exercise b
//    Piano P3(P1);
//    P1 = P2;


    //Exercise c
//    Uncopyable *ptr = new Violin("XXX");
//
//    delete ptr;

    return 0;
}


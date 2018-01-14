/******************************
* TNG033: Lesson 4            *
* Exercise 2                  *
*******************************/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*******************************
* Class Uncopyable             *
********************************/

//Standard class to use if you want something uncopyable
class Uncopyable
{

protected: //Must be protected because you should not be able to compile (Uncopyable XX);
    Uncopyable() = default; //Needed for Constructor for Instrument to compile.
    ~Uncopyable() { };

private:
    Uncopyable(const Uncopyable& x);

    const Uncopyable& operator=(const Uncopyable& x);
};


/*******************************
* Class Instrument             *
********************************/

class Instrument : public Uncopyable
{
public:

    //Constructor
    Instrument(string b);

    string get_identification() const;

    void set_brand(string b)
    {
        brand = b;
    }


protected:
    string brand;
    const int id; // const so it's impossible to change the id's afterwards

    static int id_counter;

};

int Instrument::id_counter = 0;

/**********************************
* Class Instrument                *
* Member functions implementation *
***********************************/

//Constructor
Instrument::Instrument(string b)
    :brand(b), id(id_counter)
{
    ++id_counter;

};

string Instrument::get_identification() const
{
    ostringstream os;

    os << brand << "<" << id << ">";

    return os.str();
}

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

    Violin(string b, bool wood = true) //Must initialized cause of the exercise
        : Instrument(b), wood_violin(wood)
    { };

    bool is_wooden() const //Must be const member function
    {
        return wood_violin;
    }

protected:
    bool wood_violin;

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
    cout << I1.get_identification() << endl;
    cout << P1.get_identification() << endl;
    cout << P2.get_identification() << endl;
    cout << V1.get_identification() << endl;

    //Exercise b
    //Should not compile
    //Piano P3(P1);
    //P1 = P2;
    //Uncopyable A;
    //Uncopyable B(A);

    //Exercise c
    //Uncopyable *ptr = new Violin("XXX");
    //delete ptr;

    return 0;
}


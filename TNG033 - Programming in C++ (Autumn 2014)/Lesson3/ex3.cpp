/******************************
* TNG033: Lesson 3            *
* Exercise 3                  *
*******************************/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*******************************
* Class Instrument             *
********************************/

class Instrument
{
public:

    //Constructor
    Instrument(string b);

    ~Instrument()
    {
        //Update all_brands table
        remove(b);
    }

    Instrument(const Instrument& i)
     : brand(i.brand)
     {
         //Update all_brands table
         add(b);
     }

    static void display_brands();

protected:
    string brand;

    typedef pair<string,int> Instrument_counter;

    static Instrument_counter all_brands[100];
    static int howMany;

    static void add(string b);
    static void remove(string b);
};

/*=========================================*/

Instrument::Instrument_counter all_brands[100];
int Instrument::howMany = 0;

/*=========================================*/


/**********************************
* Class Instrument                *
* Member functions implementation *
***********************************/


//Cosntructor
Instrument::Instrument(string b)
    : brand(b)
{
    //Update all_brands table
    add(b);
};

void Instrument::add(string b)
{
    int i = 0;

    if( (i = find_brand(b)) != -1) //Found brand b in counter
    {
        all_brands[i].second++;
        return;
    }
    if(howMany < 100)
    {
        all_brands[howMany].first = b;
        all_brands[howMany++].second = 1;
    }

}

void Instrument::display_brands()
{
    all_brand[]
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
* Class Flute                  *
********************************/


class Flute : public Instrument
{
public:

    Flute(string b) : Instrument(b)
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


void do_nothing(Piano P)
{
    cout << "\nDo nothing piano ..." << endl;

    //call display_brands()
    Instrument::display_brands();
}

void do_nothing(Flute F)
{
    cout << "\nDo nothing flute..." << endl;

   //call display_brands()
   Instrument::display_brands();
}

void do_nothing(Violin V)
{
    cout << "\nDo nothing violin..." << endl;

   //call display_brands()
   Instrument::display_brands();
}


int main()
{
    Piano P1("Yamaha");
    do_nothing(P1);

    Flute F1("PureTone");
    do_nothing(F1);

    Instrument *ptr_I = new Violin("Stradivarius");

    Piano P2("Bach");
    do_nothing(P2);

    //call display_brands()
    Instrument::display_brands();

    delete ptr_I;

    Flute F2("PureTone");
    do_nothing(F2);

   //call display_brands()
   Instrument::display_brands();

    return 0;
}


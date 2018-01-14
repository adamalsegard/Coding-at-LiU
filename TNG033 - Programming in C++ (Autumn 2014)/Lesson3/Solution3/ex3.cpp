/*****************************************************
* TNG033: Lesson 3                                   *
* Exercise 2                                         *
******************************************************/


#include <iostream>
#include <string>
#include <utility>  //pair
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


    //Copy constructor
    Instrument(const Instrument& ii);


    //Destructor
    ~Instrument();

    //Display all brands
    static void display_brands();

protected:
    string brand;

    static const int MAX = 100;
    static const int NOT_FOUND = -1;

    //Defines a pair<Brand,counter>
    typedef pair<string,int> Instrument_counter;

    //Table of all brands
    static Instrument_counter all_brands[MAX];
    static int howMany; //number of brands in the table


    //Add an instrument of brand b to the table all_brands
    static void add(string b);

    //Remove an instrument of brand b from the table all_brands
    static void remove(string b);

    //Find brand b in the table all_brands
    //Return the index of the position where b is found
    //Otherwise, return NOT_FOUND
    static int find_brand(string b);
};


/**********************************
* Class Instrument                *
* Member functions implementation *
***********************************/

//Static data members initialization

int Instrument::howMany = 0;
Instrument::Instrument_counter Instrument::all_brands[MAX];

//Cosntructor
Instrument::Instrument(string b)
    : brand(b)
{
    add(b);
};


//Copy constructor
Instrument::Instrument(const Instrument& ii)
    : brand(ii.brand)
{
    add(brand);
};


//Destructor
Instrument::~Instrument()
{
    remove(brand);
};


void Instrument::display_brands()
{
    cout << "\nInstrument"
         << "       " << "Quantity" << endl
         << "============================" <<endl;

    for(int i = 0; i < howMany; i++)
    {
        cout << setw(20) << left << all_brands[i].first
             << setw(15) << all_brands[i].second << endl;
    }
};


//Add an instrument of brand b to the table all_brands
void Instrument::add(string b)
{
    int i = 0;

    if ( (i = find_brand(b)) != NOT_FOUND )
    {
        ++all_brands[i].second;  //increment the brand b counter
        return;
    }

    if (howMany < MAX)  //Add another brand to the table
    {
        all_brands[howMany].first = b;
        all_brands[howMany++].second = 1;
    }
};


//Remove an instrument of brand b from the table all_brands
void Instrument::remove(string b)
{
    int i = 0;

    if ( (i = find_brand(b)) != NOT_FOUND )
    {

        --all_brands[i].second;  //decrement the brand b counter
        return;
    }
    else
        cout << "The code has a bug!!" << endl;

};


//Find brand b in the table all_brands
//Return the index of the position where b is found
//Otherwise, return NOT_FOUND
int Instrument::find_brand(string b)
{
    for(int i = 0; i < howMany; i++)
        if (all_brands[i].first == b)
        {
            return i;
        }

    return NOT_FOUND;
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


void do_nothing(Piano P)  //call by value
{
    cout << "\nDo nothing piano ..." << endl;

    Instrument::display_brands();
}

void do_nothing(Flute F)  //call by value
{
    cout << "\nDo nothing flute..." << endl;

    Instrument::display_brands();
}

void do_nothing(Violin V)  //call by value
{
    cout << "\nDo nothing violin..." << endl;

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

    Instrument::display_brands();

    delete ptr_I;

    Flute F2("PureTone");
    do_nothing(F2);

    Instrument::display_brands();

    return 0;
}


/******************************
* TNG033: Lesson 3            *
* Exercise 2                  *
*******************************/

#include <iostream>
#include <string>

using namespace std;


class Instrument
{
    public:

       Instrument(string b)
        {
            brand = b;
        };

       virtual void play(string note) const // Needs to be virtual to use dynamic binding
        {
            cout << "Instrument::play with "
                 << "tune " << note << endl;
        };

    protected:
        string brand;  //the intrument's brand
};


class Piano : public Instrument
{
    public:

        Piano(string b) : Instrument(b)
        { };

        void play(string note) const
        {
            cout << "Piano::play with "
                  << "tune " << note << endl;
        }
};


class Flute : public Instrument
{
    public:

        Flute(string b) : Instrument(b)
        { };

        void play(string note) const
        {
            cout << "Flute::play with "
                  << "tune " << note << endl;
        }
};


class Violin : public Instrument
{
    public:

        Violin(string b) : Instrument(b)
        { };

        void play(string note) const
        {
            cout << "Violin::play with "
                  << "tune " << note << endl;
        }
};

/* ****************************************** */


//DO NOT MODIFY this function
void tune(Instrument& i)
{
    i.play("middleC"); //Needs dynamic binding!
}


int main()
{
    Piano P1("Yamaha");
    tune(P1);

    Flute F("PureTone");
    tune(F);

    Instrument *ptr_I = new Violin("Stradivarius");
    tune(*ptr_I);

    Piano P2("Bach");
    tune(P2);

    delete ptr_I;


    return 0;
}


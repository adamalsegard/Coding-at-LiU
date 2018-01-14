#include "movies.h"

//Read the data for a new movie (name, number of copies, type) from file in
//Number of rented copies is set to zero
void get(ifstream &in, Movie& m)
{

    in >> ws;

    getline(in, m.name);

    in >> m.genre;

    in >> m.owned;

    m.rented = 0;

    in.ignore ();


}


//Write the data of movie m to file ut
//Only movie name, number of copies, type,
//and number of copies rented are written
void put(ofstream &ut, Movie m)
{
   ut << setw (5) << m.name << endl;
   ut << setw (5) << m.genre << endl;
   ut << setw (5) << m.owned << endl;
   ut << setw (5) << m.rented << endl;



}


//Write the data of movie m to cout
//Only movie name, number of copies, type,
//and number of copies rented are displayed
void put(Movie m)
{
    cout << "Movie: " << m.name << endl;
    cout << "Genre: " << m.genre << endl;
    cout << "Owned copies: " << m.owned << endl;
    cout << "Rented copies: " << m.rented << endl;


}


//Return true if m1's name is alphabetically larger than m2's name
//Otherwise, returns false
bool operator>(Movie m1, Movie m2)
{
        return m1.name > m2.name;
}



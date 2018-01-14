#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

//DO NOT MODIFY ANY FUNCTION DECLARATION
//DO NOT ADD NEW FUNCTIONS

using namespace std;

const int MAX_COPIES = 4;

//ADD NEW DATA TYPE Movie
struct Movie
{
    string name;
    string genre;
    int owned;
    int rented;
    int customerID[];

};



//Read the data for a new movie (name, number of copies, type) from file in
//Number of rented copies is set to zero
void get(ifstream &in, Movie& m);


//Write the data of movie m to file ut
//Only movie name, number of copies, type,
//and number of copies rented are written
void put(ofstream &ut, Movie m);


//Write the data of movie m to cout
//Only movie name, number of copies, type,
//and number of copies rented are displayed
void put(Movie m);


//Returns true if m1's name is alphabetically larger than m2's name
//Otherwise, returns false
bool operator>(Movie m1, Movie m2);


#endif // MOVIES_H_INCLUDED

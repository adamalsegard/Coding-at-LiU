#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

//DO NOT CHNANGE THE FUNCTION DECLARATIONS
//DO NOT ADD NEW FUNCTIONS

using namespace std;

const int MAX_COPIES = 4;

struct Movie
{
    string name;
    string genre;
    int owned;
    int rented;
    int customerID[MAX_COPIES];

};


//Read the data for a new movie (name, number of copies, type) from file in
//Number of rented copies is set to zero
void get(ifstream &in, Movie& m); //uppgift 1


//Write the data of movie m to file ut
//Only movie name, number of copies, type,
//and number of copies rented are written
void put(ofstream &ut, Movie m); //uppgift 1


//Write the data of movie m to cout
//Only movie name, number of copies, type,
//and number of copies rented are displayed
void put(Movie m); //uppgift 1


//Display all customers of movie m to cout
void display_customers(Movie m);


//Add one more rental to movie m
//id is the persnr of the customer
//If all copies rented then display an error message message
void add_rental(Movie& m, int id);


//Remove rental of movie m by customer id
//id is the persnr of the person who rented the movie
//If id not found in m.customers then an error message is displayed
void remove_rental(Movie& m, int id);


//Return true if m1's name is alphabetically larger than m2's name
//Otherwise, returns false
bool operator>(Movie m1, Movie m2); //uppgift 1


#endif // MOVIES_H_INCLUDED

//DO NOT MODIFY the function declarations

#ifndef DIVER_INFO_H
#define DIVER_INFO_H

#include <iostream>
#include <string>

using namespace std;

const int NR_OF_REF = 7;  //NR_OF_REF = antal domare


//New data type representing a diver
struct Diver
{
	string name;
	double points[NR_OF_REF];
	double difficulty;
	double final_score;
};


//Overload operator>> to read data for a diver d from stream in
//If errors were encountered while reading the data for a diver d
//then d.difficulty is set to a negative value
//Return the stream in
istream& operator>>(istream& in, Diver& d);


//Calculate final score for diver d
//and store it in d.final_score
void calculate_final_score(Diver& d);


//Overload operator<< to write data for diver d
//to stream out: name and final score
ostream& operator<<(ostream& out, const Diver& d);


//Overload comparison operator<
//Return true if d1.final_score < d2.final_score
bool operator<(const Diver& d1, const Diver& d2);


#endif



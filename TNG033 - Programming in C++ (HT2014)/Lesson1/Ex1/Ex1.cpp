
// Lesson 1, Exercise 1.

using namespace std;

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>


//Definition of structure Vector
struct Vector
{
    double* coord; //pointer to an array with the coordinates
    int n_coord;
};

//Functions declaration

//Create a vector with n coordinates
//All coordinates are initialized to zero
void reserve_vector_memory(Vector &V, int n);

//Free the memory occupied by the coordinates of V
void release_vector_memory(Vector &V);

istream& operator>>(istream& is, Vector &v);

ostream& operator<<(ostream& os, const Vector &v);

//Return length of vector V
double length(const Vector &v);



int main()
{
    Vector V;
    int numb_coord = 0;

    cout << "Number of coordinates: ";

    while (cin >> numb_coord && numb_coord > 0) //Läser in så länge antalet koordinater är på korrekt format
    {
        //Reserve memory for the vector
        reserve_vector_memory(V, numb_coord);

        //Read vector coordinates
        cout << "Enter coordinates: ";
        cin >> V;

        //Calculate the length of the vector
        cout << "length(" << V << ")= "
             << length(V) << endl;

        //Free the vector's memory
        release_vector_memory(V);

        cout << "\nNumber of coordinates: ";
    }

    cout << "Bye beautiful!" << endl;

    return 0;
}


//Create a vector with n coordinates
//All coordinates are initialized to zero
void reserve_vector_memory(Vector &V, int n)
{
    //Allocate memory for the array storing the coordinates
    V.coord = new (nothrow) double[n];

    if(!V.coord)
    {
        cout << "Not enough memory!!" << endl;
        V.n_coord = 0;
    }
    else
    {
        V.n_coord = n;

        for(int i=0; i<n; i++)
        {
            V.coord[i] = 0.0;
        }
    }
}

//Free the memory occupied by the coordinates of V
void release_vector_memory(Vector &V)
{
    delete [] V.coord; //Deallocate the memory

    V.coord = nullptr;
    V.n_coord = 0;

}


istream& operator>>(istream& is, Vector &v)
{
/* Funkar så länge användaren är snäll - men bättre med string stream
    double d;
    int i=0;

    while(is >> coord)
    {
        v.coord[i++] = coord;

        if(i == v.n_coord)
            return is;
    }
    return is;
    */

    string line;

    is >> ws;
    getline(is, line); // read as text
    istringstream in(line);

    for(int i = 0; i < v.n_coord; i++)
        in >> v.coord[i];

    return is;
}


ostream& operator<<(ostream& os, const Vector &v)
{
    os << "<" << fixed << setprecision(2);

    for(int i = 0; i< v.n_coord-1; i++)
    {
        os << v.coord[i] << ", ";
    }

    os << v.coord[v.n_coord-1] << ">";

    return os;

}

//Return the length of vector V
double length(const Vector &v)
{
    double sum = 0;
    const double *v_end = v.coord + v.n_coord;

//     for(int i = 0; i < v.n_coord; i++)
//        sum += pow(v.coord[i],2);

    for(const double* p = v.coord; p != v_end; p++)
        sum += pow(*p, 2);


    return sqrt(sum);

}

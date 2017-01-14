/**********************************************
* TNG033: Lesson 1, exercise 1                *
* *********************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>  //pow
#include <sstream>

using namespace std;

/****************************************
* Definition of new data type Vector    *
*****************************************/

struct Vector
{
    double* coord;  //pointer to an array with the coordinates
    int n_coord;
};


/****************************************
* Function declarations (prototypes)    *
*****************************************/


//Create a vector with n coordinates
//All coordinates are initialized to zero
void reserve_vector_memory(Vector &V, int n);


//Free the memory occupied by the coordinates of V
void release_vector_memory(Vector &V);


istream& operator>>(istream& is, Vector &v);


ostream& operator<<(ostream& os, const Vector &v);


//Return the length of vector V
double length(const Vector &v);


/**************************
* MAIN                    *
***************************/

int main()
{
    Vector V;
    int numb_coord = 0;

    cout << "Number of coordinates: ";

    while (cin >> numb_coord && numb_coord > 0)
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

    cout << "Bye ..." << endl;

    return 0;
}

/*************************************
* Function definitions               *
**************************************/

//Create a vector with n coordinates
//All coordinates are initialized to zero
void reserve_vector_memory(Vector &V, int n)
{
    V.coord = new (nothrow) double[n];  //allocate memory for the coordinates

    if (V.coord)
        V.n_coord = n;
    else
        V.n_coord = 0;


    for(int i = 0; i <  V.n_coord; i++)
        V.coord[i] = 0.0;
}


//Free the memory occupied by the coordinates of V
void release_vector_memory(Vector &V)
{
    delete [] V.coord;  //deallocate the memory

    V.coord = nullptr;
    V.n_coord = 0;
}


istream& operator>>(istream& is, Vector &v)
{
    string line;

    is >> ws;

    getline(is, line);

    istringstream in(line);

    for(int i = 0; i <  v.n_coord; i++)
        in >> v.coord[i];

    return is;
}

ostream& operator<<(ostream& os, const Vector &v)
{
    os << "<"
       << fixed << setprecision(2);

    for(int i = 0; i < v.n_coord-1; i++)
        os << v.coord[i] << ", ";

    os << v.coord[v.n_coord-1] << ">";

    return os;
}


//Return the length of vector V
double length(const Vector &v)
{
    double sum = 0;
    const double* v_end = v.coord + v.n_coord;

//     for(int i = 0; i < v.n_coord; i++)
//        sum += pow(v.coord[i],2);

    for(const double* p = v.coord; p != v_end; p++)
        sum += pow(*p,2);

     return sqrt(sum);
}


#include <iostream>
#include <fstream>

#include "movies.h"

using namespace std;

const int SIZE = 100;

/****************************************/
//Function declarations (prototypes)
/****************************************/

//DO NOT CHNAGE THE GIVEN FUNCTION DECLARATIONS


//Sort alphabetically array V with n movies
//movies name is used for sorting
void sort(Movie V[], int n);


//Read a text file f of movies and
//Load the movies into array V
//Function returns the number of movies read
//Array V has n movie slots
int read_from_file(ifstream& f, Movie V[], int n);


//Write all movies in V to file f
//Array V stores n movies
void write_to_file(ofstream& f, Movie V[], int n);


//Display all movies in V to the screen
//Array V stores n movies
void display_DB(Movie V[], int n);


/****************************************/
// Main program
/****************************************/


//DO NOT CHANGE THE main()
int main()
{

    ifstream in_file("movies.txt");         //file to read
    ofstream out_file("movies_sorted.txt"); //file to write

    Movie DB[SIZE]; //A database of movies

    //Test if opening the files succeeded
    if ( !in_file.is_open() || !out_file.is_open() )
    {
        cout << "Error in file opening" << endl;
        return 0; // end the program
    }

    //Load a file of movies into array DB
    int howMany = read_from_file(in_file, DB, SIZE);



    if (!howMany)
    {
        cout << "File is empty!!" << endl;
        return 0;
    }

    //Sort array DB by movies name
    sort(DB, howMany);

    //Display the sorted movies in array DB to the screen
    display_DB(DB, howMany);

    //Save the sorted movies stored in DB to a text file
    write_to_file(out_file, DB, howMany);

    //close the files
    in_file.close();
    out_file.close();



    return 0;
}

/****************************************/
//Function definitions
/****************************************/

//Sort alphabetically array V with n movies
//movies name is used for sorting
void sort(Movie V[], int n)
{

   for (int pass = 0; pass< n-1; pass++)
   {
        for (int i = 0; i< n-1; i++)
        {

            if (V[i] > V[i+1])
            {

                Movie temp = V[i];
                V[i] = V[i+1];
                V[i+1] = temp;

            }
        }
   }

}


//Read a text file f of movies and
//Load the movies into array V
//Function returns the number of movies read
//Array V has n movie slots
int read_from_file(ifstream& f, Movie V[], int n)
{
    int count = 0;
    Movie temp;


   get (f, temp);

   while (f)
   {
       V[count] = temp;
       count++;
       get(f, temp);

       if (count == n)
       break;
   }


    return count;
}

//Display all movies in V to the screen
//Array V stores n movies
void display_DB(Movie V[], int n)
{

    for (int i=0; i<n; i++)
    {
        put (V[i]);
    }

}


//Write all movies in V to file f
//Array V stores n movies
void write_to_file(ofstream& f, Movie V[], int n)
{
    for (int i =0; i<n; i++)
    {
        put (f, V[i]);
    }

}


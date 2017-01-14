#include <iostream>
#include <fstream>

#include "movies.h"

using namespace std;

const int SIZE = 100;
const int NOT_FOUND = -1;
const int EXIT = 5;
const int zero = 0;

/****************************************/
//Function declarations (prototypes)
/****************************************/

//Sort alphabetically array V with n movies
//movies name is used for sorting
void sort(Movie V[], int n); //uppgift 1


//Read a text file f of movies and
//Load the movies into array V
//Returns number of movies stored in V
//At most n movies can be stored in V
int read_from_file(ifstream& f, Movie V[], int n); //uppgift 1


//Display all movies in V to the screen
//Array V stores n movies
void display_DB(Movie V[], int n); //uppgift 1


//Display the menu
void display_menu();


//Search for movie name in array V: see examples from Fö 5
//Search key: movie name
//Array V stores n movies
//Return the index of the position where the movie is found, or
//Return NOT_FOUND, if movie not found
int find_movie(Movie V[], int n, string name);


//Display all customer who are renting movie name
//V stores n movies
//If movie name not found in V then an error message is displayed
void display_rentals(Movie V[], int n, string name);

//Rent movie name to person ID
//V stores n movies
//If rental not possible then an error message is displayed
void rent_movie(Movie V[], int n, string name, int ID);

//Return rental of movie by person ID
//V stores n movies
//If rental not possible then an error message is displayed
void return_rental(Movie V[], int n, string movie, int ID);


/****************************************/
// Main program
/****************************************/

int main()
{
    ifstream in_file("movies.txt"); //file to read

    Movie DB[SIZE]; //A database of movies

    //Test if opening the file succeeded
    if ( !in_file.is_open() )
    {
        cout << "Error in file opening!!" << endl;
        return 0; // end the program
    }

    //Load a file of movies into array DB
    int howMany = read_from_file(in_file, DB, SIZE);

    //Sort array DB by movies name
    sort(DB, howMany);

    int option;
    string name;

    do {
        display_menu();

        cout << "Option? ";
        cin >> option;
        cin.ignore();

        cout << endl;

        switch (option)
        {
            case 1: //Display the sorted movies in array DB to the screen
                    display_DB(DB, howMany);
                    break;

            case 2: //Read movie name
                    cout << "Movie name? ";
                    getline(cin, name);

                    display_rentals(DB, howMany, name);
                    break;

            case 3:
                    cout << "Movie name: ";
                    getline(cin, name);

                    rent_movie(DB, howMany, name, zero);
                    break;

            case 4:
                    cout << "Movie name: ";
                    getline(cin, name);

                    return_rental(DB, howMany, name, zero);
                    break;

            case 5: cout << "Goodbye!!" << endl;
                    break;

            default: cout << "Wrong option!!" << endl;
        }

    } while (option != EXIT);


    //close the files
    in_file.close();

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
//Returns number of movies stored in V
//At most n movies can be stored in V
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


//Display the menu
void display_menu()
{
    cout << "\n**************************" << endl;
    cout << "*1. Display all movies" << endl;
    cout << "*2. Display movie rentals" << endl;
    cout << "*3. Rent a movie" << endl;
    cout << "*4. Return a movie" << endl;
    cout << "*5. Exit" << endl;
    cout << "**************************" << endl;
}


//Search for movie name in array V: see examples from Fö 5
//Search key: movie name
//Array V stores n movies
//Return the index of the position where the movie is found, or
//Return NOT_FOUND, if movie not found
int find_movie(Movie V[], int n, string name)
{

   for (int i=0; i<n; i++)
   {
       if (V[i].name == name)
       {
           return i;
       }
   }

   return NOT_FOUND;
}


//Display all customers who are renting movie name
//V stores n movies
//If movie name not found in V then an error message is displayed
void display_rentals(Movie V[], int n, string name)
{
   int value = 0;
    value = find_movie (V, n, name);

    if (value == NOT_FOUND)
    {
        cout << "Movie not found!" << endl;
    }
    else
    {
       display_customers (V[value]);

    }

}

//Rent movie name to person ID
//V stores n movies
//If rental not possible then an error message is displayed
void rent_movie(Movie V[], int n, string name, int ID)
{
    int num = 0;

    cout << "Personal number: ";
    cin >> ID;

    num = find_movie(V, n, name);

    if (num == NOT_FOUND)
    {
       cout << "Movie not found!" << endl;
    }
    else
    {
        add_rental (V[num], ID);
    }

}

//Return rental of movie by person ID
//V stores n movies
//If rental not possible then an error message is displayed
void return_rental(Movie V[], int n, string name, int ID)
{

    int num = 0;

    cout << "Personal number: ";
    cin >> ID;

    num = find_movie(V, n, name);

    if (num == NOT_FOUND)
    {
       cout << "Movie not found!" << endl;
    }
    else
    {
        remove_rental(V[num], ID);
    }

}


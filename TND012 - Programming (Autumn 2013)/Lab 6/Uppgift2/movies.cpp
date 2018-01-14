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

    for (int i = 0; i<MAX_COPIES; i++)
    {
        m.customerID[i] = 0;
    }

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
    cout << "Movie: " << m.name <<endl
         << "Genre: "  << m.genre<< endl
         << "Owned copies: " << m.owned << endl
         << "Rented: " << m.rented << endl << endl;
}


//Return true if m1's name is alphabetically larger than m2's name
//Otherwise, returns false
bool operator>(Movie m1, Movie m2)
{
    return m1.name > m2.name;
}


//Display all customers of movie m to cout, if any
void display_customers(Movie m)
{
    for (int i= 0; i< m.owned; i++)
    {

       if (m.customerID[i] >0)
       {
           cout << "Customer: " << m.customerID[i] << endl;
       }

    }

}

//Add one more rental to movie m
//id is the persnr of the customer
//If all copies rented then display an error message message
void add_rental(Movie& m, int id)
{

      if (m.rented == m.owned)
      {
          cout << "All copies already rented!" << endl;
      }
      else
      {
          for (int i = 0; i<m.owned; i++)
          {
              if (m.customerID[i] == 0)
              {
                  m.customerID[i] = id;
                  m.rented++;
                  break;
              }
          }

      }

}

//Remove rental of movie m by customer id
//id is the persnr of the person who rented the movie
//If id not found in customers then an error message is displayed
void remove_rental(Movie& m, int id)
{
    for (int i = 0; i<m.owned; i++)
    {
        if (m.customerID[i] == id)
        {
            m.rented--;
            m.customerID[i] =0;
            break;
        }
        else if (m.owned-1 == i)
        {
            cout << "Customer ID not found!" << endl;
        }
    }

}


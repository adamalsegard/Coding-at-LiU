
#include <iostream>
#include <iomanip>
#include <fstream>
#include "diver.h"

using namespace std;

/******************************
* 1. Functions declarations   *
*******************************/

//Read divers data from stream in and
//If correct diver's data then store a diver's record in array V
//If incorrect diver's data then write diver's name in log file
//Return number of divers read and stored in V
//V has n slots
//overloaded operator>> should be used in this function
int read_divers(istream& in, Diver V[], int n, ostream& log);


//Display all divers stored in array V to cout
//V stores n divers
//overloaded operator<< should be used in this function
void display(const Diver V[], int n);


//Sort V decreasingly by divers final score
//V stores n divers
//operator< should be used in this function
void sort_divers(Diver V[], int n);


/******************************
* 2. Main function            *
*******************************/



int main ()
{
    const int NR_OF_DIVERS = 50;

    int howMany = 0;
    Diver alla[NR_OF_DIVERS];


    string filnamn;

    //Läs från fil!
    cout << "Filnamn: ";
    cin >> filnamn;

    ifstream inFil(filnamn);		//C++11
    ofstream errFil("errors.txt");

    if ( !inFil || !errFil ) // Läs från fil
    //if (!errFil ) // Läs från tangentbord
    {
        cout << "Någon av filerna kunde inte öppnas!!" << endl;
        return 0;
    }


    howMany = read_divers(inFil, alla, NR_OF_DIVERS, errFil); // Läs från fil
    //howMany = read_divers(cin, alla, NR_OF_DIVERS, errFil); // Läs från tangentbord


    for(int i=0; i<howMany; i++)
    {
        calculate_final_score(alla[i]);
    }

    sort_divers(alla, howMany);

    display(alla, howMany);

    return 0;
}


/******************************
* 3. Functions definitions    *
*******************************/


//Read divers data from stream in and
//If correct diver's data then store a diver's record in array V
//If incorrect diver's data then write diver's name in log file
//Return number of divers read and stored in V
//V has n slots
//overloaded operator>> should be used in this function
int read_divers(istream& in, Diver V[], int n, ostream& log)
{
    int howMany = 0;
    Diver logfil[n];
    int logfel = 0;
    Diver temp[n];
    int counter = 0;

    //cout << "Enter Diver(Correct format: Name \n Dif, scores x7): "; // Fråga användaren
    in >> temp[counter]; //Läs första dykarrn

    while(in) //test stream
    {

        if(temp[counter].difficulty > 0)
        {
            V[howMany] = temp[counter];
            howMany++;
        }
        else
        {
            logfil[logfel] = temp[counter];
            logfel++;
            //break; // Avsluta inläsningen från skärmen
        }

        counter++;
        //cout << "Enter another Diver(Correct format: Name \n Dif, scores x7): "; // Fråga användaren
        in >> temp[counter];  //read en annan dykarre'
    }

    for(int k=0; k<logfel; k++)
    {
        log << logfil[k];
    }

    // Läs från fil!
    if ( !in.eof() ) //test if reading loop exited before the end-of-file was reached
    {
        cout << "Kunde inte läsa hela filen :( " << endl;
    }
    return howMany;
}


//Display all divers stored in array V to cout
//V stores n divers
//overloaded operator<< should be used in this function
void display(const Diver V[], int n)
{

   cout << "   Divers Result" << endl
   << "====================================" << endl;

   for(int i=0; i<n; i++)
   {
       cout << setw(2) << i + 1 << ". " << V[i];
   }

}

//To be used by sort function
void swap(Diver& a, Diver& b)
{
    Diver temp = a;
    a = b;
    b = temp;
}


//Sort V decreasingly by divers final score
//V stores n divers
//operator< should be used in this function
void sort_divers(Diver V[], int n)
{

    for(int pass = 0; pass<n-1; pass++ ) // passes

        for(int i = 0; i<n-1; i++ )      // one pass
        {

            if (V[i] < V[i+1]) //overloaded operator< called
            {
                swap(V[i], V[i+1]);
            }
        }

}




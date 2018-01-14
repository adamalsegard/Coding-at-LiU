#include <iostream>
#include <iomanip>
#include <fstream>

#include "statistics.h"

using namespace std;

/******************************
* 1. Functions declarations   *
*******************************/

//Read a sequence of values from cin and store them in array a
//Array a has n slots
//Return how many values were read and stored in a
int read_seq(int a[], int size);


//Display all values stored in array a to cout
//array a stores n integers
//At most, 10 values per line should be displayed
void display(int a[], int n);


//Copy n values from array *from* into array *to*
void copy_list(int to[], int from[], int n);


//Sort array a
//a is an array storing n values
//Use a sorting algorithm different from bubblesort, e.g. selection sort, insertion sort
void sort_list(int a[], int n);


//swap the values of parameters a and b
//to be used by sort function
void swap(int& a, int& b);



/******************************
* 2. Main function            *
******************************/


int main ()  //DO NOT MODIFY
{
    const int SIZE = 1000;

	int theNumbers[SIZE], theCopy[SIZE];

	int howMany = read_seq(theNumbers, SIZE);

	if (!howMany)
	{
	    cout << "No data given!!" << endl;
	    return 0;
	}

	cout << "Sequence size = " << howMany << endl;

	copy_list(theCopy, theNumbers, howMany);
	sort_list(theCopy, howMany);

	cout << "\nList of values not sorted" << endl;
	display(theNumbers, howMany);
	cout << endl;

	cout << "\nList of sorted values" << endl;
	display(theCopy, howMany);
	cout << endl;

	int max = 0, min = 0;

	max = max_min(theNumbers, howMany, min);
	cout << "\n\nMax = " << max
	     << " and Min = " << min << endl;

	double theMean = mean(theNumbers, howMany);
	cout << "Average = " << theMean << endl;

	double theMedian = median (theCopy, howMany);
	cout << "Median = " << theMedian << endl;

	double theStandardDev = standard_deviation(theNumbers, howMany);
	cout << "Standard deviation = " << theStandardDev << endl;

	return 0;
}


/******************************
* 3. Functions definitions    *
*******************************/


//Read a sequence of values from cin and store them in array a
//Array a has size slots
//Return how many values were read and stored in a
int read_seq(int a[], int size)
{
    int howMany = 0;

    /*// Skriv in filen själv
    string filnamn;

    cout << "Filnamn: ";
    cin >> filnamn;

    ifstream inFil(filnamn);

    if (!inFil)
    {
        cout << "Filen kunde inte öppnas!" << endl;
        return 0;
    }

    inFil >>  a[howMany];//Läsa in första
    */
    //while (inFil)
    while(cin >> a[howMany])
    {
        howMany++;
        if(howMany == size)
        {
            break;
        }
        //inFil >> a[howMany];
    }

    //Läs in från fil
    /*if ( !inFil.eof() ) //Kolla ifall vi kommer till slutet av filen
    {
        cout << "Kunde inte läsa hela textfilen!" << endl;
    }
    */

	return howMany;
}


//Display all values stored in array a to cout
//array a stores n integers
//At most, 10 values per line should be displayed
void display(int a[], int n)
{
    int counter = 0;

    for(int i=0; i<n; i++)
    {
        cout << a[i] << "   ";
        counter++;

        if(counter%10 == 0)
        {
            cout << endl;
        }
    }

}


//Copy n values from array *from* into array *to*
void copy_list(int to[], int from[], int n)
{

    for(int i =0; i<n; i++)
    {

        to[i] = from[i];

    }

}


//Sort array a
//a is an array storing n values
//Use a sorting algorithm different from bubblesort
void sort_list(int a[], int n) //selection sort
{
   int pos_min = 0;


   for(int i=0; i<n-1; i++)
   {
       pos_min = i;

       for(int j=i+1; j<n; j++)
       {
           if(a[pos_min]>a[j])
           {
               pos_min = j;
           }
       }

       if(pos_min != i)
       {
           swap(a[i], a[pos_min]);
       }

   }


}

//swap the values of parameters a and b
//to be used by sort function
void swap(int& a, int& b)
{
    int temp = a;

	a = b;
	b = temp;
}



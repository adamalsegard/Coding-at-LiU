//Adam Alsegård & Jonas Kinnvall
// Lab 5, Exercise 2

/**************************************************************************
 Author: Aida Nordman
 Course: tnd012, lab5, exercise 2
 Program to display a graph
 Input: ...
************************************************************************* */

//Input data
//average 2000-2011: 50 50 100 250 100 50 100 85 100 180 10 100
//2012: 70 78 170 250 105 90 120 96 160 250 18 150

#include <iostream>
#include <iomanip>
#include<cmath>

using namespace std;

const int JITTER = 10; //how many units corresponds to each '*'


//Read a sequence of n integers and store them in V
//Negative integers should be simply ignored
void read_seq(int V[], int n = 12)
{
    int value = 0;
    int i = 0;

    while (i < n)
        {
             cin >> value;

            if (value >=0)
            {
                V[i] = value;
                i++;

            }
        }

}


//Calculate the difference between the values stored in V1 and V2
//and store the result in V3
//V1, V2, and V3 store n ints
void difference(int V1[], int V2[], int V3[], int n = 12)
{

    for (int i=0; i<n;i++)
    {
        V3[i] = (V2[i]-V1[i]);
    }


}


//Returns the number of '*' corresponding to n
//Each '*' corresponds to 10 units
//n < 5 corresponds to '*'
int count_stars(int n)
{
    if (n%JITTER >4)
    {
        return ((n/JITTER)+1);
    }
    else if (n%JITTER<5)
    {
        return (n/JITTER);
    }

}


//Display one line of the graph, for value v
//The line must start with the month
void display_graph_line(int v, char month)
{

    cout << month << "  ";
     for(int i = 1; i<= count_stars (v); i++)
     {
         cout << "*";
     }
    cout << endl;

}

//Calculate the maximum and minimum values stored in array V
//V stores n integers
//min and max are reference parameters carrying out function's results
void max_min(int V[], int n, int &min, int &max)
{

    min = max = V[0];

    for (int i=0; i<n; i++)
    {
        if ( V[i]< min)
        {
            min = V[i];
        }
        else if (V[i] > max)
        {
            max = V[i];
        }
    }


}


int main()
{
    //Declare the needed variables here
    int const month = 12;
    int average [month] = {0};
    int TwoTwelve [month] = {0};
    int Diff [month] = {0};
    int least_month = 0;
    int most_month = 0;
    string word = "JFMAMJJASOND";
    const string year [month] = {"January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October", "November", "December"};



    cout << "Enter average data for 2000-2011" << endl;
    //1. Read the average data sequence
    read_seq (average, month);

    cout << "Enter data for 2012" << endl;
    //2. Read the 2012 data sequence
    read_seq (TwoTwelve, month);

    //3. Calculate the difference between 2012 data and average
    difference (average, TwoTwelve, Diff, month);

    cout << endl << "The Graph" << endl << endl;
    //4. Display the graph, line by line

    for (int i =0; i < month; i++)
    {
    display_graph_line(Diff[i], word[i]);

    }


    max_min (Diff, month, least_month, most_month);

    cout << endl << "Month(s) least deviate from average:" << endl;
    //5. Display the months that differ least from the average

    for (int i=0; i<month; i++)
    {
        if (Diff[i] == least_month)
        {
            cout << year[i] << ", ";
        }
    }

   cout << least_month << endl;


    cout << endl << "Month(s) mostly deviate from average:" << endl;
    //6. Display the months that differ most from the average

    for (int i=0; i<month; i++)
    {
        if (Diff[i] == most_month)
        {
            cout << year[i] << ", ";
        }
    }
      cout << most_month << endl;

   return 0;
}


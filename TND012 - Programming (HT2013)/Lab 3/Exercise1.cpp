// Lab 1, exercise 1
// Jonas and Adam
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    // Declare variables
    int price = 0, price_1 = 80, price_2 = 30, price_3 = 0, tickets = 0, total_cost = 0;
    int age = 0, age_15 = 15, age_8 = 8, age_0 = 0, i;
    // Ask user about how many tickets to buy

    cout << "Welcome to our football arena!" << endl
         << "------------------------------" << endl;
    do
    {
        cout << "Number of tickets: ";
        cin >> tickets;
        cout << endl;


        if (tickets < 1)
            cout << "Invalid number of tickets!" << endl << endl;
    }
    while (tickets < 1);


    // Request the age of each ticket owner
    for (int i = 1; i <= tickets; i++)
    {
        cout << "Enter age of person " << i << ": ";
        cin >> age ;
        if ( age > age_15)
        {
            price = price_1;
            total_cost += price;
        }

        else if (age <= age_15 && age >= age_8)
        {
            price = price_2;
            total_cost += price;
        }

        else
        {
            price = price_3;
            total_cost += price;
        }
    }


    // Calculate the total ticket price

    // Display total ticket price
    cout << "Total cost: " << total_cost <<  " SEK." << endl;


    return 0;
}

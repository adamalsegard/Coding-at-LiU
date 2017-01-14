#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main ()
{
    //declare variables
    int age, age_1, age_2;
    int price_1 = 0;
    int price_2 = 30;
    int price_3 = 80;
    const double rabatt = 0.8;
    int option;
    double tot_price, price_F, price_S;

    // user input - option
    cout << "Welcome to our football arena" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Price of one ticket." << endl;
    cout << "2. Price of two tickets." << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter option: ";
    cin >> option;

    //read options
    if (option==1){
    //calculate option 1

        cout << "Enter age: ";
        cin >> age;

        if (age> 15)
            cout << "Price: " << price_3 << " SEK." << endl;
        else if (age<=15 && age>= 8)
            cout << "Price: " << price_2 << " SEK." << endl;
        else
            cout << "Price: " << price_1 << " SEK." << endl;
        }
    else if (option==2)
        //calculate option 2
        {
            cout << "Enter age for 1st ticket: ";
            cin >> age_1;

        if (age_1> 15)
            {
            price_F = price_3;}
        else if (age_1<=15 && age_1>= 8)
           {
               price_F = price_2;
           }
        else{
            price_F = price_1;}


            cout << "Enter age for 2nd ticket: ";
            cin >> age_2;
        if (age_2> 15) {
            price_S = price_3;}
        else if (age_2<=15 && age_2>= 8){
            price_S = price_2;}
        else{
            price_S = price_1;
            }
//display results
        if (age_1>7 && age_2>7)
            {
                tot_price = price_F+ price_S;
                tot_price = tot_price *rabatt;
                cout << "Total price: " << tot_price << endl;
            }
        else {
                tot_price = price_F+ price_S;
                cout << "Total price: " << tot_price << endl;

            }
        }

    else
    {
        cout << "Invalid option!" << endl;
    }




    return 0;
}

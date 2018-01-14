/**************************************************************************
 Author: Jonas Kinnvall, Adam Alsegård
 Course: tnd012, lab4
 Program to find prime numbers
************************************************************************* */

#include <iostream>
#include <windows.h>
#include <ctime>
using namespace std;

const int EXIT = 5;

//ADD any needed functions here
bool Test_Prime (int N)
{
    if (N == 1 || N== 2)

        return true;

    else
    {
        for (int i = 2; i<N; i++)
        {

            if ( (N % i) == 0 )

                return false;

        }
        return true;
    }
}

int Next_Prime (int x)
{

   while (!Test_Prime(x))
    {
           x++;
    }


    return x;

}


int Prev_Prime (int y)
{

   while (!Test_Prime(y))
    {
           y--;
    }


    return y;

}


void Display_Primes (int z)
{

int const stoppingPoint = z;


    for (int n = 1; n <= stoppingPoint ; n++)
       {
        if (Test_Prime (n))
            cout << n << " ";


    }


}


int main()
{
    int option = EXIT;

    //declare any other needed variables and constants here
    int number = 0;
    system ("color F0");
    do
    {
        //Display the menu
        cout << endl << "=================" << endl
             << "1. Test Prime" << endl
             << "2. Next Prime" << endl
             << "3. Prev Prime" << endl
             << "4. Display Primes" << endl
             << "5. Exit" << endl
             << "=================" << endl;

        //Read user option
        cout << "Your choice: ";

        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Test prime? ";
            cin >> number;
            if (Test_Prime (number) == true)

                cout << endl<< number << " is a prime number!" << endl;

            else
                cout << endl << number << " is not a prime number!" << endl;

            break;

        case 2:
            cout << "Next prime? ";
            cin >> number;

            cout << endl << "Next prime of " << number << " is " << Next_Prime(number) << endl;



            break;

        case 3:
            cout << "Prev prime? ";
            cin >> number;

            cout << endl << "Previous prime of " << number << " is " << Prev_Prime (number) << endl;

            break;

        case 4:
            cout << "N? ";
            cin >> number;

            cout << endl << "Primes in [1," << number << "] " << endl;
            Display_Primes(number);
            cout << endl;

            break;


        case 5:
            cout << endl << "Exiting..." << endl;

            break;

        default:
            cout << endl << "Wrong option!" << endl;

            break;

        }

        //Handle user option
    }
    while (option != EXIT);


    return 0;
}

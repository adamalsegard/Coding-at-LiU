// Lab 3, exercise 2
// Jonas (jonki910) and Adam (adaal265)
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

int main()
{
system("color F0");
// Declare varibles
    double first_p = 0.0, last_p = 0.0, step = 0.0, tax_p = 0.0, price_tax = 0.0, tax =0.0, price=0.0;
    int percentage = 100;

    cout << setprecision(2) << fixed;

// Ask for user input
    do
    {

        cout << "       " << "First price: ";
        cin >> first_p;

        cout << "       " << "Last price: ";
        cin >> last_p;

        cout << "       " << "Price step: ";
        cin >> step;

        cout << "       " << "Tax percentage: ";
        cin >> tax_p;

        if (first_p < 0 || last_p < 0 || step < 0 || tax_p < 0 || first_p > last_p || step <= 0)
            cout << endl << "Wrong input!!!" << endl << endl;

    }
    while (first_p < 0 || last_p < 0 || step < 0 || tax_p < 0 || first_p > last_p || step <= 0);

    // Display results
            cout << endl << "Taxes Table" << endl << "Tax = " << tax_p << " %" << endl;
            cout << endl << "Price tax free" << setw(11) << "Tax" << setw(30) << "Price with tax" << endl
                 << "========================================================";

    // Calculate results

    for (first_p; first_p <= last_p; first_p += step)
        {
            price = first_p;
            tax = price * (tax_p/percentage);
            price_tax = price + tax;

            cout << endl << price << setw (21) << tax << setw(20) << price_tax << endl;

        }

    return 0;
}

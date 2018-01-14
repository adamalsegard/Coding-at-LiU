// Lab 3, exercise 2
// Jonas (jonki910) and Adam (adaal265)
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{

    // Declare varibles
    double tax_p = 0.0, price_tax = 0.0, tax =0.0, price=0.0;
    const int percentage = 100, SIZE = 20;

    double prices[SIZE] = {0.0};

    // Ask for user input and read the prices

   cout << "Enter products price (" <<SIZE<<" products): ";

        for (int i=0; i < SIZE; i++)
            cin >> prices[i];

        cout << endl << "Enter tax: ";
        cin >> tax_p;

    cout << fixed << setprecision (2);

    // Display results
            cout << endl << "Taxes Table" << endl << "Tax = " << tax_p << " %" << endl;
            cout << endl << "Price tax free" << setw(14) << "Tax" << setw(27) << "Price with tax" << endl
                 << "========================================================";

    // Calculate results

    for (int t = 0; t < SIZE; t++)
        {
            price = prices[t];
            tax = price * (tax_p/percentage);
            price_tax = price + tax;

            cout << endl << setw (10) << price << setw (21) << tax << setw(20) << price_tax << endl;

        }

    return 0;
}

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main ()
{

//declare constants and variables
double b, c;
double x_1, x_2;


//user input
    cout << "Solving a second degree equation of the form x^2 + b*x + c" << endl;
    cout << "Enter coefficiant b: ";
    cin >> b;
    cout << "Enter coefficiant c: ";
    cin >> c;



//calculate equation

x_1 = (-(b/2)+ sqrt(pow((b/2),2)-c));
x_2 = (-(b/2)- sqrt(pow((b/2),2)-c));



//display results






    return 0;
}

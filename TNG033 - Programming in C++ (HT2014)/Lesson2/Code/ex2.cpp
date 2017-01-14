/***************************************************************************
* TNG033, Lesson 2                                                         *
* Exeercise 2                                                              *
* **************************************************************************/

#include <iostream>

using namespace std;

typedef bool (*Test)(int);
//Define function selected_average
double selected_average(int *A, int n, Test t)
{
    double sum = 0;
    int counter = 0;

    for(int i=0; i<n; i++)
    {
        if(t(A[i]))
        {
            sum += A[i];
            counter++;
        }
    }
    if(counter)
        return sum/counter;

    return 0;
}


bool odd(int n)
{
    if (n%2) return true;

    return false;
}


bool prime(int n)
{
    if (n == 1) return false;

    if ( n == 2 ) return true;

    if ( !(n%2) ) return false;

    for(int i = 3; i < n; i++)
      if (!(n%i)) return false;

    return true;
}


int main()
{

    int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //Display the average of all prime numbers in V
    cout << "Average of the prime numbers = " << selected_average(V, 10, prime) << endl;

    //Display the average of all odd numbers in V
    cout << "Average of the odd numbers = " << selected_average(V, 10, odd) << endl;

    return 0;
}


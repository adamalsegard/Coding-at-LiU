/***************************************************************************
* TNG033, Lesson 2                                                         *
* Exeercise 2                                                              *
* **************************************************************************/

#include <iostream>

using namespace std;

typedef bool (*Test)(int);


double selected_average(int *A, int n, Test t)
{
    double sum = 0;
    int count = 0;

    for(int i = 0; i < n; i++)
        if ( t(A[i]) )
        {
            sum += A[i];
            count++;
        }

    if (count) return sum / count; //Avoid division by zero!!

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

    cout << "Average = " << selected_average(V, 10, prime) << endl;
    cout << "Average = " << selected_average(V, 10, odd) << endl;

    return 0;
}


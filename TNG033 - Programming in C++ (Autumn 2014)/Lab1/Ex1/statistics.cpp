#include <iostream>
#include <cmath>

#include "statistics.h"


//Return the largest value stored in V
//Return the smallest value stored in V through reference argument min
//a is an array storing n ints
int max_min (int a[], int n, int& min)
{
    int max = 0;
    min = a[0];

    for(int i= 0; i<n; i++)
    {
        if(a[i]> max)
        {
            max = a[i];
        }
        if(a[i]<min)
        {
            min = a[i];
        }

    }

	return max;
}

//Return the average of the values stored in a
//a is an array storing n ints
double mean (int a[], int n)
{

    double sum = 0;

    for(int i=0; i<n; i++)
    {
        sum += a[i];
    }

    double medel = sum/n;

	return medel;
}


//Return the median of the values stored in a
//a is a sorted array storing n ints
//Median is the middle value in the sorted array, if n is odd
//Otherwise, the median is the average of the two middle values
double median (int a[], int n)
{

    double medi = 0;
    double half = 0.5;

    if(n%2 == 0)
    {
        int mitten = n/2;
        medi = (a[mitten]+a[mitten+1])/2;
    }
    else
    {
        int mitten = n/2 + half;
        medi = (a[mitten]);
    }

	return medi;
}


//Returns the standard deviation of n integers stored in array a
double standard_deviation(int a[], int n)
{
    double sum = 0;
    double sum2 = 0;
    double medel = 0;
    double standDev = 0;

    for(int i=0; i<n; i++)
    {
        sum += a[i];
    }

    medel = sum/n;

    for(int i=0; i<n; i++)
    {
        sum2 += pow((a[i]-medel), 2);

    }


    standDev = sqrt(sum2/n);

	return standDev;

}


/********************************
* DO NOT MODIFY any declaration *
*********************************/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>

//Return the largest value stored in V
//Return the smallest value stored in V through reference argument min
//a is an array storing n ints
int max_min (int a[], int n, int& min);


//Return the average of the values stored in a
//a is an array storing n ints
double mean (int a[], int n);


//Return the median of the values stored in a
//a is a sorted array storing n ints
//Median is the middle value inthe sorted array, if n is odd
//Otherwise, the median is the average of the two middle values
double median (int a[], int n);


//Returns the standard deviation of n integers stored in array a
double standard_deviation(int a[], int n);

#endif

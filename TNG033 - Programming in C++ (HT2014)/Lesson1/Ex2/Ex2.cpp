/********************************************************
* TNG033, Lesson 1                                      *
* Exercise 2: merge two sorted sequences                *
* The merge algorithm used here can be useful for       *
* implementing operator+ of class Set, Lab 2            *
* ******************************************************/

//Test data:
//seq 1: 1 3 5 7 9
//seq2: 2 5 6 9 12

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int SIZE = 100;

/****************************************
* Function declarations (prototypes)    *
*****************************************/

//Re-set the stream in to good state
void clean_up_stream(istream &in);

//Read a sequence of integers a store them in array V
//array V can store at most n values
//Return number of ints read and stored in V
int read_seq(int *V, int n);

//Merger S1 with S2 and store the result in S3
//Return number of values stored in S3
int merge_seq(const int *S1, int n1, const int *S2, int n2, int *S3, int n);

//Display n values stored in array V
void display_seq(int *V, int n);


/**************************
* MAIN: do not modify     *
***************************/

int main()  //test program
{
    int seq1[SIZE], seq2[SIZE], seq3[SIZE];
    int howMany1 = 0, howMany2 = 0, howMany3 = SIZE;

    cout << "Enter sequence 1: ";
    howMany1 = read_seq(seq1, SIZE);

    cout << "Enter sequence 2: ";
    howMany2 = read_seq(seq2, SIZE);

    howMany3 = merge_seq(seq1, howMany1, seq2, howMany2, seq3, howMany3);

    //cout << howMany3;

    cout << "\Merged sequence: ";
    display_seq(seq3, howMany3);

    return 0;
}

/*************************************
* Function definitions               *
**************************************/


//Re-set the stream in to good state
void clean_up_stream(istream &in)
{
    in.clear(); //Reset the stream error flags, i.e. put stream in back to good state

    //Extract the non-valid input from the stream’s buffer
    string trash;
    getline(cin, trash);
}


//Read a sequence of integers a store them in array V
//array V can store at most n values
//Return number of ints read and stored in V
int read_seq(int *V, int n)
{
    int counter = 0;

    while ( counter < n && cin >> V[counter] ) //stop reading when a non-numeric value is entered
        counter++;

    //stream cin is in sad and depressed state -- we need to help it
    clean_up_stream(cin);

    return counter;
}


//Display n values stored in array V
void display_seq(int *V, int n)
{
    for(int i = 0; i < n; i++)
        cout << V[i] << " ";

    cout << endl;
}

/*
//Merge S1 with S2 and store the result in S3
//Return number of values stored in S3
//with array notation
int merge_seq(const int *S1, int n1, const int *S2, int n2, int *S3, int n)
{
    int count1 = 0, count2 = 0, count3 = 0;

    //Merge S1 with S2
    while (count1 < n1 && count2 < n2 && count3 < n)
    {
        if (S1[count1] < S2[count2])
        {
            S3[count3++] = S1[count1++];
            // Equals to
            //S3[count3] = S1[count1];
            //count3++;
            //count1++;

        }
        else if (S2[count2] < S1[count1])
        {
            S3[count3++] = S2[count2++];
        }
        else
        {
             S3[count3++] = S1[count1++];
             count2++;
        }
    }

    //copy any remaining values from S1 to S3
    while(count1 < n1 && count3 < n)
    {
        S3[count3++] = S1[count1++];
    }

    //copy any remaining values from S2 to S3
    while(count2 < n2 && count3 < n)
    {
        S3[count3++] = S2[count2++];
    }

    return count3;
}
*/



//Merger S1 with S2 and store the result in S3
//Return number of values stored in S3
// POINTERS!!!
int merge_seq(const int *S1, int n1, const int *S2, int n2, int *S3, int n3)
{
    //merge S1 & S2
    // Need to do this with pointers in lab 2!!!

    const int *S1_end = S1 + n1;
    const int *S2_end = S2 + n2;
    const int *S3_end = S3 + n3;
    const int *S3_begin = S3;

    //Merge S1 with S2
    while (S1 != S1_end && S2 != S2_end && S3 != S3_end)
    {
        if(*S1 < *S2)
        {
            *S3++ = *S1++;
            //S3++;
            //S1++;
        }
        else if(*S1 > *S2)
        {
            *S3++ = *S2++;
        }
        else // if(*S1 == *S2)
        {
            *S3++ = *S2++;
            S1++;
        }
    }

    //copy any remaining values from S1 to S3
    while(S1 != S1_end && S3 != S3_end)
    {
        *S3++ = *S1++;
    }

    //copy any remaining values from S2 to S3
    while(S2 != S2_end && S3 != S3_end)
    {
        *S3++ = *S2++;
    }

    return S3 - S3_begin;  //number of ints stored in S3
}

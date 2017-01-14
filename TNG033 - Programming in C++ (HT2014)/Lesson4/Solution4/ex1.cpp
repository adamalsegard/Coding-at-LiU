/*****************************************************
* TNG033: Lesson 4                                   *
* Exercise 1                                         *
******************************************************/
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm> //copy, sort
#include <cstdlib>   //rand, srand
#include <ctime>    //time


using namespace std;


//Solution 1: uses sets
int main()
{
    const int RAD_SIZE = 20;
    const int EXTRA_SIZE = 11;
    const int LIMIT = 95;

    //Note: set does not allow repeated values to be stored in it
    set<int> rad;
    set<int> extra;

    //srand ( time(NULL) );

    //slumpa 20 heltal  till set rad
    while (rad.size() != RAD_SIZE)
    {
    	int slump = rand() % LIMIT + 1;

    	rad.insert(slump); //insert in the set rad, no repeatitions
    }

    //slumpa 11 heltal  till set extra
    while (extra.size() != EXTRA_SIZE)
    {
    	int slump = rand() % LIMIT + 1;

    	if ( find(rad.begin(), rad.end(), slump) == rad.end() )
    	//if ( rad.find(slump) == rad.end() ) //test if slump is not part of set rad
            extra.insert(slump); //insert in the set extra, no repeatitions
    }

    //utskrift: sets are sorted
    ostream_iterator<int> out_it(cout," ");

    cout << "First " << RAD_SIZE << " values: ";
    copy(rad.begin(), rad.end(), out_it);


    cout << endl << endl
         << "Last " << EXTRA_SIZE << " values: ";;
    copy(extra.begin(), extra.end(), out_it);

    cout << endl << endl;


    return 0;
}



/* ********************************** */


//Solution 2: uses one vector

/*
int main()
{
    const int RAD_SIZE = 20;
    const int EXTRA_SIZE = 11;
    const int LIMIT = 95;

    vector<int> rad;

    //srand ( time(NULL) );

    //slumpa 11 heltal  till vectorn rad
    while (rad.size() != RAD_SIZE+EXTRA_SIZE)
    {
        int slump = rand() % LIMIT + 1;

        if ( find(rad.begin(), rad.end(), slump) == rad.end() )
        {
            rad.push_back(slump); //insert in the vector rad
        }
    }

    //sort the first 20 numbers
    sort(rad.begin(), rad.begin() + RAD_SIZE);

    //sort the last 11 numbers
    sort(rad.begin() + RAD_SIZE, rad.end());

    //utskrift
    ostream_iterator<int> out_it(cout," ");

    cout << "Lottoraden: ";
    copy(rad.begin(), rad.begin() + RAD_SIZE, out_it);


    cout << endl << "Extra numbers: ";
    copy(rad.begin() + RAD_SIZE, rad.end(), out_it);

    cout << endl << endl;

    return 0;
}
*/







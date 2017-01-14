/******************************
* TNG033: Lesson 4            *
* Exercise 1, vectors         *
*******************************/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void display(int a)
{
    cout << a << " ";
}

int main()
{
    vector<int> V;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 95);

    int i =0;
    while(i<31)
    {
        int num = distribution(generator);
        //Test if value has been previously entered by the user
    	if (find(V.begin(), V.end(), num) == V.end())
    	{
    	    V.push_back(num); //add new value to the vector
    	    i++;
    	}
    }

    //Sort
    sort(V.begin(), V.end());

    cout << endl << "First 20:" << endl;

    for_each(V.begin(), V.begin()+20, display);

    cout << endl << endl << "Last 11:" << endl;

    for_each(V.begin()+20, V.end(), display);

    return 0;
}

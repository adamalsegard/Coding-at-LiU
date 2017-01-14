#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main ()
{

//declare variables and constants
int start_time_h, flight_time_h, arrival_time_h;
int start_time_m, flight_time_m, arrival_time_m;
int arrival_final_m, arrival_final_h;
int minutes = 60;
int hours = 24;


// Enter departure time and flight duration
    cout << "Departure time (Hours): ";
    cin >> start_time_h;
    cout << "Departure time (Minutes): ";
    cin >> start_time_m;
    cout << "Flight duration (Hours): ";
    cin >> flight_time_h;
    cout << "Flight duration (Minutes): ";
    cin >> flight_time_m;


// Calcuate arrival time

    arrival_time_m = start_time_m + flight_time_m;

    if ((arrival_time_m) > 59)
       {
        arrival_final_m = arrival_time_m - minutes;
        start_time_h++;
       }
    else if (start_time_m > 59 || flight_time_m > 59)
        cout << "Invalid input - minutes!" << endl;

    else
    {
        arrival_final_m = start_time_m + flight_time_m;
    }

    if ( start_time_h > 23 || flight_time_h > 23)
       {
           cout << "Invalid input - hours" << endl;
       }
    else
        arrival_time_h = start_time_h + flight_time_h;

    if (arrival_time_h > 23)
        arrival_final_h = arrival_time_h - hours;

    else
        arrival_final_h = start_time_h + flight_time_h;


//display arrival time

    if (arrival_final_h < 10 && arrival_final_m < 10){
    cout << "Arrival time: 0" << arrival_final_h << ":0" << arrival_final_m << endl;
    }
    else if (arrival_final_h < 10)
    {cout << "Arrival time: 0" << arrival_final_h << ":" << arrival_final_m << endl;
    }
    else if (arrival_final_m < 10)
    {cout << "Arrival time: " << arrival_final_h << ":0" << arrival_final_m << endl;
    }
    else
    {cout << "Arrival time: " << arrival_final_h << ":" << arrival_final_m << endl;
    }

    return 0;
}

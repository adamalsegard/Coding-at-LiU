// Lab 3, exercise 2
// Jonas (jonki910) and Adam (adaal265)
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <ctime>

using namespace std;

int main()

{
    int T, G, O, D;

    for (G=0; G<10; G++)
    {

           for (D=0; D<10;D++)
            {
                 if (D!= G)
                 {
                    for (T=0; T<10; T++)
                    {
                       if ( T!=D && T!=G)
                       {
                           for (O=0; O<10; O++)
                           {
                               if (O !=T && O!=G && O != D)
                               {
                                   if (4 * (T*100 + O*10 + O) == (G*1000 + O*100 + O*10 + D))
                                   {
                                       cout << "Too = " << T<<O<<O<< endl;
                                       cout << "Good = " << G <<O<<O<<D<< endl;
                                   }
                               }
                           }


                       }


                    }
                 }

            }


    }

do{
system("color F0");
Sleep (200);
system("color 0F");
Sleep (200);
}
while(G >= -1);

    return 0;
}

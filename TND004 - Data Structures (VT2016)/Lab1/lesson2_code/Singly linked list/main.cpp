#include <iostream>
#include <iomanip>

#include "set.h"

using namespace std;


int main()  //A simple test program
{
    List L0;
    List L1(5);

    int A[] {1, 9, 2, 8, 3, 7};
    List L2(A, 6);

    cout << "List L0: " << L0 << endl;
    cout << "List L1: " << L1 << endl;
    cout << "List L2: " << L2 << endl;

    if (L2._find(8))
        cout << "8 found in L2" << endl;

    if (!L2._find(10))
        cout << "10 not found in L2" << endl;

    List L3(L2+L1);

    cout << "\nList L3: " << L3 << endl;

    L3 += 44;

    cout << "List L3: " << L3 << endl;

    List *ptr = new List(L2);

    L0 = std::move(*ptr);  //L0 steals the contents of *ptr

    cout << "List L0: " << L0 << endl;

    delete ptr;

    L0._remove(2)._remove(88)._remove(7);

    cout << "List L0: " << L0 << endl;

    L0 = std::move(-55 + L3) + (L3 + 55);

    cout << "List L0: " << L0 << endl;

    if ( !(L0 == L3) )
        cout << "L0 != L3" << endl;

    cout << "List L0: " << L0.make_empty() << endl;

    return 0;
}

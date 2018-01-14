//Test the List and functions available for Lists

#include <iostream>
#include <iomanip>
#include <iostream>

using namespace std;

#include "list.h"


int main()
{
   List L = nullptr; //empty list

   cout << "L:  " << L << endl;

   cout << "\nInserting ..." << endl;

    insert(L,30);
    insert(L,20);
    insert(L,15);
    insert(L,10);

    cout << "L: " << L;

    cout << "\nSearching ..." << endl;

    //search for values in the list
    Node *p1 = search(L,10); //first value
    Node *p2 = search(L,30); //last value
    Node *p3 = search(L,40); //does not exist
    Node *p4 = search(L,15);


    if (p1)
        cout << "Found " << p1->value << endl;
    else
        cout << "10 not found!!" << endl;


    if (p2)
        cout << "Found " << p2->value << endl;
    else
        cout << "30 not found!!" << endl;


    if (p3)
        cout << "Found " << p3->value << endl;
    else
        cout << "40 not found!!" << endl;


    if (p4)
        cout << "Found " << p4->value << endl;
    else
        cout << "15 not found!!" << endl;

    cout << "\nInsert sorted ..." << endl;

    insert_sorted(L, 23);
    insert_sorted(L, 32);
    insert_sorted(L, 8);

    cout << "L: " << L << endl;

    cout << "\nRemoving ..." << endl;

    remove(L, 32);
    remove(L, 8);
    remove(L, 20);

    cout << "L: " << L << endl;

     cout << "\nInsert last ..." << endl;

    insert_last(L, 30);
    insert_last(L, 23);
    insert_last(L, 15);

    cout << "L: " << L << endl;

    return 0;
}

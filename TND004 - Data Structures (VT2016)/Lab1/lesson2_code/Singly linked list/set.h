#include <iostream>
#include <memory>  //shared_ptr
#include <utility>

using namespace std;

//Class to represent a singly-linked list of ints
class List
{

private:

    class Node
    {
    public:

        //Constructor
        explicit Node (int n = 0, const shared_ptr<Node> & nextPtr = nullptr)
            : value(n), next (nextPtr)
        {  }

        //Node data members
        int value;
        shared_ptr<Node> next; //pointer to the next Node
    };

    //Private data members of List
    shared_ptr<Node> head;  //Pointer to the dummy header Node

    unsigned counter; //count number of elements in the list


public:

    //Default constructor
    List ();

    //Conversion constructor
    List (int val);

    //Constructor to create a List from an array
    List (int a[], int n);

    //Copy constructor
    List (const List& b);

    //Move constructor
    List (List&& b) noexcept;

    //Destructor
    ~List () = default;

    //Copy-and-swap assignment operator
    const List& operator=(List source) noexcept;

    int number_of_elements() const;

    //Test whether a List is empty
    bool _empty () const;

    bool _find(int val) const;

    //Make the list empty
    List& make_empty();

    //Add an int to the beginning of the list
    List& operator+=(List S);

    //Remove val from the list, if it exists there
    List& _remove(int val);

    bool operator==(const List& b) const;


private:

    /* ************************** *
    * Private Member Functions    *
    * **************************  */

    //Insert a new Node storing val after the Node pointed by p
    List& _insert(const shared_ptr<Node>& p, int val);

    //Remove the Node pointed by p
    List& _remove(const shared_ptr<Node>& p);

    //Display the List to ostream os
    void print(ostream& os) const;


    /* **************************** *
    * Overloaded Global Operators   *
    * ***************************** */

    friend ostream& operator<<(ostream& os, const List& b);

};


//overloaded operator+
//Create a new list with a copy of L2 appended to a copy of L1
List operator+ (List L1, const List& L2);











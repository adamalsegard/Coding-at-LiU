#include "set.h"

//Default constructor
List::List ()
    : head(make_shared<Node>(0, nullptr)), counter(0)
{ }


//conversion constructor
List::List (int val)
    : head(make_shared<Node>(0, nullptr)), counter(0)
{
    _insert(head, val);
}


//Constructor to create a List from an array
List::List (int a[], int n)
    : head(make_shared<Node>()), counter(0)
{
    shared_ptr<Node> tmp = head;

    //insert each node in the end of the list
    for (int i = 0; i < n; ++i)
    {
        //insert a new node after tmp
        _insert(tmp, a[i]);

        tmp = tmp->next;
    }
}


//Copy constructor
List::List (const List& source)
    : head(make_shared<Node>()), counter(0)
{

    shared_ptr<Node> tmp = head;

    //insert each item of source in the end of the list
    for(auto sourcePtr = source.head->next;                 //initialize
            sourcePtr;                                      //test
            sourcePtr = sourcePtr->next, tmp = tmp->next    //increment
       )
    {
        //insert a new node after tmp
        _insert(tmp, sourcePtr->value);
    }
}


//Move constructor
List::List (List&& b) noexcept
  : head(b.head), counter(b.counter)
{
    cout << "Move constructor ..." << endl;

    //The "moved-from" object b must remain a destructible object
    b.head = nullptr;
    b.counter = -1;
}

//Copy-and-swap assignment operator
const List& List::operator=(List source) noexcept
{
    swap(head, source.head);
    swap(counter, source.counter);

    return *this;
    //destructor for source is called and the old list is deallocated
}


//Test whether a List is empty
bool List::_empty () const
{
    return (!counter);
}


//Test List membership
bool List::_find (int val) const
{
    auto temp = head->next;

    while (temp && temp->value != val )
    {
        temp = temp->next;
    }

    return (temp != nullptr);
}


//Return number of elements in the List
int List::number_of_elements() const
{
    return counter;
}


//Make the List empty
List& List::make_empty()
{
    head = nullptr;

    counter = 0;

    return *this;
}


//Add to *this all elements in List L
List& List::operator+=(List L)
{
    auto pa = head;

    while ( pa->next )
    {
        pa = pa->next;
    }

    pa->next = L.head->next;

    L.head->next = nullptr;

    return *this;
}


bool List::operator==(const List& b) const
{
    auto pa = head->next;
    auto pb = b.head->next;

    while (pa && pb)
    {
        if (pa->value != pb->value)   return false;

        pa = pa->next;
        pb = pb->next;
    }

    if ( pa )   return false;
    if ( pb )   return false;

    return true;
}


//Remove val from the list, if it exists there
List& List::_remove(int val)
{
    auto temp = head;

    while (temp->next && temp->next->value != val )
    {
        temp = temp->next;
    }

    if (temp->next && temp->next->value == val)
    {
        _remove(temp);
    }

    return *this;

}


/* ******************************************* *
* Private Member Functions -- Implementation   *
* ******************************************** */

//Insert a new Node storing val after the Node pointed by p
List& List::_insert(const shared_ptr<Node>& p, int val)
{
    p->next = make_shared<Node>(val, p->next);

    ++counter;

    return *this;
}


//Remove the Node after the Node pointed by p
List& List::_remove(const shared_ptr<Node>& p)
{
    p->next = p->next->next;

    --counter;

    return *this;
}


//Display all elements of a non-empty list
void List::print(ostream& os) const
{
    shared_ptr<Node> temp = head->next;

    os << "{ ";
    while ( temp )
    {
        os << temp->value << " ";
        temp = temp->next;
    }

    os << "}" << endl;
}



/* **************************** *
* Overloaded Global Operators   *
* ***************************** */


//No need to be a friend since it only calls a public member function
List operator+ (List L1, const List& L2)
//const List operator+ (const List& L1, const List& L2)
{
    return (L1 += L2);
    //return (List(L1) += L2);
}


ostream& operator<<(ostream& os, const List& b)
{
    if (b._empty ())
        os << "List is empty!" << endl;
    else
    {
        b.print(os);
    }

    return os;
}

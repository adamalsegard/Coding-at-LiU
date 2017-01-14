#include "set.h"

//Default constructor
Set::Set ()
{
    Node* L = new Node(0, nullptr);  //dummy node

    head = L;

}

//Constructor creating a set
//from n integers in a non-sorted array a
Set::Set (int a[], int n)
{
    head = new Node(0, nullptr);  //dummy node

    for(int i=0;i<n;i++)
    {
        insert(a[i]);
    }
}

//copy constructor
Set::Set (const Set &source)
{
    //Shallow copy
    //head = source.head;

    if(!source.head->next)
    {
        head->next = nullptr;
        return;
    }
    else
    {
        head = new (nothrow) Node(0, nullptr);  //dummy node, Do we really need nothrow!?

        Node *newNode = source.head->next;

        while(newNode)
        {
            insert(newNode->value);

            newNode = newNode->next;
        }
    }

}


//Destructor: deallocate all nodes
Set::~Set ()
{

    while(head)
    {
        Node *newNode = head;
        head = head->next;
        delete newNode;
    }

}

//Test if set is empty
bool Set::empty () const
{
    if(!head->next)
    {
        return true;
    }
    return false;
}

//Return number of elements in the set
int Set::cardinality() const
{
    int counter = 0;

    Node *newNode = head->next;
    while(newNode)
    {
        counter++;
        newNode = newNode->next;
    }

    return counter;
}

//Test if x is an element of the set
bool Set::member (int x) const
{
    Node *newNode = head->next;
    while(newNode)
    {
        if(newNode->value == x)
            return true;

        newNode = newNode->next;
    }


    return false;
}

bool Set:: operator<=(const Set& b) const
{

    Set temp(*this); //Deep copy of "A"

    for(Node *nodeB = b.head->next; nodeB; nodeB = nodeB->next)
    {
        temp.remove(nodeB->value);
    }

    if(temp.empty())
        return true;
    else
        return false;

}


bool Set:: operator==(const Set& b) const
{

    Set temp(*this); //Deep copy of "A"
    int nrA = temp.cardinality();
    int nrB = b.cardinality();


    if(temp <=b && nrA == nrB)
        return true;
    else
        return false;
}

bool Set:: operator<(const Set& b)  const
{
    Set temp(*this); //Deep copy of "A"
    int nrA = temp.cardinality();
    int nrB = b.cardinality();


    if(temp <= b && nrA < nrB)
        return true;
    else
        return false;

}


//Set union
//Repeated values are not allowed
Set Set::operator+ (const Set& b) const
{
    Set temp(*this); //Deep copy of "A"

    for(Node *nodeB = b.head->next; nodeB; nodeB = nodeB->next)
    {
        temp.insert(nodeB->value);
    }

    return temp;
}


//Set intersection
Set Set::operator* (const Set& b) const
{
    Set temp; //Empty new Set

    for(Node *nodeA = head->next; nodeA; nodeA = nodeA->next)
    {
        for(Node *nodeB = b.head->next; nodeB; nodeB = nodeB->next)
        {
            if(nodeA->value == nodeB->value)
            {
                temp.insert(nodeA->value);
            }

        }
    }

    return temp;
}

//Set difference
Set Set::operator- (const Set& b) const
{
    Set temp(*this); //Deep copy of "A"

    for(Node *nodeB = b.head->next; nodeB; nodeB = nodeB->next)
    {
        temp.remove(nodeB->value);
    }

    return temp;

}

//set union with set {x}
Set Set::operator+(int x) const
{
    Set temp(*this); //Deep copy of "A"

    temp.insert(x);
    return temp;

}

//set difference with set {x}
Set Set::operator-(int x) const
{
    Set temp(*this); //Deep copy of "A"

    temp.remove(x);
    return temp;
}

//Assignment operator
const Set& Set::operator=(const Set &s)
{
    if(this != &s)
    {
        //Copy constructor performs a deep copy
        Set temp(s); // temporary set

        swap(head, temp.head); //Swap dummy nodes
    }

    return *this; //to be deleted = call destructor
}



ostream& operator<< (ostream& os, const Set& theSet)
{

    if(theSet.empty())
    {
        cout << "Set is empty!" << endl;
    }
    else
    {
        os << "{ ";

        for(Node *p = theSet.head->next; p; p = p->next)
            os << p->value << " ";

        os << "}" << endl;
    }

    return os;
}

//Insert n in the beginning of the list L
void Set::insert(int &n)
{
        //insert in an empty list or as first node of the list
    if (!head->next || head->next->value > n )
    {
        Node *newNode = new Node(n, head->next);
        head->next = newNode; //update dummy node to point to the new node
    }
    else
    {
        Node* ptr = head->next; //L is not empty

        //1. find the node after which insertion should occur
        while( (ptr->next != nullptr) && (ptr->next->value <= n) )  //do not swap the tests
        {
            ptr = ptr->next;
            //Check if it's the same value

            if (ptr->value == n)
            {
                return;
            }
        }

        //2. insert new node after node pointed by ptr
        Node* newNode = new Node(n, ptr->next);
        ptr->next = newNode;


    }
}
void Set::remove(int &n)
{

        Node* ptr = head;

        while( (ptr->next != nullptr) && (ptr->next->value != n) )
            ptr = ptr->next;

        if (!ptr->next)  //n not found
            return;

        //2. Remove
        Node *node = ptr->next;

        ptr->next = node->next;
        delete node; //deallocate

}


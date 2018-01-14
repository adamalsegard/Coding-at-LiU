/*************************************************
* TNG033, Fö 5                                   *
* Definition of functions declared in node.h     *
* ************************************************/

#include "list.h"


//Insert n in the beginning of the list L
void insert(List& L, int n)
{
    Node *newNode = new Node;

    newNode->value = n;
    newNode->next = L; //link the new node to the first node of list L
    L = newNode; //update L to point to the new node
}


//Remove the node storing n from list L
//If n is not in the list L then L is not modified
void remove(List& L, int n)
{
    if (!L) //empty list
        return;

    //remove first node of the list
    if (L->value == n )
    {
        Node* node = L; //New pointer to first node
        L = L->next;

        delete node; //delete first node
    }
    else
    {
        Node *ptr = L;  //L is not empty

        //1. Find the node before the node to be removed
        while( (ptr->next != nullptr) && (ptr->next->value != n) )
            ptr = ptr->next;

        if (!ptr->next)  //n not found
            return;

        //2. Remove
        Node *node = ptr->next; //"Döper om" pointern som ska tas bort

        ptr->next = node->next; //"Flytta fram" originalpointern
        delete node; //deallocate den omdöpta pointern
    }
}


//Search for a value n in the list
//Return a pointer to the node storing n, if n found
//otherwise, return nullptr
Node* search(List L, int n)
{
    Node *p = L;

    while( (p != nullptr) && (p->value != n) )
        p = p->next;

    //for(p = L; p && (p->value != n); p = p->next) ;

    return p;
}


//overloaded operator<<
ostream& operator<<(ostream& out, const List L)
{

    if (!L)
        cout << "List is empty!!" << endl;
    else
    {
        for(Node *p = L; p; p = p->next)
            out << p->value << "->";

        out << endl;
    }

    return out;
}

/*
//Insert n in the end of the list
//Return  the new updated list
void insert_last(List& L, int n)
{
    if (!L) //if (L == nullptr) -- empty list
        return( insert(L, n) ); //return a pointer to the first node
    else
    {
        Node *p;

        //Go until end of the list
        for(p = L; p->next; p = p->next);

        //now, p points to the last node in the list
        insert(p->next,n); //insert new node after p
    }
}

*/

//Lesson 1: exercise 3

//Insert n in the end of the list
void insert_last(List& L, int n)
{
    if(L == nullptr) // equals to if(!L) - List is empty
    {
        //Create a new node
        L = new Node;

        L->value = n;
        L->next = nullptr;
    }
    else
    {
        Node* p;

        // 1. Make P point to last node
        for(p=L; p->next != nullptr; p=p->next); // equals to for(p = L; p->next; p = p->next);


        //2. Create a new node
        Node* newNode = new Node;
        newNode->value = n;

        //3. Link the node to the list
        newNode->next = p->next;
        p->next = newNode;
    }
}


//Insert n in a sorted list L
//After insertion L should remain sorted
void insert_sorted(List& L, int n)
{
    //Insert as first node of the list
    if(L == nullptr || L->value >= n )//List is empty or the value is the smallest one
    {
        //Create a new node
        Node* newNode = new Node;
        newNode->value = n;

        //Change the original pointer
        newNode->next = L;
        L = newNode; //update L to point to the new node
    }
    else
    {
        Node* p = L; // L is not empty

        //1. Find the node after which insertion should occur
        while((p->next != nullptr) && (p->next->value < n))
        {
            p = p->next;
        }
        //for(p = L; p->next && p->next->value < n; p = p->next) ;

        //2. Insert new node after node pointed by p
        Node *newNode = new Node;
        newNode->value = n;
        newNode->next = p->next;
        p->next = newNode;
    }
}

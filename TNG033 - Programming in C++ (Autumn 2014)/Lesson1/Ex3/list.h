/*****************************************************************************
* TNG033, Fö 5                                                               *
* Header file defining a List of nodes                                       *
* each node stores an int and a pointer to the next node                     *
* Pointers and dynamic memory allocation are used!!                          *
* Note: the lists implementation does not contain a dummy node               *
* ****************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node* next; //points to the next node in the list
};



typedef Node* List; //pointer to the first node in a list
                    //nullptr represents an empty list

//Note: no dummy nodes are used in the lists


//Insert n in the beginning of the list L
void insert(List& L, int n);

//Insert n in the end of the list
void insert_last(List& L, int n); //Exerc 3, Lesson 1


//Insert n in a sorted list L
//After insertion L should remain sorted
void insert_sorted(List& L, int n); //Exerc 3, Lesson 1


//Remove the node storing n from list L
//If n is not in the list L then L is not modified
void remove(List& L, int n);


//Search for a value n in the list
//Return a pointer to the node storing n, if n found
//otherwise, return nullptr
Node* search(List L, int n);


//overloaded operator<<
ostream& operator<<(ostream& out, const List L);


#endif

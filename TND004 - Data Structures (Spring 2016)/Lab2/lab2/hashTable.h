
/*
  Author: Aida Nordman
  Course: TND004, Lab 2
  Description: template class HashTable represents an open addressing hash table
              (also known as closed_hashing) with linear probing
*/

#include "Item.h"

#include <iostream>
#include <iomanip>

using namespace std;

const int NOT_FOUND = -1;
const double MAX_LOAD_FACTOR = 0.5;


//Template class to represent an open addressing hash table using linear probing to resolve collisions
//Internally the table is represented as an array of pointers to Items
template <typename Key_Type, typename Value_Type>
class HashTable
{
public:

    //New type HASH: pointer to a hash function
    typedef unsigned (*HASH)(Key_Type, int);


    //Constructor to create a hash table
    //table_size is number of slots in the table (next prime number is used)
    //f is the hash function
    HashTable(int table_size, HASH f);


    //Destructor
    ~HashTable();


    //Return the load factor of the table, i.e. percentage of slots in use or deleted
    double loadFactor() const
    {
        return (double) (nItems+nDeleted) / _size;
    }


    //Return number of items stored in the table
    unsigned get_number_of_items() const
    {
        return nItems;
    }

    //Return the total number of visited slots (during search, insert, remove, or re-hash)
    unsigned get_total_visited_slots() const
    {
        return total_visited_slots;
    }

    //Return the total number of call to new Item()
    unsigned get_count_new_items() const
    {
        return count_new_items;
    }


    //Return a pointer to the value associated with key
    //If key does not exist in the table then nullptr is returned
    const Value_Type* _find(const Key_Type& key);


    //Insert the Item (key, v) in the table
    //If key already exists in the table then change the value associated with key to v
    //Re-hash if the table reaches the MAX_LOAD_FACTOR
    void _insert(const Key_Type& key, const Value_Type& v);


    //Remove Item with key, if the item exists
    //If an Item was removed then return true
    //otherwise, return false
    bool _remove(const Key_Type& key);

    //Overloaded subscript operator
    //If key is not in the table then insert a new Item = (key, Value_Type())
    Value_Type& operator[](const Key_Type& key);


    //Display all items in table T to stream os
    friend ostream& operator<<(ostream& os, const HashTable& T)
    {
        for (unsigned i = 0; i < T._size; ++i)
        {
            if (T.hTable[i] && T.hTable[i] != Deleted_Item<Key_Type,Value_Type>::get_Item())
            {
                os << *T.hTable[i] << endl;
            }
        }

        return os;
    }


    //Display the table for debug and testing purposes
    //Thus, empty and deleted entries are also displayed
    void display(ostream& os);


private:

    /* ********************************** *
    * Data members                        *
    * *********************************** */

    //Number of slots in the table, a prime number
    unsigned _size;

    //Hash function
    const HASH h;

    //Number of items stored in the table
    //Instances of Deleted_Items are not counted
    unsigned nItems;

    //Number of slots that are marked as deleted
    unsigned nDeleted;

    //Table is an array of pointers to Items
    //Each slot of the table stores a pointer to an Item =(key, value)
    Item<Key_Type, Value_Type>** hTable;

    //Some statistics
    unsigned total_visited_slots;  //total number of visited slots
    unsigned count_new_items;      //number of calls to new Item()


    /* ********************************** *
    * Auxiliary member functions          *
    * *********************************** */

    //Disable copy constructor!!
    HashTable(const HashTable &) = delete;

    //Disable assignment operator!!
    const HashTable& operator=(const HashTable &) = delete;

    //Our functions

    const bool try_find(const Key_Type& key, unsigned &index);

    const void rehash();

    const void ensure_capacity();

    Item<Key_Type, Value_Type> *new_Item(const Key_Type &key, const Value_Type &value);

};


//Test if a number is prime
bool isPrime( int n );

//Return a prime number at least as large as n
int nextPrime( int n );


/* ********************************** *
* Member functions implementation     *
* *********************************** */

//Constructor to create a hash table
//table_size number of slots in the table (next prime number is used)
//f is the hash function
template <typename Key_Type, typename Value_Type>
HashTable<Key_Type, Value_Type>::HashTable(int table_size, HASH f)
    : h(f), nItems(0), nDeleted(0), total_visited_slots(0), count_new_items(0),
     _size( nextPrime(table_size) ),
    hTable( new Item<Key_Type, Value_Type>*[_size]() )
{

    // Allocate
    //hTable = new Item<Key_Type, Value_Type>*[_size]();
}


//Destructor
template <typename Key_Type, typename Value_Type>
HashTable<Key_Type, Value_Type>::~HashTable()
{
    //Delete all items
    for(unsigned i = 0; i<_size; i++)
    {
        if(hTable[i] && hTable[i] != Deleted_Item<Key_Type, Value_Type>::get_Item())
        {
            delete hTable[i];
        }
    }

    //Delete table
    delete[] hTable;
}


//Return a pointer to the value associated with key
//If key does not exist in the table then nullptr is returned
template <typename Key_Type, typename Value_Type>
const Value_Type* HashTable<Key_Type, Value_Type>::_find(const Key_Type& key)
{
    unsigned index = 0;

    if (try_find(key, index))
    {
        return &hTable[index]->get_value();
    }

    return nullptr;
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the value associated with key to v
//Re-hash if the table reaches the MAX_LOAD_FACTOR
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::_insert(const Key_Type& key, const Value_Type& v)
{
    unsigned index = 0;

    if (try_find(key, index))
    {
        hTable[index]->set_value(v);
    }

    else
    {
        hTable[index] = new_Item(key, v);
        ++nItems;

        ensure_capacity();
    }
}


//Remove Item with key, if the item exists
//If an Item was removed then return true
//otherwise, return false
template <typename Key_Type, typename Value_Type>
bool HashTable<Key_Type, Value_Type>::_remove(const Key_Type& key)
{
    unsigned index = 0;

    if (try_find(key, index))
    {
        delete hTable[index];
        hTable[index] = Deleted_Item<Key_Type, Value_Type>::get_Item();
        ++nDeleted;

        return true;
    }

    return false;
}


//Display the table for debug and testing purposes
//This function is used for debugging and testing purposes
//Thus, empty and deleted entries are also displayed
template <typename Key_Type, typename Value_Type>
void HashTable<Key_Type, Value_Type>::display(ostream& os)
{
    os << "-------------------------------\n";
    os << "Number of items in the table: " << get_number_of_items() << endl;
    os << "Load factor: " << fixed << setprecision(2) << loadFactor() << endl;

    for (unsigned i = 0; i < _size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else if (hTable[i] == Deleted_Item<Key_Type, Value_Type>::get_Item())
        {
            os << "deleted" << endl;
        }
        else
        {
            os << *hTable[i]
               << "  (" << h(hTable[i]->get_key(),_size) << ")" << endl;
        }
    }

    os << endl;
}

template <typename Key_Type, typename Value_Type>
Value_Type& HashTable<Key_Type, Value_Type>::operator[](const Key_Type& key)
{
    unsigned index;

    if (!try_find(key, index))
    {
        hTable[index] = new_Item(key, Value_Type());
        ++nItems;

        Value_Type &value = hTable[index]->get_value();

        ensure_capacity();
        return value;
    }

    return hTable[index]->get_value();
}


/* ********************************** *
* Auxiliar member functions           *
* *********************************** */

template <typename Key_Type, typename Value_Type>
const bool HashTable<Key_Type, Value_Type>::try_find(const Key_Type& key, unsigned &index)
{
    index = h(key, _size);

    Item<Key_Type, Value_Type> *look_item;

    while ( (look_item = hTable[index]) )
    {
        ++total_visited_slots;

        if (look_item->get_key() == key && // found the key we are looking for?
            look_item != Deleted_Item<Key_Type, Value_Type>::get_Item()) // the item is NOT a deleted item?
        {
            return true;
        }

        // wrap to beginning if end was reached
        if (++index == _size)
        {
            index = 0;
        }
    }

    ++total_visited_slots;
    return false;
}

template <typename Key_Type, typename Value_Type>
const void HashTable<Key_Type, Value_Type>::rehash()
{
    // Allocate new memory for items
    auto old_hTable = hTable;
    const unsigned old_size = _size;
    _size = nextPrime(old_size*2);

    hTable = new Item<Key_Type, Value_Type>*[_size]();

    // For each old item
        // Hash and insert in new memory
    for(unsigned i = 0; i<old_size; i++)
    {
        //++total_visited_slots;

        if(old_hTable[i] && old_hTable[i] != Deleted_Item<Key_Type, Value_Type>::get_Item())
        {
            unsigned insertion_index;

            if(!try_find(old_hTable[i]->get_key(), insertion_index))
            {
                hTable[insertion_index] = old_hTable[i];
            }

            else
            {
                // only happens if the hashtable contains duplicate keys
                cout << "Duplicate keys found during rehash." << endl;
                throw new exception;
            }
        }
    }

    cout << "Rehashing..." << endl;
    cout << "New tablesize: " << _size << endl;

    // Deallocate old memory
    delete[] old_hTable;
}

template <typename Key_Type, typename Value_Type>
const void HashTable<Key_Type, Value_Type>::ensure_capacity()
{
    if (loadFactor() > MAX_LOAD_FACTOR)
    {
        rehash();
    }
}

template <typename Key_Type, typename Value_Type>
Item<Key_Type, Value_Type> *HashTable<Key_Type, Value_Type>::new_Item(const Key_Type &key, const Value_Type &value)
{
    ++count_new_items;
    return new Item<Key_Type, Value_Type>(key, value);
}

/* ********************************** *
* Functions to find prime numbers     *
* *********************************** */


//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}



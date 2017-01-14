//Adam Alsegård & Jonas Kinnvall
//Lab 5, Exercise 1

/**************************************************************************
 Author: Aida Nordman
 Course: tnd012, lab5, exercise 1
 Program to test whether a word as repeated letters
 Input: a string
**************************************************************************/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Test words:
//uncopyrightable
//female
//hydropneumatics


//IMPLEMENT function repeated_letters

void to_lower (string &word)
{

    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower (word[i]);
    }
}


bool repeated_letters (string word)
{


  for( int i = 0; i < word.length() ; i++)
  {
      for( int n= 0 ; n < word.length(); n++)
      {
          if(word[i] == word[n] && i!=n )
            return true;
      }
  }
    return false;

}


int main()
{

    string word;

    do
    {
        //Read a word
    cout << endl << "Enter word: ";
    cin >> word;

    to_lower(word);

    //Test whether the word has repeated letters
    if (repeated_letters(word) && word != "stop")
        cout << word << " has repeated letters."  << endl;
    else if (word != "stop")
        cout << word << " has no repeated letters."  << endl;

    }

    while (word != "stop");


    return 0;
}

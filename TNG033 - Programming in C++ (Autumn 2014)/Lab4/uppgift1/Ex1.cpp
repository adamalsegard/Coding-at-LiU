/******************************
* TNG033: Lab 4               *
* Exercise 1                  *
*******************************/

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

typedef map<string,int> Wordlist;
typedef pair<string, int> myPair;

ostream& operator<<(ostream& out, const myPair& p);
bool IsChar(char c);
bool compare(const myPair &p1, const myPair &p2);

int main()
{
    Wordlist entry;
    string inNamn;
    string ord;
    int nrOfWords = 0;
    int nrUniWords = 0;

    //Läs från fil!
//    cout << "Filnamn input: ";
//    cin >> inNamn;
//
//    ifstream inFil(inNamn);

    //ifstream inFil("uppgift1.txt");
    ifstream inFil("uppgift1_kort.txt");
    ofstream utFil("Output.txt");

    //test if opening the file suceeded
    if ( !inFil )
    {
        cout << "Filerna kunde inte läsas!!" << endl;
        return 0;
    }

    inFil >> ord;
    while(inFil)
    {
        string nytt = "";
        remove_copy_if(ord.begin(), ord.end(), back_inserter(nytt), IsChar); //Ta bort konstiga tecken
        transform(nytt.begin(), nytt.end(), nytt.begin(), ::tolower);

        entry[nytt]++; // same as entry[ord] = entry[ord] + 1;
        inFil >> ord;
        nrOfWords++;
    }
    nrUniWords = entry.size();


    utFil << "Number of words in the file = " << nrOfWords << endl;
    utFil << "Number of unique words in the file = " << nrUniWords << endl << endl;

    utFil << endl << "Frequency table sorted alphabetically..." << endl << endl;

    ostream_iterator<myPair> oit(utFil, "\n");
    copy(entry.begin(), entry.end(), oit);


    //Sort by frequency!!!
    vector<myPair> vec_table(entry.size());

    //1. Copy the pairs in the map to a vector
    copy(entry.begin(), entry.end(), vec_table.begin());

    //2. Sort vector by frequency
    sort(vec_table.begin(), vec_table.end(), compare);

    //3. Display vector sorted by frequency (int)
    utFil << endl << "Frequency table sorted by frequence..." << endl << endl;
    copy(vec_table.begin(), vec_table.end(), oit);

    return 0;
}

bool IsChar(char c)
{
    if(isalpha(c) || c == '\'' || isdigit(c))
        return false;
    else
        return true;
}

namespace std{
    ostream& operator<<(ostream& out, const myPair& p)
    {
        out << setw(25) << left <<  p.first << "  " << p.second;

        return out;
    }
}

bool compare(const myPair &p1, const myPair &p2)
{
    return (p1.second > p2.second);
}

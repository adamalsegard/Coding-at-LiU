/******************************
* TNG033: Lab 4               *
* Exercise 2                  *
*******************************/

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <utility>

using namespace std;

typedef map<string,vector<string>> Anagram;
typedef pair<string,vector<string>> myPair;

ostream& operator<<(ostream& out, const vector<string>& w);

int main()
{
    Anagram subject;

    string inNamn;
    string ord;
    int nrOfWords = 0;

    //Läs från fil!
//    cout << "Filnamn input: ";
//    cin >> inNamn;
//
//    ifstream inFil(inNamn);

    //ifstream inFil("uppgift2.txt");
    ifstream inFil("uppgift2_kort.txt");
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
        transform(ord.begin(), ord.end(), ord.begin(), ::tolower);

        string w = ord;
        sort(w.begin(), w.end());

        //If anagram is found, add to subject, else create new subject!
        subject[w].push_back(ord);

        nrOfWords++;
        inFil >> ord;
    }

    utFil << "Number of words = " << nrOfWords << endl;

    utFil << endl << "-- ANAGRAMS --" << endl << endl;

    ostream_iterator<myPair> oit(utFil, "");
    copy(subject.begin(), subject.end(), oit);

    return 0;
}

namespace std{
    ostream& operator<<(ostream& out, const myPair &w)
    {
        if(w.second.size() > 1)
        {
            ostream_iterator<string> utit(out, ", ");
            copy(w.second.begin(), w.second.end(), utit);
            out << "--> " << w.second.size() << "words." << endl;
        }

//        if(w.second.size() > 1)
//        {
//            for(vector<string>::const_iterator it = w.second.begin(); it != w.second.end(); ++it)
//            {
//                out << *it << ", ";
//            }
//            out << "--> " << w.second.size() << "words." << endl;
//        }

        return out;
    }
}

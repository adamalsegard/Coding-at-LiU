/******************************
* TNG033: Lab 4               *
* Exercise 3                  *
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

void display(ostream& os, string s);
bool compare(const myPair &p1, const myPair &p2);

ostream& operator<<(ostream& out, const vector<string>& w);

int main()
{
    Anagram subject;
    string ord;
    int nrOfWords = 0;

    //Läs från fil!
//    string inNamn;
//    cout << "Filnamn input: ";
//    cin >> inNamn;
//
//    ifstream inFil(inNamn);

    //ifstream inFil("uppgift3.txt");
    ifstream inFil("uppgift3_kort.txt");
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

        vector<string> words;
        string w = ord;
        sort(w.begin(), w.end());

        //If anagram is found, add to subject, else create new subject!
        subject[w].push_back(ord);

        nrOfWords++;
        inFil >> ord;
    }

    utFil << "Number of words = " << nrOfWords << endl;

    utFil << endl << "-- ANAGRAMS --" << endl << endl;


    //Sort by vector size()
    vector<myPair> vec_table(subject.size()) ;

    copy(subject.begin(), subject.end(), vec_table.begin());
    sort(vec_table.begin(), vec_table.end(), compare);

    //Display map
    ostream_iterator<myPair> oit(utFil, "");
    copy(vec_table.begin(), vec_table.end(), oit);

    return 0;
}

namespace std{
    ostream& operator<<(ostream& out, const myPair &w)
    {
        ostream_iterator<string> utit(out, ", ");
        copy(w.second.begin(), w.second.end(), utit);
        out << "--> " << w.second.size() << "words." << endl;


//      for(vector<string>::const_iterator it = w.second.begin(); it != w.second.end(); ++it)
//      {
//          out << *it << ", ";
//      }
//      out << "--> " << w.second.size() << "words." << endl;

        //for_each(w.second.begin(), w.second.end(), display);

        return out;
    }
}

void display(ostream& os, string s)
{
    os << s << ", ";
}

bool compare(const myPair &p1, const myPair &p2)
{
    return (p1.second.size() > p2.second.size());
}

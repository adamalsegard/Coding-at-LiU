#include <iomanip>
#include <ios>
#include <sstream>

#include "diver.h"


//Test if scores line has correct format
//Accepted line format: difficulty, followed by 7 scores, and (possibly) some text
//The 7 scores should be stored in array scores and
//difficulty should be stored in dif
//If the line has correct format then return true
//stringstreams are used, see sec. 11.9 of course book
bool test_scores_line(string line, double scores[], double &dif)
{

    istringstream in_stream(line);
    string rubbish = "";


    if(in_stream >> ws >> dif >> scores[0] >> scores[1] >> scores[2] >> scores[3] >> scores[4]
       >> scores[5] >> scores[6])
    {

        if(dif< 0)
            return false;

        for(int i=0; i<7; i++)
        {
            if(scores[i] <= 0)
                return false;
        }

        /*if(in_stream.eof())
            return true;
        else
            return false;*/

        return true;
    }
    else
        return false;


}



//Overload operator>> to read data for a diver d from stream in
//If errors were encountered while reading the data for a diver d
//then d.difficulty is set to a negative value
//Return the stream in
istream& operator>>(istream& in, Diver& d)
{
    string line = "";
    double dif = 0;
    const int sizeOf = 7;
    int neg = -1;
    double scores[sizeOf];

    //Check if there is empty lines, if so: ignore the line
    if(in>>ws && getline(in, d.name) && in>>ws &&  getline(in, line))
   {

    //Test if the line has correct format and set the values
   if(test_scores_line(line, scores, dif))
   {
        d.difficulty = dif;

       for (int i = 0; i<7; i++)
        {
            d.points[i] = scores[i];
        }
    }
   else
   {
        d.difficulty = neg;
   }

   }

   return in;
}


//Calculate final score for diver d
//and store it in d.final_score
void calculate_final_score(Diver& d)
{
     double sum =0;

     for(int i =0; i<6; i++)
     {
         for(int j=0; j<6; j++)
         {
             if(d.points[j] < d.points[j+1])
             {
                 double temp = d.points[j];
                 d.points[j] = d.points[j+1];
                 d.points[j+1] = temp;
             }
         }
     }

     for(int i=1; i<6; i++)
     {
         sum += d.points[i];
     }

     d.final_score = (sum/5)*3*d.difficulty;

}


//Overload operator<< to write data for diver d
//to stream out: name and final score
ostream& operator<<(ostream& out, const Diver& d)
{

    out << left << setw(25) << d.name << setprecision(3) << d.final_score << endl;

    return out;
}


//Overload comparison operator
//Return true if d1.final_score < d2.final_score
bool operator<(const Diver& d1, const Diver& d2)
{
    if(d1.final_score < d2.final_score)
        return true;

    return false;
}


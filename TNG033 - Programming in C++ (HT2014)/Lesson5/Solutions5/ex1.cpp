// =======================================================
// TNG033: Lesson 5, exercise 1
// Aida Nordman
// 2014/HT2
// =======================================================

#include <iostream>
#include <string>

using namespace std;

//Answer to 1.i: the problem is to have one counter that counts
//number of instances of any of the classes Course, Car, or Employee.
//Note that the counter is a static data member of Countable
//So, if different hierarchies of classes are inheriting from Countable
//one cannot really say how many Courses (or Cars or Employees) there are
//Answer to 1.ii: the problem can be addressed by turning Countable into a template class
//Then for instance, Course hierarchy can create
//a specific instanciation of the Countable class template -- see code below

/**************************************
* Template class Countable            *
***************************************/

template <class CountedType>
class Countable
{
protected:

    //Default constructor
    Countable()
    {
        ++counter;
    }; //constructor is not public
    //to avoid that instances of Countable that are not instances
    //of another class are created

    //Copy constructor
    Countable(const Countable& c)
    {
        ++counter;
    };

    ~Countable() //this class is not polymorphic, thus destructor is not virtual
    {
        //cout << "Countable destructor" << endl;
        --counter;
    }

    static int get_counter()
    {
        return counter;
    };

private:
    static unsigned int counter;
};

template <class CountedType>
unsigned int Countable<CountedType>::counter = 0;


/**************************************
* Class Course definition             *
***************************************/

class Course : public Countable<Course>
{
public:

    explicit Course(string n) : name(n) {   } ;

    virtual ~Course()  //Class Course is polymorphic, thus virtual destructor
    {
        //cout << "Course destructor" << endl;
    };

    string get_name() const
    {
        return name;
    };

    static int number_of_courses()
    {
        return get_counter();
    };

    friend ostream& operator<<(ostream& os, const Course& c);

protected:

    string name;

    virtual void display(ostream& os) const = 0;
};


/***********************************************************
* Class Course member functions implementation             *
************************************************************/


ostream& operator<<(ostream& os, const Course& c)
{
    c.display(os);
    return os;
}


/*********************************
* Class Programming definition   *
**********************************/


class Programming : public Course
{
public:

    Programming(string n, string lang)
        : Course(n), language(lang)
    { };

//    ~Programming()
//    {
//        cout << "Programming destructor" << endl;
//    }

    string get_language() const
    {
        return language;
    }

    void set_language(string l)
    {
        language = l;
    }


protected:
    string language;

    virtual void display(ostream& os) const;
};



/******************************************************
* Class Programming member functions implementation   *
*******************************************************/


void Programming::display(ostream& os) const
{
    os << "Programming course: " << name
       << " uses programming language " << language
       << "." << endl;
}


/*********************************
* Class Planet definition        *
**********************************/


class Math : public Course
{
public:

    explicit Math(string n, bool d = false)
        : Course(n), discrete(d)
    { };

//    ~Math()
//    {
//        cout << "Math destructor" << endl;
//    }


    bool is_discrete( ) const
    {
        return discrete;
    }

protected:
    const bool discrete;

    virtual void display(ostream& os) const;
};



/**************************************************
* Class Planet member functions implementation    *
***************************************************/


void Math::display(ostream& os) const
{
    if (discrete)
    {
        os << "Course in descrete math: " << name
           << "." << endl;
    }
    else
    {
        os << "Math course: " << name
           << "." << endl;
    }
}


/**************************************
* Main function                       *
***************************************/


int main()
{
    /*****************************************************
    * TEST PHASE 0                                       *
    *Programming class: constructor and operator<<       *
    ******************************************************/
    cout << "\nTEST PHASE 0" << endl;

    const Programming P1("*Graph Algorithms*", "R++");
    Programming P2("*Scripting languages*", "PHP");

    cout << "P1>>" << P1 << endl;
    cout << "P2>>" << P2 << endl;

    /*****************************************************
    * TEST PHASE 1                                       *
    *Programming class: get_lang, set_lang               *
    *Course: get_name                                    *
    ******************************************************/
    cout << "\nTEST PHASE 1" << endl;

    P2.set_language("*JavaScript*");

    cout << "The course " << P2.get_name()
         << " has changed programming language to "
         << P2.get_language() << endl;

    if ( P2.get_language() != P1.get_language() )
        cout << "There are two courses with different programming languages." << endl;
    else
        cout << "There are two courses with same programming language." << endl;

    cout << endl;

    /*****************************************************
    * TEST PHASE 2                                       *
    *Course Math: constructor, operator<<, is_discrete   *
    ******************************************************/
    cout << "\nTEST PHASE 2" << endl;

    const Math M1("*Game Theory*", true);
    Math M2("*Fourier Transform*");

    cout << "M1>>" << M1 << endl;
    cout << "M2>>" << M2 << endl;

    if ( M1.is_discrete() )
        cout << "There is a course in discrete mathematics!"
             << endl;

    /*****************************************************
    * TEST PHASE 3                                       *
    * Polymorphism                                       *
    ******************************************************/
    cout << "\nTEST PHASE 3" << endl;

    const int MAX = 6;

    Course* DB[MAX];
    int howMany = 3;

    DB[0] = new Programming("*Introduction to programming*", "C++");
    DB[1] = new Math("*Graph theory*", true);
    DB[2] = new Math("*Calculus*");

    for(int i = 0; i < howMany; i++)
        cout << *DB[i] << endl;

    /*****************************************************
    * TEST PHASE 4                                       *
    * number_of_courses                                  *
    ******************************************************/
    cout << "\nTEST PHASE 4" << endl;

    cout << "Number of courses: "
         << Course::number_of_courses() << endl;

    Programming P3(P2);

    cout << "\nP3>>" << P3 << endl;

    cout << "Number of courses: "
         << Course::number_of_courses() << endl;

    /*****************************************************
    * TEST PHASE 5                                       *
    * destructors, number_of_courses                     *
    ******************************************************/
    cout << "\nTEST PHASE 5" << endl;

    cout << endl << "Deleting some courses..." << endl << endl;
    for(int i = 0; i < howMany; i++)
        delete DB[i];

    cout << "\nNumber of courses: "
         << Course::number_of_courses() << endl;

//    /*****************************************************
//    * TEST PHASE 6                                       *
//    * Instances of Course that are not instances of one  *
//    * of its subclasses cannot be declared               *
//    ******************************************************/
//    cout << "\nTEST PHASE 6" << endl;
//
//    //Course C("XXX");  //should not compile!!
//
//    /*****************************************************
//    * TEST PHASE 7                                       *
//    * Instances of Countable that                        *
//    * are not instances of another cannot be declared    *
//    ******************************************************/
//    cout << "\nTEST PHASE 7" << endl;
//
//    Countable<Course> NNN;  //should not compile!!
//
//    /*****************************************************
//    * TEST PHASE 8                                       *
//    * Countable objects should never be removed          *
//    * through pointers of type Countable*                *
//    ******************************************************/
//    cout << "\nTEST PHASE 8" << endl;
//
//    Countable* ptr = new Programming("Data structures");
//    delete ptr;  //should not compile
//
//    cout << "\nand the program ends ..." << endl;

    return 0;
}

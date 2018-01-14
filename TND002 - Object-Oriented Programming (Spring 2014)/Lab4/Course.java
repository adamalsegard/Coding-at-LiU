package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\Course.java
// anm:    klass f�r enskilda kurser (f�rdigt)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

public class Course
{
    // -- INSTANSVARIABLER

    private String code;
    private String name;

    // -- KONSTRUKTORER

    public Course(String theCode, String theName)
    {
	code = theCode;
	name = theName;
    }

    // -- INSTANSMETODER
    
    // Returnerar kod f�r aktuell kurs
    public String getCode()
    {
	return code;
    }

    // Returnerar namn f�r aktuell kurs
    public String getName()
    {
	return name;
    }

    // Returnerar kod och namn som en str�ng
    public String toString()
    {
	return String.format("%-7s%s", code, name);
    }
}

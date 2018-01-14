package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\Program.java
// anm:    klass f�r enskilda entries (f�rdigt)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

public class Entry
{
    // -- INSTANSVARIABLER

    private String program;
    private String course;

    // -- KONSTRUKTORER

    public Entry(String theProgram, String theCourse)
    {
        program = theProgram;
        course  = theCourse;
    }

    // -- INSTANSMETODER

    // Returnerar programkod f�r aktuellt entry
    public String getProgram()
    {
        return program;
    }

    // Returnerar kurskod f�r aktuellt entry
    public String getCourse()
    {
        return course;
    }

    // Returnerar programkod och kurskod som en str�ng
    public String toString()
    {
        return String.format("%-7s%s", program, course);
    }
}

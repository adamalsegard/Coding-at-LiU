package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\Program.java
// anm:    klass f�r enskilda program (f�rdigt)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

public class Program
{
    // -- INSTANSVARIABLER

    private String code;
    private String name;

    // -- KONSTRUKTORER

    public Program(String theCode, String theName)
    {
        code = theCode;
        name = theName;
    }

    // -- INSTANSMETODER

    // Returnerar kod f�r aktuellt program
    public String getCode()
    {
        return code;
    }

    // Returnerar namn f�r aktuellt program
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

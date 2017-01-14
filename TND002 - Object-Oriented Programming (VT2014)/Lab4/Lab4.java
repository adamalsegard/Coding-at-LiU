package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\Lab4.java
// anm:    f�rdigt testprogram
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

import java.io.*;
import java.util.*;

public class Lab4
{
    // startmetoden main

    public static void main (String[] args) throws IOException
    {
        String  code;
        Scanner sc = new Scanner(System.in);
        
        ProgramList programs = new ProgramList();
        CourseList  courses  = new CourseList();
        StudyGuide  guide    = new StudyGuide(programs, courses);

        System.out.println("\n** Alla program\n");
        programs.load();
        programs.print();

        System.out.println("\n** Alla kurser\n");
        courses.load();
        courses.print();

        System.out.println("\n** Studiehandboken\n");
        guide.load();
        guide.print();

        System.out.println("\n** Sok program\n");
        System.out.print("Ange programkod ? ");
        System.out.flush();
        code = sc.nextLine().trim();
        System.out.println();
        guide.printProgram(code);

        System.out.println("\n** Sok kurs\n");
        System.out.print("Ange kurskod ? ");
        System.out.flush();
        code = sc.nextLine().trim();
        System.out.println();
        guide.printCourse(code);
    }
}

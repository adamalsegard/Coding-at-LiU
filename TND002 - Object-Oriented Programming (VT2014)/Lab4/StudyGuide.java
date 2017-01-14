package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\StudyGuide.java
// anm:    klass f�r lista �ver entries, dvs
//         klass f�r studiehandbok (uppgift)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

import java.io.*;
import java.util.*;

public class StudyGuide
{
    // -- INSTANSVARIABLER

    private Vector<Entry> list;

    ProgramList programs;
    CourseList  courses;

    // -- KONSTRUKTORER

    // Skapar en tom studiehandbok
    public StudyGuide(ProgramList thePrograms, CourseList  theCourses){
        
        list = new Vector<Entry>();
        programs = thePrograms;
        courses = theCourses;
    }
    
    // -- INSTANSMETODER

    // L�ser in alla entries fr�n filen curriculum.txt
    public void load() throws IOException{
        
        String line, program, course = "";
        StringTokenizer tokens;
        
        BufferedReader infil = new BufferedReader
            (new FileReader("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab4\\curriculum.txt"));
        
            while ((line = infil.readLine()) != null){
                tokens = new StringTokenizer(line);
                program = tokens.nextToken();
                
                while (tokens.hasMoreTokens()){
                    course = course + " " + tokens.nextToken();
                }
                list.add(new Entry(program, course.trim()));   
                course = "";

            }      
        infil.close();
    }

    // Skriver ut alla entries till kommandof�nstret
    public void print(){
        
        for (int i = 0; i<list.size(); i++){
            System.out.println(list.get(i));
        }
        
    }

    // Skriver ut programmet med angiven kod
    // samt aktuella kurser till kommandof�nstret
    // Skriver ut felmeddelande om s�dant program saknas
    public void printProgram(String code){
        
        if(programs.lookup(code) == null){
            System.out.println("Ange en korrekt programkod!");
            return;
        }
        
        System.out.println(programs.lookup(code) + "\n");
        
        for(int i=0; i<list.size(); i++){
            if(code.equalsIgnoreCase(list.get(i).getProgram())){
                System.out.println(courses.lookup(list.get(i).getCourse()));
            }
        }
        
    }

    // Skriver ut kursen med angiven kod
    // samt aktuella program till konsolen
    // Skriver ut felmeddelande om s�dan kurs saknas
    public void printCourse(String code){
        
        if(courses.lookup(code) == null){
            System.out.println("Ange en korrekt kurskod!");
            return;
        }
        
        System.out.println(courses.lookup(code) + "\n");
        
        for(int i=0; i< list.size(); i++){
            if(code.equalsIgnoreCase(list.get(i).getCourse())){
                System.out.println(programs.lookup(list.get(i).getProgram()));
            }
        }        
    }
}

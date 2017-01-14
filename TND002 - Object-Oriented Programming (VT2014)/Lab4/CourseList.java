package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\CourseList.java
// anm:    klass f�r lista �ver kurser (uppgift)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

import java.io.*;
import java.util.*;

public class CourseList
{
    // -- INSTANSVARIABLER

    private Vector<Course> list;

    // -- KONSTRUKTORER

    // Skapar en tom lista f�r kurser
    public CourseList(){
        
        list = new Vector<Course>();
    }

    // -- INSTANSMETODER

    // L�ser in alla kurser fr�n filen courses.txt
    public void load() throws IOException{
        
        String line, code, name = "";
        StringTokenizer tokens;
        
        BufferedReader infil = new BufferedReader
        (new FileReader("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab4\\courses.txt"));
        
            while ((line = infil.readLine()) != null){
                tokens = new StringTokenizer(line);
                code = tokens.nextToken();
                
                while (tokens.hasMoreTokens()){
                    name = name + " " + tokens.nextToken();
                }
                list.add(new Course(code, name));   
                name = "";

            }
            
        
        infil.close();
        
        
    }

    // Skriver ut alla kurser till kommandof�nstret
    public void print(){
               
        for (int i = 0; i<list.size(); i++){
            System.out.println(list.get(i));
        }
        
        
    }

    // Returnerar kursen med angiven kod
    // Returnerar null om s�dan kurs saknas
    public Course lookup(String code){
        
        for (int i=0; i<list.size(); i++){
            if (code.equalsIgnoreCase(list.get(i).getCode())){
                return list.get(i);
            }
        }
        
        return null;
    }
}

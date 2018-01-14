package Lab4;

// ===================================================================
// fil:    ~\tnd002\lab\lab4\ProgramList.java
// anm:    klass f�r lista �ver program (uppgift)
// skapad: 2013-02-12 / janpe
// �ndrad: 2013-02-12 / janpe
// ===================================================================

import java.io.*;
import java.util.*;

public class ProgramList
{
    // -- INSTANSVARIABLER

    private Vector<Program> list;

    // -- KONSTRUKTORER

    // Skapar en tom lista f�r program
    public ProgramList(){
        
        list = new Vector<Program>();
        
    }

    // -- INSTANSMETODER

    // L�ser in alla program fr�n filen programs.txt
    public void load() throws IOException{
        
        String line, code, name = "";
        StringTokenizer tokens;
        
        BufferedReader infil = new BufferedReader
        (new FileReader("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab4\\programs.txt"));
        
            while ((line = infil.readLine()) != null){
                tokens = new StringTokenizer(line);
                code = tokens.nextToken();
                
                while (tokens.hasMoreTokens()){
                    name = name + " " + tokens.nextToken();
                }
                list.add(new Program(code, name));   
                name = "";

            }
            
        
        infil.close();

    }

    // Skriver ut alla program till kommandof�nstret
    public void print(){
        
        for (int i = 0; i<list.size(); i++){
            System.out.println(list.get(i));
        }
    }

    // Returnerar programmet med angiven kod
    // Returnerar null om s�dant program saknas
    public Program lookup(String code){
        
        for (int i=0; i<list.size(); i++){
            if (code.equalsIgnoreCase(list.get(i).getCode())){
                return list.get(i);
            }
        }
        return null;
    }
}

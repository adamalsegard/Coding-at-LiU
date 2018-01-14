/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab3;
import java.io.*;
import java.util.*;
import javax.swing.*;
/**
 *
 * @author Adam
 */
public class Lab3A {
    public static void main(String[] args) throws IOException{
        
        //Declarera variabler
        Dictionary ordlista = new Dictionary();
        String line, in, ut;
        StringTokenizer tokens;
        
        //Användaren väljer fil
        Scanner sc = new Scanner(System.in);
        System.out.println("Ange infil: ");
        in = sc.next();
       // in = JOptionPane.showInputDialog("Ange utfil: ");
        System.out.flush();
        //ut = JOptionPane.showInputDialog("Ange utfil: ");
         System.out.println("Ange utfil: ");
        ut = sc.next();
        System.out.flush();
        // öppna infil
        BufferedReader infil = new BufferedReader
            (new FileReader("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab3\\" + in));
        

        // läs infil rad för rad
        while ((line = infil.readLine()) != null){
            tokens = new StringTokenizer(line, ",- /.");
            
            while(tokens.hasMoreTokens()){
                 ordlista.insertWord(tokens.nextToken());
            }
            
        }
        
        
        
        ordlista.sort();
        
        ordlista.toString();
        
        System.out.println("\nTotal words: " + ordlista.countTotWords());
        System.out.println("Unique words: " + ordlista.countUniWords() + "\n");


        // stäng infil
        infil.close();
        
        ordlista.save(ut);
        
        System.out.println("Ordlistan återfinns i " + ut);

    }
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab6;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
/**
 *
 * @author Adam
 */
public class Register {
    
    //Variabler
    
    private Vector<Person> reg = new Vector<Person>();
    
    
    //Constructor
    public Register(){
        
    }
    
    
    //Händelser
    public void load() throws IOException{
        
        String line, first, last, num = "";
        StringTokenizer tokens;
        reg.clear();
        
        BufferedReader infil = new BufferedReader
        (new FileReader("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab6\\reg.txt"));
        
            while ((line = infil.readLine()) != null){
                tokens = new StringTokenizer(line);
                last = tokens.nextToken();
                first = tokens.nextToken();
                
                while (tokens.hasMoreTokens()){
                    num = num + " " + tokens.nextToken();
                }
                reg.add(new Person(first.trim(), last.trim(), num.trim()));   
                num = "";

            }

        infil.close();

    }
    
    // Skriver ut alla program till kommandofönstret
    public void print(){
        
        for (int i = 0; i<reg.size(); i++){
            System.out.println(reg.get(i));
        }
    }
    
    public void save(String ut) throws IOException{
            
        Collections.sort(reg);
        
        PrintWriter utfil = new PrintWriter (new BufferedWriter 
            (new FileWriter("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab6\\" + ut)));

        for (int i = 0; i < reg.size(); i++){

            utfil.format("%-16s%-16s%-16s%n", reg.get(i).getLastName(), reg.get(i).getFirstName(), reg.get(i).getTelNum());               
        }

        utfil.close();
    }
    
    public void insertPerson(Person ny){
        int i;
        for(i=0; i<reg.size(); i++){
            if(reg.get(i) == null){
                reg.add(ny); 
                break;
            }
        }
        if(i == reg.size()){
             reg.add(ny);  
        }        
    }
    
    public void deletePerson(Person ny){
        
        for(int i = 0; i<reg.size(); i++){
            if(reg.get(i).compareTo(ny) == 0){
                reg.remove(reg.get(i));                
            }
        }    
    }
    
    public Person searchName(Person ny){
        
        for(int i = 0; i<reg.size(); i++){
            if(reg.get(i).compareTo(ny) == 2){
                return reg.get(i);
            }
        }        
        return null;
    }
    
    public Person searchNum(Person ny){
        
        for(int i = 0; i<reg.size(); i++){
            if(reg.get(i).getTelNum().equals(ny.getTelNum())){
                return reg.get(i);
            }
        }        
        return null;
    }
    
    public Person searchAll(Person ny){
        
        for(int i = 0; i<reg.size(); i++){
            if(reg.get(i).compareTo(ny) == 0){
                return reg.get(i);
            }
        }        
        return null;
    }
   
}

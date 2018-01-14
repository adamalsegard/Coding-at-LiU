/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson2;

import java.io.*;
import java.util.*;
/**
 *
 * @author Adam
 */
public class Dictionary {
    
    
    private Vector<Zoophobia> vec;
    
    //Constructors
    public Dictionary(){
        vec = new Vector<Zoophobia>();
    }
    
    public void load() throws IOException{
        String line, phobia, animal;
        StringTokenizer tokens;
        
        BufferedReader infil = new BufferedReader
        (new FileReader("C:/Users/Adam/Documents/NetBeansProjects/TND002/src/Lesson2/old.txt"));
        
        while ((line = infil.readLine()) != null){
            tokens = new StringTokenizer(line);
            phobia = tokens.nextToken();
            animal = tokens.nextToken();
            vec.add(new Zoophobia(phobia, animal));
            
        }
        infil.close();
    }
    
    public void print(){
        
        Collections.sort(vec);

        for (int i = 0; i < vec.size(); i++)
        {
            System.out.println(vec.get(i));
        }
    }
    
    public void insert(Zoophobia zp){
        int i = 0;

        while (i < vec.size() && zp.compareTo(vec.get(i)) != 0){
            i++;
        }

        if (i < vec.size()){
            vec.get(i).setAnimal(zp.getAnimal());
        }
        else{
            vec.add(zp);
        }
    }
    
    public void delete(String phobia){
        
        for (int i = 0; i < vec.size(); i++){
            
            if (phobia.equals(vec.get(i).getPhobia())){
                vec.remove(i);
                break;
            }
        }
    }
    
    public String lookup(String phobia){
        
        for (int i = 0; i < vec.size(); i++){
            
            if (phobia.equals(vec.get(i).getPhobia())){
                
                return vec.get(i).getAnimal();
            }
        }

        return "unknown";
    }
    
    public void save() throws IOException{
            
        Collections.sort(vec);

        PrintWriter utfil = new PrintWriter (new BufferedWriter 
        (new FileWriter("C:/Users/Adam/Documents/NetBeansProjects/TND002/src/Lesson2/old.txt")));

        for (int i = 0; i < vec.size(); i++){
            
            utfil.format("%-20s%s\n", vec.get(i).getPhobia(), vec.get(i).getAnimal());
        }

        utfil.close();
    }
}

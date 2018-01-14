/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab3;
import java.io.*;
import java.util.*;
/**
 *
 * @author Adam
 */
public class Dictionary {
    
    // Nya declarationer
    private Vector<Entry> vec = new Vector<Entry>();
    
    //Default constructor
    public Dictionary(){
        
    }
          
    //methods
    public void insertWord(String word){
        
        word = word.toLowerCase();
        Entry next = new Entry(word);
        int i;
        
        for (i=0; i < vec.size(); i++){
            
            Entry ny = vec.get(i);
            
            int res = ny.compareTo(next);
            
            if(res == 0){
                ny.addCounter();
                break;
            }               
        }
        if(i == vec.size()){
             vec.add(next);  
        }
    }
    //Behövs denna?
    @Override
    public String toString(){
        
        for (int i= 0; i< vec.size(); i++){
            Entry kul = vec.get(i);
            System.out.println(kul);
        }
        return "";
        
    }
    
    public void sort(){
        
        Collections.sort(vec);
        
    }
    
    public int countUniWords(){
        
        return vec.size();
    }
    
    public int countTotWords(){
        
        int total = 0;
        
        for(int i=0; i<vec.size(); i++){
            total= total + vec.get(i).getCounter();
        }
        
        return total;
    }
    
    public void save(String ut) throws IOException{
            
        
        PrintWriter utfil = new PrintWriter (new BufferedWriter 
            (new FileWriter("C:\\Users\\Adam\\Documents\\NetBeansProjects\\TND002\\src\\Lab3\\" + ut)));

        for (int i = 0; i < vec.size(); i++){

                utfil.format("%-20s%s%n", vec.get(i).getWord(), "(" + vec.get(i).getCounter() + ")");
                
        }

        utfil.close();
    }
}

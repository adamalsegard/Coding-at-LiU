/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab3;

/**
 *
 * @author Adam
 */
public class Entry implements Comparable<Entry>{
    
    
    private String word;
    private int counter = 1;
    
    public Entry(String theWord){
        setWord(theWord);
    }
    
    public void setWord(String theWord){
        word = theWord;
    }
    
    public void addCounter(){
        counter++;
    }
    
    public String getWord(){
        return word;
    }
    
    public int getCounter(){
        return counter;
    }
    
    @Override
    public int compareTo(Entry NyttInslag){
        
        int result = word.compareTo(NyttInslag.getWord());
        
        return result;
    }
    
    @Override
    public String toString(){
        
        String full = "";        
        if (word.length()>15){
            return full = word + "\t(" + counter + ")";
        }
        else if (word.length()<8){
            return full = word + "\t\t\t(" + counter + ")";
        }
        else{
           return full = word + "\t\t(" + counter + ")"; 
        }
        
    }
    
}

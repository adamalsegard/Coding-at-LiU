/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson2;

/**
 *
 * @author Adam
 */
public class Zoophobia implements Comparable<Zoophobia>{
    
    private String phobia;
    private String animal;
    
            
    public Zoophobia(String thePhobia, String theAnimal){
        setPhobia(thePhobia);
        setAnimal(theAnimal);
    }
    
    public void setPhobia (String thePhobia){
        phobia = thePhobia;
    }
    
    public void setAnimal(String theAnimal){
        animal = theAnimal;
    }
    
    public String getPhobia(){
        return phobia;
    }
    
    public String getAnimal(){
        return animal;
    }
    
    public String toString(){
        String full = "";
        return full = phobia + " - fear of " + animal;
    }
    
    public int compareTo(Zoophobia zp){
        return phobia.compareTo(zp.phobia);
    }
}

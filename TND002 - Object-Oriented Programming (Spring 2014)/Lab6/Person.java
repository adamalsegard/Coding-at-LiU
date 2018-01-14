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
/**
 *
 * @author Adam
 */
public class Person implements Comparable<Person>{
    
    private String firstName;
    private String lastName;
    private String telnum;
    
    //Constructors
    public Person(){
        
    }
    
    public Person(String theFirst, String theSur, String theTel){
        firstName = theFirst;
        lastName = theSur;
        telnum = theTel;
    }
    
    
    //Methods
    public String getFirstName(){
        return firstName;
    }
    
    public String getLastName(){
        return lastName;
    }
    
    public String getTelNum(){
        return telnum;
    }
    
    @Override
    public int compareTo(Person nytt){
        
        if(lastName.compareTo(nytt.getLastName()) == 0){
            if(firstName.compareTo(nytt.getFirstName()) == 0){
                if(telnum.compareTo(nytt.getTelNum()) == 0){
                    return 0;   
                }
                else{
                    return 2;
                }
            }
            else if(firstName.compareTo(nytt.getFirstName()) < 0){
                return -1;
            }
            else{
                return 1;
            }
        }  
        else if(lastName.compareTo(nytt.getLastName()) < 0){
            return -1;
        }
        else{
            return 1;
        }    
        
    }
    
        
    @Override
    public String toString(){
        
        return String.format("%-16s%-16s%s", lastName, firstName, telnum);
 
    }
    
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson3;

/**
 *
 * @author Adam
 */
public abstract class Employee implements Comparable<Employee>{
    
    //instance variables
    protected String firstName;
    protected String lastName;
    
    //Contructors
    public Employee(String theFirst, String theLast){
        
        firstName = theFirst;
        lastName = theLast;
    }
    
    //Fun things
    
    abstract public double earnings();
    
    
    public String toString(){
        
        return String.format("%-8s%-12s", firstName, lastName);
    }
    
    public int compareTo(Employee emp){
        
        if (earnings() == emp.earnings()){
            
            return 0;
        }
        
        else if (earnings() > emp.earnings()){
            
            return +1;
        }
        
        else {
            
            return -1;
        }
        
    }
    
}

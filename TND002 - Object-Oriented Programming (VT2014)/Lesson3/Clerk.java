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
public class Clerk extends Employee{
    
    
    protected double hours;
    protected double wage;
    
    public Clerk(String F, String L, double H, double W){
        super(F, L);
        setHours(H);
        setWage(W);
    }
    
    public void setWage(double w){
        
        wage = (w < 0.0) ? 0.0 : w;
    }

    public void setHours(double h){
        
        hours = (h < 0.0) ? 0.0 : h;
    }

    public double earnings(){
        
        return wage * hours;
    }

    public String toString(){
        
        return String.format("%-8s%s", "Clerk", super.toString());
    }
}

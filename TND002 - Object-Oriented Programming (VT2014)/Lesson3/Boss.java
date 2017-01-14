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
public class Boss extends Employee{
    
    // instansvariabler

    protected double salary;

    // konstruktorer

    public Boss(String F, String L, double S){
        
        super(F, L);
        setSalary(S);
    }

    // instansmetoder

    public void setSalary(double s){
        
        salary = (s < 0.0) ? 0.0 : s;
    }

    @Override
    public double earnings(){
        
        return salary;
    }

    @Override
    public String toString(){
        
        return String.format("%-8s%s", "Boss", super.toString());
    }
    
}

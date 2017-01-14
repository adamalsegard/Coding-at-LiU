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
public class Worker extends Employee{
    
    // instansvariabler

    protected double  rate;
    protected int quantity;

    // konstruktorer

    public Worker(String F, String L, double R, int Q){
        
        super(F, L);
        setRate(R);
        setQuantity(Q);
    }

    // instansmetoder

    public void setRate(double r){
        
        rate = (r < 0.0) ? 0.0 : r;
    }

    public void setQuantity(int q){
        
        quantity = (q < 0) ? 0 : q;
    }

    public double earnings(){
        
        return rate * quantity;
    }

    public String toString(){
        
        return String.format("%-8s%s", "Worker", super.toString());
    }
    
}

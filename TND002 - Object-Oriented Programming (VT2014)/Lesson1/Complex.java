/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson1;

/**
 *
 * @author Adam
 */
public class Complex {
    
    
    //Instance variables
    private double a;
    private double b;
    public static final int SIMPLE_FORMAT = 0;
    public static final int PRETTY_FORMAT = 1;
    private static int format;
    
    //Constructors
   public Complex(){
       this(0.0, 0.0);
}
   
   public Complex(double ina, double inb){
       setVal(ina, inb);
   }
    
    //Instance methods
    public void setVal(double a, double b){
        this.a = a;
        this.b = b;
    }
    
    public double getRe(){
        return a;
    }
    
    public double getIm(){
        return b;
    }
    
    public double magnitude(){
       
        double m = Math.sqrt(Math.pow(a, 2) + Math.pow(b, 2));
        return m;
    }
    
    public Complex add(Complex z){
        
        double c = a + z.getRe();
        double d = b + z.getIm();
        
        Complex ny = new Complex(c, d);
        return ny;
    }
    
    public Complex mul(Complex z){
        double c = z.getRe();
        double d = z.getIm();
        
        double nyA = (a*c - b*d);
        double nyB = (c*b + a*d);
        
        Complex ny = new Complex(nyA, nyB);
        return ny;
    }
    
    public static void setFormat(int f){
        if(f==SIMPLE_FORMAT || f== PRETTY_FORMAT){
            format = f;
        }
    }
    
    public String toString(){
        String full = "";  
        
        if (format == SIMPLE_FORMAT)
            return full = "(" + a + ", " + b + ")";
        
        else
            return full = a + "+" + b + "i";
    }
    
    public int compareTo(Complex z){
        if(this.magnitude() == z.magnitude())
            return 0;
        else if (this.magnitude() < z.magnitude())
            return -1;
        else
            return 1;
    }
}

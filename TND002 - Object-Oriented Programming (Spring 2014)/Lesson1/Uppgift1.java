/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson1;
import javax.swing.*;
/**
 *
 * @author Adam
 */
public class Uppgift1 {
    public static void main(String[]args){
        
        double x = -3.0;
        double y = 2.0;
        
        Complex z1 = new Complex();
        Complex z2 = new Complex(6.0, -4.0);
        
        z1.setVal(x, y);
        
        Complex.setFormat(Complex.SIMPLE_FORMAT);
        System.out.println("Format set to default" + "\n");
        
        System.out.println("z1.toString() = " + z1.toString());
        System.out.println("z2.toString() = " + z2.toString() + "\n");
        
        System.out.println("z1.getRe() = " + z1.getRe());
        System.out.println("z1.getIm() = " + z1.getIm() + "\n");
        System.out.println("z2.getRe() = " + z2.getRe());
        System.out.println("z2.getIm() = " + z2.getIm() + "\n");
        
        System.out.println("z1.magnitude() = " + z1.magnitude());
        System.out.println("z2.magnitude() = " + z2.magnitude() + "\n");
        
        System.out.println("z1.add(z2) = " + z1.add(z2));
        System.out.println("z1.mul(z2) = " + z1.mul(z2) + "\n");
        
        System.out.println("z1.compareTo(z2) = " + z1.compareTo(z2));
        System.out.println("z2.compareTo(z1) = " + z2.compareTo(z1));
        System.out.println("z1.compareTo(z1) = " + z1.compareTo(z1) + "\n");
       
        //Ändra format
        Complex.setFormat(Complex.PRETTY_FORMAT);
        System.out.println("Format changed" + "\n");
        
        System.out.println("z1.toString() = " + z1.toString());
        System.out.println("z2.toString() = " + z2.toString() + "\n");
    }
}

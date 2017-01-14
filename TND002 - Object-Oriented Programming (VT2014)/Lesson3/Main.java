/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson3;
import java.util.*;

public class Main {

    public static void main(String[] args)
    {
        Locale.setDefault(Locale.US);   // -- amerikanska konventioner

        Payroll list = new Payroll();

        list.insert(new Boss("Joakim", "Andersson", 25000.00));
        list.insert(new Boss("Like a", "Boss", 9000000));
        list.insert(new Clerk("Kalle", "Pettersson", 105.00, 168.0));
        list.insert(new Clerk("Kajsa", "Lundstrom", 145.00, 176.0));
        list.insert(new Worker("Knatte", "Karlsson", 2.25, 12321));
        list.insert(new Worker("Fnatte", "Nilsson", 1.75, 10101));
        list.insert(new Worker("Tjatte", "Svensson", 2.00, 13579));

        System.out.println("*** Employees unsorted:\n");
        list.print();

        System.out.println("*** Employees sorted by earnings:\n");
        list.sort();
        list.print();
    }
}
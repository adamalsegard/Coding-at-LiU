/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson3;

import java.util.*;
/**
 *
 * @author Adam
 */
public class Payroll {

    // instansvariabler

    private Vector<Employee> vec;

    // konstruktorer

    public Payroll(){
        
        vec = new Vector<Employee>();
        
    }

    // instansmetoder

    public void insert(Employee emp){
        
        vec.add(emp);
    }

    public void sort(){
        
        Collections.sort(vec);
    }

    public void print()
    {
        for (int i = 0; i < vec.size(); i++)
        {
            System.out.format("%s : %8.2f\n", vec.get(i), vec.get(i).earnings());
        }
        System.out.println();
    }
}


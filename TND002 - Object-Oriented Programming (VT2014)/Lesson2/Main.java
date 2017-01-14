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
import java.io.*;

public class Main
{
    // startmetoden main

    public static void main(String[] args) throws IOException
    {
        Dictionary dic = new Dictionary();

        dic.load();

        System.out.println("** Empty dictionary created");
        System.out.println("** File old.txt loaded" + "\n");
        dic.print();

        dic.insert(new Zoophobia("hippophobia", "horses"));
        dic.insert(new Zoophobia("musophobia", "mice"));

        dic.delete("ichthyophobia");
        dic.delete("arachnophobia");

        System.out.println("\n" + "** Zoophobias inserted");
        System.out.println("** Zoophobias deleted" + "\n");
        dic.print();

        System.out.println("\n" + "** Dictionary lookup's" + "\n");
        System.out.println("hippophobia -> " + dic.lookup("hippophobia"));
        System.out.println("ichthyophobia -> " + dic.lookup("ichthyophobia"));
        System.out.println("javaphobia -> " + dic.lookup("javaphobia"));

        dic.save();

        System.out.println("\n" + "** File new.txt saved" + "\n");
    }
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson4;
import java.awt.*;
import javax.swing.*;
/**
 *
 * @author Adam
 */
public class Uppgift0 extends JFrame{
    
    // instansvariabler

    private String fntName  = "SansSerif";
    private int    fntStyle = Font.PLAIN;
    private int    fntSize  = 20;

    private JLabel lblSample;

    // konstruktor

    public Uppgift0()
    {
        lblSample = new JLabel("Sample Text", JLabel.CENTER);

        lblSample.setOpaque(true);
        lblSample.setBackground(Color.WHITE);
        lblSample.setForeground(Color.BLACK);
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));

        JPanel pnlEast = new JPanel();

        pnlEast.setLayout(new FlowLayout());  // default
        pnlEast.add(new JLabel("Uppgift 1-4"));

        Container c = getContentPane();

        c.setLayout(new BorderLayout());     // default
        c.add(lblSample, BorderLayout.CENTER);
        c.add(pnlEast, BorderLayout.EAST);

        setSize(300, 105);
        setTitle("Uppgift 0");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // händelsehanterare ...

    // startmetoden main

    public static void main(String[] args)
    {
        Uppgift0 frame = new Uppgift0();
    }
}

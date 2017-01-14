/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson4;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 *
 * @author Adam
 */
public class Uppgift3 extends JFrame implements ActionListener{
    
    // instansvariabler

    private String fntName  = "SansSerif";
    private int    fntStyle = Font.PLAIN;
    private int    fntSize  = 16;

    private JLabel lblSample;
    private JRadioButton small, medium, large;

    // konstruktor

    public Uppgift3()
    {
        lblSample = new JLabel("Sample Text", JLabel.CENTER);

        lblSample.setOpaque(true);
        lblSample.setBackground(Color.WHITE);
        lblSample.setForeground(Color.BLACK);
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));

        small = new JRadioButton("Small");
        medium = new JRadioButton("Medium");
        large = new JRadioButton("Large");
        
        small.addActionListener(this);
        medium.addActionListener(this);
        large.addActionListener(this);
        
        ButtonGroup grpSize = new ButtonGroup();

        grpSize.add(small);
        grpSize.add(medium);
        grpSize.add(large);
        
        JPanel pnlEast = new JPanel();

        pnlEast.setLayout(new GridLayout(3,1)); 
        pnlEast.add(small);
        pnlEast.add(medium);
        pnlEast.add(large);

        Container c = getContentPane();

        c.setLayout(new BorderLayout());
        c.add(lblSample, BorderLayout.CENTER);
        c.add(pnlEast, BorderLayout.EAST);

        setSize(300, 105);
        setTitle("Uppgift 3");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // händelsehanterare ...
    @Override
    public void actionPerformed(ActionEvent e){
        
        if(e.getSource() == small){
            fntSize = 16;
        }
        else if(e.getSource() == medium){
            fntSize = 20;
        }
        else{
            fntSize = 24;
        }
        
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));
    }
    
    
    // startmetoden main

    public static void main(String[] args)
    {
        Uppgift3 frame = new Uppgift3();
    }

}

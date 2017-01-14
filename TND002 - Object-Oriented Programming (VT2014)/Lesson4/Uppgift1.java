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
public class Uppgift1 extends JFrame implements ActionListener{
    
    // instansvariabler

    private String fontName  = "SansSerif";
    private int    fontStyle = Font.PLAIN;
    private int    fontSize  = 20;

    private JLabel labelSample;
    private JButton buttSans, buttMono;

    // konstruktor

    public Uppgift1()
    {
        labelSample = new JLabel("Sample Text", JLabel.CENTER);

        labelSample.setOpaque(true);
        labelSample.setBackground(Color.WHITE);
        labelSample.setForeground(Color.BLACK);
        labelSample.setFont(new Font(fontName, fontStyle, fontSize));

        buttSans = new JButton("SansSerif");
        buttMono = new JButton("MonoSpaced");
        
        buttSans.addActionListener(this);
        buttMono.addActionListener(this);
        
        JPanel pnlEast = new JPanel();

        pnlEast.setLayout(new GridLayout(2, 1));
        pnlEast.add(buttSans);
        pnlEast.add(buttMono);

        Container c = getContentPane();

        c.setLayout(new BorderLayout());     // default
        c.add(labelSample, BorderLayout.CENTER);
        c.add(pnlEast, BorderLayout.EAST);

        setSize(300, 105);
        setTitle("Uppgift 1");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // händelsehanterare ...
    public void actionPerformed(ActionEvent e){
        
        if(e.getSource() == buttSans){
            fontName = "SansSerif";
        }
        else {
            fontName = "MonoSpaced";
        }
        labelSample.setFont(new Font(fontName, fontStyle, fontSize));
    }
    
    
    // startmetoden main

    public static void main(String[] args)
    {
        Uppgift1 frame = new Uppgift1();
    }
}


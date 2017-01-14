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
public class Uppgift2 extends JFrame implements ActionListener{
    
    // instansvariabler

    private String fntName  = "SansSerif";
    private int    fntStyle = Font.PLAIN;
    private int    fntSize  = 20;

    private JLabel lblSample;
    private JCheckBox bold, italic;

    // konstruktor

    public Uppgift2()
    {
        lblSample = new JLabel("Sample Text", JLabel.CENTER);

        lblSample.setOpaque(true);
        lblSample.setBackground(Color.WHITE);
        lblSample.setForeground(Color.BLACK);
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));

        bold = new JCheckBox("Bold");
        italic = new JCheckBox("Italics");
        
        bold.addActionListener(this);
        italic.addActionListener(this);
        
        JPanel pnlEast = new JPanel();

        pnlEast.setLayout(new GridLayout(2, 1)); 
        pnlEast.add(bold);
        pnlEast.add(italic);

        Container c = getContentPane();

        c.setLayout(new BorderLayout());     // default
        c.add(lblSample, BorderLayout.CENTER);
        c.add(pnlEast, BorderLayout.EAST);

        setSize(300, 105);
        setTitle("Uppgift 2");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // händelsehanterare ...
    @Override
    public void actionPerformed(ActionEvent e){
     
        int valBold, valItalic;
        
        valBold = bold.isSelected()     ?   Font.BOLD   :   Font.PLAIN;
        valItalic = italic.isSelected() ?   Font.ITALIC :   Font.PLAIN;
        fntStyle = valBold + valItalic;
        
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));
    }
    
    // startmetoden main

    public static void main(String[] args)
    {
        Uppgift2 frame = new Uppgift2();
    }
}


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
public class Uppgift4 extends JFrame implements ActionListener{
    
    // instansvariabler

    private String fntName  = "SansSerif";
    private int    fntStyle = Font.PLAIN;
    private int    fntSize  = 16;

    private JLabel lblSample;
    private JComboBox comboSize;
    private String[]    strSizes = {"Small", "Medium", "Large"};
    private int[]       intSizes = {16, 20, 24};    

    // konstruktor

    public Uppgift4()
    {
        lblSample = new JLabel("Sample Text", JLabel.CENTER);

        lblSample.setOpaque(true);
        lblSample.setBackground(Color.WHITE);
        lblSample.setForeground(Color.BLACK);
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));

        comboSize = new JComboBox(strSizes);
        
        comboSize.setMaximumRowCount(3);
        comboSize.addActionListener(this);
                
        JPanel pnlEast = new JPanel();

        pnlEast.setLayout(new GridLayout(3,1)); 
        pnlEast.add(comboSize);

        Container c = getContentPane();

        c.setLayout(new BorderLayout());
        c.add(lblSample, BorderLayout.CENTER);
        c.add(pnlEast, BorderLayout.EAST);

        setSize(300, 105);
        setTitle("Uppgift 4");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // händelsehanterare ...
    @Override
    public void actionPerformed(ActionEvent e){
        
        fntSize = intSizes[comboSize.getSelectedIndex()];
               
        lblSample.setFont(new Font(fntName, fntStyle, fntSize));
    }
    
    
    // startmetoden main

    public static void main(String[] args)
    {
        Uppgift4 frame = new Uppgift4();
    }

}

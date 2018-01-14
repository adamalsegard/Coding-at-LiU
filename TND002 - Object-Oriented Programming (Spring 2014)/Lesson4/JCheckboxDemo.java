/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson4;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
/**
 *
 * @author Adam
 */
public class JCheckboxDemo extends JFrame implements ActionListener{
    
    //Instance variables
    private JLabel labelDemo;
    private JCheckBox chRed, chGreen, chBlue;
    
    //Contructors
    public JCheckboxDemo(){
        
        labelDemo = new JLabel("Swing Demo", JLabel.CENTER);
        
        labelDemo.setOpaque(true);
        labelDemo.setBackground(Color.WHITE);
        labelDemo.setForeground(Color.RED);
        labelDemo.setFont(new Font("SansSerif", Font.PLAIN, 24));       
        
        chRed = new JCheckBox("Red");
        chGreen = new JCheckBox("Green");
        chBlue = new JCheckBox("Blue");
        
        chRed.addActionListener(this);
        chGreen.addActionListener(this);
        chBlue.addActionListener(this);

        
        //JButton buttA = new JButton("A");
        //JButton buttB = new JButton("BB");
        //JButton buttC = new JButton("CCC");
        //JButton buttD = new JButton("DDDD");
        //JButton buttE = new JButton("EEEEE");
        
        JPanel panelEast = new JPanel();
        
        panelEast.setLayout(new GridLayout(3, 1));
        panelEast.add(chRed);
        panelEast.add(chGreen);
        panelEast.add(chBlue);
        
        Container c = getContentPane();
        
        c.setLayout(new BorderLayout()); //FlowLayout.CENTER def, GridLayout, BorderLayout
        c.add(labelDemo, BorderLayout.CENTER);
        c.add(panelEast, BorderLayout.EAST);
        
        //c.add(buttA, BorderLayout.NORTH); 
        //c.add(buttB, BorderLayout.EAST); 
        //c.add(buttC, BorderLayout.SOUTH); 
        //c.add(buttD, BorderLayout.WEST); 
        //c.add(buttE, BorderLayout.CENTER);

        //c.add(labelDemo);
        
        
        pack();
        
        //setSize(500, 200);
        setTitle("JCheckboxDemo");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }
    
    @Override
    public void actionPerformed(ActionEvent e){
        int red = chRed.isSelected()        ? 255 : 0;
        int green = chGreen.isSelected()    ? 255 : 0;
        int blue = chBlue.isSelected()      ? 255 : 0;
            
        labelDemo.setForeground(new Color(red, green, blue));
    }
      public static void main(String[] args){
            JCheckboxDemo lek = new JCheckboxDemo();
        }
    
}

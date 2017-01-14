/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lesson4;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
/**
 *
 * @author Adam
 */
public class Uppgift5 extends JFrame implements ActionListener{
    
    private JTextField txtRadie, txtOmkrets, txtArea;
    
    
    
    public Uppgift5(){
        
        Locale.setDefault(Locale.US);
        
        txtRadie = new JTextField("0.0");
        txtOmkrets = new JTextField("0.000");
        txtArea = new JTextField("0.000");
        
        txtRadie.addActionListener(this);
        txtOmkrets.setEditable(false);
        txtArea.setEditable(false);
        
        Container c = getContentPane();
        
        c.setLayout(new GridLayout(3, 2, 5, 5));
        c.add(new JLabel("Radie: ", JLabel.RIGHT));
        c.add(txtRadie);
        c.add(new JLabel("Omkrets: ", JLabel.RIGHT));
        c.add(txtOmkrets);
        c.add(new JLabel("Area: ", JLabel.RIGHT));
        c.add(txtArea);
        
        setSize(300, 200);
        setTitle("Uppgift5");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    public void actionPerformed(ActionEvent e){
        
        double radie, omkrets, area;
        
        try{
            //Detta kan ge NumberFormatExeption
            radie = Double.parseDouble(txtRadie.getText());
            //Detta duger inte så vi kastar NumberFormatException
            if(radie < 0.0) throw new NumberFormatException();
        }
        catch(NumberFormatException nfe){
            
            radie = 0.0;
            txtRadie.setText("0.0");
        }
        
        omkrets = Math.PI * radie * 2.0;
        area    = Math.PI * radie * radie;
        
        txtOmkrets.setText(String.format("%.3f", omkrets));
        txtArea.setText(String.format("%.3f", area));
        
    } 
    
    
    public static void main(String[] args){
        Uppgift5 frame = new Uppgift5();
    }
    
}

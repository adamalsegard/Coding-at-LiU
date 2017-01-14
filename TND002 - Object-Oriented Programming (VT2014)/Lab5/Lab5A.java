/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Math;

/**
 *
 * @author Adam
 */
public class Lab5A extends JFrame implements ActionListener{
    
    private JLabel label1;
    private JLabel label2;
    private JLabel label3;
    private JButton startButton;
    private JTextField guess;
    private JTextField total;
    private JPanel texter;
    private JPanel knappar;
    int svaret =1, gissning = 0, count = 1;
    
    
    
    
    public Lab5A(){
        
        label1 = new JLabel("Klicka här för att starta provet:    ", JLabel.RIGHT);       
        
        label1.setOpaque(true);
        label1.setBackground(Color.WHITE);
        label1.setForeground(Color.BLACK);
        label1.setFont(new Font("SansSerif", Font.PLAIN, 16));       
        
        label2 = new JLabel("Gissa ett tal mellan 1 och 100:    ", JLabel.RIGHT );
        
        label2.setOpaque(true);
        label2.setBackground(Color.WHITE);
        label2.setForeground(Color.RED);
        label2.setFont(new Font("SansSerif", Font.PLAIN, 16)); 
        
        label3 = new JLabel("Antal gissningar:    ", JLabel.RIGHT );
        
        label3.setOpaque(true);
        label3.setBackground(Color.WHITE);
        label3.setForeground(Color.BLACK);
        label3.setFont(new Font("SansSerif", Font.PLAIN, 16)); 
        
        startButton = new JButton("Start test!");
        guess = new JTextField(10);
        total = new JTextField(10);
        
        startButton.addActionListener(this);
        guess.setEditable(false);
        total.setEditable(false);
           
        
        
        texter = new JPanel();
        
        texter.setLayout(new GridLayout(3, 1));
        texter.add(label1);
        texter.add(label2);
        texter.add(label3);
        
        knappar = new JPanel();
        
        knappar.setLayout(new GridLayout(3, 1, 10, 10));
        knappar.add(startButton);
        knappar.add(guess);
        knappar.add(total);
        
        
        Container c = getContentPane();
        
        c.setLayout(new BorderLayout());
        c.add(texter);
        c.add(knappar, BorderLayout.EAST);
        
        
        
        pack();
        setSize(400, 150);
        setTitle("Högskoleprovet");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    @Override
    public void actionPerformed(ActionEvent e){
         
        
        if(e.getSource() == startButton){
            
            startButton.setEnabled(false);
            guess.setEditable(true);
            guess.addActionListener(this);
            
            Random randNum = new Random();
            svaret = randNum.nextInt((100 - 1) + 1) + 1;
            System.out.println(svaret);
            
            total.setText("0");
        }
        
        if(e.getSource() == guess){
                
                gissning = Integer.parseInt(guess.getText()); 
                           
                if(gissning == svaret){
                    	
		switch(count){
		case 1: case 2: case 3: 
			JOptionPane.showMessageDialog(null, "Välkommen till LiTH!");
                        break;
                case 4: case 5: case 6: 
			JOptionPane.showMessageDialog(null, "Välkommen till Chalmers!");
			break;
		case 7: case 8: case 9: 
			JOptionPane.showMessageDialog(null, "Välkommen till KTH!");
			break;
		default: 
			JOptionPane.showMessageDialog(null, "Välkommen åter nästa år!");
			break;
                }		
                
               //återställning
                startButton.setEnabled(true);
                guess.setEditable(false);
                label2.setText("Gissa ett tal mellan 1 och 100:    ");
                guess.setText("");
                total.setText("");
                count = 1;
                }
                
                else if(gissning != svaret){
                    
                     if(gissning>svaret){
				label2.setText(gissning + " var för stort. Försök igen!    ");
				total.setText(Integer.toString(count));
                                count++;
			}
			else{
				label2.setText(gissning + " var för litet. Försök igen!    ");
				total.setText(Integer.toString(count));
                                count++;
			}
                guess.setText(""); 
                }
            
        }
               
        
    }
    
    
    public static void main(String[] args){
        Lab5A lek = new Lab5A();
    }
    
}

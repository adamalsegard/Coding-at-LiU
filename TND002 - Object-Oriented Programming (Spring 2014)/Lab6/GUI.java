/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Lab6;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
/**
 *
 * @author Adam
 */
public class GUI extends JFrame implements ActionListener{
    
    //Deklarera variabler
    private JTextField fornamn, eftnamn, telnum, meddel;
    private JButton sokNum, sokNamn, setPost, remPost, about, clear, openReg, saveReg;
    private JLabel för, eft, tel, med;
    private JPanel meddelanden, text, knappar;
    private Register reg = new Register();
    private int count = 1;
    private Person found = new Person();
    private Person found2 = new Person();
    
    //Konstruktor
    public GUI(){
        
        för = new JLabel("Förnamn: ", JLabel.RIGHT);
        eft = new JLabel("Efternamn: ", JLabel.RIGHT);
        tel = new JLabel("Telefonnr: ", JLabel.RIGHT);
        med = new JLabel("Meddelande: ", JLabel.RIGHT);
        
        fornamn = new JTextField(15);
        eftnamn = new JTextField(15);
        telnum = new JTextField(15);
        meddel = new JTextField(15);
        
        sokNum = new JButton("Sök nummer");
        sokNamn = new JButton("Sök namn");
        setPost = new JButton("Sätt in post");
        remPost = new JButton ("Ta bort post");
        about = new JButton("Om programmet");
        clear = new JButton("Rensa fält");
        openReg = new JButton("Öppna register");
        saveReg = new JButton("Spara register");
        
        fornamn.addActionListener(this);
        eftnamn.addActionListener(this);
        telnum.addActionListener(this);
        meddel.setEditable(false);
        
        sokNum.addActionListener(this);
        sokNamn.addActionListener(this);
        setPost.addActionListener(this);
        remPost.addActionListener(this);
        about.addActionListener(this);
        clear.addActionListener(this);
        openReg.addActionListener(this);
        saveReg.addActionListener(this);
        
        
        meddelanden = new JPanel();
        meddelanden.setLayout(new GridLayout(4, 1, 2, 2));
        meddelanden.add(för);
        meddelanden.add(eft);
        meddelanden.add(tel);
        meddelanden.add(med);
        
        
        text = new JPanel();
        text.setLayout(new GridLayout(4, 1, 2, 2));
        text.add(fornamn);
        text.add(eftnamn);
        text.add(telnum);
        text.add(meddel);
        
        
        knappar = new JPanel();
        
        knappar.setLayout(new GridLayout(4, 2, 2, 2));
        knappar.add(sokNum);
        knappar.add(about);
        knappar.add(sokNamn);
        knappar.add(clear);
        knappar.add(setPost);
        knappar.add(openReg);
        knappar.add(remPost);
        knappar.add(saveReg);      
        
        
        Container c = getContentPane();
        
        c.setLayout(new BorderLayout());
        c.add(meddelanden, BorderLayout.WEST);
        c.add(text, BorderLayout.CENTER);
        c.add(knappar, BorderLayout.EAST);
        
        
        
        pack();
        //setSize(500, 160);
        setTitle("Lab 6");
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        
    }
    
    
    @Override
    public void actionPerformed(ActionEvent e){
        
        //Om programmet
        if(e.getSource() == about){
            JOptionPane.showMessageDialog(null, " Register Pro 1.0 \n Copyright 2006-2012 \n Amazing Software, Inc.");
        }
        
        //Rensa fält
        if(e.getSource() == clear){
            fornamn.setText("");
            eftnamn.setText("");
            telnum.setText("");
            meddel.setText("Fälten rensade");
        }
        
        //Öppna register, bara kunna göra en gång.
        if(e.getSource() == openReg && count == 1){
            try {
                reg.load();
                reg.print();
                meddel.setText("Filen reg.txt öppnad.");
                count++;
            } catch (IOException ex) {
                meddel.setText("Filen reg.txt kan inte läsas.");
            }
            
        }
        else if(e.getSource() == openReg && count != 1){
            meddel.setText("Filen reg.txt redan läst.");
        }
        
        //Spara register
        if(e.getSource() == saveReg){
            try {
                
                reg.save("reg.txt");
                reg.print();
                meddel.setText("Filen reg.txt sparad.");
                count = 1;
                
            } catch (IOException ex) {
                meddel.setText("Filen reg.txt kan inte skrivas.");
            }
           
        }
        
        //Sätt in post
        if(e.getSource() == setPost){
            
            if(!"".equals(fornamn.getText()) && !"".equals(eftnamn.getText()) && !"".equals(telnum.getText())){
               
                Person ny = new Person(fornamn.getText(), eftnamn.getText(), telnum.getText());
                found = reg.searchNum(ny);
                found2 = reg.searchName(ny);
                if(found2 != null){
                    meddel.setText("Personen finns redan!");
                }
                else if(found != null){
                    meddel.setText("Numret finns redan!");
                }
                else{
                    reg.insertPerson(ny);
                    meddel.setText("Personen sparad!");
                    
                }
                
            }
            
            else{
                meddel.setText("Alla fält ej ifyllda.");
            }
        }
        
        //Ta bort post
        if(e.getSource() == remPost){
            
            if(!"".equals(fornamn.getText()) && !"".equals(eftnamn.getText()) && !"".equals(telnum.getText())){
               
                Person ny = new Person(fornamn.getText(), eftnamn.getText(), telnum.getText());
                found = reg.searchAll(ny);
                
                if(found != null){
                    reg.deletePerson(ny);
                    meddel.setText("Personen borttagen!");
                }
                else{
                    meddel.setText("Personen finns inte!");
                }
                
            }
            
            else{
                meddel.setText("Alla fält ej ifyllda.");
            }
            
        }
        
        //Sök nummer efter namn
        if(e.getSource() == sokNum){
            if(!"".equals(fornamn.getText()) && !"".equals(eftnamn.getText())){
                
                Person ny = new Person(fornamn.getText(), eftnamn.getText(), telnum.getText());
                
                found = reg.searchAll(ny);
                if(found != null){
                    meddel.setText("Telefonnr redan inskriven!");
                }
                else{
                    found = reg.searchName(ny);
                    if(found != null){
                        telnum.setText(found.getTelNum());
                        meddel.setText("Personen funnen!");
                    }
                    else{
                        meddel.setText("Personen finns ej!");
                    }
                }       
            }            
            else{
                meddel.setText("Vänligen fyll i båda fälten.");
            }
        }
        
        //Sök namn efter nummer
        if(e.getSource() == sokNamn){
            if(!"".equals(telnum.getText())){
                
                Person ny = new Person(fornamn.getText(), eftnamn.getText(), telnum.getText());
                found = reg.searchAll(ny);
                if(found != null){
                    meddel.setText("Personen redan inskriven!");
                }
                else{
                    found = reg.searchNum(ny);
                    if(found != null){
                        fornamn.setText(found.getFirstName());
                        eftnamn.setText(found.getLastName());
                        meddel.setText("Personen funnen!");
                    }
                    else{
                        meddel.setText("Personen finns ej!");
                    }
                }          
            }
            else{
                meddel.setText("Vänligen fyll i rätt fält.");
            }
        }
    }
    
    
    public static void main(String[] args){
        GUI KBK = new GUI();
    }
}

package Lab1;
import javax.swing.*;

public class Lab1E {
	public static void main(String[]args){
		
		int count = 1;
		String input;
		int X = 0;
		
		input = JOptionPane.showInputDialog("Provledare, ange ett tal mellan 1 och 100: ");
		X = Integer.parseInt(input);
		
		input = JOptionPane.showInputDialog("Provdeltagare, gissa ett tal mellan 1 och 100: ");
		int Guess = Integer.parseInt(input);
		
		while (Guess!=X){
			if(Guess>X){
				input = JOptionPane.showInputDialog(Guess + " �r f�r stort. F�rs�k igen: ");
				Guess = Integer.parseInt(input);
				count++; 
			}
			else{
				input = JOptionPane.showInputDialog(Guess + " �r f�r litet. F�rs�k igen: ");
				Guess = Integer.parseInt(input);
				count++;
			}
		}
		
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
		System.exit(0);		
	}

}

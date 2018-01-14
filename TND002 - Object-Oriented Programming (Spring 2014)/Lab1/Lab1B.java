package Lab1;
import javax.swing.*;

public class Lab1B {
	public static void main(String[]args){
		
		String input;
		double C, K, F;
		final double zero = -273.15;
		input = JOptionPane.showInputDialog("Ange temperatur i Celsius: ");
		C = Double.parseDouble(input);
		
		while(C>= zero){
			K = C - zero;
			F = (9*C)/5 + 32;
			JOptionPane.showMessageDialog(null, " Temperaturen i Kelvin: " + K + "\n Temperaturen i Fahrenheit: " + F);
			
			input = JOptionPane.showInputDialog("Ange temperatur i Celsius: ");
			C = Double.parseDouble(input);
		}
		JOptionPane.showMessageDialog(null, "Angiven temperatur under absoluta nollpunkten. Hej d�!");	
		System.exit(0);	
	}
}

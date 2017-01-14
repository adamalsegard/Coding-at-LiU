package Lab1;
import javax.swing.*;

public class Lab1D {
	public static void main(String[] args) {
		
		double C, K, F;
		final double zero = -273.15;
		String tabell = "Celsius-\t-Kelvin-\t-Fahrenheit";
		double in, stop, plus;
		String input;
		
		input = JOptionPane.showInputDialog("Ange start p� intervall: ");
		in = Double.parseDouble(input);
		input = JOptionPane.showInputDialog("Ange stopp p� intervall: ");
		stop = Double.parseDouble(input);
		input = JOptionPane.showInputDialog("Ange start p� intervall: ");
		plus = Double.parseDouble(input);
		
		double i = in;
		
		while(i<=stop){
			C = i;
			K = C - zero;
			F = (9*C)/5 + 32;
			tabell = tabell + "\n" + C + "-\t-" + K + "-\t-" + F;
			i=i+plus;
			}
		
		JOptionPane.showMessageDialog(null, tabell);
		System.exit(0);	
	}
}

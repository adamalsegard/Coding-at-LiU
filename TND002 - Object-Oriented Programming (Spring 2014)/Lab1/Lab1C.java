package Lab1;
import javax.swing.*;

public class Lab1C {
	public static void main(String[]args){
		
		double C, K, F;
		final double zero = -273.15;
		String tabell = "Celsius-\t-Kelvin-\t-Fahrenheit";
		
		for (int i=0; i<=100; i=i+10){
			C = i;
			K = C - zero;
			F = (9*C)/5 + 32;
			tabell = tabell + "\n" + C + "-\t-" + K + "-\t-" + F;
		}
			JOptionPane.showMessageDialog(null, tabell);	
			System.exit(0);	
	}

}

package Lab2;
import javax.swing.*;

public class Lab2A {
	public static void main(String[]args){
		
		int year = Integer.parseInt(JOptionPane.showInputDialog("Ange år: "));
		int month = Integer.parseInt(JOptionPane.showInputDialog("Ange månad: "));
		int day = Integer.parseInt(JOptionPane.showInputDialog("Ange dag: "));
		
		Date d1 = new Date ();
		Date d2 = new Date (year, month, day);
		
                d1.setDate(2011, 01, 31);
                
		//Format set to SE
		Date.setFormat(Date.SE_FORMAT);
		System.out.println("Date format set default" + "\n");
		
		System.out.println("d1.toString() = " + d1.toString());
		System.out.println("d1.toString() = " + d2.toString() + "\n");
		
		
		System.out.println("d1.getYear() = " + d1.getYear());
		System.out.println("d1.getMonth() = " + d1.getMonth());
		System.out.println("d1.getDay() = " + d1.getDay() + "\n");
		
		System.out.println("d2.getYear() = " + d2.getYear());
		System.out.println("d2.getMonth() = " + d2.getMonth());
		System.out.println("d2.getDay() = " + d2.getDay() + "\n");
		
		System.out.println("d1.nextDate() = " + d1.nextDate());
		System.out.println("d1.prevDate() = " + d1.prevDate());
		System.out.println("d2.nextDate() = " + d2.nextDate());
		System.out.println("d2.prevDate() = " + d2.prevDate() + "\n");
		
		System.out.println("d1.compareTo(d2)" + d1.compareTo(d2));
		System.out.println("d2.compareTo(d1)" + d2.compareTo(d1));
		System.out.println("d1.compareTo(d1)" + d1.compareTo(d1) + "\n");
		
		
		//Format set to US
		System.out.println("Date format set to US_FORMAT");
		
		Date.setFormat(Date.US_FORMAT);
		System.out.println("d1.toString())" + d1.toString());
		System.out.println("d2.toString())" + d2.toString() + "\n");
	}
}

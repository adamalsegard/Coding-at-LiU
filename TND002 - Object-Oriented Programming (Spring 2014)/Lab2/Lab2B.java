package Lab2;

import Lab2.Date;
import Lab2.Person;

public class Lab2B {
	public static void main(String[]args){
	
		Date d1 = new Date();
		Date d2 = new Date(1992, 01, 25);
                
                d1.setDate(1932, 06, 06);
                
                Person p1 = new Person();
		Person p2 = new Person ("Kalle", "Anka", d1);
		
                p1.setPerson("Adam", "Alsegård", d2);
                
		System.out.println("Using default date format"+"\n");
		Date.setFormat(Date.SE_FORMAT);
                
		System.out.println(p1.toString());
		System.out.println(p2.toString() + "\n");
		
		System.out.println("First name: \t" + p1.getFirstName());
		System.out.println("Last name: \t" + p1.getLastName());
		System.out.println("Birth date: \t" + p1.getBirthDate() + "\n");
                
                System.out.println("First name: \t" + p2.getFirstName());
		System.out.println("Last name: \t" + p2.getLastName());
		System.out.println("Birth date: \t" + p2.getBirthDate() + "\n");
		
		System.out.println("Birth year (p1): " + p1.getBirthDate().getYear());
		System.out.println("Birth year (p2): " + p2.getBirthDate().getYear() + "\n");
		
		System.out.println("Age (p1): \t" + p1.getAge());
		System.out.println("Age (p2): \t" + p2.getAge() + "\n");
		
	}
}

package Lab2;
import javax.swing.*;

public class Date implements Comparable<Date> {
	
//Instance variables
	private int Year; 
	private int Month; //1-12
	private int Day; // 1-31
	private final int zero = 0;
	private int DaysofMonth;
	public static final int SE_FORMAT = 1;
	public static final int US_FORMAT = 2;
	private static int format;
	
//Constructors
	Date(){
            this(2014,02,12);
	}
	
	Date(int theYear, int theMonth, int theDay){
		setDate(theYear, theMonth, theDay);
	}
	
//Instance methods
	public void setDate(int theYear, int theMonth, int theDay){
		
		if(theYear>=0 && theMonth<=12 && theMonth>=1 && theDay>=1){
			
			DaysofMonth  = returnDays(theMonth);
			
			if (theDay<=DaysofMonth){
				Year = theYear;
				Month = theMonth;
				Day = theDay;
			}
			else{
				Year = zero;
				Month = zero;
				Day = zero;	
			}
		}
	}
	
	public int getYear(){
		return Year;
	}
	
	public int getMonth(){
		return Month;
	}
	
	public int getDay(){
		return Day;
	}
        
	//Return how many day there are in the specific month
	private int returnDays(int m){
			switch (m){
			case 2:
				return 28;
			
			case 4: case 6: case 9: case 11:
				return 30;
				
			default:
				return 31;
			}
		}
        
	private int returnMonth(int m){
		if(m == 2)
			return 1;
		
		else if(m == 4 || m == 6 || m == 9 || m == 11)
			return 2;
		
		else
			return 3;
	}
	
	public Date nextDate(){
		int y = Year;
		int m = Month;
		int d = Day+1;
		
		if(m==12 && d>31){
			d = 01;
			m = 01;
			y = Year + 1;
		}
		
		else if(d > returnDays(m)){
			d = 01;
			m = Month + 1;
		}	
			
		Date newD = new Date(y, m, d);
		
		return newD;
	}
	
	public Date prevDate(){
		int y = Year;
		int m = Month;
		int d = Day-1;
		
		if(m==01 && d==zero){
			d = 31;
			m = 12;
			y = Year - 1;
		}
		
		else if(d==zero){
			m = Month - 1;
			
			if(returnMonth(m)==1)
				d = 28;				
			
			else if(returnMonth(m)==2)
				d = 30;				
			
			else
				d = 31;
		}	
			
		Date newD = new Date(y, m, d);
		
		return newD;
	}
	
	public int compareTo(Date theDate){
		
		if (Day == theDate.getDay() && Month == theDate.getMonth() && Year == theDate.getYear())
			return 0;
		
		else if (Year > theDate.getYear() || Year == theDate.getYear() && Month > theDate.getMonth() ||
				Year == theDate.getYear() && Month == theDate.getMonth() && Day > theDate.getDay())
			return 1;
		else
			return -1; 
	}
	
	public static void setFormat(int theFormat){
		if(theFormat == SE_FORMAT)
			format = SE_FORMAT;
		
		else
			format = US_FORMAT;
	}
	
	public String toString(){
		
		String datum = "";
		
		if(format == SE_FORMAT)
			return datum = Year + "-" + Month + "-" + Day;
		else
			return datum = Month + "/" + Day + "/" + Year;
	}

	
}

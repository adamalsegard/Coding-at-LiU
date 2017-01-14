package Lab2;

public class Person {

	private String FirstName;
	private String LastName;
	private Date BirthDate;
        
        public Person(){
            
        }
        
	public Person(String thaFirstName, String thaLastName, Date thaBirthDate){
		setPerson(thaFirstName, thaLastName, thaBirthDate);
	}


	public void setPerson(String thaFirstName, String thaLastName, Date thaBirthDate){
		FirstName = thaFirstName;
		LastName = thaLastName;
		BirthDate = thaBirthDate;
	}
	
	public String getFirstName(){
		return FirstName;
	}
	
	public String getLastName(){
		return LastName;
	}
	
	public Date getBirthDate(){
		return BirthDate;
	}
	
	public int getAge(){
		Date today = new Date();
                today.setDate(2014, 02, 06);
		int age = 0;
		
                age = today.getYear() - BirthDate.getYear();
                
                if(BirthDate.getMonth() > today.getMonth() || 
                        BirthDate.getMonth() == today.getMonth() && BirthDate.getDay() > today.getDay())
                    age = age-1;
		
		
		return age;
	}
	
	public String toString(){
		
		String name = "";
		
		return name = FirstName + " " + LastName + "\t" + BirthDate;
	}


}
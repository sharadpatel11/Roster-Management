package project3;


public class Student {
	
	private String FirstName;
	private String LastName;
	private String IDNo;

//Constructors
	
	public Student()
	{
		this.FirstName = null;
		this.LastName = null;
		this.IDNo = null;
		
	}
	public Student(String a, String b, String c) 
	{
		this.FirstName = a;
		this.LastName = b;
		this.IDNo = c;
	}
	
//accessors
	
	public String getFirstName()
	{
		return this.FirstName;
	}
	public String getLastName()
	{
		return this.LastName;
	}
	public String getIDNo()
	{
		return this.IDNo;
	}
	
//mutators
	
	public void setFirstName(String f)
	{
		this.FirstName = f;
	}
	public void setLastName(String l)
	{
		this.LastName = l;
	}
	public void setIDNo(String i)
	{
		this.IDNo = i;
	}
	
//other functions
	
	public boolean equals(Student i) //returns boolean whether the two students' IDno. are same or not.
	{
		if(this.IDNo == i.IDNo)
		{
			return true;
		}
		
		return false;
	}
	
	/**
	   *Parameters: Student
	   *
	   *Method: 
	   *		It compares this student with the other student based on their first and last names. 
	   *		it returns 0 if they are equal, returns -1 if this students is less than other student or returns 1 if its greater than other student.
	   *
	   *Returns; int
	   *
	   *Runtime: O(n)
	   *
	*/
	public int compareTo(Student s)
	{
		if(s.LastName.equals(this.LastName))
		{
			if(s.FirstName.equals(this.FirstName))
			{
				if(s.IDNo.equals(this.IDNo))
				{	
					return 0;
				}
			}
			else if(this.FirstName.compareTo(s.FirstName) < 0)
			{
				return -1;
			}
			else return 1;
		}
		
		if(this.LastName.compareTo(s.LastName) < 0)
		{
			return -1;
		}
		else return 1;
		
	}
	
	public String toString()
	{
		String s = "Name:" + this.FirstName + " " + this.LastName + "  ID:" + this.IDNo;
		return s;
	}
}

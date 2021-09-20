package project3;

public class LinkedStudentList {
/*	
	private LNode head;

	public LinkedStudentList()
	{
		this.head = new LNode();
	}
	
	public LNode getHead()
	{
		return this.head;
	}
	
	public boolean isEmpty()
	{
		if(this.head.next == null)
		{
			return true;
		}
		return false;
	}
	
	public void inserSorted(Student s)
	{
		
		LNode curr = this.head.next;
		LNode prev = this.head;
			
		while(curr != null && curr.data.compareTo(s) < 0)
		{
			prev = curr; 
			curr = curr.next;
		}
		
		prev.next = new LNode(s, curr);		
	}
	
	public void delete(Student s)
	{
		if(isEmpty())
		{
			System.out.println("Roster is empty");
		}
		else
		{
			LNode curr = this.head.next;
			LNode prev = this.head;
				
			while(curr != null && curr.data.compareTo(s) < 0)
			{
				prev = curr; 
				curr = curr.next;
			}
	
			if(curr.data.equals(s))
			{
				prev.next = curr.next;
			}
			else
			{
				System.out.println("Student was not in the Roster");
			}
		}
	
	}
	
	public String toString()
	{
		String s = ""; 		
		LNode curr = this.head.next;
		
		while(curr.next != null)	
		{
			s += curr.data.toString() + "\n";
			curr = curr.next;
		}
		
		s += curr.data.toString();
		
		return s;
	}
*/	
}

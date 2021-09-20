package project3;

public class LNode {
	
	protected Student data;
	protected LNode next;

//Constructors
	public LNode()
	{
		this.data = null;
		this.next = null;
	}
	public LNode(Student s)
	{
		this.data = s;
		this.next = null;
	}
	public LNode(Student s, LNode l)
	{
		this.data = s;
		this.next = l;
	}
	
//setters and getters
	public Student getData()
	{
		return  this.data;
	}
	public LNode getNext()
	{
		return this.next;
	}
	public void setData(Student s)
	{
		this.data = s;
	}
	public void setNext(LNode l)
	{
		this.next = l;
	}
}

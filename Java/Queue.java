package project3;

public class Queue {

	/**
	   *It has private Student node rear and front to access the front and back of the queue.
	   *It has enqueue() and dequeue() function to push and pop students into queue.
	   *It has a peak() function that returns the student at front and isEmpty() function that returns null if the queue is empty.
	   *
	*/
	private LNode rear;
	private LNode front;
	
	public Queue()
	{
		this.rear = null;
		this.front = null;
	}
	
	public boolean isEmpty()
	{
		return this.rear == null;
	}
	
	/**
	   *Parameters: Student.....
	   *
	   *Method: 
	   *		It creates the new node with student s and adds it to the rear.....
	   *
	   *Runtime: O(1)
	   *
	*/
	public void enqueue(Student s)
	{
		if(isEmpty())
		{
			this.rear = new LNode(s);
			this.front = this.rear;
		}
		else
		{
			this.rear.next = new LNode(s);
			this.rear = this.rear.next;
		}
	}
	
	/**
	   *Parameters: Student.....
	   *
	   *Method: 
	   *		It assigns the new student with front nodes' data and removes the first node. Then, returns the student.....
	   *
	   *Runtime: O(1)
	   *
	*/
	public Student dequeue()
	{
		if(isEmpty()) { return null; }
		Student s = this.front.data;
		if(this.front == this.rear) { this.rear = null; this.front = null; }
		else { this.front = this.front.next; }
		return s;
	}
	
	/**
	   *Parameters: Student....
	   *
	   *Method: 
	   *		It returns the data at the front of the queue.....
	   *
	   *Runtime: O(1)
	   *
	*/
	public Student peek()
	{
		if(this.front != null)
		{
			return (this.front.data);
		}
		else
		{
			return null;
		}
	}
}

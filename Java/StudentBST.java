package project3;

public class StudentBST {

	/**
	   *Create a BNode class for a node that has a Student data, BNode left and BNode right. it has one parameter constructor which assigns the value to data. 
	   *It has get and set functions for data, left and right.
	   *
	*/
	class BNode {
		
			protected Student data;
			protected BNode left;
			protected BNode right;
			
			public BNode() {  this.data = null; this.left = null; this.right = null; }
			public BNode(Student s) {  this.data = s; this.left = null; this.right = null; }
			
			public Student getData() {  return this.data; }
			public BNode getLeft() {  return this.left; }
			public BNode getRight() { return this.right; }
			
			public void setData(Student s) { this.data = s; }
			public void setLeft(BNode l) { this.left = l; }
			public void setRight(BNode r) { this.right = r; }
	}
	
	/**
	   *BST has private root that can be used to access all the otehr nodes.
	   *It has get function for root. 
	   *It has insert and remove method to add and remove students.
	   *
	*/
	private BNode root; 
	
	public StudentBST() {  this.root = null; }
	
	public BNode getRoot() { return this.root; }
	
	
	/**
	   * It takes the student and passes it to the insertStudent() with the root of the BST.
	   *
	*/
	public void insert(Student s)
	{
		this.root = insertStudent(this.root, s);
	}
	/**
	   *Parameters: BNode, Student....
	   *
	   *Method: 
	   *		First, it takes the root and recursively check for the place where the student can be added. 
	   *		It checks by comparing the given student with BNodes' data.
	   *		At the end, it returns the root of the updated BST.....
	   *
	   *Returns: BNode.....
	   *
	   *Runtime: O(log n)
	   *
	*/
	private BNode insertStudent(BNode b, Student s)
	{
		if (b == null)
	    {
	          b = new BNode(s);
	          return b;
	    }
		 	
		if (s.compareTo(b.data) < 0)
	    {
			b.left = insertStudent(b.left, s);		
	    }
	    else if (s.compareTo(b.data) > 0)
	    {   	    	
	    	b.right = insertStudent(b.right, s); 	
	    }
	     
		 return b;
	}
	
	/**
	   * It takes the student and passes it to the removeStudent() with the root of the BST.
	   *
	*/
	public void remove(Student s)
	{
		this.root = removeStudent(this.root, s);
	}
	/**
	   *Parameters: BNode, Student....
	   *
	   *Method: 
	   *		First, it takes the root and recursively check for the place where the student is. 
	   *		It checks by comparing the given student with BNodes' data.
	   *		When the place if found it assigns the minimum data of its right side to curernt node and retunrs the data of the current node.....
	   *
	   *Returns: BNode....
	   *
	   *Runtime: O(log n)
	   *
	*/
	private BNode removeStudent(BNode b, Student s)
	{
		if (b == null)
            return b;
 
        
        if (s.compareTo(b.data) < 0)
        {	
            b.left = removeStudent(b.left, s);
        }
        else if (s.compareTo(b.data) > 0)
        { 
        	b.right = removeStudent(b.right, s);
        }
        else 
        {
            if (b.left == null)
                return b.right;
            else if (b.right == null)
                return b.left;
 
            b.data = minStudent(b.right);
 
            b.right = removeStudent(b.right, b.data);
        }             
        return b;
	}
	/**
	   *Parameters: BNode....
	   *
	   *Method: 
	   *		It finds the least value by checking the left sides of the node and returns that least value....
	   *
	   *Returns: Student....
	   *
	   *Runtime: Best case is O(1) and worst case is O(log n)
	   *
	*/
    public Student minStudent(BNode b)
    {
        Student mins = b.data;
        while (b.left != null)
        {
            mins = b.left.data;
            b = b.left;
        }
        return mins;
    }
}

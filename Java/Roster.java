package project3;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.*;
import javax.swing.JOptionPane;

import project3.StudentBST.BNode;

public class Roster {

	public static void main(String[] args) throws FileNotFoundException {
	
		/**
		   *First, we instantiate StudentBST, waiting Queue, Sorted Student array, HashArray to use for our program.
		   *Then, we load roster using loadRoster() method into StudentBST and the waiting Queue using LoadWaitingList() method into waitingList.
		   * After we load the roster we assign the length to the return value - 1 so we can use it during add and remove to figure out if the class is full or not
		   *
		*/
		StudentBST Roster = new StudentBST();
		Queue WaitingList = new Queue();
		ArrayList<Student>[] rosterArray = new ArrayList[100]; 
		Student[] StudentArray = new Student[20];		
		int length = 0;	
		String Rosterfile = "Roster.txt";
		String Waitingfile = "WaitingList.txt";
		
		loadWaitingList(Waitingfile, WaitingList);		
		length = loadRoster(Rosterfile, Roster, rosterArray) - 1; 
		
		
		/**
		   *We check the length and waitinglist to make sure there is no one waiting if the class is not full.
		   *
		*/
		if(length != 19)
		{
			while(length <= 19 && WaitingList.peek() != null)
			{
				Roster.insert(WaitingList.dequeue());
				length++;
			}
		}
		
		/**
		   *We give use options 1 to 5 to perform operations on our roster using a while loop, the loop ends when the user chooses option 5
		   *
		   *Option 1: it adds the student to the roster if its not full or else puts him/her in a waiting queue. Method used: addStudent()
		   *Option 2: it removes the student from the roater and adds the waiting student to the roster. Method Used: removeStudent()
		   *Option 3: it searches for a student based on their id. Method Used: searchID()
		   *Option 4: it searches for a student based on their first and last name. Method used: searchName()
		   *Option 5: It closes the registration where no more adding or removing can happen and saves the roster into a sorted array. Method Used: BSTtoArray()
		   *
		*/
		int choice = Integer.parseInt(JOptionPane.showInputDialog("           Roster Management \n\n1)Add Student \n2)Remove Student "
													+ "\n3)Search Student by ID \n4)Search Student by Name \n5)Close Registration and Save \n\nChoose Option No.:" ));
		
		while(true)
		{
			if(choice == 1)
			{
				
				String fn = JOptionPane.showInputDialog("Enter the first name:");
				String ln = JOptionPane.showInputDialog("Enter the last name:");
				String id = JOptionPane.showInputDialog("Enter the ID No.:");
				
				Student temp = new Student(fn, ln, id);
				
				if(length == 19) //check if the roster is full if it is then add it to the waitinglist
				{
					WaitingList.enqueue(temp);	
					JOptionPane.showMessageDialog(null, "Sorry, Roster is currently full. You have been added to the waiting list.");
				}
				else
				{
					addStudent(Roster, temp, rosterArray);	
					length++; //increment length after each add
					JOptionPane.showMessageDialog(null, "Student has been added");
				}
			}
			if(choice == 2)
			{
				removeStudent(Roster, WaitingList, rosterArray);
				if(length < 19)
				{
					length--; //decrement length if the class is not full
				}
			}
			if(choice == 3)
			{
				Student s = searchID(rosterArray);
				if(s != null)
				{	
					JOptionPane.showMessageDialog(null, "The Student is in the roster:\n" + s);
				}
			}
			if(choice == 4)
			{
				Student s1 = searchName(Roster);
				if(s1 != null)
				{	
					JOptionPane.showMessageDialog(null, "The Student is in the roster:\n" + s1);
				}
			}
			if(choice == 5)
			{
				int start = 0;
				BSTtoArray(StudentArray, start, Roster.getRoot());
				uploadRoster(Rosterfile, StudentArray, length);
				uploadWaitingList(Waitingfile, WaitingList);
				JOptionPane.showMessageDialog(null, "Saved and Uploaded");
				break; //finish looping and close the program
			}
			if(choice <= 0 || choice > 5)
			{
				JOptionPane.showMessageDialog(null, "Invalid Option"); //if the given input is invalid then prompt again
			}
			
		    choice = Integer.parseInt(JOptionPane.showInputDialog("           Roster Management \n\n1)Add Student \n2)Remove Student \n3)Search Student by ID "
		    		+ "\n4)Search Student by Name \n5)Close Registration and Save \n\nChoose Option No.::"));
		}		
	}
	
	/**
	   *Parameters: String...
	   *
	   *Method:
	   *		It takes the string id and then then returns the integer value of id's last two digits.....
	   *
	   *Return: int...
	   *
	   *Runtime: O(1)
	   *
	*/
	public static int lasttwo(String id)
	{
		String value = id;
		String lt = null;
		if (value != null && value.length() >= 2) {  
		    lt = value.substring(value.length() - 2); //assign lt to last two digits of id
		}
		
		return Integer.parseInt(lt);
	}
	
	/**
	   *Parameters: String, StudentBST, Arraylist<Student>[]...
	   *
	   *Method:
	   *		it opens the file and then reads the data line by line.
	   *		after every 3 lines it creates the student using last 3 lines info and adds it to the StudentBST using insert(). 
	   *		It also puts the student at the index of their last two digits into Arraylist. 
	   *		At the end it returns the amount of students added.....
	   *	   
	   *Returns: int....
	   *
	   *Runtime: O(n)
	   *
	*/
	public static int loadRoster(String fileName, StudentBST b, ArrayList<Student>[] a) throws FileNotFoundException
	{
		File inputFile = new File(fileName);
		int length = 0;
		
		Scanner in = new Scanner(inputFile);
		int count = 0; //to make sure we add after we read id from the textfile
		Student s = new Student();
		
		String fn = null, ln = null, id = null, line = null;
		
		while (in.hasNextLine())
		{
		  line = in.nextLine();		  
		  
		  /*
		   *Since one student takes 3 lines in our text file, we will keep a counter to add student when counter equals 2. so we have all the needed data to create a student. 
		   */
		  if(count == 0)
		  {
			  fn = line;
			  count++;
		  }
		  else if(count == 1)
		  {
			  ln = line;
			  count++;
		  } 
		  else if(count == 2)
		  {
			  id = line;
			  s = new Student(fn, ln, id);
			  b.insert(s);
			  int index = lasttwo(id) % 100;
			  if(a[index] == null)
			  {
				a[index] = new ArrayList<Student>();
			  	a[index].add(s);
		  	  }
			  else
			  {
				  a[index].add(s);
			  }
			  count = 0;
			  length++; //increment after each student add
		  }
		}
		in.close();
		
		return length;
	}
	
	/**
	   *Parameters: filename, Queue.... 
	   *
	   *Method:
	   *		it opens the file and then reads the data line by line.
	   *		after every 3 lines it creates the student using last 3 lines info and adds it to the queue using enqueue().....
	   * 
	   *Runtime: O(n).
	   *
	*/
	public static void loadWaitingList(String fileName, Queue b) throws FileNotFoundException
	{
		File inputFile = new File(fileName);
		
		Scanner in = new Scanner(inputFile);
		int count = 0;
		Student s = new Student();
		
		String fn = null, ln = null, id = null, line = null;
		
		while (in.hasNextLine())
		{
		  line = in.nextLine();		  
		  
		  if(count == 0)
		  {
			  fn = line;
			  count++;
		  }
		  else if(count == 1)
		  {
			  ln = line;
			  count++;
		  } 
		  else if(count == 2)
		  {
			  id = line;
			  s = new Student(fn, ln, id);
			  b.enqueue(s);
			  count = 0;
		  }
		}
		in.close();
	}
	
	/**
	   *Parameters: String, Student[], int.....
	   *
	   *Method: it opens the file we want to write to and then it loops till the end of the array. 
	   *		In the loop, it writes data of the array on the file......
	   *		
	   *Runtime: O(n).
	   *
	*/
	public static void uploadRoster(String fileName, Student[] a, int length) throws FileNotFoundException
	{
		if(a[0] != null)
		{	
			PrintWriter out = new PrintWriter(fileName);
		
			for(int i = 0; i <= length; i++)
			{
				if(a[i] != null)
				{
					out.println(a[i].getFirstName());
					out.println(a[i].getLastName());
					out.println(a[i].getIDNo());
				}
			}
			out.close();
		}
	}
	
	/**
	   *Parameters: String, Queue....
	   *
	   *Method:
	   *		it opens the file we want to write to and then it loops till the queue is finished. 
	   *		In the loop, it pops the front data of the queue and then writes it on the file.....
	   *
	   *Runtime: O(n).
	   *
	*/
	public static void uploadWaitingList(String fileName, Queue b) throws FileNotFoundException
	{
		PrintWriter out = new PrintWriter(fileName);
		
		while(true)
		{
			if(b.isEmpty()) { break; }
			else
			{
				Student a = b.dequeue();
				out.println(a.getFirstName());
				out.println(a.getLastName());
				out.println(a.getIDNo());
			}
		}	
		out.close();
	}

	/**
	   *Parameters: StudentBST, Student, ArrayList<Student>[]....
	   *
	   *Method:
	   *		First, it adds the student to the BST using insert() method and then it assigns the students at the index of their id's last two degits to the arraylist......
	   *
	   *Runtime: 
	   *		It has a runtime of O(log n).
	   *
	*/
	public static void addStudent(StudentBST b, Student s, ArrayList<Student>[] a)
	{
		b.insert(s);
		int index = lasttwo(s.getIDNo()) % 100;
		if(a[index] == null)
		{
			a[index] = new ArrayList<Student>();
		  	a[index].add(s);
	  	}
		else
		{
			a[index].add(s);
		}		
	}
	
	/**
	   *Parameters: StudentBST, Queue, ArrayList<Student>[]....
	   *
	   *Method:
	   *		First, it prompts the user to choose if they want to delete by id or name and then asks for that info.
	   *		if the student is not in the roster then it returns null
	   *		Else, if it's in the list then BST removes the student using remove() and ArrayList removes using the last two digits of student's id. 
	   *		At the end, if someone is waiting in the queue then it adds them to the Roster using addStudent().....
	   *
	   *Runtime: 
	   *		Method has a best case runtime O(1), average case runtime O(log N) and, worse case is O(n).
	   *
	*/
	public static void removeStudent(StudentBST b, Queue q, ArrayList<Student>[] a)
	{
		Student del = new Student();
		int option = Integer.parseInt(JOptionPane.showInputDialog("1)Remove by IDNo. \n2)Remove by Name \nChoose an Option:"));
		
		while(true)
		{	
			if(option == 1) { del = searchID(a); break; }
			else if(option == 2) { del = searchName(b); break; }
			else { option = Integer.parseInt(JOptionPane.showInputDialog("1)Remove by IDNo. \n2)Remove by Name \nChoose a VALID Option:")); }
		}
		
		
		if(del == null)
		{
			JOptionPane.showMessageDialog(null, "Unfortunataly, we cannot delete a student becuase he is not in the Roster.");
		}
		else
		{
			b.remove(del);
			a[lasttwo(del.getIDNo()) % 100].remove(del);
			
			if(!q.isEmpty())
			{
				Student s = q.dequeue();
				addStudent(b, s, a);
			}
			
			JOptionPane.showMessageDialog(null, "Student has been deleted from the roster and waiting student has been added");
		}		
	}

	/**
	   *Parameters: Student[], int, BNode....
	   *
	   *Method: 
	   *		it takes the root of the BST and then put them into the array in sorted order.
	   *		First, it goes through the left side of the tree, Copies the value and then the right side.
	   *		It used a inorder traversal of BST using recursion.....
	   *
	   *Returns: int.....
	   *
	   *Runtime:
	   *		TGhe runtime for this method is O(n) since we will be going through all the values.	
	   *
	*/
	public static int BSTtoArray(Student[] s, int length, BNode b)
	{	
		if(length <= 19)
		{
			if(b.getLeft() != null)
			{
				length = BSTtoArray(s, length, b.getLeft());
			}
			s[length++] = b.getData();
			if(b.getRight() != null)
			{	
				length = BSTtoArray(s, length, b.getRight());
			}
		}	
	    return length;
	}
	
	/**
	   *Parameters: BNode, String....
	   *
	   *Method: 
	   *		it takes the root of a BST and the id that is used to search.
	   *		Then, if the node is null then it returns null.
	   *		Else, it compares the id of the node's data to given id and if it is not equal then it searches the left side.
	   *		After searching the left side if the node is still not found then it searches the right side.
	   *		At the end, it returns the BNode if found or else returns null.....
	   *
	   *Returns: BNode or null.....
	   *
	   *Runtime:
	   *		It has the best runtime of O(1), average runtime of O(log n) if it only searches the left and, the worse runtime of O(n) if the value is far right.
	   *
	*/
	public static BNode search(BNode b, String id)
	{
		if(b != null)
		{
			if(b.getData().getIDNo().equals(id))
			{
				return b;
			}
			else
			{
				BNode foundNode = search(b.getLeft(), id);
	            
				if(foundNode == null) {
	                foundNode = search(b.getRight(), id);
	            }	    
	            return foundNode;
			}
		}
		else
		{
			return null;
		}
	}
	
	/**
	   *Parameters: Arraylist<Student>[]....
	   *
	   *Method:
	   *		it takes an array of arrylist and then prompts the user to provide the id they want to search.
	   *        Then, it searches the arraylist at the index of id's last two digits.
	   *        It returns the student if the id matches or else it returns null.....
	   *        
	   *Returns: Student or null.....
	   *
	   *Runtime:
	   *		It runs at O(1).
	   *
	*/
	public static Student searchID(ArrayList<Student>[] a)
	{		
		String id = JOptionPane.showInputDialog("Enter the ID No. of a Student:");
		
		for(Student s : a[lasttwo(id) % 100])
		{
			if(s.getIDNo().equals(id))
			{
				return s;
			}
		}		
		
		JOptionPane.showMessageDialog(null, "Student was not found in the Roster");
		return null;
	}
	
	/**
	   *Parameters: StudentBST....
	   *
	   *Method: 
	   *		it prompts the user to give students first and last name. Then, if the tree is empty then returns null.
	   *        Else, it loops around till it reaches the end of the tree. If the student is found within the loop then it returns that student or else it returns null.....
	   *
	   *Returns: Student or null.....      
	   *       
	   *Runtime:
	   *		Method has a best case runtime O(1) if the first element is what we are looking for, average case runtime O(log N) and, worse case is O(n) if the tree is sorted.
	*/
	public static Student searchName(StudentBST bst)
	{
		String a = JOptionPane.showInputDialog("Enter the First Name:");
		String b = JOptionPane.showInputDialog("Enter the Last Name:");
		
		if(bst.getRoot() == null) { return null; }
			
		BNode temp = bst.getRoot();
		while(temp != null)
		{
			if(temp.getData().getLastName().equals(b) && temp.getData().getFirstName().equals(a))
			{
				return temp.getData();
			}
			else if(temp.getData().getLastName().equals(b) && temp.getData().getFirstName().compareTo(a) > 0)
			{
				temp = temp.getLeft();
			}
			else if(temp.getData().getLastName().equals(b) && temp.getData().getFirstName().compareTo(a) < 0)
			{
				temp = temp.getRight();	
			}
			else if(temp.getData().getLastName().compareTo(b) > 0)
			{
				temp = temp.getLeft();
			}
			else if(temp.getData().getLastName().compareTo(b) < 0)
			{
				temp = temp.getRight();
			}
		}
		
		JOptionPane.showMessageDialog(null, "Student was not found in the Roster");
		return null;
		
	}
}


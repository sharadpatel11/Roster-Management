//Name
//Date
//Homework 6
//CS211 Lab

//This is the implementation file roster.cpp of the class Roster
//The interface for this class is in header file roster.h


#include <iostream>
#include <cstdlib>
#include "roster.h"

//Default Constructor
Roster::Roster()
{
	this->courseName = "CSCI";
	this->courseCode = "211";
	this->instructor = "Yosef Alayev";
	this->credits = 3;
	this->studentList = new Student * [this->capacity];
}

//4 Parameter Constructor
Roster::Roster(std::string cN, std::string cC, std::string ins, int cred)
{
	this->courseName = cN;
	this->courseCode = cC;
	this->instructor = ins;
	this->credits = cred;
	this->studentList = new Student * [this->capacity];

}

//Copy Constructor
Roster::Roster(const Roster& r)
{
	this->courseName = r.courseName;
	this->courseCode = r.courseCode;
	this->instructor = r.instructor;
	this->credits = r.credits;
	this->numStudents = r.numStudents;
	this->capacity = r.capacity;
	this->studentList = new Student * [this->capacity];
	Student* newStudent;
	for (int i = 0; i < this->numStudents; i++)
	{
		newStudent = new Student(*r.studentList[i]);
		studentList[i] = newStudent;
		newStudent = nullptr;
	}
}

//Destructor
Roster::~Roster()
{
	for (int i = 0; i < this->numStudents; i++)
	{
		delete studentList[i];
	}
	delete[] studentList;
}

//Accessors
std::string Roster::getCourseName() const { return this->courseName; }
std::string Roster::getCourseCode() const { return this->courseCode; }
std::string Roster::getInstructor() const { return this->instructor; }
int Roster::getCredits() const { return this->credits; }
int Roster::getNumStudents() const { return this->numStudents; }

//Returns the student in the array at the given index.
//If no student exists at the index, outputs error text to console and exits
Student Roster::getStudent(int index) const
{
	if (index < 0 || index >(MAX_CAPACITY - 1))
	{
		std::cout << "Error: Index out of bounds in delStudent function" << std::endl;
		exit(0);
	}
	else if (index > this->numStudents)
	{
		std::cout << "Error: There is no student at index " << index << std::endl;
		exit(0);
	}
	else
	{
		return *this->studentList[index];
	}
}

//Mutators
void Roster::setCourseName(std::string cN) { this->courseName = cN; }
void Roster::setCourseCode(std::string cC) { this->courseCode = cC; }
void Roster::setInstructor(std::string ins) { this->instructor = ins; }
void Roster::setCredits(int cred) { this->credits = cred; }

//Array Functions

//(1)
//Adds a student in the earliest available index.
//If there is no available space, outputs error text to console and exits
void Roster::addStudent(Student s)
{
	if (this->numStudents >= this->capacity)
	{
		grow();
	}
	Student* newStudent = new Student(s);
	this->studentList[numStudents] = newStudent;
	newStudent = nullptr;
	numStudents++;
}


void Roster::updateStudent(Student s, int index)
{
	Student* newStudent = new Student(s);
	this->studentList[index] = newStudent;
	newStudent = nullptr;
}

//(2)
//Removes the student at the given index, then shifts any succeeding elements down.
//If no student at the index, outputs error text to the console and exits
void Roster::delStudent(int index)
{
	if (index < 0 || index >(MAX_CAPACITY - 1))
	{
		std::cout << "Error: Index out of bounds in delStudent function" << std::endl;
		exit(0);
	}
	else if (index > this->numStudents)
	{
		std::cout << "Error: There is no student at index " << index << std::endl;
		exit(0);
	}
	else
	{
		numStudents--;
		delete this->studentList[index];
		for (int i = index; i < this->numStudents; i++)
		{
			*this->studentList[i] = *this->studentList[i + 1];
		}
	}
}

//(3)
//Checks the studentList for a student with matching first and last name.
//If the student exists in the array, returns the index in the array.
//Otherwise, returns -1.
int Roster::findStudent(std::string fName, std::string lName)
{
	int index = -1;
	for (int i = 0; i < this->numStudents; i++)
	{
		if (((*this->studentList[i]).getFirst() == fName) && ((*this->studentList[i]).getLast() == lName))
		{
			index = i;
			break;
		}
	}
	return index;
}

//(4)
//Outputs the studentList to the console.
void Roster::outputArray()
{
	this->sort();

	for (int i = 0; i < numStudents; i++)
	{
		std::cout << "****Student " << (i + 1) << "****" << std::endl;
		(*studentList[i]).output();
		std::cout << std::endl;
	}
	if (numStudents == 0) std::cout << "The Roster is empty" << std::endl;
}

const Student & Roster::operator[](int index)
{
	if (index < 0 || index > numStudents - 1)
	{
		std::cout << "Index out of bounds in operator[]" << std::endl;
		exit(0);
	}
	return *studentList[index];
}

Roster& Roster::operator=(const Roster & r)
{
	//Check to see if the calling object is also the argument by
	//comparing this memory addresses
	if (this != &r)
	{
		this->courseName = r.courseName;
		this->courseCode = r.courseCode;
		this->instructor = r.instructor;
		this->credits = r.credits;
		for (int i = 0; i < this->numStudents; i++) delete this->studentList[i];
		delete[] studentList;
		this->numStudents = r.numStudents;
		this->capacity = r.capacity;
		Student * *newList = new Student * [this->capacity];
		Student * newStudent;
		for (int i = 0; i < this->numStudents; i++)
		{
			newStudent = new Student(*r.studentList[i]);
			newList[i] = newStudent;
			newStudent = nullptr;
		}
		studentList = newList;
	}
	return *this;
}

std::ostream& operator <<(std::ostream & out, const Roster & r)
{
	out << "Course Name: " << r.courseName << std::endl
		<< "Course Code: " << r.courseCode << std::endl
		<< "Instructor: " << r.instructor << std::endl
		<< "Credits: " << r.credits << std::endl
		<< "Number of Students: " << r.numStudents << std::endl;
	for (int i = 0; i < r.numStudents; i++)
	{
		out << "*** Student " << (i + 1) << " ***\n";
		out << *r.studentList[i] << std::endl;
	}
	return out;
}

std::istream& operator >>(std::istream & in, Roster & r)
{
	in >> r.courseName >> r.courseCode >> r.instructor >> r.credits;
	return in;
}

void Roster::grow()
{
	this->capacity *= 2;
	Student** newList = new Student * [this->capacity];
	for (int i = 0; i < this->numStudents; i++)
	{
		newList[i] = studentList[i];
	}
	delete[] studentList;
	studentList = newList;
}

void Roster::sort() {
	int minIndex;

	for (int i = 0; i < numStudents - 1; ++i) {
		minIndex = i;
		for (int j = i + 1; j < numStudents; ++j) {
			if (studentList[j] < studentList[minIndex]) {
				minIndex = j;
			}
		}
		
		Student* s = studentList[minIndex];
		studentList[minIndex] = studentList[i];
		studentList[i] = s;
		s = nullptr;
	}
}
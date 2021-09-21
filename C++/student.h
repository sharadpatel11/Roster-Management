//Header File for Student class

#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Date.h"

class Student
{
private:
	//member variables
	std::string firstName, lastName, standing;
	Date dateOfBirth, dateOfMatriculation;
	int credits;
	double gpa;
	int studentId;

	//private member function to correct standing when credits change
	void correctStanding();

public:
	//constructors
	Student();
	Student(std::string fn, std::string ln, Date dob, Date dom, int c, double g, int sid);

	//mutators
	void setFirst(std::string);
	void setLast(std::string);
	void setDateOfBirth(Date);
	void setDateOfMatriculation(Date);
	void setCredits(int);
	void setGPA(double);
	void setStudentId(int);

	//accessors
	std::string getFirst();
	std::string getLast();
	Date getDateOfBirth();
	Date getDateOfMatriculation();
	std::string getStanding();
	int getCredits();
	double getGPA();
	int getStudentId();

	//console i/o functions
	void input();
	void output();

	//operator overload
	bool operator == (const Student& b);
	bool operator != (const Student& b);
	bool operator < (const Student& b);
	bool operator <= (const Student& b);
	bool operator > (const Student& b);
	bool operator >= (const Student& b);

	//cin and cout functions
	friend std::istream& operator >> (std::istream& in, Student& a);
	friend std::ostream& operator << (std::ostream& out, const Student& a);
};
#endif

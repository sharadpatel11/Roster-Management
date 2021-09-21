//This is the implementation file student.cpp of the class Student
//The interface for this class is in header file student.h


#include <iostream>
#include <cstdlib>
#include "student.h"
#include "Date.h"

Student::Student(std::string fn, std::string ln, Date dob, Date dom, int c, double g, int sid)
{
	firstName = fn;
	lastName = ln;
	dateOfBirth = dob;
	dateOfMatriculation = dom;
	credits = c;
	gpa = g;
	studentId = sid;
	correctStanding();
}

Student::Student()
{
	firstName = "John";
	lastName = "Doe";
	dateOfBirth = Date(01, 01, 1970);
	dateOfMatriculation = Date(05, 25, 1995);
	credits = 0;
	gpa = 4.0;
	studentId = 0;
}

void Student::correctStanding()
{
	if (credits < 0)
	{
		std::cout << "Illegal number of credits in Student object\n";
		exit(0);
	}
	int x = credits / 15;
	switch (x)
	{
	case 0: standing = "Lower Freshman";
		break;
	case 1: standing = "Upper Freshman";
		break;
	case 2: standing = "Lower Sophomore";
		break;
	case 3: standing = "Upper Sophomore";
		break;
	case 4: standing = "Lower Junior";
		break;
	case 5: standing = "Upper Junior";
		break;
	case 6: standing = "Lower Senior";
		break;
	default: standing = "Upper Senior";
	}
}

//Mutators
void Student::setFirst(std::string fn)
{
	firstName = fn;
}
void Student::setLast(std::string ln)
{
	lastName = ln;
}
void Student::setDateOfBirth(Date dob)
{
	dateOfBirth = dob;
}
void Student::setDateOfMatriculation(Date dom)
{
	dateOfMatriculation = dom;
}
void Student::setCredits(int c)
{
	credits = c;
	correctStanding();
}
void Student::setGPA(double g)
{
	gpa = g;
}
void Student::setStudentId(int sid)
{
	studentId = sid;
}

//Accessors
std::string Student::getFirst()
{
	return firstName;
}
std::string Student::getLast()
{
	return lastName;
}
Date Student::getDateOfBirth()
{
	return dateOfBirth;
}
Date Student::getDateOfMatriculation()
{
	return dateOfMatriculation;
}
std::string Student::getStanding()
{
	return standing;
}
int Student::getCredits()
{
	return credits;
}
double Student::getGPA()
{
	return gpa;
}
int Student::getStudentId()
{
	return studentId;
}

//Console I/O Functions
void Student::input()
{
	std::cout << "Enter the student's first name: ";
	std::cin >> firstName;
	std::cout << "Enter the student's last name: ";
	std::cin >> lastName;
	std::cout << "Enter the student's Date of Birth (Format: dd/mm/yyyy): ";
	std::cin >> dateOfBirth;
	std::cout << "Enter the student's Date of Matriculation (Format: dd/mm/yyyy): ";
	std::cin >> dateOfMatriculation;
	std::cout << "Enter the student's credit number: ";
	std::cin >> credits;
	std::cout << "Enter the student's GPA: ";
	std::cin >> gpa;
	std::cout << "Enter the student ID: ";
	std::cin >> studentId;
}
void Student::output()
{
	std::cout << "First Name: " << firstName << std::endl
		<< "Last Name: " << lastName << std::endl
		<< "Date of Birth: " << dateOfBirth << std::endl
		<< "Date of Matriculation: " << dateOfMatriculation << std::endl
		<< "Credits: " << credits << std::endl
		<< "Standing: " << standing << std::endl
		<< "GPA: " << gpa << " Student Id: " << studentId << std::endl;
}

bool Student::operator == (const Student& b)
{
	if (this->firstName == b.firstName && this->lastName == b.lastName
		&& this->studentId == b.studentId)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Student::operator != (const Student& b)
{
	return !(*this == b);
}

bool Student::operator < (const Student & b)
{
	char f1, f2, l1, l2;

	f1 = this->firstName.at(0);
	f2 = b.firstName.at(0);
	l1 = this->lastName.at(0);
	l2 = b.lastName.at(0);

	if (l1 < l2)
	{
		return true;
	}
	else if (f1 < f2)
	{
		return true;
	}
	else if (this->studentId < b.studentId)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Student::operator <= (const Student & b)
{
	if (*this == b || *this < b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Student::operator > (const Student & b)
{
	char f1, f2, l1, l2;

	f1 = this->firstName.at(0);
	f2 = b.firstName.at(0);
	l1 = this->lastName.at(0);
	l2 = b.lastName.at(0);

	if (l1 > l2)
	{
		return true;
	}
	else if (f1 > f2)
	{
		return true;
	}
	else if (this->studentId > b.studentId)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Student::operator >= (const Student & b)
{
	if (*this == b || *this > b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::istream& operator >> (std::istream & in, Student & a)
{
	std::cout << "Enter the student's first name: ";
	in >> a.firstName;
	std::cout << "Enter the student's last name: ";
	in >> a.lastName;
	std::cout << "Enter the student's Date of Birth (Format: dd/mm/yyyy): ";
	in >> a.dateOfBirth;
	std::cout << "Enter the student's Date of Matriculation (Format: dd/mm/yyyy): ";
	in >> a.dateOfMatriculation;
	std::cout << "Enter the student's credit number: ";
	in >> a.credits;
	a.correctStanding();
	std::cout << "Enter the student's GPA: ";
	in >> a.gpa;
	std::cout << "Enter the student Id: ";
	in >> a.studentId;

	return in;
}

std::ostream& operator << (std::ostream & out, const Student & a)
{
	std::cout << "First Name: ";
	out << a.firstName;
	std::cout << std::endl;

	std::cout << "Last Name: ";
	out << a.lastName;
	std::cout << std::endl;

	std::cout << "Date of Birth: ";
	out << a.dateOfBirth;
	std::cout << std::endl;

	std::cout << "Date of Matriculation: ";
	out << a.dateOfMatriculation;
	std::cout << std::endl;

	std::cout << "Credits: ";
	out << a.credits;
	std::cout << std::endl;

	std::cout << "Standing: ";
	out << a.standing;
	std::cout << std::endl;

	std::cout << "GPA: ";
	out << a.gpa;
	std::cout << std::endl;

	std::cout << "Student Id: ";
	out << a.studentId;
	std::cout << std::endl;

	return out;
}

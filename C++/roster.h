//Name
//Date
//Homework 6
//CS211 Lab

#ifndef ROSTER_H
#define ROSTER_H
#define MAX_CAPACITY 10
#include "student.h"

class Roster
{
public:
	//Constructors
	Roster();
	Roster(std::string, std::string, std::string, int);
	Roster(const Roster&);
	~Roster();

	//Accessors
	std::string getCourseName() const;
	std::string getCourseCode() const;
	std::string getInstructor() const;
	int getCredits() const;
	int getNumStudents() const;
	Student getStudent(int) const;

	//Mutators
	void setCourseName(std::string);
	void setCourseCode(std::string);
	void setInstructor(std::string);
	void setCredits(int);

	//Array Functions
	void addStudent(Student);
	void updateStudent(Student, int);
	void delStudent(int);
	int findStudent(std::string, std::string);
	void outputArray();

	//Operators
	const Student& operator[](int);
	Roster& operator=(const Roster&);
	void sort();
	friend std::ostream& operator <<(std::ostream&, const Roster&);
	friend std::istream& operator >>(std::istream&, Roster&);
private:
	std::string courseName, courseCode, instructor;
	int credits, numStudents = 0, capacity = 10;
	Student** studentList;

	void grow();
};
#endif
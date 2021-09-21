#include <iostream>
#include <string>
#include <fstream>
#include "student.h"
#include "roster.h"
#include "Date.h"

int rosterserach(Roster* r, int capacity, std::string cd);

int main()
{
	int capacity = 10;
	int nrofrosters = 0;

	Roster* r = new Roster[capacity];

	std::ifstream rosters;

	//to collect roster info
	std::string cn;
	std::string cc;
	std::string in;
	int cred;

	//to collect student info
	double gpa;
	int scred, sid, totalStudents = 0;
	int m, d, y, m2, d2, y2;
	std::string ln, fn, standing;
	Date bd;
	Date md;
	std::string waste;

	//to search for a roster
	std::string rcheck;
	int ind = 0;

	Student st;

	rosters.open("rosters.txt");

	while (!rosters.eof())
	{
		totalStudents = 0;

		std::getline(rosters, cn, '|');
		std::getline(rosters, cc, '|');
		rosters >> cred;
		rosters.ignore();
		std::getline(rosters, in, '|');
		rosters >> totalStudents;
		rosters.ignore();

		if (nrofrosters == capacity)
		{
			capacity *= 2;
			Roster* newList = new Roster[capacity];
			for (int i = 0; i < nrofrosters; i++)
			{
				newList[i] = r[i];
			}

			delete[] r;
			r = new Roster[capacity];
			r = newList;
		}

		Roster r2(cn, cc, in, cred);
		r[nrofrosters] = r2;

		for (int i = 0; i < totalStudents; i++)
		{
			std::getline(rosters, fn, '|');
			std::getline(rosters, ln, '|');

			rosters >> sid;
			rosters.ignore();

			std::getline(rosters, standing, '|');

			rosters >> scred;
			rosters.ignore();

			rosters >> gpa;
			rosters.ignore();

			rosters >> m;
			rosters.ignore();

			rosters >> d;
			rosters.ignore();

			rosters >> y;
			rosters.ignore();

			rosters >> m2;
			rosters.ignore();

			rosters >> d2;
			rosters.ignore();

			rosters >> y2;
			rosters.ignore();

			Date bd(m, d, y);
			Date md(m2, d2, y2);

			Student st(fn, ln, bd, md, scred, gpa, sid);
			r[nrofrosters].addStudent(st);
		}

		getline(rosters, waste);
		nrofrosters++;
	}

	rosters.close();

	std::ifstream myfile;
	//std::ofstream rosters;

	myfile.open("DataBase.txt");

	if (myfile.fail())
	{
		std::cout << "File did not open" << std::endl;
	}

	std::cout << "--------------------Welcome to the Roster Managament Program--------------------" << std::endl;

	std::cout << std::endl;

	char a;
	std::cout << "Please choose (A)Superviser Mode, (B)User Mode or (C)Exit: ";
	std::cin >> a;

	string check;
	myfile >> check;
	myfile.close();

	while (a < 'A' || a > 'C')
	{
		std::cout << "TRY AGAIN: ";
		std::cin >> a;
	}

	do
	{
		if (a == 'A')
		{
			string up;
			std::cout << "Please enter the username and password for the superviser mode access(Format:username/password): ";
			std::cin >> up;

			if (up == check)
			{
				std::cout << std::endl;
				std::cout << "Access Granted. Entering Superviser Mode....." << std::endl;
				std::cout << std::endl;
			}
			else
			{
				std::cout << std::endl;
				std::cout << "wrong username and password for Superviser. Access denied." << std::endl;

				while (up != check)
				{
					std::cout << "TRY AGAIN: ";
					std::cin >> up;
				}

				std::cout << "Entering Superviser mode...." << std::endl;
				std::cout << std::endl;
			}

			if (up == check)
			{
				std::cout << "                     Superviser Mode Options:" << std::endl;
				std::cout << "1)Create a new Roster (that will be stored in a growable array of Rosters in your main program)" << std::endl;
				std::cout << "2)Drop a Roster (selected by course number)" << std::endl;
				std::cout << "3)Display Roster information (selected by course number)" << std::endl;
				std::cout << "4)Disply all Rosters (in your system)" << std::endl;
				std::cout << "5)Select a Roster to perform Student operations" << std::endl;

				std::cout << std::endl;

				int option;
				std::cout << "Enter a number of Superviser Mode option to operate: ";
				std::cin >> option;
				cin.ignore();

				while (option < 1 || option > 5)
				{
					std::cout << "TRY AGAIN: ";
					std::cin >> option;
				}

				if (option == 1)
				{
					std::cout << "Enter the Course Name: ";
					std::getline(cin, cn);
					std::cout << "Enter the Course Code: ";
					std::getline(cin, cc);
					std::cout << "Enter the Instructor's Name: ";
					std::getline(cin, in);
					std::cout << "Enter the Amount of Credits: ";
					std::cin >> cred;

					std::cout << "Enter the Amount of Students in class: ";
					std::cin >> totalStudents;

					std::cout << std::endl;

					if (nrofrosters == capacity)
					{
						capacity *= 2;
						Roster* newList = new Roster[capacity];
						for (int i = 0; i < nrofrosters; i++)
						{
							newList[i] = r[i];
						}

						delete[] r;
						r = new Roster[capacity];
						r = newList;
					}

					r[nrofrosters] = Roster(cn, cc, in, cred);

					Student s1;
					for (int i = 0; i < totalStudents; i++)
					{
						std::cout << "Enter Student No." << i + 1 << "'s Information: " << std::endl;
						std::cin >> s1;
						r[nrofrosters].addStudent(s1);
						std::cout << std::endl;
					}

					nrofrosters++;

					std::cout << "Roster successfully added" << std::endl;
				}
				else if (option == 2)
				{
					std::cout << "Please Enter a Course Code of a Roster that you want to drop: ";
					cin >> rcheck;

					ind = rosterserach(r, nrofrosters, rcheck);

					if (ind != -1)
					{
						nrofrosters--;
						r[ind] = Roster();
						for (int i = ind; i < nrofrosters; i++)
						{
							r[i] = r[i + 1];
						}
					}

					std::cout << "Roster Dropped" << std::endl;
				}
				else if (option == 3)
				{
					std::cout << "Enter the Course Code of the Roster you want to display: ";
					cin >> rcheck;

					std::cout << std::endl;
					ind = rosterserach(r, nrofrosters, rcheck);

					if (ind != -1)
					{
						std::cout << r[ind];
						std::cout << std::endl;
					}
				}
				else if (option == 4)
				{
					std::cout << std::endl;

					for (int i = 0; i < nrofrosters; i++)
					{	
						std::cout << "********Roster No." << i + 1 << std::endl;
						std::cout << r[i] << std::endl;
					}
				}
				else if (option == 5)
				{
					char c1;

					std::cout << std::endl;
					std::cout << "a)Insert new Student to a Roster" << std::endl;
					std::cout << "b)Remove a Student from a Roster" << std::endl;
					std::cout << "c)Update a Student in a Roster" << std::endl;
					std::cout << "d)List all Students in one Roster in sorted order" << std::endl;

					std::cout << "Choose one of the Student operation from above: ";
					std::cin >> c1;

					std::cout << "Enter the Course Code of the Roster that you want to perform Student operations on: ";
					std::cin >> rcheck;

					std::cout << std::endl;
					ind = rosterserach(r, nrofrosters, rcheck);
					
					while (c1 < 'a' || c1 > 'd')
					{
						std::cout << "TRY AGAIN: ";
						std::cin >> c1;
					}

					if (c1 == 'a')
					{		
						if (ind != -1)
						{
							std::cout << "Enter the Student's Information..." << std::endl;
							std::cin >> st;

							r[ind].addStudent(st);

							std::cout << "Student Added to the Roster" << std::endl;
						}
					}
					else if (c1 == 'b')
					{
						if (ind != -1)
						{
							std::cout << "Enter the Student's First name: ";
							std::cin >> fn;
							std::cout << "Enter the Student's Last name: ";
							std::cin >> ln;

							int sind = r[ind].findStudent(fn, ln);

							r[ind].delStudent(sind);

							std::cout << "Student Deleted from the Roster" << std::endl;
						}
					}
					else if (c1 == 'c')
					{
						if (ind != -1)
						{
							std::cout << "Enter a Student of the student you want to Update" << std::endl;
							std::cout << "Enter the Student's First name: ";
							std::cin >> fn;
							std::cout << "Enter the Student's Last name: ";
							std::cin >> ln;

							int sind = r[ind].findStudent(fn, ln);

							std::cout << std::endl;

							std::cout << "Now enter the updated student info" << std::endl;
							std::cin >> st;

							r[ind].updateStudent(st, sind);

							std::cout << "Student Successfully Updated" << std::endl;
						}
					}
					else if (c1 == 'd')
					{
						if (ind != -1)
						{
							std::cout << std::endl;
							r[ind].outputArray();
						}
					}
				}
			}
		}
		else
		{
			std::cout << "Entering User mode....." << std::endl;
			std::cout << std::endl;

			std::cout << "               User Mode Options:" << std::endl;
			std::cout << "1)Select a Roster to perform a following options:" << std::endl;
			std::cout << "   a)Insert new Student to a Roster" << std::endl;
			std::cout << "   b)Remove a Student from a Roster" << std::endl;
			std::cout << "   c)Update a Student in a Roster" << std::endl;
			std::cout << "   d)List all Students in one Roster in sorted order" << std::endl;

			std::cout << std::endl;

			std::cout << "Choose one of the option from above: ";

			char c2;

			std::cin >> c2;
			cin.ignore();

			std::cout << "Enter the Course Code of the Roster that you want to perform these operations on: ";
			cin >> rcheck;
			cin.ignore();

			std::cout << std::endl;
			ind = rosterserach(r, nrofrosters, rcheck);

			while (c2 < 'a' || c2 > 'd')
			{
				std::cout << "TRY AGAIN: ";
				std::cin >> c2;
			}

			if (c2 == 'a')
			{
				if (ind != -1)
				{
					std::cout << "Enter the Student's Information..." << std::endl;
					std::cin >> st;

					r[ind].addStudent(st);

					std::cout << "Student Added to the Roster" << std::endl;
				}
			}
			else if (c2 == 'b')
			{
				if (ind != -1)
				{
					std::cout << "Enter the Student's First name: ";
					std::cin >> fn;
					std::cout << "Enter the Student's Last name: ";
					std::cin >> ln;

					int sind = r[ind].findStudent(fn, ln);

					r[ind].delStudent(sind);

					std::cout << "Student Deleted from the Roster" << std::endl;
				}
			}
			else if (c2 == 'c')
			{
				if (ind != -1)
				{
					std::cout << "Enter a Student of the student you want to Update" << std::endl;
					std::cout << "Enter the Student's First name: ";
					std::cin >> fn;
					std::cout << "Enter the Student's Last name: ";
					std::cin >> ln;

					int sind = r[ind].findStudent(fn, ln);

					std::cout << std::endl;

					std::cout << "Now enter the updated student info" << std::endl;
					std::cin >> st;

					r[ind].updateStudent(st, sind);

					std::cout << "Student Successfully Updated" << std::endl;
				}
			}
			else if (c2 == 'd')
			{
				if (ind != -1)
				{
					std::cout << std::endl;
					r[ind].outputArray();
				}
			}
		}

		std::cout << std::endl;

		std::cout << "Please choose (A)Superviser Mode, (B)User Mode or (C)Exit: ";
		std::cin >> a;

		while (a < 'A' || a > 'C')
		{
			std::cout << "TRY AGAIN: ";
			std::cin >> a;
		}

	}while (a != 'C');

	std::ofstream output;
	output.open("rosters.txt", std::ofstream::trunc);

	if (output.good())
	{
		for (int i = 0; i < nrofrosters; i++)
		{
			output << r[i].getCourseName() << "|" << r[i].getCourseCode() << "|" << r[i].getCredits() << "|" << r[i].getInstructor()
			<< "|" << r[i].getNumStudents() << "\n";

			for (int j = 0; j < r[i].getNumStudents(); j++)
			{
				output << r[i].getStudent(j).getFirst() << "|" << r[i].getStudent(j).getLast() << "|" << r[i].getStudent(j).getStudentId() << "|" << r[i].getStudent(j).getStanding() << "|"
					<< r[i].getStudent(j).getCredits() << "|" << r[i].getStudent(j).getGPA() << "|" << r[i].getStudent(j).getDateOfBirth().getMonthNum() << "/"
					<< r[i].getStudent(j).getDateOfBirth().getDay() << "/" << r[i].getStudent(j).getDateOfBirth().getYear() << "|"
					<< r[i].getStudent(j).getDateOfMatriculation().getMonthNum() << "/" << r[i].getStudent(j).getDateOfMatriculation().getDay() << "/"
					<< r[i].getStudent(j).getDateOfMatriculation().getYear() << "\n";
			}

			if (i < nrofrosters - 1)
			{
				output << "\n";
			}
		}
	}
	else
	{
		std::cout << "Roster file did not open and it wasn't updated" << std::endl;
	}
	output.close();

	std::cout << std::endl;
	std::cout << "-----------------File Saved and now exiting from the program......." << std::endl;

	delete[] r;

	return 0;
}

int rosterserach(Roster* r, int capacity, std::string cd)
{
	for (int i = 0; i < capacity; i++)
	{
		if (r[i].getCourseCode() == cd)
		{
			return i;
		}
	}

	std::cout << "Roster can't be found" << std::endl;
	return -1;
}
/*
 * Main.cpp
 *
 *  Created on: May 30, 2017
 *      Author: 293359
 */

//Bunch of imports
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* HashTable by Kevin Jin. A storage system for a list of students.
 * Takes in the inputs "ADD", "DELETE", "PRINT", "RANDOM", or "QUIT".
 * "ADD" allows one to enter the parameters for a new student.
 * "DELETE" allows one to delete a student using their ID.
 * "PRINT" allows one to print the current list of students.
 * "RANDOM" allows one to add a specified number of randomly-generated students to the hash table.
 * "QUIT" works as generally advertised.
 * Please enter valid inputs or the code may crash unexpectedly!
 * The hash function: Add the ASCII values of the first name, add double the ASCII vlaues of the second name,
 * add the ID, and divide by size.
 */

using namespace std;

//The Student class. Each Student object stores the parameters for a student.
struct Student {
	//These arrays and variables store values for the student.
	char firstName[80];
	char lastName[80];
	int id;
	float gpa;
	//TODO Maybe try adding <Student* next;> and initialize it as NULL in like main or something, this might make it chainable.
};

//Declare functions
void addStudent(Student** hashTable, int size);
void printOut(Student** hashTable, int size);
void deleteStudent(Student** hashTable, int size);
void randomStudents(Student** hashTable, int size);

//Main class. Takes in inputs and does stuff with it.
int main() {
	srand(time(NULL));
	char input;
	Student** hashTable = new Student*[100];
	for (int i = 0; i < 100; i++) {
		hashTable[i] = NULL;
	}
	int size = 100;
	bool running = true;

	//While quit has not been called:
	while (running) {
		cout << "Please type \"ADD\", \"PRINT\", \"DELETE\", \"RANDOM\", or \"QUIT\" as commands. Single-letter inputs will work too." << endl << "Input: ";
		cout << setprecision(2) << fixed;
		//Takes in input then determines what the input was and calls the corresponding function.
		cin >> input;
		cin.ignore(256, '\n');
		if (input == 'a' || input == 'A') {
			addStudent(hashTable, size);
		}
		else if (input == 'p' || input == 'P') {
			printOut(hashTable, size);
		}
		else if (input == 'd' || input == 'D') {
			deleteStudent(hashTable, size);
		}
		else if (input == 'r' || input == 'R') {
			randomStudents(hashTable, size);
		}
		else if (input == 'q' || input == 'Q') {
			cout << "Quitting..." << endl << "Program terminated. Thank you for your time.";
			running = false;
		}
		else {
			cout << "That input isn't valid. Please try again." << endl;
		}

	}
}

void addStudent(Student** hashTable, int size) {
	Student* newStudent = new Student;
	cout << "Please enter the first name of the student." << endl << "First name: ";
	cin >> newStudent->firstName;
	cout << "Please enter the last name of the student." << endl << "Last name: ";
	cin >> newStudent->lastName;
	cout << "Please enter the student ID." << endl << "Student ID: ";
	cin >> newStudent->id;
	cout << "Please enter the student\'s GPA (between 0 and 10, exclusive)." << endl << "Student\'s GPA: ";
	cin >> newStudent->gpa;
	cin.ignore();
	cout << setprecision(2) << fixed << endl;
	//TODO Do the hash function here to add it to the hash table. For now just add it into the first empty space.
	//TODO Remove the temporary stuff below
	for (int i = 0; i < 100; i++) {
		if (hashTable[i] == NULL) {
			hashTable[i] = newStudent;
			cout << "The student " << newStudent->firstName << " " << newStudent->lastName << " was successfully added." << endl;
			return;
		}
	}
	cout << "Fatal: Hash Table is full!" << endl;
	//TODO Temp stuff ends here
}

void printOut(Student** hashTable, int size) {
	if (hashTable[0] == NULL) {
		cout << "There are no students registered. You can add some with the \"ADD\" command." << endl << endl;
		return;
	}
	for (int i = 0; i < 100; i++) {
		if (hashTable[i] == NULL) {
			continue;
		}
		Student* temp = hashTable[i];
		cout << i + 1 << ".\tName: " << temp->lastName << ", " << temp->firstName << "\t\tID: " << temp->id << "\t\tGPA: " << temp->gpa << endl;
	}
}
void deleteStudent(Student** hashTable, int size) {

}
void randomStudents(Student** hashTable, int size) {
	cout << "How many random students would you like to generate?" << endl << "Num: ";
	int num;
	cin >> num;
	int largestId = -1;
	for (int i = 0; i < size; i++) {
		if (hashTable[i]->id > largestId) largestId = hashTable[i]->id;
	}
	ifstream firstNames ("firstNames.txt");
	ifstream lastNames ("lastNames.txt");
	for (int i = 0; i < num; i++) {
		Student* newStudent = new Student;
		int randFirst = rand() % 100;
		int randLast = rand() % 100;
		float gpa = rand() % 10;
		int id = ++largestId;
		char newfirstName[80];
		char newlastName[80];
		for (int i = 0; i < 100; i++) {
			if (i <= randFirst) {
				firstNames.getline(newfirstName, 80);
			}
			if (i <= randLast) {
				lastNames.getline(newlastName, 80);
			}
		}
		//TODO Oops, use strcpy here!!!
		newStudent->firstName = newfirstName;
		newStudent->lastName = newlastName;
		newStudent->gpa = gpa;
		newStudent->id = id;
		//TODO Placeholder insert
		for (int i = 0; i < 100; i++) {
				if (hashTable[i] == NULL) {
					hashTable[i] = newStudent;
					cout << "The student " << newStudent->firstName << " " << newStudent->lastName << " was successfully added." << endl;
					return;
				}
			}
		//TODO End of placeholder
	}
}

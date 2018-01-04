#include "dateType-ryanKane.h"
#include <string>

using namespace std;

class patientType
{

public:
	patientType();
	void setPatientInfo(int newID, string fName, string lName, dateType newCheckIn, dateType newCheckOut);
	void printPatient();
	int getID();
	//Note that these get functions are needed to print out a patient information in a CSV.
	string getFirst();
	string getLast();
	dateType getCheckIn();
	dateType getCheckOut();
	bool operator==(const patientType&) const;
	bool operator!=(const patientType&) const;
	bool operator>(const patientType&) const;
	bool operator<(const patientType&) const;
	bool operator<=(const patientType&) const;

private:
	friend ostream& operator<< (ostream&, const patientType&);
	int id;
	string firstName;
	string lastName;
	dateType checkIn;
	dateType checkOut;
};

patientType::patientType()
{
	id = 0;
	firstName = "";
	lastName = "";
	//The default constructor for the dateType variables are invoked automatically.
}

void patientType::setPatientInfo(int newID, string fName, string lName, dateType newCheckIn, dateType newCheckOut) //Populate the member variables for a patient.
{
	id = newID;
	firstName = fName;
	lastName = lName;
	checkIn = newCheckIn;
	checkOut = newCheckOut;
}

int patientType::getID() //This will be used in the patientList function to locate items in the search function.
{
	return id;
}

string patientType::getFirst()
{
	return firstName;
}

string patientType::getLast()
{
	return lastName;
}

dateType patientType::getCheckIn()
{
	return checkIn;
}

dateType patientType::getCheckOut()
{
	return checkOut;
}
ostream& operator<< (ostream& osObject, const patientType& patient) //Overload the operator so that the patient's information can easily be printed in the patientListType implementation.
{
	//Format the output for a patient object by overloading the stream insertion operator.
	osObject << "Name: " << patient.firstName << " " << patient.lastName << endl;
	osObject << "ID: " << patient.id << endl;
	osObject << "Check-in date: " << patient.checkIn << endl;
	osObject << "Check-out date: " << patient.checkOut << endl;
	osObject << "\n";
	return osObject;
}

//Overload five of the comparison operators that are needed to compare items in the search and isnert functions of the circularLinkedList class.
bool patientType:: operator>(const patientType& otherPt) const 
{
	if (id > otherPt.id)
	{
		return true;
	}
	else
		return false;
}

bool patientType:: operator==(const patientType& otherPt) const 
{
	if (id == otherPt.id)
	{
		return true;
	}
	else
		return false;
}
bool patientType:: operator!=(const patientType& otherPt) const
{
	if (id != otherPt.id)
	{
		return true;
	}
	else
		return false;
}

bool patientType:: operator<(const patientType& otherPt) const
{
	if (id < otherPt.id)
	{
		return true;
	}
	else
		return false;
}

bool patientType:: operator<=(const patientType& otherPatient) const
{
	if (id <= otherPatient.id)
	{
		return true;
	}

	else
	{
		return false;
	}
}

//This function is not likely to be used in the implementation due to overoading the stream insertion operator. It was still created as it was requested in the directions.
void patientType::printPatient()
{
	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "ID: " << id << endl;
	cout << "Check-in date: " << checkIn << endl;
	cout << "Check-out date: " << checkOut << endl;
	cout << "\n";
}
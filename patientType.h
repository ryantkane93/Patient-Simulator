#include <iostream>

using namespace std;

class patientType
{
private:
	int arrivalTime;
	int priority; //Where one is the highest priority and five is the lowest.
	friend ostream& operator<< (ostream&, const patientType&); //Prints the priority first followed by the arrival time.

public:
	patientType(); //Default constructor
	patientType(int pr, int arrival); //Parameterized constructor
	bool operator < (const patientType& otherPatient);
	bool operator > (const patientType& otherPatient);
	int getArrivalTime(); //Required to print patient data into the original input file in an inverse order of the overloaded stream insertion operator.
	int getPriority(); //Required to print patient data into the original input file in an inverse order of the overloaded stream insertion operator.
};

patientType::patientType()
{
	patientType(0, 0); //Initializes a patientType object.
}

patientType::patientType(int pr, int arrival)
{
	arrivalTime = arrival;
	priority = pr;
}

bool patientType::operator < (const patientType& otherPatient)
{
	//A patient is thought to be "less than" another patient if its priority number is a higher.

	if (priority == otherPatient.priority)
	{
		if (arrivalTime > otherPatient.arrivalTime) //If two patient's priorities are equal, the patient who arrived first should be helped. 
		{
			return true; //The patient with the lowest int value for arrival time would be helped first.
		}
		else
		{
			return false;
		}
	}
	if (priority > otherPatient.priority) //Since 1 is the highest priority and 5 is the lowest, a patient is "less than" another patient if their int value is higher.
	{
		return true;
	}
	else //If the patient has a lower int value for priority, they should be serviced first, therefore return false.
		return false;
}

bool patientType::operator >(const patientType& otherPatient)
{
	if (priority == otherPatient.priority)
	{
		if (arrivalTime < otherPatient.arrivalTime) //If two patient's priorities are equal, the patient who arrived first should be helped. 
		{
			return true; //The patient with the lowest int value for arrival time would be helped first.
		}
		else
		{
			return false;
		}
	}

	if (priority < otherPatient.priority) //Since 1 is the highest priority and 5 is the lowest, a patient is "greater than" another patient if their int value is lower.
	{
		return true;
	}
	else
		return false;
}
ostream& operator<< (ostream& osObject, const patientType& patient) //Overload the operator so that the patient's information can easily be printed in the patientListType implementation.
{
	//Format the output for a patient object by overloading the stream insertion operator.
	osObject << patient.priority <<"," << patient.arrivalTime;
	return osObject;
}
int patientType::getArrivalTime()
{
	return arrivalTime;
}

int patientType::getPriority()
{
	return priority;
}
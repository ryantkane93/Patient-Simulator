#include <iostream>

using namespace std;

class dateType{

public:
	dateType(); //Default constructor
	void setDate(int m, int d, int y);
	void printDate();

private:
	friend ostream& operator<< (ostream&, const dateType&);
	int month;
	int day;
	int year;
};

dateType::dateType() //Initialize the date to the January 1st, 2015.
{
	month = 1;
	day = 1;
	year = 2015;
}

void dateType::setDate(int m, int d, int y)
{
	// The lowest is set for 1995 under the assumptions that appointments in the last 20 years are kept on record.
	if (y >= 1995 && y <= 2016) //Make sure that the year is not a negative number. Since the max year will be used for checkout, we can assume that the upper-bound is 2016 (for future appointments).
	{
		year = y; //Change the year value.
	}
	else //Do not change the year value.
	{
		cout << "The year for this date was not changed and will remain the same value. Please try again while entering a valid value for the year." << endl;
	}

	if (m <= 12 && m >= 1) //Assure the the value for the year is a valid.
	{
		month = m;
	}
	else
	{
		cout << "The month entered is invalid and was not changed and will remain the same value. Please try again while entering a number from 1-12." << endl;
	}

	if (d >= 1 || d <= 31) //The day value is within range.
	{
		if (month == 9 || month == 4 || month == 6 || month == 11) //Check for months that only have thirty days.
		{
			if (d == 31) //Don't change the day if the month only has thirty days.
			{
				cout << "The day you have entered is invalid for this month and will remain the same value. Please be sure that the month has thirty one days in it." << endl;
			}

			else //The date is O.K. to change.
			{
				day = d;
			}
		}

		else if (month == 2 && year % 4 == 0) //If the month is February and it is a leap year, only accept 1-29.
		{
			if (d > 29)
			{
				cout << "The day you have entered is invalid for this month and will remain the same value. Please note that February has 29 days during a leap year." << endl;
			}
			else
			{
				day = d;
			}
		}

		else if (month == 2 && year % 4 != 0) //If the month is February and it isn't a leap yar, accept 1-28.
		{
			if (d > 28)
			{
				cout << "The day you have entered is invalid for this month and was remain the same value. Please note that February only has 28 days." << endl;
			}

			else
			{
				day = d;
					
			}
		}
		else //The month has 31 days and therefore can be entered.
		{
			day = d;
		}
			
	}
}

ostream& operator<< (ostream& osObject, const dateType& dateType) //Overload the stream insertion operator so that the date can easily be printed when class objects are used in the patientListType implementation.
{
	osObject <<dateType.month << "/" << dateType.day << "/" << dateType.year; //Format the output so that the date object is printed with each value seperated by a comma.
	return osObject;

}

void dateType::printDate()
{
	cout << month << "/" << day << "/" << year << endl;
}
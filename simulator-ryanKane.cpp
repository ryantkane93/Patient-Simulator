#include"patientListType-ryanKane.h"
#include <fstream>

//Function Prototypes
dateType extractDate(ifstream& fileIn); //Function extracts the date written in "m/d/yyyy" format in the file and places it into a date object.

int main()
{
	int choice = 0; //Int variable used to select menu options.
	patientListType testList;
	ifstream fileIn;
	fileIn.open("F:\\patientList.csv"); //Open the CSV containning the patients.
	if (fileIn)
	{
		cout << "List of patients successfully loaded!" << endl;
	}
	while (fileIn.good()) //While the fiile has info in it, continue loading patients.

	{
		int newID; //Declare a variable to hold an ID from the file.
		fileIn >> newID; //Extract the ID from the file.
		fileIn.ignore(1); //Ignore the comma.
		string first, last; //Declare two string variables to extract the name.
		getline(fileIn, first, ','); //Extract the first name and ignore the comma.
		getline(fileIn, last, ','); //Extract the last name and ignore the comma.

		dateType inDate = extractDate(fileIn); //Call the extract function to load the check-in date into a dateType object.
		fileIn.ignore(1); //Ignore the comma in between the dates.
		dateType outDate = extractDate(fileIn); //Call the extract function to load the check-out date into a dateType object.
		patientType newPatient; //Declare a new patient object to hold the new informaton.
		newPatient.setPatientInfo(newID, first, last, inDate, outDate); //Populate the patientType object with the extracted information.
		testList.insertItem(newPatient); //Add the patient to the list.
	}
	fileIn.close(); //Close the file once all of the data has been read.
	do
	{
		//Print out a menu of options for the user.
		cout << "Please select one of the following menu options:" << endl;
		cout << "1. Print patients" << endl;
		cout << "2. Add a new patient" << endl;
		cout << "3. Delete a patient" << endl;
		cout << "4. Search for a patient" << endl;
		cout << "5. Exit the menu" << endl;
		cin>>choice;

		switch (choice)
		{
			case 1:
			{
				testList.printList();
				break;
			}
			case 2:
			{
				testList.insertNewPatient();
				break;
			}
			case 3:
			{
				int id;
				cout << "Insert the ID of the patient that you wish to remove: " << endl;
				cin >> id;
				testList.deleteItem(id);
				break;
			}
			case 4:
			{
				int id;
				cout << "Insert the ID of the patient that you wish to search for: " << endl;
				cin >> id;
				testList.searchList(id);
				break;
			}
			case 5:
			{
				break;
			}
			default:
			{
				cout << "You have entered an incorrect menu option. Please only enter a number from 1-5." << endl;
				break;
			}


		}
	} 
	while (choice != 5);

	//Before the program terminates open a file to write the list into.
	ofstream fileOut;
	fileOut.open("F:\\patientOut.csv");
	if (fileOut)
	{
		cout << "Output file successfully loaded!" << endl;
		cout << "Writing patients to a CSV file ..." << endl;
	}
	testList.printToCSV(fileOut); //Call the function in the patientList type that prints the nodes to an output file.
	fileOut.close(); //Close the output file.
	cout << "Patients information was successfully saved!" << endl;
	system("pause");
	return 0;
}

dateType extractDate(ifstream& fileIn)
{
	int inMonth, inDay, inYear; //Declare three integers to hold each parameter of the date.
	fileIn >> inMonth; //Input the month from the file into the variable.
	fileIn.ignore(1); //Ignore the slash in between the month and the day.
	fileIn >> inDay; //Input the day from the file into a variable.
	fileIn.ignore(1); //Ignore the slash in between the month and year.
	fileIn >> inYear; //Extract the year from the file.
	dateType newDate; //Declare a new dateType object to hold the date parameters.
	newDate.setDate(inMonth, inDay, inYear); //Load the date parameters into the object.
	return newDate; //Return the date object so that it an be stored in the patientType object in main.
}
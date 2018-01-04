#include "patientType-ryanKane.h"
#include "circularLinkedListADT.h"
#include <fstream>

class patientListType : public circularLinkedListType<patientType> //Class inherits the circularLinkedList type using objects of patientType
{
public:
	patientListType();

	bool searchList(int id); 
	//Overrride the search list function from the base class to search by ID and then print the element that is found.
	//Note that the searchList function remained a bool to be properly overrided and also since its bool return type is needed for the deleteItem function to work properly.

	void deleteItem(int id); 
	//Override the remove item function from the base class to search for a patient by ID and then delete that item if it is found.
	
	void insertNewPatient(); 
	//Prompts the user to enter patient information in the function and then adds that patient to the linked list.

	void printList(); 
	//Override the printList function from the derived class to assure proper formatting.

	void printToCSV(ofstream& fileOut);
	//Takes a filestream output variable and populates it with the patient information in a CSV format.

	~patientListType();

private:
patientType getNewPatient(); 
	//Prompts the user to enter in the information for a patient that will be added to the list and then return these parameters as an object of patientType.
	//This primarily used to insert a new patient into the list.
};

patientListType::patientListType() //The default constructor of the base class is called automatically. This was included for good practice.
{
	circularLinkedListType();
}

patientListType::~patientListType()
{
	deleteList(); //Call the deleteList function that acts as the destructor in the base class. This should be called automatically when the object
	//goes out of scope, but was included for good practice.
}

void patientListType::printList() //Modify the code from the printList function of the derived class so that the output is formatted for larger amounts of data.
{
	if (isEmpty()) //Check if the list is empty or not.
		cout << "The list is empty and cannot be printed!" << endl; //Output a message and perform no further action if the list is empty.

	else //The list isn't empty and therefore can be printed.
	{
		nodeType<patientType> * temp;
		temp = first; //Point to the first element.
		cout << temp->info; //Output the first element.
		while (temp->link != first) //Traverse the length of the linked list and output each element.
		{
			temp = temp->link; //Move to the next node.
			cout << temp->info; //Output the node and a space for formatting.
		}
		cout << endl;
	}
}

bool patientListType::searchList(int id) //Search the patient list by ID and then print the patients information if it is found.
{
	if (isEmpty()) //The list is empty and therefore cannot contain the element.
	{
		cout << "The patient was not found in the list because it is empty!" << endl;
		return false;
	}

	else
	{
		if (first->info.getID() == id) //The item is contained in the head and therefore is found.
		{
			cout << "Patient found! Printing out their information..." << endl;
			cout << "\n";
			cout << first->info;
			return true;
		}

		//The list is not empty and the item did not match the first node.
		nodeType<patientType> *temp;
		temp = first;
		while (temp->link != first) //Terminate the loop if the last item is found or if the last element is reached.
		{
			temp = temp->link; //Traverses the list.
			if (temp->info.getID() == id) //If the item is found print it out or return true.
			{
				cout << "Patient found! Printing out their information..." << endl;
				cout << temp->info;
				return true;
			}
		}
		cout << "The patient is not in the list!" << endl;
		return false;
	}
}

void patientListType::deleteItem(int id) //Searches for and deletes a patient in the list when given an ID.
{
	if (searchList(id)) //The item is somewhere in the linked list and the list is not empty.
	{
		cout << "The patient profile above was retrieved for this ID number. This patient will be deleted!" << endl;
		nodeType<patientType> *temp;
		temp = first;
		if (first->info.getID() == id && elementCount>1) //If the item is located at the head of the linked list but it is not the last element in the list.
		{
			while (temp->link != first) //Traverse the list to find the last element.
			{
				temp = temp->link;
			}
			temp->link = first->link; //Link the last element to the second element in the list to maintain circularity.
			temp = first; //Temporarily point to first.
			first = first->link; //Move the first pointer to the second element in the list.
			delete temp; //Delete the original first node.
			elementCount--;
		}
		else if (first->info.getID() == id && elementCount == 1) //If there is only one element in the list.
		{
			cout << "Removing the last element in the list!" << endl;
			deleteList();
		}
		else //If the element is found, but is not the first item. and is not the only item in the list.
		{
			nodeType<patientType> *remove;
			while (temp->link->info.getID() != id) //Traverse the list until the item before the item to be removed is found.
			{
				temp = temp->link;
			}

			//When the node is found ...
			if (temp->link->link == first) //Item to be deleted is at the end of the list.
			{
				remove = temp->link; //Set a temporary pointer equal to the last element.
				temp->link = first; //Link the 2nd to last node to first to keep the list circular.
				delete remove; //Remove the last element
				elementCount--;
			}
			else //Item to be deleted is in the middle of the list.
			{
				remove = temp->link; //Set a temporary pointer equal to the node that must be removed.
				temp->link = remove->link; //Link the node before the link of the node that will be deleted.
				delete remove; //Remove the middle element.
				elementCount--;
			}
		}
	}
}

patientType patientListType::getNewPatient()
{
	patientType newPatient;
	dateType inDate, outDate;
	string first, last;
	int day, month, year, id;

	cout << "Please enter the first name of the patient you wish to add:" << endl;
	cin >> first;
	cout << "Please enter the last name of the patient you wish to add:" << endl;
	cin >> last;
	cout << "Please enter the ID number for this patient:" << endl;
	cin >> id;

	cout << "Please enter the number of the month that the patient is checking in: " << endl;
	cin >> month;
	cout << "Please enter the number of the day that the patient is checking in: " << endl;
	cin >> day;
	cout << "Please enter the number of the year that the patient is checking in: " << endl;
	cin >> year;
	inDate.setDate(month, day, year); //Insert the date parameters into an object of type date.

	cout << "Please enter the number of the month that the patient is checking out: " << endl;
	cin >> month;
	cout << "Please enter the number of the day that the patient is checking out: " << endl;
	cin >> day;
	cout << "Please enter the number of the year that the patient is checking out: " << endl;
	cin >> year;
	outDate.setDate(month, day, year); //Insert the date parameters into an object of type date.

	newPatient.setPatientInfo(id, first, last, inDate, outDate); //Populate the patient type of object

	return newPatient;
}
void patientListType::insertNewPatient()
{
	//Retrieve a new patient object from the user via the getNewPatient function. Use the base class insert function to add the patient to the list.
	insertItem(getNewPatient());
	cout << "Patient added!" << endl;
}

void patientListType::printToCSV(ofstream& fileOut) //Function will write each patient to a CSV file.
{
	nodeType<patientType> *temp;
	temp = first; //Point to the first element.
	fileOut << temp->info.getID() << "," << temp->info.getFirst() << "," << temp->info.getLast() << "," << temp->info.getCheckIn() << "," << temp->info.getCheckOut() << endl; //Copy the first element to the file.
	while (temp->link != first) //Traverse the length of the linked list and output each element.
	{
		temp = temp->link; //Move to the next node.
		fileOut << temp->info.getID() << "," << temp->info.getFirst() << "," << temp->info.getLast() << "," << temp->info.getCheckIn() << "," << temp->info.getCheckOut() << endl; //Output the next patient to the file.
	}
	cout << endl;
}
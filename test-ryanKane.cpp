#include "circularLinkedListADT.h"

int main()
{
	circularLinkedListType<int> testList; //Declare a circular linked list object that invokes the default constructor. Check if first, last and temp pointers are set to NULL. Check if elementCount is equal to zero.
	if (testList.isEmpty()) //Test if the isEmpty function correctly distinguishes an empty list.
	{
		cout << "The isEmpty function correctly recognizes an empty list!" << endl;
	}
	else
	{
		cout << "The function could not detect an empty list!" << endl;
	}
	testList.printList(); //Test if the printList function recognizes when the list is empty.
	
	if (testList.searchList(1) == false) //Search for an item in an empty list.
	{
		cout << "The searchList function returned false while searching an empty list for an item." << endl;
	}
	else
	{
		cout << "The searchList function found an element while searching an empty list." << endl;
	}


	//Testing insertion cases
	cout << "Adding an item to an empty list..." << endl;
	testList.insertItem(2);
	testList.printList(); 
	cout << "\n";
	cout << "Adding an item that will be placed before the head node ..." << endl;
	testList.insertItem(0);
	testList.printList();
	cout << "\n";
	cout << "Adding an item that will be placed in the middle of the list..." << endl;
	testList.insertItem(1);
	testList.printList();
	cout << "\n";
	cout << "Adding an item that will be the largest in the list..." << endl;
	testList.insertItem(3);
	testList.printList();
	cout << "\n";
	
	//Tests whether self-assignment is possible
	testList = testList;

	//Testing the isEmpty function.
	cout << "Checking if the list is empty ..." << endl;
	if (testList.isEmpty())
	{
		cout << "The list is empty." << endl;
	}
	else
	{
		cout << "The list is not empty!" << endl;
	}
	cout << "\n";
	//Testing search function.
	cout << "Searching the list for an item that it does not have ..." << endl;
	if (testList.searchList(5))
	{
		cout << "The searchList function found an item that it does not have." << endl;
	}
	else
	{
		cout << "The searchList function did not find an item that was not supposed to be in the list." << endl;
	}
	cout << "\n";
	cout << "Searching the list for an item that the list does have ..." << endl;
	if (testList.searchList(1))
	{
		cout << "The searchList function found the item!" << endl;
	}
	else
	{
		cout << "The searchList function did not find an item that is in the list." << endl;
	}
	cout << "\n";

	circularLinkedListType<int> myList; //Declare a new object that can be used to test the copy constructor and overloaded assignment operator.
	myList = testList; //Test the overloaded assignment operator.
	cout << "After using the overloaded assignment operator the lists are as follows: " << endl;
	cout << "Original list: ";
	testList.printList();
	cout << endl;
	cout << "Copied list: ";
	myList.printList();
	cout << endl;
	cout << "\n";

	cout << "Testing the deleteList function on the copied list." << endl;
	myList.deleteList(); //Please note that the deleteList function is the only code found inside of the destructor function definition.
	myList.printList();
	cout << "\n";
	
	cout << "Testing the deleteList function on an empty list ..." << endl;
	myList.deleteList();
	cout << "\n";

	cout << "The original list is as follows: " << endl;
	testList.printList();
	cout << "\n";
	
	cout << "Removing the last element ..." << endl;
	testList.deleteItem(3);
	testList.printList();
	cout << "\n";

	cout << "Removing a node from the middle ..." << endl;
	testList.deleteItem(1);
	testList.printList();
	cout << "\n";

	cout << "Removing the first node in the list ..." << endl;
	testList.deleteItem(0);
	testList.printList();
	cout << "\n";

	cout << "Removing a node that is the only element in the list .." << endl;
	testList.deleteItem(2);
	testList.printList();
	cout << "\n";
	
	cout << "Trying to remove a node on an empty list..." << endl;
	testList.deleteItem(2);
	system("pause");
	return 0;
}
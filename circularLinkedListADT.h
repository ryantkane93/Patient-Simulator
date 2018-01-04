#include <iostream>

using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link; //Pointer to element of the same class type
};

//Class template
template <class Type>
class circularLinkedListType
{
public:
	//There is one (or more) pointer member variables. Therefore, the class must abide by the rule of three - needs a defined destructor, copy constructor (to avoid shallow copies) and an overrided assignment operator.
	circularLinkedListType(); //Default constructor
	const circularLinkedListType<Type>& operator=(const circularLinkedListType<Type>&); //Overloaded assignment operator (rule of three)
	~circularLinkedListType(); //Destructor (rule of three)
	void deleteList();
	void printList();
	bool searchList(const Type& item); //Returns true if the parameter is found in the info of a node within the list.
	void insertItem(const Type& item); //Used to insert an item in its proper spot in the list. The location of the insertion is based off of the value of the info provided in the parameter.
	bool isEmpty(); //Checks if the linked list is empty.
	void deleteItem(const Type& item); //Uses the search function to determine whether the information is on the list and then deletes it if it exists.

protected:
	nodeType<Type> *first; //Pointer that will be point to the first element of the linked list.
	int elementCount; //Will be used to keep track of the number of elements being held in the linked list. This needs to be protected in order for it to be used in the patientListType class.

private:	
	void copyCircularList(const circularLinkedListType<Type>& otherCircularList); //Copy constructor (rule of three)
};

//Function definitions

//Initializes the first pointer to NULL as there is not yet any nodes available to add.
//Also initializes elementCount to zero to assure that an accurate number of nodes is maintained.
template <class Type>
circularLinkedListType<Type>::circularLinkedListType()
{
	first = NULL;
	elementCount = 0;
}

//Invokes deleteList() function
template <class Type>
circularLinkedListType<Type>::~circularLinkedListType()
{
	deleteList();
}
template <class Type>
void circularLinkedListType<Type>::deleteList()
{
	
	if (!isEmpty()) //If the list contains at least one element.
	{
		while (first != NULL) //Traverse the list and delete each node until first is no longer pointing to a node.
		{
			nodeType<Type> *current; //Use a temporary pointer to remove elements.
			current = first; //Have the temporary pointer point to the first element in the list.

			//Use the element count to delete the last node in the list so that you do not have to maintain the circular structure as each node is deleted.
			if (elementCount == 1) //If there is one node left in the list.
			{
				delete current; //Delete the last node.
				first = NULL; //Set first to NULL.
			}
			else
			{
				first = current->link; //Move to the next node.
				delete current; //Delete the current node.
				elementCount--;
			}
		}

		elementCount = 0; //Reset the element count once all elements are removed
	}
	//If the list is already empty, make no changes.
}

template <class Type>
const circularLinkedListType<Type>& circularLinkedListType<Type>::operator=(const circularLinkedListType<Type>& otherList)
{
	if (this != &otherList) //This is included to prevent the copy constructor from being invoked while self-copying.
	{
		copyCircularList(otherList);
	}
	return *this; 
}

template <class Type>
bool circularLinkedListType<Type>::isEmpty()
{
	//The list is empty if there has not been an insertion performed.
	if (elementCount == 0 && first == NULL)
	{
		return true;
	}

	//The list isn't empty if there is a positive value for elementCount.
	else
	{
		return false;
	}
}

template <class Type>
void circularLinkedListType<Type>::insertItem(const Type& item)
{
	//Declare a new nodeType struct as an ADT.
	nodeType<Type> *newNode; //Declares the pointer
	newNode = new nodeType <Type>; //Creates a 
	newNode->info = item;

	if (isEmpty())//If the list is empty, add one node and establish the circular structure.
	{
		first = newNode; //First points to new node.
		newNode->link = first; //Make the list circular by making the link of first equal to first.
	}
	else if (newNode->info <= first->info) //The node needs to be entered as the smallest element of the list.
	{
		nodeType<Type> *temp; //Declare a temporary pointer.
		temp = first; //Set the temporary pointer equal to the first node.
		while (temp->link != first) //Traverse the list to find the last element.
		{
			temp = temp->link;
		}

		temp->link = newNode; //Link the last element to the newNode to maintain ciruclarity.
		newNode->link = first; //Link the smallest node to the previous smallest.
		first = newNode; //Move the first pointer to the new smallest element.
	}

	else //The inserted node is not the first element added and is not the smallest element.
	{
		nodeType<Type> *temp;
		temp = first;
		while (temp->link != first) //Traverse the list to find the last element.
		{
			temp = temp->link;
		}

		if (newNode->info > temp->info) //If the added element is greater than the largest element in the list ..
		{
			temp->link = newNode; //Add the newNode onto the end of the list.
			newNode->link = first; //Link the last element to the first.
		}

		else
		{

			temp = first;
			while (temp->link->info < newNode->info) //Locate the node after the position that newNode must be inserted.			
			{
				temp = temp->link;
			}
			newNode->link = temp->link; //Link the newNode to the proceeding node in the list.
			temp->link = newNode; //Insert the newNode in the correct spot.
		}

	}
	elementCount++;
}

template <class Type>
bool circularLinkedListType<Type>::searchList(const Type& item)
{
	if (isEmpty()) //The list is empty and therefore cannot contain the element.
	{
		return false;
	}
	
	else
	{
		if (first->info == item) //The item is contained in the head and therefore is found.
		{
			return true;
		}

		//The list is not empty and the item did not match the first node.
		nodeType<Type> *temp;
		temp = first;
		while (temp->link != first)
		{
			temp = temp->link; //Traverses the list.
			if (temp->info == item)
			{
				return true; //If the item is found, return true.
			}
		}
	}
	return false; //If the item is never found after searching each element, return false.
}

template <class Type>
void circularLinkedListType<Type>::deleteItem(const Type& item)
{
	if (searchList(item)) //The item is somewhere in the linked list and the list is not empty.
	{
		nodeType<Type> *temp;
		temp = first;
		if (first->info == item && elementCount>1) //If the item is located at the head of the linked list but it is not the last element in the list.
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
		else if (first->info == item && elementCount == 1) //If there is only one element in the list.
		{
			cout << "Removing the last element in the list!" << endl;
			deleteList();
		}
		else //If the element is found, but is not the first item. and is not the only item in the list.
		{
			nodeType<Type> *remove;
			while (temp->link->info != item) //Traverse the list until the item before the item to be removed is found.
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

		//Note that elementCount-- could not be used here. The condition where a list with one node is to be deleted calls the destroyList
		//function, which sets elementCount=0. Keeping elementCount-- would result in all lists passing through destroyList to have an elementCount of
		//-1.
	}

	else //The list is either empty or does not contain the element.
		cout << "The list does not have this element or is empty!" << endl;
}

template <class Type>
void circularLinkedListType<Type>::printList()
{
	if (isEmpty()) //Check if the list is empty or not.
		cout << "The list is empty and cannot be printed!" << endl; //Output a message and perform no further action if the list is empty.

	else //The list isn't empty and therefore can be printed.
	{
		nodeType<Type> * temp;
		temp = first; //Point to the first element.
		cout << temp->info << " "; //Output the first element.
		while(temp->link != first) //Traverse the length of the linked list and output each element.
		{
			temp = temp->link; //Move to the next node.
			cout << temp->info << " "; //Output the node and a space for formatting.
		}
		cout << endl;
	}
}
template <class Type>
void circularLinkedListType<Type>::copyCircularList(const circularLinkedListType<Type>& otherCircularList)
{
	if (first != NULL) //Assure that the list is empty and initialized.
	{
		deleteList();
	}

	if (otherCircularList.first == NULL) //If the list to be copied is empty, simply initialize the other list.
	{
		first = NULL;
		elementCount = 0;
	}

	else //The list to be copied has at least one node.
	{
		nodeType<Type> *temp; //Use a temporary pointer to traverse the list to be copied.
		temp = otherCircularList.first; //Set the pointer equal to the head of the "template" list.
		insertItem(temp->info); //Insert the first node of the list that is being copied using the insert function.
		while (temp->link != otherCircularList.first) //Continue to traverse the list until the last node is reached.
		{
			temp = temp->link; //Move to the next node.
			insertItem(temp->info); //Copy the info of the node into the new list.
			
		}
	}
}
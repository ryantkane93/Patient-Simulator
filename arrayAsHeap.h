#include <iostream>
#include <assert.h>

using namespace std;

template <class Type> 
class arrayAsHeap
{
private:
	Type *list; //Pointer that points to the dynamic array. This is a pointer acting as a private member variable and therefore the class must abide by the rule of three.
	int maxSize; //Maximum size allowed in the dynamic array.
	int length; //Length of the heap.

protected:
	void insertSort(int root, int last); //Recursive function that locates where the newly-added node must go and then places it in that location.
	void removeSort(int root, int last); //Recrusive function that starts at the root node and the traverses down the tree until the heap is restored.

public:
	arrayAsHeap(); //Creates a queue containg a maximum of 1000 elements.
	arrayAsHeap(int max); //Parameterized constructor
	~arrayAsHeap(); //Destructor (rule of three)
	arrayAsHeap(const arrayAsHeap<Type>& otherHeap); //Copy constructor (rule of three)
	const arrayAsHeap<Type>& operator= (const arrayAsHeap<Type>&); //Overloaded assignment operator (rule of three)
	void insertNode(Type info); //Will insert a node into the first avavilable position in the heap and then call the insertSort function to find its correct location.
	void removeNode(); //Removes the highest priority value in the queue.
	void printQueue();
	Type getFront(); //Returns the top of the heap. Implemented in order to write items in the queue to a file before removing them.
	int getLength(); //Returns the amount of values in the heap. Implemented in order to remove all of the nodes out of the heap in the simulation program.

};

template <class Type>
arrayAsHeap<Type>::arrayAsHeap()
{
	arrayAsHeap(1000); //Creates a heap that can hold a maximum of 1000 elements.
	//Call the parameterized constructor that also initializes the maxSize, length and list dynamic array accordingly.
}
template <class Type>
arrayAsHeap<Type>::arrayAsHeap(int max)
{
	//10,000 as a maximum value of the queue is arbitrary. Ideally you'd like to use as little memory as possible. The ten thousand element
	//limit is simply to avoid the program from taking up too much memory.
	if (0 < max && max <= 10000) //Assure that the max size ranges from 1-10,000.
	{
		maxSize = max;
		length = 0;
	}
	else
	{
		cout << "Invalid entry for the maximum size of the heap. Initializing it to to one thousand by default." << endl;
		//Note that one thousand was chosen as a default value to avoid dynamically allocating too much memory in the event that multiple queues are created.
		maxSize = 1000;
	}

	list = new Type[maxSize];
}

template <class Type>
arrayAsHeap<Type>::~arrayAsHeap()
{
	delete[] list; //Delete the dynamic array and let the compiler manage the rest of the non-dynamic variables.
}



template <class Type>
void arrayAsHeap<Type>::insertNode(Type info)
{
	if (length < maxSize) //Check that there is enough room in the array to add another node.
	{
		list[length] = info; //Insert the node at the last position in the array.
		insertSort(0, length); //Pass the root and the newly added node into the insertSort function.
		length++; //Increase the length by one once the node has been moved to its proper location.
	}
	else
	{
		cout << "The node was not added as the queue is already full!" << endl;
	}
}

template<class Type>
void arrayAsHeap<Type>::removeNode()
{
	if (length == 0)
	{
		cout << "The queue is empty so there are no nodes that can be removed." << endl;
	}
	else
	{
		list[0] = list[length-1]; //Set the head of the heap equal to the last element in the list. This allows us to "delete" the item in the queue.
		length--; //Decrease the length of the heap so that the last element is no longer a part of it.
		removeSort(0, length); //Call the recursive sort function to move the head node to its proper place in the list.
	}
}


template<class Type>
void arrayAsHeap<Type>::insertSort(int root, int last) //Places a newly added node in its correct position in the heap.
{

	if (last > root) //Allows for us to stop recursively calling the function if the newly added node has worked its way to the top of the heap.
	{
		int subRoot = (last - 1) / 2; //Allows for us to locate the parent of a particuar node ("undos" the 2k + 1 formula for locating child nodes).

		//Note that the proceeding if statement is not reached once the added node is in its right position (where it is less than the parent of its sub-tree
		//or it is the head node of the entire heap). This serves as the base case.

		if (list[subRoot] < list[last]) //If the parent of the sub-tree is smaller than the node we are trying to place in the heap.
		{
			Type temp = list[subRoot]; //Use a temporary variable to hold the value of the sub-tree's root.
			list[subRoot] = list[last]; //The value of the child is now equal to the value of the subRoot.
			list[last] = temp; //The child is now equal to the original parent.
			//Swap is complete.
			insertSort(root, subRoot); //Recursively call the function using the root of the heap and the root of the current sub-tree.
			//This traverses us up the heap.
		}
	}
}

template <class Type>
void arrayAsHeap<Type>::removeSort(int root, int last)
{
	int largestChild; //Variable that will be used to represent the index of the largset child in the sub-tree.
	largestChild = 2 * root + 1; //Assume the left branch is the largest child (it will eventually be compared to the right).

	Type parent = list[root]; //Obtain the contents of the root of the tree that will be sorted.

	if (largestChild <= last) //The base case is executed once the the largestChild in a sub-branch is either the last node in the tree or is a "sister" branch of the last branch.
	{
		if (largestChild == last) //If there is no other child in that sub-tree
		{
			largestChild = largestChild; //The left child must be the largest in this case.
		}
		else //There is another child node in the sub-tree.
		{
			if (list[largestChild] < list[largestChild + 1]) //If the left child is smaller than the right child, set largestChild as the right child.
			{
				largestChild = largestChild + 1; //Have largestChild be equal to the right branch.
			}
		}

		if (parent < list[largestChild]) //If the parent is smaller than the largest child swap the two.
		{
			Type temp = list[root]; //Declare a temporary variable to hold the sub-tree root.
			list[root] = list[largestChild]; //Swap the largest child with the sub-tree root.
			list[largestChild] = temp; //Have the original sub-tree root now become the child.
			removeSort(largestChild, last); //Recursively call the function, this time using the next sub-tree in the heap as the root.
		}
	}
}

template <class Type>
arrayAsHeap<Type>::arrayAsHeap(const arrayAsHeap<Type>& otherHeap)
{
	maxSize = otherHeap.maxSize;
	list = new Type[maxSize];
	length = 0; 

	for (int i = 0; i < otherHeap.length; i++)
	{
		insertNode(otherHeap.list[i]); //The insert function will set the length of the new list as nodes are added to the heap.
	}

}

template <class Type>
const arrayAsHeap<Type>& arrayAsHeap<Type>::operator= (const arrayAsHeap<Type>& otherHeap)
{
	if (this != &otherHeap) //Checks for self-assignment.
	{
		if (list != NULL) //Check if the heap that is going to be copied to is empty.
		{
			delete[] list; //list is now null.
		}
		
		length = 0; //Initialize the length and allow the insertNode function to update the length value as nodes are added.
		maxSize = otherHeap.maxSize;
		list = new Type[maxSize]; //Create a new dynamic array that has the correct maxSize.

		//If the otherHeap is empty, the following if statement will not execute, and will not effect the length variable.
		
		if (otherHeap.length != 0) //If the otherHeap has elements in it, copy them in.
		{
			for (int i = 0; i < otherHeap.length; i++)
			{
				insertNode(otherHeap.list[i]); //Insert function will increase the count of length on its own.
			}
		}
	}
	else
	{
		cout << "Assignment not performed as this would result in self-assignment!" << endl; //For testing purposes.
	}

	return *this;
}

template <class Type>
void arrayAsHeap<Type>::printQueue() //Prints out the array order, not the order of the heap. For testing purposes.
{
	if (length == 0)
	{
		cout << "The list is empty and cannot be printed!" << endl;
	}

	else
	{
		for (int i = 0; i < length; i++)
		{
			cout << list[i] << " ";
		}
		cout << endl;
	}
}

template <class Type>
Type arrayAsHeap<Type>::getFront()
{
	assert(length != 0);
	return list[0];
	/*Calling the getFront() function when there are no elements in the list will result in improper output.
	The assert statement will cause the program to terminate, but will avoid printing or writing the bad output
	There are no conditions where either test programs would trigger this assert, but it was included for good practice
	as the potential to read from unpopulated memory was recognized.*/
}

template <class Type>
int arrayAsHeap<Type>::getLength()
{
	return length;
}
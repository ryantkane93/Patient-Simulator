#include "arrayAsHeap.h"

//Non-main functions
void constructorAsParameter(arrayAsHeap<char>parameter)
{
	cout << "The copy constructor passed the queue by value. Its elements are as follows: " << endl;
	parameter.printQueue();
}

arrayAsHeap<int> constructorReturn()
{
	arrayAsHeap<int>copy(5);
	copy.insertNode(27);
	copy.insertNode(5);
	copy.insertNode(18);
	copy.insertNode(17);
	copy.insertNode(91);

	return copy;
}

void testEmptyDestructor()
{
	arrayAsHeap<char>test(5); //Declare an empty queue.
	//The class destructor is invoked after the object goes out of scope (the scope of the compiler goes back to main).
}

void testFullDestructor()
{
	arrayAsHeap<char>test(3);
	test.insertNode('n');
	test.insertNode('y');
	test.insertNode('r');
	cout << "The locally declared queue contains:";
	test.printQueue(); //Print the local queue to show that there was elements in it before the destructor was invoked.
	//Class destructor is invoked once the object goes out of scope.
}

int main()
{
	arrayAsHeap<char> newObj(10); //Declare a new priority queue using the PARAMETERIZED CONSTRUCTOR.

	cout << "Testing insertion function by inserting ten characters ..." << endl;
	//Populate the heap with ten nodes.
	newObj.insertNode('c');
	newObj.insertNode('d');
	newObj.insertNode('d');
	newObj.insertNode('c');
	newObj.insertNode('e');
	newObj.insertNode('b');
	newObj.insertNode('b');
	newObj.insertNode('e');
	newObj.insertNode('a');
	newObj.insertNode('c');

	cout << "The queue is as follows: ";
	newObj.printQueue(); //Print out the queue to see if the nodes were inserted and are in order.
	cout << "\n";

	cout << "Attempting to add a node to a queue that is already full..." << endl;
	newObj.insertNode('a');

	cout << "The queue is as follows: ";
	newObj.printQueue(); 
	cout << "\n";

	cout << "Now removing five nodes..." << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << newObj.getFront() << " is at the front of the queue and is being removed!" << endl;
		newObj.removeNode(); //Remove the first element in the queue.
	}
	
	cout << "After deletion, the queue is as follows: ";
	newObj.printQueue(); //Print out the queue to see if the nodes are still in order after being deleted.
	cout << "\n";

	cout << "Deleting the rest of the nodes ..." << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << newObj.getFront() << " is at the front of the queue and is being removed!" << endl;
		newObj.removeNode(); //Remove the first element in the queue.
	}
	newObj.printQueue(); //Print out the list to prove that it is empty.
	cout << "\n";

	cout << "Attempting to delete from an already empty list ..." << endl;
	newObj.removeNode();
	cout << "\n";
	
	//End of testing for insertion and deletion algorithms.

	cout << "Testing the copy constructor using an empty queue ..." << endl;
	arrayAsHeap<char>secondObj(newObj); //Test the copy constructor using an empty queue.
	secondObj.printQueue();
	cout << "\n";

	cout << "Repopulating the queue..." << endl;
	//Populate the heap with ten nodes.
	newObj.insertNode('c');
	newObj.insertNode('a');
	newObj.insertNode('d');
	newObj.insertNode('c');
	newObj.insertNode('c');
	newObj.insertNode('b');
	newObj.insertNode('x');
	newObj.insertNode('e');
	newObj.insertNode('a');
	newObj.insertNode('v');
	cout << "\n";

	cout << "Testing the copy constructor with a populated queue ..." << endl;
	arrayAsHeap<char> testObject(newObj); //Instantiate the object with a populated queue.
	cout << "The queue is as follows: " << endl;
	testObject.printQueue();
	cout << "\n";

	cout << "Passing a queue by value as a function parameter..." << endl;
	constructorAsParameter(testObject);
	cout << "\n";

	cout << "Returning a queue from a function to provoke the copy constructor ..." << endl;
	arrayAsHeap<int>assignmentTest; //Tests the DEFAULT CONSTRUCTOR 
	assignmentTest= constructorReturn(); //Testing the overloaded asssignment operator by assigining a populated queue to an empty one.
	cout << "The returned queue from the function was assigned to another queue using the overloaded operator. The queue is as follows:" << endl;
	assignmentTest.printQueue();
	cout << "\n";
	
	//End testing of copy constructor
	
	cout << "Using the overloaded assignment operator to assign an empty queue to an already populated queue ..." << endl;
	testObject = secondObj; //Tests using the assignment operator to copy data from an empty queue into a populated queue object.
	cout << "The queue is now as follows: " << endl;
	testObject.printQueue();
	cout << "\n";

	cout << "Using the overloaded assignment operator to copy a populated queue to another queue that already has the same number of values." << endl;
	arrayAsHeap<int>intTest(10); //Declare a new queue object.
	for (int i = 0; i < 7; i++)
	{
		intTest.insertNode(i); //Populate the new object with the values 1-10.
	}
	cout << "Queue 1's original values: ";
	intTest.printQueue();
	cout << "Queue 2's original values: ";
	assignmentTest.printQueue();
	cout << "Assigning Queue 1 to Queue 2 ..." << endl;
	assignmentTest = intTest; //Copies a populated queue to another populated queue.
	cout << "Queue 2's new values are: ";
	assignmentTest.printQueue();
	cout << "\n";

	cout << "Attemtping self-assignment ..." << endl; 
	assignmentTest = assignmentTest;
	cout << "\n"; 

	cout << "Assigning an empty queue to another empty queue ..." << endl;
	secondObj = testObject;
	cout << "\n";
	//End testing of overloaded assignment operator

	//Note that in the copy constructor functions, the destructor was also invoked when a locally declared queue went out of scope.
	//The following destructor tests re-iterate that principle and allows the user to know that the destructor was tested purposely.
	
	cout << "Testing the destructor on an empty locally declared queue object..." << endl;
	testEmptyDestructor();
	cout << "\n";

	cout << "Testing the destructor on a locally declared full queue..." << endl;
	testFullDestructor();

	system("pause");
	return 0;
}
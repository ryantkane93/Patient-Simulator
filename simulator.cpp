#define _USE_MATH_DEFINES //This is required to obtain the Euler's number constant.
#include "arrayAsHeap.h"
#include "patientType.h"
#include <time.h> //Needed to generate random sequence of numbers.
#include <fstream>
#include <cmath> //This is required to obtain the Euler's number constant from the precompiled library.
 
//Function prototypes
void loadPatients(double interArrivalTime, int simTime); //Randomly generates patient data and then writes it to a file that can be used for input.
arrayAsHeap<patientType> populateQueue(int simTime); //Reads data from the file and then populates the queue with said data.
void processQueue(arrayAsHeap<patientType>queue); //Removes all elements from the queue and writes the data to an output file.

int main()
{
	int simTime; 
	double interArrivalTime; //Interarrival time must be a double as it will be used in a calculation with euler's number to get an accurate decimal value.

	cout << "Please enter the total number of time units you wish for the simulator to run: ";
	cin >> simTime;
	cout << endl;

	while (simTime > 10000 || simTime < 1)
	{
		/*As a point of good practice, the dynamic array in the arrayAsHeap class was limited to 10,000 elements, in order to avoid potentially 
		memory hogging by the user inserting too many elements. Since, in theory, a patient can arrive at every time unit, the simulation
		time must abide by this maximum value of the queue.*/
		cout << "The simulation time must be a value between 1 and 10,000. Please try again with a valid value: ";
		cin >> simTime;
		cout << endl;
	}

	cout << "Please enter the time unit value for the interarrival time: ";
	cin >> interArrivalTime;

	while (interArrivalTime > simTime || interArrivalTime < 0)
	{
		/*In theory, calculating the the value for lambda (in order to make a number to determine whether or not a patient arrives
		at a particular point in time) would result in an overflow error if zero is used for the interarrival time, as 
		division by zero is taking place. The compiler instead evaluates a double value with division by zero as positive infinity
		and results in a patient arriving at every time interval. Expressing an interarrival time as zero should, in theory,
		result in zero patients arriving in the queue. For this reason, interArrivalTime must be greater than zero.

		The interArrivalTime can exceed the simulation time as it is an average. While it is inprobable for a patient to arrive if the
		interarrival time exceeds the simulation time, it is still possible.*/

		cout << "The interarrival time must be a value greater than zero. Please try again with a valid value.";
		cin >> interArrivalTime;
	}
	cout << "\n";
	loadPatients(interArrivalTime, simTime); //Create patient data and store it in a file that will be used as input.
	processQueue(populateQueue(simTime)); //Store the queue from the populateQueue function into a queue object and then use this queue to write
	//the data to a file as information is removed.
	system("pause");
	return 0;
}

void loadPatients(double interArrivalTime, int simTime)
{
	ofstream patientList;
	patientList.open("F:\\patientList.txt");
	if (patientList) //Check if the list is open.
	{
		cout << "File successfully opened! Populating the file with patient data..." << endl; //Output a message for testing purposes.
		cout << "\n";
	}
	else
	{
		cout << "File unable to be opened." << endl; //Output a message for testing purposes.
	}

	srand(time(NULL)); //Seeding the pseudo-random number generator with time(NULL) assures that a difference sequence of numbers is used
	//each time the program is excecuted.

	double lambda = 1 / interArrivalTime; //Calculate the lambda value that will be used as the exponent in Euler's number to determine whether
	//a patient arrives at a particular time unit. Note that the formula is e^(-lambda)
	double probNoEvent = pow(M_E, -lambda); //Calculates the value for e^(-lambda) which will be used to determine whether or not a patient
	//arrives at a particular time unit.

	//For purposes of displaying data have the simulation start at one time unit in case a patient arrives right away.
	//This allows for the arrival time to be displayed as 1 as opposed to 0 (or on the max simTime as opposed to max simTime-1.

	for (int i = 1; i <= simTime; i++)
	{
		double customerArrives = ((double)rand() / (RAND_MAX)); //Generates a random double between 0 and 1.
		if (customerArrives > probNoEvent) //If the random double value is greater than e^(-lambda), then a patient arrives at that time interval.
		{
			patientType newPt(rand() % 5 + 1, i); //Instantiates a new patient object with a random number between one and five for the priority
			//and the arrival time (i) if said patient. 
			patientList << newPt.getArrivalTime() << "," << newPt.getPriority() << endl; //Since the overloaded insertion operator of patientType prints the priority first,
			//use the get functions to populate the file with the data in (arrival time, priority) order.
		}
	}
	patientList.close(); //Close the file once all of the data has been written.
}

arrayAsHeap<patientType> populateQueue(int simTime)
{
	arrayAsHeap<patientType>queue(simTime); //Although it is highly unlikely, a patient can arrive at every time unit. As a result, a dynamic array of simTime
	//must be created in order to hold the potential number of patients.

	ifstream fileIn; 
	fileIn.open("F:\\patientList.txt"); //Open the same file that was originally written to in to by the loadPatients function.
	if (fileIn) //Check if the file is opened.
	{
		cout << "Input file opened! Now loading the patients into the queue...." << endl;
		cout << "\n";
	}
	else
	{
		cout << "Input file not opened." << endl;
	}


	while (fileIn.good()) //While the file still has data inside of it.
	{
		int priority, arrivalTime;
		fileIn >> arrivalTime;
		fileIn.ignore(1);
		fileIn >> priority;
		patientType dummyPt(priority, arrivalTime);
		//Note that while using fileIn.good() once the compiler reaches the end of file character, it will go back and attempt to retrieve the previous line.
		//As a result, the last line of the output file will be copied twice. Having the loop break when the end of file is detected prevents this problem.
		if (fileIn.eof()) //Once the end-of-file character is detected, break the loop in order to prevent the same record from being loaded into the queue twice.
		{
			break;
		}
		queue.insertNode(dummyPt);
	}
	fileIn.close(); //Close the input file once all of the data has been loaded into the queue.
	return queue; //Return the queue so that it could be placed in an output file.
}

void processQueue(arrayAsHeap<patientType>queue)
{
	ofstream printQueue; //Open another output stream variable.

	printQueue.open("F:\\priorityQueue.txt");
	if (printQueue)
	{
		cout << "File successfully opened! Processing the queue ..." << endl;
		cout << "\n";
	}
	else
	{
		cout << "Output file did not open!" << endl;
	}

	int originalLength = queue.getLength(); //Since the length variable descreases as nodes are removed, we must store the original length
	//as a variable and then use it as a condition for the for loop.

	for (int i = 0; i < originalLength; i++)
	{
		printQueue << queue.getFront() << endl; //Write the front of the queue into the file.
		queue.removeNode(); //Remove the front node after it is in the file.
	}
	printQueue.close(); //Close the file.

	cout << "Queue successfully processed! Please view the priorityQueue.txt outout file for the results." << endl;
}
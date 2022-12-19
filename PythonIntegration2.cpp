#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>


using namespace std;


// Beginning of provided code
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/


void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python_modules.my_python_code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_modules.my_python_code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_modules.my_python_code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
// End of provided code

void main()
{
	int menuNum; //variable for user input for their menu option 
	string userItem;
	ifstream inFS;
	string groceryList;
	string histogramDisplay;



	inFS.open("myfile.txt");

	if (!inFS.is_open()) { //Print "Could not open file if file is not able to be opened 
		cout << "Could not open file myfile.txt." << endl;
	}

	inFS >> groceryList; //Input as groceryList
	while (!inFS.fail()) { //Create a string with all grocery items in it 
		string oneItem; 
		inFS >> oneItem;
		groceryList += "    " + oneItem;
	
	}
	if (!inFS.eof()) { //Print error message if file can't be read completely 
		cout << "Input failure before reaching end of file." << endl;
	}

	inFS.close(); // Close file 
	

	// Print a menu with four options
	cout << "Select an option: " << endl << endl;
	cout << "Option 1: Display today's grocery list" << endl; // List with all items and amounts 
	cout << "Option 2: Determine the frequency of specific item" << endl; // List with user input and amount 
	cout << "Option 3: View histogram" << endl; //List of all items with *** to represent amounts 
	cout << "Option 4: End program" << endl;

	cin >> menuNum; // Get user input for menu option

	system("cls"); // clear screen 

	// While loop to check for invalid user entry
	while ((menuNum != 1) && (menuNum != 2) && (menuNum != 3) && (menuNum != 4)) { 
		cout << "Invalid entry. Please enter a 1, 2, 3, or 4" << endl; // Displays a message requesting a valid number
		cin.clear(); // Clears current input
		cin >> menuNum; // Gets new user input for menuNum
	}
	if (menuNum == 1) { // when userInput is 1 
		//Call python function to display todays grocery list 
		cout << "Items Purchased" << endl << endl;
		cout << callIntFunc("AllFrequency", groceryList) << endl; //Call function AllFrequency in python with groceryList parameter
	}

	if (menuNum == 2) { // When userInput is 2 
		cout << "Which item would you like to check the frequency of?" << endl; // Print to ask the user for input 
		cout << callIntFunc("SpecificItem", groceryList) << "many times" << endl; // Call function SpecificItem in python with groceryList parameter
	}
	if (menuNum == 3) { // When userInput is 3
		cout << "Displaying Histogram" << endl << endl; // Print to let user know 
		cout << callIntFunc("CreateHistogram", groceryList); // Call create histogram function

		inFS.open("frequency.txt"); //Open frequency.txt

		if (!inFS.is_open()) { //Print "Could not open file if file is not able to be opened 
			cout << "Could not open file frequency.txt" << endl;
		}

		if (inFS.fail()) { //if unable to read file print error message
			cout << "Could not read" << endl;
		}
		while (!inFS.fail()) { //Create a string with all items in it 
			string histData;

			getline(inFS, histData);
			cout << histData << endl;

		}
		if (!inFS.eof()) { //Print error message if file can't be read completely 
			cout << "Input failure before reaching end of file." << endl;
		}

		
	}

	

}
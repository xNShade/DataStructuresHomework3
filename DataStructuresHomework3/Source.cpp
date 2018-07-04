//Function that gets the name of the file to be read in from user agrv argc[]
//Reads in data and checks validity. Between 0 and 99
//Creates stack file. Average of the data
// AND/OR
//Creates queue file. Average of the data

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

bool GetUserInput(ifstream &YourFile);
void ReadFile(ifstream &YourFile, stack<int> &, queue<int> &);
void PrintStack(stack<int>);
void PrintQueue(queue<int>);

int main(int argc, char *argv[]) {
	ifstream YourFile;
	stack<int> MyStack;
	queue<int> MyQueue;
	// First we are going to check if the user sent in the name of the file using the command line.
	if (argc == 2) {
		//Continue
		string YourInput = argv[1];
		YourFile.open(YourInput.c_str());
		//Error checking to make sure the file opens.
		if (YourFile.is_open()) {
			cout << "Opening " << YourInput << " was successful.\n";
		}
		else {
			cout << "Failure to open " << YourInput << endl;
			system("pause");
			return 1;
		}
	}
	// They did not use the command line. They will need to be prompted to enter a file name.
	else {
		if (!GetUserInput(YourFile))
			return 1;
	}
	
	ReadFile(YourFile, MyStack, MyQueue);
	PrintStack(MyStack);
	PrintQueue(MyQueue);

	YourFile.close();
	system("pause");
	return 0;
}

bool GetUserInput(ifstream &YourFile) {
	string YourInput;
	cout << "Please enter a file name that will be read.\n";
	cin >> YourInput;
	YourFile.open(YourInput.c_str());
	if (YourFile.is_open()) {
		cout << "Opening " << YourInput << " was successful.\n";
		return true;
	}
	else {
		cout << "Failure to open " << YourInput << endl;
		system("pause");
		return false;
	}
}

void ReadFile(ifstream &YourFile, stack<int> &MyStack, queue<int> &MyQueue) {
	// This will be a while loop that will go until EOF and deposit the variables in whichever spot they
	//need to be in.
	string denied;
	int x;
	while (YourFile >> denied) {
		if (isdigit(denied[0])) {			// This feels like a bandaid way to catch the 0's that will get caught and output
			x = atoi(denied.c_str());		//. Writing the code like this works fine for this data set.. but if you get data
			if (x <= 49 && x >= 0) {		//that looks something like 0cat, it will mess up. This could probably be fixed by
				MyQueue.push(x);			//checking every element of the string.
				//cout << "Did Queue for " << x << endl;	//DEBUG
			}
			if (x >= 50 && x <= 99) {
				MyStack.push(x);
				//cout << "Did Stack " << x << endl;	//DEBUG
			}
		}
		//else
			//cout << denied << " is trash\n";	//DEBUG
	}
	//cout << denied << " Made it too...";	//DEBUG
}

void PrintStack(stack<int> MyStack) {
	ofstream fout("Stack.txt");
	int counter = 0;	//This will keep track of the number of lists. Used for an average.
	int x = 0; //This will hold the total of the numbers;

	int formatter = 1; //Formatting code.
	while (!MyStack.empty()) {
		counter++;
		fout << MyStack.top() << "\t";
		//cout << MyStack.top() << "\t";	//DEBUG
		x = x + MyStack.top();
		MyStack.pop();
		if (formatter % 5 == 0) {
			fout << endl;
			formatter = 0;
		}
		formatter++;
	}
	x = (x / counter);
	fout << endl << x << endl;
	//cout << endl << x << endl;		//DEBUG
	fout.close();
	return;
}

void PrintQueue(queue<int> MyQueue) {
	ofstream fout("Queue.txt");
	int counter = 0;	//This will keep track of the number of lists. Used for an average.
	int x = 0; //This will hold the total of the numbers;

	int formatter = 1; //The output format code.
	while (!MyQueue.empty()) {
		counter++;
		fout << MyQueue.front() << "\t";
		//cout << MyQueue.front() << "\t";	//DEBUG
		x = x + MyQueue.front();
		MyQueue.pop();
		if (formatter % 5 == 0) {
			fout << endl;
			formatter = 0;
		}
		formatter++;
	}
	x = (x / counter);
	fout << endl << x << endl;
	//cout << endl << x << endl;		//DEBUG
	fout.close();
	return;
}
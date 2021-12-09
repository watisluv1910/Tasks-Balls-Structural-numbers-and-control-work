#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <fstream> // for if/ofstream
#include <time.h> // for srand
#include <vector> // for vector
#include <stdio.h> // for printf
#include <stdlib.h> // for rand, srand
#include <sstream> // for switchstream
#include <utility> // for swap
#include <algorithm> // for sort

using namespace std;

//function that check type error or "border crossing"
int initializeInteger(string path, int lowerBound, int upperBound) {
	bool isCorrect = false;
	int temporaryVariable;
	while (!isCorrect) {
		string temporaryVariableString;
		cin >> temporaryVariableString;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if (i < (int)'0' || i >(int)'9') {
				if (i != (int)'-') {
					if (temporaryVariableString.find((char)i) != string::npos) {
						isCorrect = false;
					}
				}
				else if (temporaryVariableString.find((char)i) != string::npos) {
					if ((count(temporaryVariableString.begin(),
						temporaryVariableString.end(), (char)i) > 1)
						|| temporaryVariableString.length() == 1) {
						isCorrect = false;
					}
				}
			}
		}
		if (isCorrect) {
			temporaryVariable = stoi(temporaryVariableString);
			if (lowerBound != 0 || upperBound != 0) {
				if (temporaryVariable < lowerBound
					|| temporaryVariable > upperBound) {
					cout << "Initialization error.\nEnter correct value:\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
					// operator >> will no longer fetch data from the stream 
					// as it is in the wrong format
				}
			}
			else if (path == "allExceptZero" && temporaryVariable == 0 ||
				path == "negative" && temporaryVariable >= 0 ||
				path == "notpositive" && temporaryVariable > 0 ||
				path == "notnegative" && temporaryVariable < 0 ||
				path == "positive" && temporaryVariable <= 0) {
				cout << "Initialization error.\nEnter correct value:\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				isCorrect = false;
			}
		}
		else {
			cout << "Initialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return temporaryVariable;
}

// function that check type error or "border crossing"
double initializeDouble(string path, double lowerBound, double upperBound) {
	bool isCorrect = false;
	double temporaryVariable;
	while (!isCorrect) {
		string temporaryVariableString;
		cin >> temporaryVariableString;
		isCorrect = true;
		for (size_t i = 0; i < 128; i++) {
			if (i < (int)'0' || i >(int)'9') {
				if (i != (int)'-' && i != (int)'.') {
					if (temporaryVariableString.find((char)i) != string::npos) {
						isCorrect = false;
					}
				}
				else if (temporaryVariableString.find((char)i) != string::npos) {
					if ((count(temporaryVariableString.begin(),
						temporaryVariableString.end(), (char)i) > 1)
						|| temporaryVariableString.length() == 1) {
						isCorrect = false;
					}
				}
			}
		}
		if (isCorrect) {
			// turns a string into a stream:
			istringstream stringStream(temporaryVariableString);
			stringStream >> temporaryVariable; // reads data from the stream
			if (lowerBound != 0.0 || upperBound != 0.0) {
				if (temporaryVariable < lowerBound ||
					temporaryVariable > upperBound) {
					cout << "Initialization error.\nEnter correct value:\n";
					cin.clear();
					// operator >> will no longer fetch data from the stream:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					isCorrect = false;
				}
			}
			else if (path == "allExceptZero" && temporaryVariable == 0.0 ||
				path == "negative" && temporaryVariable >= 0.0 ||
				path == "notpositive" && temporaryVariable > 0.0 ||
				path == "notnegative" && temporaryVariable < 0.0 ||
				path == "positive" && temporaryVariable <= 0.0) {
				cout << "Initialization error.\nEnter correct value:\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				isCorrect = false;
			}
		}
		else {
			cout << "Initialization error.\nEnter correct value:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return temporaryVariable;
}

bool isInterrupted(int a) {
	// this function checks the interruption of the task by user entering 0
	if (a == 0) {
		cout << "\nThe task was interrupted by user.\n";
		return true;
	}
	else {
		return false;
	}
}

int countFactorial(int value) {
	// this function counts factorial using recursive algorithm
	if (value > 2) {
		return value * countFactorial(value - 1);
	}
	else {
		return value;
	}
}

void doReswap(int* array, int i, int j) { // for "Balls" task
	// this function is the same as built-in swap() function
	int swapVariable = array[i];
	array[i] = array[j];
	array[j] = swapVariable;
}

int* findNextSet(int* array, int ballsNumber) { // for "Balls" task
	int j = ballsNumber - 2;
	while (j != -1 && array[j] >= array[j + 1]) {
		j--;
	}
	if (j == -1) { // no more swaps condition
		return 0;
	}
	int k = ballsNumber - 1;
	while (array[j] >= array[k]) {
		k--;
	}
	doReswap(array, j, k);
	// sorting the rest of the sequence:
	int l = j + 1, r = ballsNumber - 1;
	while (l < r) {
		doReswap(array, l++, r--);
	}
	return array;
}

int runBallsTask() {
	int ballsNumber, * array;
	cout << "\nEnter the number of balls or 0 to interrupt the task:\n";
	ballsNumber = initializeInteger("notnegative", 0, 0);
	if (isInterrupted(ballsNumber)) {
		return 0;
	}
	array = new int[ballsNumber];
	// filling the array by the balls numbers:
	for (size_t i = 0; i < ballsNumber; i++) {
		array[i] = i + 1;
	}
	// the number of suitable combinations:
	long long result = 1;
	while (findNextSet(array, ballsNumber)) {
		for (size_t i = 0; i <= ballsNumber; i++) {
			if (i == array[i - 1]) {
				result++;
				break;
			}
		}
	}
	cout << "\nThe result is " << result << " suitable combinations.\n";
	return 1;
}

int findFibonacciNumber(int n) {
	// function that finds nth Fibonacci number using recursive algorithm
	if (n < 3) {
		return 1;
	}
	else {
		return findFibonacciNumber(n - 1) + findFibonacciNumber(n - 2);
	}
}

int runStructuralNumbersTask() {
	cout << "\nEnter the position of the Fibonacci number or "
		"0 to interrupt the task:\n";
	int position = initializeInteger("notnegative", 0, 0);
	if (isInterrupted(position)) {
		return 0;
	}
	int number = findFibonacciNumber(position);
	// pretty outout:
	switch (position) {
	case 1:
		cout << "\nThe 1st Fibonacci number is " << number << ".\n";
		break;
	case 2:
		cout << "\nThe 2nd Fibonacci number is " << number << ".\n";
		break;
	case 3:
		cout << "\nThe 3rd Fibonacci number is " << number << ".\n";
		break;
	default:
		cout << "\nThe " << position << "th Fibonacci number is " 
			<< number << ".\n";
		break;
	}
	return 1;
}

int runSubtaskFirst() {
	cout << "\nEnter the cost of the spinner base:\n";
	int baseCost = initializeInteger("positive", 0, 0);
	cout << "\nEnter the cost of the spinner blade:\n";
	int bladeCost = initializeInteger("positive", 0, 0);
	cout << "\nEnter the maximum cost of the spinner:\n";
	int maxCost = initializeInteger("positive", 0, 0);
	// error check:
	if (baseCost > maxCost) {
		cout << "\nBase cost can't be bigger than the maximum cost.\n"
			"None of the spinners'll be sold.\n";
		return 0;
	}
	int bladesNumber = (maxCost - baseCost) / bladeCost;
	cout << "\nThe maximum number of blades is " << bladesNumber << ".\n";
	return 1;
}

int runSubtaskSecond() {
	cout << "\nEnter the number of the spinner blades:\n";
	int bladesNumber = initializeInteger("all", 3, numeric_limits<int>::max());
	if (bladesNumber % 3 == 0)	{
		cout << "\nThe number of spinners with 3 blades is " 
			<< bladesNumber / 3 << ".\n";
		cout << "\nThe number of spinners with 4 blades is 0.\n";
		return 1;
	}
	else if (bladesNumber % 4 == 0) {
		cout << "\nThe number of spinners with 3 blades is 0.\n";
		cout << "\nThe number of spinners with 4 blades is " 
			<< bladesNumber / 4 << ".\n";
		return 1;
	}
	else {
		int n = 1; // the number of 3 blades spinners
		while (bladesNumber > 0) {
			// if there are extra blades and it's impossible 
			//to produce an integer number of spinners:
			if ((bladesNumber - 3 * n) < 0) {
				cout << "\nIt's impossible to produce spinners with the condition "
					"that the total number of blades is " << bladesNumber << ".\n"
					"0\n0\n";
				return 0;
			}
			else if ((bladesNumber - 3 * n) % 4 == 0) {
				cout << "\nThe number of spinners with 3 blades is " 
					<< n << ".\n";
				cout << "\nThe number of spinners with 4 blades is "
					<< (bladesNumber - 3 * n) / 4 << ".\n";
				return 1;
			}
			else {
				n++;
			}
		}
	}
}

void runSubtaskThird() {
	cout << "\nEnter the length of rectangle:\n";
	int length = initializeInteger("positive", 0, 0);
	cout << "\nEnter the width of rectangle:\n";
	int width = initializeInteger("positive", 0, 0);
	// combinatorial formula:
	cout << "\nThe number of possible cut rectangles is "
		<< length * (length + 1) * width * (width + 1) / 4 << ".\n";
}

int runSubtaskFourth() {
	int compartmentsNumber = 9;
	int bigCompartments[9][4];
	int smallCompartments[9][2];
	cout << "\nEnter 0 to interrupt the subtask.";
	cout << "\nEnter the number of available seats:\n";
	int freeSeats = initializeInteger("notnegative", 0, 0);
	if (isInterrupted(freeSeats)) {
		return 0;
	}
	cout << "\nEnter the positions of available seats:\n";
	for (size_t i = 0; i < freeSeats; i++) {
		int position = initializeInteger("notnegative", 0, 0);
		if (isInterrupted(position)) {
			return 0;
		}
		// filling arrays according to the scheme of places:
		else if (position < 37) {
			bigCompartments[(position - 1) / 4][(position - 1) % 4] = 1;
		}
		else {
			smallCompartments[(position - 37) / 2][(position - 37) % 2] = 1;
		}
	}
	// mirror rearrangement of small compartments array elements 
	// to match the train car pattern:
	for (size_t i = 0, j = compartmentsNumber - 1; i < j; ++i, --j) {
		for (size_t k = 0, t = 1; k < 2; ++k, --t)
		{
			int swapVariable = smallCompartments[i][k];
			smallCompartments[i][k] = smallCompartments[j][t];
			smallCompartments[j][t] = swapVariable;
		}
	}
	// number of free compartments running in a row:
	int numberOfConsecutive = 0, maxnumberOfConsecutive = 0;
	for (size_t i = 0; i < compartmentsNumber; i++) {
		int sum = 0;
		for (size_t j = 0; j < 4; j++) {
			if (bigCompartments[i][j] == 1) {
				sum++;
			}
		}
		for (size_t j = 0; j < 2; j++) {
			if (smallCompartments[i][j] == 1) {
				sum++;
			}
		}
		// the whole compartment is free only if 
		// the summary number of it's available seats is 6:
		if (sum == 6) {
			numberOfConsecutive++;
		}
		else {
			if (numberOfConsecutive > maxnumberOfConsecutive) {
				maxnumberOfConsecutive = numberOfConsecutive;
			}
			numberOfConsecutive = 0;
		}
	}
	cout << "\nThe max number of consecutive available compartments is " 
		<< maxnumberOfConsecutive << ".\n";
	return 1;
}

int runSubtaskFifth() {
	cout << "\nEnter 0 to interrupt the subtask.";
	cout << "\nEnter the number of the available seats:\n";
	int seatsNumberMax = initializeInteger("notnegative", 0, 0);
	if (isInterrupted(seatsNumberMax)) {
		return 0;
	}
	// remembering the initial value of available seats:
	int seatsNumberInitial = seatsNumberMax;
	cout << "\nEnter the number of students "
		"(not more than the number of the available seats): \n";
	int studentsNumber = initializeInteger("notnegative", 0, 0);
	if (isInterrupted(studentsNumber) || studentsNumber > seatsNumberMax) {
		return 0;
	}
	// array, which shows the position of each student:
	// 0 - free seat
	// 1 - 9 - the seat was taken by the student with appropriate number
	int* seatsList = new int[seatsNumberMax] { 0 };
	// the position of the next student (in the middle):
	int middleIndex = (seatsNumberMax - 1) / 2;
	// iteration per each student (as if they take turns entering the room):
	for (size_t i = 1; i <= studentsNumber; i++) {
		// "new student is sitting down" in place, defined before:
		seatsList[middleIndex] = i; 
		seatsNumberMax = -1; // max number of consecutive available seats
		middleIndex = -1;
		// intermediate value of the max possible number of seats:
		int seatsNumberIntermediate = 0;
		// iteration per seats to calculate 
		// the middle seat index for next student:
		for (size_t j = 0; j < seatsNumberInitial; j++) {
			if (seatsList[j] == 0 && j != seatsNumberInitial - 1) {
				seatsNumberIntermediate++;
			}
			else {
				if (seatsList[j] == 0 && j == seatsNumberInitial - 1) {
					seatsNumberIntermediate++;
				}
				if (seatsNumberIntermediate > seatsNumberMax) {
					seatsNumberMax = seatsNumberIntermediate;
					// middle is (index of the first + index of the last) / 2:
					middleIndex = ((j - seatsNumberMax + 1) + j) / 2;
				}
				seatsNumberIntermediate = 0;
			}
		}
	}
	int adjacentSeats = 0;
	size_t i = 0, j = seatsNumberInitial - 1;
	// calculating the number of free seats on the left side:
	while (seatsList[i] != studentsNumber) {
		if (seatsList[i] == 0) {
			adjacentSeats++;
		}
		else {
			adjacentSeats = 0;
		}
		i++;
	}
	cout << "\nThe number of seats in the left side of the last student is " 
		<< adjacentSeats << ".";
	adjacentSeats = 0;
	// calculating the number of free seats on the right side:
	while (seatsList[j] != studentsNumber) {
		if (seatsList[j] == 0) {
			adjacentSeats++;
		}
		else {
			adjacentSeats = 0;
		}
		j--;
	}
	cout << "\nThe number of seats in the right side of the last student is "
		<< adjacentSeats << ".\n";
}

int main() {
	int chooseTask;
	setlocale(LC_ALL, "Russian");
	cout << "Hello!\nEnter 1 to run task 'Balls'.\n"
		"Enter 2 to run task 'Structural Numbers'.\n"
		"Enter 3 to run control work tasks.\n"
		"Enter 0 to end the programm.\nEnter the task number:\n";
	chooseTask = initializeInteger("notnegative", 0, 0);
	while (chooseTask > 0) {
		switch (chooseTask) {
		case 1:
			runBallsTask();
			break;
		case 2:
			runStructuralNumbersTask();
			break;
		case 3: {
			cout << "\nEnter 0 to end the choosing of the subtask.\n"
				"Enter the number of subtask:\n";
			int chooseSubtask = initializeInteger("notnegative", 0, 0);
			while (chooseSubtask > 0) {
				switch (chooseSubtask) {
				case 1:
					runSubtaskFirst();
					break;
				case 2:
					runSubtaskSecond();
					break;
				case 3:
					runSubtaskThird();
					break;
				case 4:
					runSubtaskFourth();
					break;
				case 5:
					runSubtaskFifth();
					break;
				default:
					cout << "\nEntered task number is incorrect, try again.\n"
						"Enter 0 to end the choosing of the subtask.\n";
					break;
				}
				cout << "\nEnter the next subtask number:\n";
				chooseSubtask = initializeInteger("notnegative", 0, 0);
			}
			break;
		}
		default:
			cout << "\nEntered task number is incorrect, try again.\n"
				"Task number can't be more than 3.\n"
				"Enter 0 to end the programm.\n";
			break;
		}
		cout << "\nEnter the next task number:\n";
		chooseTask = initializeInteger("notnegative", 0, 0);
	}
}

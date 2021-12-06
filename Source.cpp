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
			if ((i < (int)'0' || i >(int)'9') && i != (int)'-') {
				if (temporaryVariableString.find((char)i) != string::npos) {
					isCorrect = false;
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
			if ((i < (int)'0' || i >(int)'9') &&
				i != (int)'-' && i != (int)'.') {
				if (temporaryVariableString.find((char)i) != string::npos) {
					isCorrect = false;
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

int countFactorial(int value) {
	if (value > 2) {
		return value * countFactorial(value - 1);
	}
	else {
		return value;
	}
}

void doReswap(int* array, int i, int j) { // for "Balls" task
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
	cout << "\nEnter the number of balls:\n";
	ballsNumber = initializeInteger("notnegative", 0, 0);
	if (ballsNumber == 0) {
		cout << "\nThe task was interrupted by user.\n";
		return 0;
	}
	array = new int[ballsNumber];
	for (size_t i = 0; i < ballsNumber; i++) {
		array[i] = i + 1;
	}
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
	if (n < 3) {
		return 1;
	}
	else {
		return findFibonacciNumber(n - 1) + findFibonacciNumber(n - 2);
	}
}

void runStructuralNumbersTask() {
	cout << "\nEnter the position of the Fibonacci number or "
		"0 to interrupt the task:\n";
	int position = initializeInteger("notnegative", 0, 0);
	int number = findFibonacciNumber(position);
	switch (position) {
	case 0:
		cout << "\nThe task was interrupted by user.\n";
		break;
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
}

void f1() {
	
}

void f2() {

}

void f3() {

}

void f4() {

}

void f5() {

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
					f1();
					break;
				case 2:
					f2();
					break;
				case 3:
					f3();
					break;
				case 4:
					f4();
					break;
				case 5:
					f5();
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

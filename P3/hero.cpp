#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isColor(char letter) {
	if (
		letter == 'G' ||
		letter == 'g' ||
		letter == 'R' ||
		letter == 'r' ||
		letter == 'Y' ||
		letter == 'y' ||
		letter == 'B' ||
		letter == 'b' ||
		letter == 'O' ||
		letter == 'o') {
		return true;
	}
	else {
		return false;
	}
}

int toInt(char singleDigit)
{
	return (singleDigit - '0');
}

int toTwoDigitInt(char TensDigit, char OnesDigit)
{
	return (toInt(TensDigit) * 10 + toInt(OnesDigit));
}

int countChars(string s, char c)
{
	int total = 0;
	for (int k = 0; k != s.size(); k++)
	{
		if (s.at(k) == c)
			total++;
	}
	return total;
}


bool hasProperSyntax(string tune) {
	//returns true if parameter is a syntactically correct tune and false otherwise
	if (tune == "")
	{
		return true;
	}
	//	else if ()
	//if zero comes first in the int value, remove/ignore it
	// //can't have more than two consecutive digits
	//can't have two consecutive colors
	//ending with a non-slash returns false
	//for each char in string
	//if it is a letter
	//		not a color return false
	//		if the following char is a letter return false
	//if it is a digit
	//		if the following two chars are digits return false
	//else return true 
	else if ((isalpha(tune.at(tune.size() - 1))) || isdigit(tune.at(tune.size() - 1)))
	{
		return false;
	}
	else if (isdigit(tune.at(0)))
	{
		return false;
	}
	for (int i = 0; i != tune.size(); i++)
	{
		if (!isalpha(tune[i]) && !isdigit(tune[i]) && tune[i] != '/')
		{
			return false;
		}
		else if (isalpha(tune[i]))
		{
			if (!isColor(tune[i]))
			{
				return false;
			}
			else if (isalpha(tune[i + 1]))
			{
				return false;
			}
		}
		else if (isdigit(tune[i]))
		{
			if (isdigit(tune[i + 1]) && isdigit(tune[i + 2]))
			{
				return false;
			}

			else if (tune[i - 1] == '/')
			{
				return false;
			}
		}
	}
	return true;
	}
bool isConvertible(string tune, int& badBeat) {
	int numOfBeats = 0;
	int sustainLength = 0;
	for (int i = 0; i != tune.size(); i++) {
		if (tune[i] == '/') {
			numOfBeats++;
			cout << "i = " << i << endl;
			cout << "tune[i] = " << tune[i] << endl;
			cout << "numOfBeats = " << numOfBeats << endl;
			continue;
		}
		else if (isdigit(tune[i])) {
			if (
				tune[i] == 0 && !isdigit(tune[i + 1]) ||
				tune[i] == 1 && !isdigit(tune[i + 1])
				)
			{
				badBeat = numOfBeats + 1;
				cout << "badBeat = " << badBeat << endl;
				//return 3
				return false;
			}
			else if (isdigit(tune[i + 1])) {
				sustainLength = toTwoDigitInt(tune[i], tune[i + 1]);
				cout << "sus= " << sustainLength << endl;
			}
			else {
				sustainLength = toInt(tune[i]); 
				cout << "sus= " << sustainLength << endl;
			}
			if (tune.size() <= sustainLength + i) {
				// set badBeat to the number of beats in the entire string, plus one
				badBeat = countChars(tune, '/') + 1;
				cout << "badBeat = " << badBeat << endl;
					//return 4
					return false;
			}
			else {

				for (int j = i; j <= i + sustainLength; j++) {
					if (tune[j] != '/') {
						badBeat = numOfBeats + 1;
						cout << "badBeat = " << badBeat << endl;
						//return 2
						return false;
					};
				}
			}

		}
		else continue;
	}
	return true;
}
// int convertTune(string tune, string& instructions, int& badBeat)
// 
// if not synt correct return false
// for each char in tune
// if char is digit
	// if next char is digit
		// convert both chars to an int using toTwoDigitInt
	// else convert the one char to an int using toInt	
	// for each character following the last digit, where i < the converted int 
		// if not / return false

//passing in badbeat by ref (&)
	int main() {
		/*
		cout << hasProperSyntax("///") << endl;
		cout << hasProperSyntax("") << endl;
		cout << hasProperSyntax("////////////////O") << endl;
		cout << hasProperSyntax("////////////////0") << endl;
		cout << hasProperSyntax("1//////") << endl;
		cout << hasProperSyntax("n3") << endl;
		cout << hasProperSyntax("\\") << endl;
		cout << hasProperSyntax("///  ///") << endl;
		cout << hasProperSyntax("//gg") << endl;
		cout << hasProperSyntax("345") << endl;
		cout << hasProperSyntax("///3g/") << endl;
		*/
		cout << isConvertible("o/r3///")
		return 0;
}
		
// not convertible
	// r0/
	// r1/
	// o/r3//
// convertible
	// o/r3///
	// r03///


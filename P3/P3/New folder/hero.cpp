// Alex Wasdahl
/// Project III
//// Computer Science XXXI
///// Professor David Smallberg
////// Spring 2022

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//function specifying the letters, both upper and lowercase, which correspond to colors
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
//makes a char lowercase
char makeLowercase(char upper) {
	if (upper == 'G') { return 'g'; }
	if (upper == 'R') { return 'r'; }
	if (upper == 'Y') { return 'y'; }
	if (upper == 'B') { return 'b'; }
	if (upper == 'O') { return 'o'; }
		return upper; 
}
// makes a char uppercase
char makeUppercase(char lower) {
	if (lower == 'g') { return 'G'; }
	if (lower == 'r') { return 'R'; }
	if (lower == 'y') { return 'Y'; }
	if (lower == 'b') { return 'B'; }
	if (lower == 'o') { return 'O'; }
	return lower;
}
//toInt function converts a char to an int
int toInt(char singleDigit)
{
	return (singleDigit - '0');
}

//toTwoDigitInt conmbines two character inputs to form a two-digit int
int toTwoDigitInt(char TensDigit, char OnesDigit)
{
	return (toInt(TensDigit) * 10 + toInt(OnesDigit));
}

//counts character instances in a string
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

//Given the assortment of symbols provided to you by the game artists at Sitar Hero, check to see if it is a syntactically correct tune 
bool hasProperSyntax(string tune) { //returns true if parameter is a syntactically correct tune and false otherwise
	
	//return true if the tune is an empty string
	if (tune == "") 
	{
		return true;
	}
	
	//	otherwise if the last character in the string is a letter/digit, return false
	else if ((isalpha(tune.at(tune.size() - 1))) || isdigit(tune.at(tune.size() - 1)))
	{
		return false;
	}
	// otherwise if the first character is a digit return false
	else if (isdigit(tune.at(0)))
	{
		return false;
	}
	// loop for each character in the tune parameter 
	for (int i = 0; i != tune.size(); i++)
	{
		// if the character at index i is not a letter, digit, or '/' character
		if (!isalpha(tune[i]) && !isdigit(tune[i]) && (tune[i] != '/'))
		{
			return false;
		}
		// otherwise if char at i is a letter
		else if (isalpha(tune[i]))
		{
			// if letter does not correspond to a color, return false 
			if (!isColor(tune[i]))
			{
				return false;
			}
			// otherwise if the following character is a letter, return false
			else if (isalpha(tune[i + 1]))
			{
				return false;
			}
		}
		// otherwise if char at i is a digit
		else if (isdigit(tune[i]))
		{
			// if digit is followed by two more digits, return false
			if (isdigit(tune[i + 1]) && isdigit(tune[i + 2]))
			{
				return false;
			}
			// otherwise if the previous char is '/', return false 
			else if (tune[i - 1] == '/')
			{
				return false;
			}
		}
	}
	// Otherwise, return true
	return true;
	}
//This int corresponds to multiple outcomes of converting the assortment of symbols provided to you by the game artists at Sitar Hero into proper Sitar Hero software instructions
int convertTune(string tune, string& instructions, int& badBeat) { //passing in instructions and badBeat by reference
	int numOfBeats = 0;
	int numOfBeatsInSustain = 0;
	int sustainLength = 0;
	int sustainLength2 = 0;
	//cout << "tune = " << tune << endl;

	//if the tune does not have proper syntax, leave badBeat unchanged and return 1
	if (!hasProperSyntax(tune)) {
		//cout << "return 1 (improper syntax). badBeat = " << badBeat << endl;
		//return 1
		return 1;
	}
	//loop through each character in tune
	for (int i = 0; i != tune.size(); i++) {
		//cout << "i = " << i << endl;
		//cout << "tune[i] = " << tune[i] << endl;
		//if the char in tune is a /, increment numofBeats
		if (tune[i] == '/') {
			numOfBeats++;
			//cout << "numOfBeats = " << numOfBeats << endl;
			continue;
		}
		//if the char in tune is a digit 
		else if (isdigit(tune[i])) {
			//cout << "tune[i+1] = " << tune[i + 1] << endl;
			//check to see if the following char is a digit. If so convert to two digit int, otherwise convert to one digit int
			if (isdigit(tune[i + 1])) {
				sustainLength = toTwoDigitInt(tune[i], tune[i + 1]);
				//cout << "sustainLength = " << sustainLength << endl;
				i++;
			}
			else {
				sustainLength = toInt(tune[i]); 
				//cout << "sustainLength = " << sustainLength << endl;
			}
			//sustained note smaller than 2: badBeat set to beat number and return 3
			if (sustainLength < 2) {
				badBeat = numOfBeats + 1;
				//cout << "return 3 (sustained note <2). badBeat = " << badBeat << endl;
				//return 3
				return 3;
			}
			if (tune.size() <= sustainLength + i) {
				// set badBeat to the number of beats in the entire string, plus one
				badBeat = countChars(tune, '/') + 1;
				//cout << "return 4 (unfinished tune). badBeat = " << badBeat << endl;
					//return 4
					return 4;
			}
			else {
				// make sure the sustain note does not get interrupted by iterating through the length of the sustain
				for (int j = i + 1; j <= i + sustainLength; j++) {
					//cout << "j = " << j << endl;
					//cout << "tune[j] = " << tune[j] << endl;
					if (tune[j] == '/') { 
						numOfBeatsInSustain++; 
						//cout << "number of beats in sustain = " << numOfBeatsInSustain << endl;
					}
					else{
						badBeat = numOfBeats + numOfBeatsInSustain + 1;
						
						//cout << "return 2 (sustained note broken by beat). badBeat = " << badBeat << endl;
						//return 2
						return 2;
					};
				}
				numOfBeatsInSustain = 0;
			}

		}
		else continue;
	}
	//Now we've checked the syntax
	//If the first character is a /, loop through the entire toon adding an x to instructions for each / until a char that isn't / is hit
	if (tune[0] == '/') {
		for (int k = 0; k <= tune.size() - 1; k++) {
			//cout << "k= " << k << endl;
			if (tune[k] != '/') {
				break;
			}
			else {
				instructions.push_back('x');
				//cout << instructions << endl;
			}
		}
	}
	//Loop through the entire toon evaluating each character
	for (int i = 0; i < tune.size() - 1; i++) {
		if (isColor(tune[i])) {
			//if the character is a color followed by a /, then add a lowercase letter for that color to instructions
			if (tune[i + 1] == '/') {
				instructions.push_back(makeLowercase(tune[i]));
				//cout << instructions << endl;
			}
		}
		else if (isdigit(tune[i])){
			if (isdigit(tune[i + 1])) {
				sustainLength2 = toTwoDigitInt(tune[i], tune[i + 1]);
				//cout << "sustainLength = " << sustainLength2 << endl;
				i++;
				//cout << "i++; i= " << i << endl;
				for (int j = 0; j < sustainLength2; j++) {
					instructions.push_back(makeUppercase(tune[i-2]));
					//cout << instructions << endl;
				}
			}
			else {
				sustainLength2 = toInt(tune[i]);
				for (int j = 0; j < sustainLength2; j++) {
					instructions.push_back(makeUppercase(tune[i-1]));
					//cout << instructions << endl;
				}
				//cout << "sustainLength = " << sustainLength2 << endl;
			}
			for (int j = (i + 1 + sustainLength2); j <= tune.size() - 1; j++) {
				//cout << "j= " << j << endl;
				if (tune[j] != '/') { 
					break; 
				}
				else {
					instructions.push_back('x');
					//cout << instructions << endl; 
				}
			}
		}
		
	}
	//cout << instructions << endl;
	return 0;
}

	int main() {
		//Test case
		//int badB;
		//string ins;
		//cout << convertTune("g/G/g/B/g2///g3///", ins, badB);
		//return 0;
}



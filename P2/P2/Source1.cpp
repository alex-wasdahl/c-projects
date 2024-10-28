/* 
Alex Wasdahl
Project 2
CS31 Spring 2022

This program calculates the water & power bill amount in dollars for a given customer.

Input: meter readings at start/end of billing cycle, customer name, month of end reading
* Meter readings are integers measured in HCF (hundred cubic feet)
* HCF used = end reading - start reading
* High usage season: Apr-Oct / Low usage season: Nov-Mar
* Season is determined by month of end reading
* High season: First 23 HCF billed at $5.41/HCF, rest billed at $9.79/HCF
* Low season: First 15 HCF billed at $5.41/HCF, rest billed at $7.77/HCF
* */
#include <iostream>
#include <string>
using namespace std;
int main() {
	int initialMeterReading;
	int finalMeterReading;
	string customerName;
	int monthNumber;
	string season;
	int billValue = 0; 
	
	/* Prompt user for input: meter readings at start/end of billing cycle, customer name, month of end reading*/
	cout << "Initial meter reading: ";
	cin >> initialMeterReading;
	cout << "Final meter reading: ";
	cin >> finalMeterReading;
	cout << "Customer name: ";
	cin >> customerName;
	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	cin >> monthNumber;
	cout << "---" << endl;

	/*total HCF (hundred cubic feet) used is equal to the difference between final and initial meter readings*/
	int HCFUsed = finalMeterReading - initialMeterReading;

	/*If the month of end reading is within high usage season, the first 23 HCF billed at $5.41/HCF, rest billed at $9.79/HCF*/
	if (monthNumber >= 4 && monthNumber <= 10) {
		season = "High";
		if (HCFUsed >= 23) {
			billValue = (23 * 5.41) + ((HCFUsed - 23) * 9.79);
		}
		else {
			billValue = HCFUsed * 5.41;
		}
	}
	/*Otherwise the month of end reading is within low usage season - first 15 HCF billed at $5.41/HCF, rest billed at $7.77/HCF*/
	else {
		season = "Low";
		if (HCFUsed >= 15) {
			billValue = (15 * 5.41) + ((HCFUsed - 15) * 7.77);
		}
		else {
			billValue = HCFUsed * 5.41;
		}
	}
	/*return different textual outputs based on erroneous user input*/
	if (initialMeterReading < 0) {
		cout << "The initial meter reading must not be negative." << endl;
	}
	else if (finalMeterReading < initialMeterReading) {
		cout << "The final meter reading must be at least as large as the initial reading." << endl;
	}
	else if (customerName == "") {
		cout << "You must enter a customer name." << endl;
	}
	else if (monthNumber < 1 || monthNumber > 12) {
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	/*If user input is appropriate, output bill value for customer*/
	else {
		cout << "The bill for " << customerName << " is $" << billValue << endl;
	}
}
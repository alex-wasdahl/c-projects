#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Return the position of the first element that is not <= the one
// that follows it.  Return -1 if there are no such elements.
/* int findFirstDisorder(const string a[], int n)
{
    for (int k = 0; k < n - 1; k++)
        if (a[k] > a[k + 1])
            return k;
    return -1;
}

int main() //Thoroughly test functions in main routine
{
    string p[5] = { "clarence", "john", "sonia", "neil", "ketanji" };
    assert(findFirstDisorder(p, 5) == 2);
    assert(findFirstDisorder(p, 4) == 2);
    assert(findFirstDisorder(p, 3) == -1);
    assert(findFirstDisorder(p, 2) == -1);
    assert(findFirstDisorder(p, 1) == -1);
    assert(findFirstDisorder(p, 0) == -1); // No disorder in empty array
      // There should be another test that passes a bad argument
    cout << "All tests succeeded" << endl;
}  */
// produce a library that provides functions for many common manipulations of arrays of strings

// All of the functions you must write take at least two parameters: an array of strings, and the number of items the function will consider to be part of the array, starting from the beginning

// The source file you turn in will contain all the functions and a main routine. You can have the main routine do whatever you want, because we will rename it to something harmless, never call it, and append our own main routine to your file. 

// all functions that return an int must return -1 if passed any bad args (e.g. negative array size or position requiring look past last element of interest)

// The one error your function implementations don't have to handle (and thus we won't test for) is when the caller of the function says to examine more items in the array than it actually has


int enumerate(const string a[], int n, string target)
// return the number of strings in the array that are equal to target
{
    int count = 0; //initiate counter variable
    if (n < 0) { return -1; }  //return -1 if passed in a negative number for n
    for (int i = 0; i < n; i++) {
        if (a[i] == target)
        {
            count++; // add 1 to counter if item i is the target string
        }
    }
    return count;
}

int findMatch(const string a[], int n, string target)
// return the position of a string in the array that is equal to target (smallest position if multiple strings)
{
    if (n < 0) { return -1; } //return -1 if passed in a negative number for n
    for (int i = 0; i < n; i++) {
        if (a[i] == target) 
        {
            return i; //return the index of the target if it is found
        }
    }
    return -1;
}

//custom findMatch function that includes an additional parameter for the current index at which to begin searching - used as helper function in subsequence
int findMatchCustom(const string a[], int n, string target, int currIndex)
// return the position of a string in the array that is equal to target (smallest position if multiple strings)
{
    //cout << "target " << target << endl;
    if (n < 0) { return -1; }
    for (int i = currIndex; i < n; i++) {
        if (a[i] == target)
        {
            //cout << "found a match, a[i] == target at index i = " << i << endl;
            return i;
        }
    }
    //cout << "no match" << endl;
    return -1;
}


bool findRun(const string a[], int n, string target, int& begin, int& end)
// find the earliest occurrence in array of one or more consecutive strings equal to target
// set begin and end to position of first and last occurence and return true
{
    int consecutive = 0; // initiate counter of consecutive variables
    if (n < 0) { return false; } // if n negative or no string in array equal to target, leave begin and end unchanged and return false
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            if (consecutive == 0) { //if this target is the first in sequence, set the begin parameter to its index
                begin = i;
            }
            consecutive++; //add to the counter
        }
        else if (consecutive > 0) { //if the counter is not zero and item i is not the target, the sequence has ended; set the end parameter to the previous index
            end = i - 1;
            return true;
        }       
    }
    return false;
}

int findMin(const string a[], int n)
// return the position of the "minimum string" (string that is <= every string in the array)
// If more than one, return smallest position number
// Return -1 if function should consider no elements to be part of array;
{
    string minString = a[0]; //set minString to the first item
    int minStringIndex = 0;
    if (n <= 0) { return -1; } //return -1 if passed in a negative number for n
    for (int i = 0; i < n; i++) {
        if (a[i] < minString) { // compare each item in the array to the minString; if it is less, make it the new minString
            minString = a[i];
            minStringIndex = i;
        }
    }
    return minStringIndex;
}

int moveToEnd(string a[], int n, int pos)
{
    string temp = a[pos]; //store the item at index pos into a temporary variable
    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1]; //copy all elements after the item at index pos one to the left
    }
    a[n - 1] = temp; //put the eliminated value (stored in temp) at the last position the array knows about
    return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
    string temp = a[pos]; //store the item at index pos into a temporary variable
    for (int i = pos; i > 0; i--) {
        a[i] = a[i - 1]; //copy all elements before the item at index pos one to the right
    }
    a[0] = temp;
    return pos; //put the eliminated value (stored in temp) at the first posn in the array
}

int findDifference(const string a1[], int n1, const string a2[], int n2)
{
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (j == i) { //for each item at a particular index in two arrays
                if (a1[i] != a2[j]) { //if the items are not equal return either of their index values
                    return j; 
                }
            }
        }

    }
    if (n1 <= n2) { return n1; } //otherwise return the number of the smaller of the two arrays 
    else return n2;
    //Return the position of the first corresponding elements of two arrays that are not equal
    //n1 and n2 are numbers of interesting elements in each array
    //equal up until both run out? return whichever value of n1 and n2 <= the other
}

int removeDups(string a[], int n) {
    // remove duplicates in sequences of consecutive identical items in array
    int dups = 0; //initiate counter
    for (int i = 0; i < n - 1; i++) {
        if (a[i] == a[i + 1]) { //if the item is equal to the one following it, augment the counter
            dups ++;
        }
    }
    for (int i = 0; i < n - 1; i++) { //move all duplicates to the end
        while (a[i] == a[i + 1]) {
            moveToEnd(a, n, i);
        }
    }

    return n - dups; //number of total items in array - number of duplicates = num of unique items
}

bool subsequence(const string a1[], int n1, const string a2[], int n2) {
    //if all n2 elements of a2 appear in a1 in the same order (but not necessarily consecutively) return true
    if (n2 > n1) { return false; }
    int currIndex = 0;
    for (int i = currIndex; i < n2; i++) { // for each element in the shorter array a2
        int z = findMatchCustom(a1, n1, a2[i], currIndex);
        //cout << "z: " << z << endl;
        if (z == -1) { return false; } // if it's not in longer array a1 return false
        else currIndex = z + 1; // otherwise find its position in longer array a1 and set currIndex to the following position 
        //cout << "currIndex: " << currIndex << endl;

    }
    return true;
}
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
    //Given two arrays that are in nondecreasing order, place in result all elements of both arrays arranged in nondecreasing order and return the # of elements so placed
    bool nonDec = true;
    for (int i = 0; i < n1 - 1; i++) {
        if (a1[i] > a1[i + 1]) { nonDec = false; }
    }
    for (int j = 0; j < n2 - 1; j++) {
        if (a2[j] > a2[j + 1]) { nonDec = false; }
    }
    if (nonDec == false) { return -1; } // if either array is non alphabetical order return -1
    int k = 0; // initiate counters for result index and startIndex for second array
    int currIndex = 0;
    int startIndex = 0;
    for (int i = 0; i < n1; i++) { //for each item in first array
        for (int j = startIndex; j < n2; j++) { //for each item in second array
            if (a2[j] <= a1[i]) { //if the second array item goes before the first array item alphabetically place it in result and augment the counters
                result[k] = a2[j];
                k++;
                currIndex++;
                startIndex++;

            }
        }
        result[k] = a1[i]; //after the second array items have been looped through place the first array item in result and augment the result counter
        k++;
    }
    for (int j = currIndex; j < n2; j++) {//place remaining second array items in result
        result[k] = a2[j];
        k++;
    }
    return k;
}

int divide(string a[], int n, string divider) {
    //rearrange elements in array such that elements < divider come first (in any order) and elements > divider come last (in any order)
    for (int i = 0; i < n; i++) {
        if (a[i] < divider) { //if an element is < divider move it to the beginning
            moveToBeginning(a, n, i);
        }
        if (a[i] > divider) {
            moveToEnd(a, n, i); // if > divider move to end
        }
    }
    for (int i = 0; i < n; i++) { //find first item >= divider and return it
        if (a[i] >= divider) {
            return i;
        }
    
    }
    return 0;
}
int main() {
}

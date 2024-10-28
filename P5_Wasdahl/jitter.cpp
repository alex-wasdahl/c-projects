#include <iostream>
#include <cassert>

using namespace std;
// a match standard is:
// distance (positive int): max distance of words between w1 and w2 (inclusive of w2)
// w1 (C string): word to match
// w2 (C string): word to match

// a set of match standards are represented by:
// an array of distances (positive ints) e.g. 
// an array of w1s (C strings)
// an array of w2s (C strings)
// with the ith index into all three arrays corresp to the ith match standard in the set 

// a set of match standards is in standard form when
// every distance is positive
// every word is at least one letter long and contains no chars other than lower case letters
// for each match standard in collection no other standard has same w1 and w2 word

const int MAX_WORD_LENGTH = 20;
const int MAX_JEET_LENGTH = 280;

void removeMatchStandardWord(char a[][MAX_WORD_LENGTH + 1], int n, int pos)
{
    for (int i = pos; i < n - 1; i++) {
        for (int j = 0; j < MAX_WORD_LENGTH; j++) {
            a[i][j] = a[i + 1][j];
        }
    }
}

void removeMatchStandardDistance(int a[], int n, int pos)
{
    int temp = a[pos]; //store the item at index pos into a temporary variable
    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1]; //copy all elements after the item at index pos one to the left
    }
    a[n - 1] = temp;
}
/*
bool isSameWord(const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], int i)
{
    for (int j = 0; j < MAX_WORD_LENGTH + 1; j++) {
        if (word1[i][j] != word2[i][j]) { return false; }
    }
    return true;
}
int isInJeet(const char word1[][MAX_WORD_LENGTH + 1], const char jeet[][MAX_WORD_LENGTH + 1]) {
    for (int j = 0; )
    for (int i = 0; i < (sizeof(word1) / sizeof(word1[0])); i++) {
        if (strcmp(word1[i], &jeet[i][0]) == 0)
    }
}
*/
int findFirstLetterInJeet(const char jeet[]) {
    for (int i = 0; i < MAX_JEET_LENGTH; i++) {
        if (isalpha(jeet[i])) {
            return i;
        }
    }
    return -99;
}

int findWordInJeetArray(const char word[], const char jeetArray[][MAX_JEET_LENGTH]) {
    for (int j = 0; j < MAX_JEET_LENGTH; j++) {
        if (strcmp(word, jeetArray[j]) == 0) { return j; }
    }
    return -99;
}

int editStandards(int distance[], char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nStandards)
{
    //nStandards is # of match standards -- they are located in positions 0 through nStandards-1 of the array 

    //remove every match standard for which at least one of these conditions hold:
    //distance is not positive
    //word in standard contains no chars or contains char that is not letter

    //if two standards hae same w1 and w2 values remove the one whose distance value is the lesser of the two distance values
    // if >1 match standards have same w1/w2/distance values, remove all but one of those standards 

    //word1 and word2 parameters - tables with undefined # of rows and 21 columns?

    /*__________PSEUDOCODE__________
    * If nStandards <= 0 return 0
    * int removedMatchStandards = 0
    * For i = 0, i < nStandards, i++
    *   if distance[i] <= 0, send distance[i] word1[i] and word2[i] to back?? Add to a counter that tracks the removed match standards (which will eventually be subtracted from nStandards)??
    *   if !isalpha(word1[i]) or !isalpha(word2[i]), send distance[i] word1[i] and word2[i] to back?? Add to a counter that tracks the removed match standards??
    *   if isupper(word1[i]), tolower(word1[i])
    *   if isupper(word2[i]), tolower(word2[i])
    * For i = 0 (same as above - need new loop for removing duplicates after cases have been corrected)
    *   For j = i, j < nStandards, j++
    *       if word1[i] == word1[j] AND word2[i] == word[j]
    *           if distance[i] < distance[j] send distance[i] word1[i] and word2[i] to back?? Add to a counter that tracks the removed match standards??
    *           else send distance[j] word1[j] and word2[j] to back?? Add to a counter that tracks the removed match standards??
    * return number of standards in set
    * */
    if (nStandards <= 0) { return 0; }; // If nStandards <= 0 return 0
    int removedSets = 0; // initialize a counter for removed MS (match standard) sets
    int i;
    int j;
    for (i = 0; i < (nStandards - removedSets); i++) {
        cout << "i (row) = " << i << endl;
        cout << "distance = " << distance[i] << ", word1[i] = " << word1[i] << ", word2[i] = " << word2[i] << endl;
        if (distance[i] <= 0) { //remove any MS sets for which distance is less than or equal to 0
            // if distance[i] <= 0, send distance[i] word1[i] and word2[i] to back?? Add to a counter that tracks the removed match standards (which will eventually be subtracted from nStandards)??
            removeMatchStandardDistance(distance, nStandards, i);
            removeMatchStandardWord(word1, nStandards, i);
            removeMatchStandardWord(word2, nStandards, i);
            removedSets++;
            continue;
        }
        for (j = 0; j < MAX_WORD_LENGTH; j++) { //remove any MS sets for which either word contains a non-alphabetic character
            // if !isalpha(word1[i]) or !isalpha(word2[i]), send distance[i] word1[i] and word2[i] to back?? Add to a counter that tracks the removed match standards??
            cout << "j (column) = " << j << endl;
            // cout << "word1[i][j] = " << word1[i][j] << ", word2[i][j] = " << word2[i][j] << endl;
            if (
                (!isalpha(word1[i][j]) && isprint(word1[i][j])) ||
                (!isalpha(word2[i][j]) && isprint(word2[i][j]))) {
                cout << "found invalid character in either word1 or word2" << endl;
                removeMatchStandardDistance(distance, nStandards, i);
                removeMatchStandardWord(word1, nStandards, i);
                removeMatchStandardWord(word2, nStandards, i);
                removedSets++;
                cout << "removedSets = " << removedSets << ". Breaking out of j loop." << endl;
                break;
            }
            if (isupper(word1[i][j])) { //convert uppercase to lowercase in word 1
                word1[i][j] = tolower(word1[i][j]);
            }
            if (isupper(word2[i][j])) {//convert uppercase to lowercase in word 2
                word2[i][j] = tolower(word2[i][j]);
            }
        }
    }
    for (i = 0; i < (nStandards - removedSets); i++) { // For i = 0 (same as above - need new loop for removing duplicates after cases have been corrected)
        cout << "removing duplicates: i (row) = " << i << endl;
        cout << "distance = " << distance[i] << ", word1[i] = " << word1[i] << ", word2[i] = " << word2[i] << endl;
        for (j = i + 1; j < (nStandards - removedSets); j++) { // iterate within the word1 and word2 arrays for duplicate match standard word combinations
            cout << "j (second row) = " << j << endl;
            cout << "word1[i] = " << word1[i] << ", word1[j] = " << word1[j] << endl;
            cout << "word2[i] = " << word2[i] << ", word2[j] = " << word2[j] << endl;
            while ((strcmp(word1[i], word1[j]) == 0) && (strcmp(word2[i], word2[j]) == 0)) //while duplicate exists, remove the duplicate with the lower distance 
            {
                cout << "found duplicate word1/word2 combo" << endl;
                cout << "distance[i] = " << distance[i] << " , distance[j] = " << distance[j] << endl;
                if (distance[i] < distance[j]) {
                    removeMatchStandardDistance(distance, nStandards, i);
                    removeMatchStandardWord(word1, nStandards, i);
                    removeMatchStandardWord(word2, nStandards, i);
                    removedSets++;
                    cout << "removedSets = " << removedSets << endl;
                }
                else {
                    removeMatchStandardDistance(distance, nStandards, j);
                    removeMatchStandardWord(word1, nStandards, j);
                    removeMatchStandardWord(word2, nStandards, j);
                    removedSets++;
                    cout << "removedSets = " << removedSets << endl;
                }
            }
        }
    }
    cout << nStandards << " - " << removedSets << " = " << (nStandards - removedSets) << endl;
    for (i = 0; i < nStandards - removedSets; i++) {
        cout << "row " << i << " | distance: " << distance[i] << ", word1: " << word1[i] << ", word2: " << word2[i] << endl;
    }
    return (nStandards - removedSets); //return the set of match standards in standard form, which is the number of MS sets inputted minus the number of removed MS sets
}

int determineMatchLevel(const int distance[],
    const char word1[][MAX_WORD_LENGTH + 1],
    const char word2[][MAX_WORD_LENGTH + 1],
    int nStandards,
    const char jeet[]) {
    //function assumes match standards are in standard form; does not need to check
    //assume jeet is <= 280 chars; does not need to check
    //function returns match level of jeet (number of match standards in a set that the jeet matches)
    //treat negative nStandards parameter as 0
    //in jeet: treat uppercase as lowercase, ignore all non-alphab chars other than space
    //function can't modify jeet but can copy it into local variable 
    //do not declare any local arrays whose size is not known at compile time

    /* PSEUDOCODE
    * f
    * standardsMet = 0; initialize counter
    * cleanjeet = [] init clean jeet array
    * new2Darray = [][] init 2D array for storing each string in the jeet
    * for char in jeet
    *   if isupper char, char = tolower char
    *   if isalpha or isspace, append to new 1D array clean jeet
    * for char in (now clean) jeet
    *   if isalpha
    * for ith (row number) MS index
    *   for jth (column number)
    *   for char in (now clean) jeet
    *       if isalpha, append to newarray[i][j] and j++
    *       if isspace, i++
    *
    */


    int standardsMet = 0;
    int columnVal = 0;
    char cleanedJeet[MAX_JEET_LENGTH + 1];
    strcpy(cleanedJeet, '\0');
    char wordsInJeet[MAX_JEET_LENGTH + 1][MAX_JEET_LENGTH + 1] = { '\0' };
    cout << "size of cleaned jeet = " << sizeof(cleanedJeet) << endl;
    /*
      for (int i = 0; i < MAX_JEET_LENGTH + 1; i++) //clean the jeet (including removing any loose spaces from beginning)
      {
          char x[] = { tolower(jeet[i]), '\0'};
          cout << x[0];

          if (isalpha(x[0])) {
             strcat_s(cleanedJeet, x);
          }
          if (isspace(x[0])) {
             strcat_s(cleanedJeet, x);
          }
          //strcat needs both to be char array
      }

          /*
          int j = 0;
          int k = 0;

          for (int i = 0; i < MAX_JEET_LENGTH; i++) //turn the jeet into an array of C-strings representing the words in the jeet
          {
              if (isalpha(cleanedJeet[i])) {
                  wordsInJeet[j][k] = cleanedJeet[i];
                  k++;
              }
              if (isspace(cleanedJeet[i])) {
                  j++;
                  k = 0;
              }
              else break;
          }
          //find word in jeet function bool
          // strcpy setting cleaned jeet to empty string set every words in jeet to empty string
          // for distance[i]
              //if both w1[i] and w2[i] are found in the jeet
              //if w1 is before w2
              // calculate the distance
          /*
          for (int i = 0; i < (sizeof(word1)/sizeof(word1[0])); i++) {
              int word1InJeet = findWordInJeetArray(word1[i], wordsInJeet);
              int word2InJeet = findWordInJeetArray(word2[i], wordsInJeet);
              if (distance[i] < word2InJeet - word1InJeet && word1InJeet > 0 && word2InJeet > 0) {
                  standardsMet++;
              }
          }

          cout << "match level = " << standardsMet << endl;*/
    return 0;
}

int main()
{
    /*
    int dists[7] = {2, 4, 1, 3, 2, 1, 13};
    char w1s[7][MAX_WORD_LENGTH + 1] = { "eccentric", "space", "ELECTRIC", "tunnel-boring", "space", "Electric", "were" };
    char w2s[7][MAX_WORD_LENGTH + 1] = { "billionaire","capsule","CAR","equipment","capsule","car","eccentric" };
    //editStandards(dists, w1s, w2s, 7);
    char jeet1[280] = "the eccentric outspoken billionaire launched a space station cargo capsule";
    determineMatchLevel(dists, w1s, w2s, 7, jeet1);
    */
    /*
    const int TEST1_NSTANDARDS = 4;
    int test1dist[TEST1_NSTANDARDS] = {
        2,             4,         1,         13
    };
    char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH + 1] = {
        "eccentric",   "space",  "electric", "were"
    };
    char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH + 1] = {
        "billionaire", "capsule", "car",     "eccentric"
    };
    determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
      "The eccentric outspoken billionaire launched a space station cargo capsule."
      );
      */
}
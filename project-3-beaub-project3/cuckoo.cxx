// Assignment 3: Cuckoo Hashing algorithm
// Doina Bein
// An open addressing method called Cuckoo Hashing
// INPUT: an input file containing strings of maximum 255 characters,
// one string per line
// OUTPUT: a detailed list of where the strings are inserted.

#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

// cuckoo tables' size
const int tablesize = 17;
// combine the two 1-dimensional table into one 2-dimensional table
char  t[tablesize][2][255];

const int prime = 37;
// define the prime number used in calculating the hash values

// compute the hash functions
size_t f(char*, size_t);

// place a string in one of the hash tables
bool place_in_hash_tables (char*);

int main() {

  // the strings to be stored in the hash tables
  char s[255]="";
  char null_st[] ="";
  size_t i, len;
  bool placed;

  // clear the tables
  for(i=0; i< tablesize; i++) {
    strcpy(t[i][0], null_st);
    strcpy(t[i][1], null_st);
  }

  char filename[255] = "";

   // display the header
  cout << endl << "CPSC 335-x - Programming Assignment #4: ";
  cout << "Cuckoo Hashing algorithm" << endl;

  // read the strings from a file
  cout << "Input the file name (no spaces)!" << endl;
  cin >> filename;

  // open the file for reading
  FILE *file = fopen ( filename, "r" );
  if ( file != NULL )
    {
      /* read line by line from the file */
      while ( fgets ( s, 255, file ) != NULL ) {
	// place null character at the end of the line instead of <return>
	len = strlen(s);
	s[len-2]='\0'; // you may need to change this line to s[len-1]='\0'
	// insert the string in the cuckoo table
	placed = place_in_hash_tables(s);
	// check whether the placement was successful
	if (!placed) {
	  cout << "Placement has failed" << endl;
	  return -1;
	}
      }
      fclose ( file );
    }
  else
    {
      perror ( filename ); /* why didn't the file open? */
    }
  return 0;

}


bool place_in_hash_tables (char *s) {

  bool placed;
  size_t pos;
  int index;
  char temp_s[255], temp[255];

  strcpy(temp_s, s);

  // use a counter to detect loops; if counter >= 2*tablesize, then loop
  int counter = 0;

  // start with table T1
  index = 0;

  placed = false;

  pos = f(temp_s, index);

  while((!placed ) && (counter < 2*tablesize)) {

    if (strcmp(t[pos][index], "") == 0 ) {
      cout << "String <" << temp_s << "> will be placed at";
      cout  << " t[" << pos <<"][" << index << "]" << endl;
      strcpy(t[pos][index], temp_s);
      placed = true;
      return placed;
    }
    else {
      // entry at index <pos> in the <index> hash table is not available
      // so obtain the string stored over there in variable <temp> and place
      // the string <temp_s> there
      // now the string <temp> needs to be placed in the other table
      cout << "String <" << temp_s << "> will be placed at" << " t[" << pos;
      cout <<"][" << index << "]" << " replacing <" << t[pos][index] << ">";
      cout << endl;

      // Get the value in the current "nest" i.e. kick out value to move
      strcpy(temp, t[pos][index]);
      // Store new value into the current "nest" i.e. put in new value
      strcpy(t[pos][index], temp_s);
      // Move the "kicked out" value into the 'temp_s' var
      strcpy(temp_s, temp);

      // Switch index value to use the other hash function and get result
      index = index ? 0 : 1;
      pos = f(temp_s, index);
      counter ++;
    }
  }
  return placed;
};


// oompute the hash functions
size_t f(char *s, size_t index) {
  size_t po, len;
  int val, temp;
  int i;
  po = 1;

  len = strlen(s);

  if (index == 0) {
    val = s[0];
    val = val % tablesize;
    if (val < 0) val += tablesize;

    if (len == 1)
      return val;

    for (i = 1; i < int(len); i++) // needed to static cast len to avoid warning
    {
      temp = s[i];
      po *= prime;

      po = po % tablesize;
      if (po < 0) po += tablesize;

      val += temp * po;
      val = val % tablesize;

      if (val < 0) val += tablesize;
    }
    return val;
}
  else {
    // Hash function(2)
    // Computes the summation of 37(given)^j + asciiValue of string[i]
    // where j begins at string.length-1(the last char), and i begins at 0
    val = s[len-1];
    val = val % tablesize;
    if (val < 0) val += tablesize;

    if (len == 1)
      return val;

    for (i = len-2; i >= 0; i--)
    {
      temp = s[i];
      po *= prime;

      po = po % tablesize;
      if (po < 0) po += tablesize;

      val += temp * po;
      val = val % tablesize;

      if (val < 0) val += tablesize;
    }
    return val;
 }
}

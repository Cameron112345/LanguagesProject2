// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	short book, chap, verse; //placeholders
	string::size_type endPos = s.find_first_of(":"); //finds position of first colon
	book = atoi(s.substr(0, endPos).c_str()); //book number is the substring leading up to the first colon
	string::size_type startPos = endPos + 1; //position after the first colon
	endPos = s.find_first_of(":", startPos) - 1; //position of the second colon
	chap = atoi(s.substr(startPos, (endPos - startPos) + 1).c_str()); //chapter number is substring from after first colon to before second colon
	startPos = endPos + 2; //position after second colon
	endPos = s.find_first_of(" ") - 1; //position before the space before the verse text
	verse = atoi(s.substr(startPos, (endPos - startPos) + 1).c_str()); //verse number is the substring from after the second colon to the character before the first space

	verseRef = Ref(book, chap, verse);
	verseText = s.substr(endPos + 2); //verse text is the rest of the line after the reference
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
	return verseText;
}

Ref Verse::getRef() {
	return verseRef;
}

// display reference and verse
void Verse::display() {
    verseRef.display();
    cout << " " << verseText << "\n";
 }

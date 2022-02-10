/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Bible.h"
#include "Verse.h"
#include "Ref.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  // Convert and check input data
  bool validInput = true;
  
  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */


  int bookNum = book->getIntegerValue();
  int chapterNum = chapter->getIntegerValue();
  int verseNum = verse->getIntegerValue();



  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */

  Bible webBible("/home/camcole/project2/web-complete");
  LookupResult result;
  Ref ref(bookNum, chapterNum, verseNum);
  Verse verseObject;
  verseObject = webBible.lookup(ref, result);
  cout << "Search Type: <b>" << **st << "</b>";

  int lastChap = 0;

  for (int x = 0; x < nv->getIntegerValue(); x++) {
	  validInput = true;
	  
	  if (result != SUCCESS)
		  validInput = false;

	  if (validInput) {
		  string verseText = verseObject.getVerse();
		  int currentChap = verseObject.getRef().getChap();

		  if (lastChap != currentChap) {
			  cout << "<p>" << verseObject.getRef().getBookName() << " " << currentChap << "</p>";
		  }
		  lastChap = currentChap;
		  
		  cout << "<p>" << verseObject.getRef().getVerse()
			  << " " << verseText<< "</p>" << endl;
	  }
	  else {
		  string errorMessage = webBible.error(result, ref);
		  cout << "<p><em>" << errorMessage << "</em></p>" << endl;
		  return 0;
	  }
	  verseObject = webBible.nextVerse(result);
	  
  }
  


  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */
 
  
  return 0;
}

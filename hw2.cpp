// Anders Dahl

/* Assingment 2 "Get the Point" source file
*
*	Topics: Multidimensional Arrays, Pointers, Dynamic Allocation, Structs
*
*/
#include<iostream>
#include<cstring>
#include<string>
using namespace std;


/* Globally defined constants
*/
const int MAX_WORD_SIZE = 20;


/* Words structure
*
*	This has three member variables list: which will contain a list 
*	of cstrings, size: the max number of words the list can store and 
*	num_words: the number of cstrings in list. 
*/

struct Words {

public:
	unsigned int num_words;		// Number of words currently in list
	unsigned int max_words;     // The total size allocated to the list.
	char **list;		        // The list storing the words
};



/* Function prototypes: 
*	To be implemented
*/

Words * newList(const unsigned int max_words); 
Words * newList(const char words[]); 
int deleteList(Words *p_w); 
int printList(Words *p_w); 
int appendList(Words *p_w, const char words[]); 
int appendList(Words *dst, const Words *src);
char* findWord(const Words *p_w, const char word[]);
int removeWord(Words *p_w, const char word[]); 



/* Main function
*
* Note the newList and deleteList functions must be implemented before appendList so the 
* calls to appendList are initally commented out.
* Your code should work with the main below. Including the appendList functionality that is initially commented out.
*/


int main() 
{
	Words *pokemon, *tb, *pokemon1, *tb1;
	char *word;
	int ok=0;
	string poke="charmeleon mewtwo pikachu charmander squirtle caterpie raichu squirtle squirtle butterfree abra kadabra alakazam slowpoke spoink";
	char team_a[]="rayquaza mew snorlax";
	string team_b="weavile shuckle ampharos toxicroak mrmime";
	string team_c="weavile     shuckle   ampharos    toxicroak    mrmime";
	string team_d="    weavile     shuckle   ampharos    toxicroak    mrmime     ";
	string team_e="weavile     shuckssssssssssssssssssssssssssssssssle   ampharos    toxicroak    mrmime"; // Should fail above 20 characters for one word
	char team_f[]="rayquaza mew snorlax    ";


	pokemon=newList(5);
	pokemon=newList(15); // 	Words * newList(const unsigned int max_words);
	pokemon=newList(20);

	ok=deleteList(pokemon); // int deleteList(Words *p_w); 
	cout << "OK? "<< ok << endl;

	pokemon=newList(poke.c_str()); // Words * newList(const char words[]);
	tb=newList(team_a); // Words * newList(const char words[]);
	cout << "*pokemon"<< endl;
	printList(pokemon); // int printList(Words *p_w); 
	cout << "*tb"<< endl;
	printList(tb); // int printList(Words *p_w);

	pokemon1=newList(team_d.c_str()); // Words * newList(const char words[]);
	tb1=newList(team_f); // Words * newList(const char words[]);
	cout << "*pokemon1"<< endl;
	printList(pokemon1); // int printList(Words *p_w); 
	cout << "*tb1"<< endl;
	printList(tb1); // int printList(Words *p_w);

	ok=appendList(tb,team_b.c_str());  // int appendList(Words *p_w, const char words[]); 
	cout << "*tb"<< endl;
	printList(tb); // int printList(Words *p_w); 

	ok=appendList(pokemon,tb); // int appendList(Words *dst, const Words *src);
	cout << "*pokemon"<< endl;
	printList(pokemon); // int printList(Words *p_w);

	ok=appendList(pokemon1,tb1); // int appendList(Words *dst, const Words *src);
	cout << "*pokemon"<< endl;
	printList(pokemon1); // int printList(Words *p_w); 

	word=findWord(pokemon,"charmeleon"); // char* findWord(const Words *p_w, const char word[]);
	cout << "*word "<< *word << " word " << word << " address " << &word << endl;

	ok=removeWord(pokemon,"squirtle"); // int removeWord(Words *p_w, const char word[]); 
	cout << "*pokemon"<< endl;
	printList(pokemon); // int printList(Words *p_w);

	getchar();
	getchar();
	getchar();
	getchar();
	getchar();

	return 0;
}

/* Function: newList
*
*
*	Takes the max_words of the list and creates a new Words
*	with the given max_words without assigning any words, sets 
*	num_words to zero. returns the new list to the calling function.
*	max_words must be greater than zero, otherwise newList returns 
*	NULL.
*/

Words * newList(const unsigned int max_words)
{
	if(max_words < 1)
		return NULL;

	// Allocate list
	Words * p_w = new Words;

	p_w -> max_words = max_words;
	p_w -> num_words = 0;
	p_w -> list = new char* [max_words];

	for (unsigned int i = 0; i < max_words; ++i) {

		p_w -> list[i] = new char[MAX_WORD_SIZE];

	}

	return p_w;

}

/* Function: newList
*
*	Overloaded version of newList, this one takes a character 
*	array with words separated by spaces, for example:
*
*	"charmeleon mewtwo pikachu charmander squirtle caterpie raichu butterfree abra kadabra alakazam slowpoke spoink"
*
*	has four words.  This newList will allocate enough space
*	for the words, then the list will be initialized to those
*	words and returns the list to the calling function. If  
*	words is empty, newList does nothing and returns NULL.
*/

Words * newList(const char words[])
{
	Words *p_w = new Words;

	// duplicate the words to handle literal input
	char *dup = _strdup(words);
	int len = strlen(dup);

	//Can't allocate zero memory
	if(len == 0)
		return NULL;

	int word_count = 0;
	bool inWord = false;

	// Find how many words the string contains
	for(int i = 0; i <len; i++) {

		if(dup[i] == ' ' || dup[i] == '\n' || dup[i] == '\t') {
			inWord = false;
		} else if(inWord == false) {
			inWord = true;
			word_count++;
		}
	}

	// Populate list with the number of words
	// and the max amount of characters possible.
	// Initalize everything to NULL
	p_w -> list = new char*[word_count];

	for(int i = 0; i < word_count; i++) {

		p_w -> list[i] = new char[MAX_WORD_SIZE];

		for (int j = 0; j < MAX_WORD_SIZE; j++) {
			p_w -> list[i][j] = '\0';

		}
	}

	// Populate the doubly linked list with
	// the cstrings
	int i = 0;
	int j = 0;
	inWord = false;

	for(int k = 0; k < len; k++) {

		// A word is longer than the max word size
		if(j >= MAX_WORD_SIZE) {
			return NULL;
		}

		if (dup[k] == ' ' || dup[k] == '\n' || dup[k] == '\t') {
			if (inWord == true) {
				i++;
			}

			j = 0;
			inWord = false;

		} else if(inWord == false) {
			inWord = true;
			p_w -> list[i][j] = dup[k];
			j++;
		} else {
			p_w -> list[i][j] = dup[k];
			j++;
		}

	}

	p_w -> max_words = word_count;
	p_w -> num_words = word_count;

	return p_w;

}

/* Function: deleteList
*
*	Takes a dynamically allocated Words and deletes
*	the list and then the Words itself, returns 0.  
*	If the Words is NULL deleteList does nothing and 
*	returns -1;
*/

int deleteList(Words *p_w)
{
	if(p_w == NULL)
		return -1;

	int max_words = p_w -> max_words;

	for (int i = 0; i < max_words; i++) {

		delete [] p_w -> list[i];

	}

	delete [] p_w -> list;

	return 0;

}

/* Function: printList
*	
*	Prints the words in the Words on a single Line 
*	with a single space between words. There is no 
*	space after the last word, but there is a newline,
*	returns 0 for successful print. If p_w is NULL, 
*	printList does nothing returns -1.
*/

int printList(Words *p_w)
{
	if(p_w == NULL)
		return -1;

	for (unsigned int i = 0; i < (p_w -> num_words); i++) {
		for (int j = 0; j < 20; j++) {

			cout << p_w -> list [i][j];

		}
	}

	return 0;
}

/* Function: appendList
*
*	Takes a Words and a character array consisting of words
*	separated by spaces, for example:
*
*	"charmander squirtle caterpie raichu"
*
*	Contains four words. appendList will take the Words
*	and append these words to list.  If the Words does not
*	have enough space, appendList will dynamically allocate
*	more space to list to allow these new words to fit.  
*	Returns the number of words appended.  If words is empty 
*	or if p_w is NULL then appendList does nothing and returns -1.
*/

int appendList(Words *p_w, const char words[])
{
	// duplicate the words to handle literal input
	char *dup = _strdup(words);
	int len = strlen(dup) ;

	if(p_w == NULL || len == 0)
		return -1;

	int word_count = 0;
	bool inWord = false;

	// Find how many words the string contains
	for(int i = 0; i <len; i++) {

		if(dup[i] == ' ' || dup[i] == '\n' || dup[i] == '\t') {
			inWord = false;
		} else if(inWord == false) {
			inWord = true;
			word_count++;
		}
	}

	// Populate list with the number of words
	// and the max amount of characters possible.
	// Initalize everything to NULL
	word_count = (p_w -> num_words) + word_count;
	char ** temp = p_w -> list;
	p_w -> list = new char*[word_count];

	for(int i = 0; i < word_count; i++) {

		p_w -> list[i] = new char[MAX_WORD_SIZE];

		for (int j = 0; j < MAX_WORD_SIZE; j++) {
			p_w -> list[i][j] = '\0';

		}
	}

	// Populate the doubly linked list with
	// the cstrings of the word
	int i = p_w -> num_words;
	int j = 0;
	inWord = false;

	for(int k = 0; k < len; k++) {

		// A word is longer than the max word size
		if(j >= MAX_WORD_SIZE) {
			return -1;
		}

		if (dup[k] == ' ' || dup[k] == '\n' || dup[k] == '\t') {
			if (inWord == true) {
				i++;
				}
			j = 0;
			inWord = false;
		} else if(inWord == false) {
			inWord = true;
			p_w -> list[i][j] = dup[k];
			j++;
		} else {
			p_w -> list[i][j] = dup[k];
			j++;
		}

	}

	// Copy over previous cstring in the Words -> list
	for(unsigned int i = 0; i < p_w -> num_words; i++) {
		p_w -> list[i] = temp[i];

	}

	p_w -> num_words = word_count;
	p_w -> max_words = word_count;

	return word_count;
}

/* Function: appendList
*
*	Takes two Wordss, appends the contents of src
*	to dst.  If dst does not have enough space
*	appendList should dynamically allocate additional space
*	then append the contents of src to dst, returns 
*	0 on success.  If either Words is NULL appendList does 
*	nothing and returns -1.
*/

int appendList(Words *dst, const Words *src)
{
	if(dst == NULL || src == NULL)
		return -1;

	int word_count = dst -> num_words + src -> num_words;
	char ** temp = dst -> list;
	dst -> list = new char* [word_count];

	// Populate list with the number of words
	// and the max amount of characters possible.
	// Initalize everything to NULL
	for(int i = 0; i < word_count; i++) {

		dst -> list[i] = new char[MAX_WORD_SIZE];

		for (int j = 0; j < MAX_WORD_SIZE; j++) {
			dst -> list[i][j] = '\0';

		}
	}

	// Copy over previous cstring in the Words -> list
	for(unsigned int i = 0; i < dst -> num_words; i++) {
		dst -> list[i] = temp[i];

	}

	int discrepancy = dst -> num_words;
	dst -> num_words = word_count;
	dst -> max_words = word_count;
	// Copy over previous cstring in the Words -> list
	for(unsigned int i = 0; i < src -> num_words; i++) {
		dst -> list[i + discrepancy] = src -> list[i];

	}

	return 0;
}

/* Function: findWord
*
*	Finds the first occurrence of the word in the Words
*	returns a pointer to that word in the list.  Otherwise
*	returns NULL. If p_w is NULL return NULL
*/

char* findWord(const Words *p_w, const char word[])
{
	// duplicate the words to handle literal input
	const char *dup = word;
	int len = strlen(dup) ;

	if(p_w == NULL || len == 0)
		return NULL;

	// Try to find the word in the list of Words
	for (unsigned int i = 0; i < p_w -> num_words; i++) {

		if(strcmp(p_w -> list[i], word) == 0) {

			return p_w -> list[i];

		}

	}

	return NULL;

}

/* Function: removeWord
*	
*	If p_w is null, returns -1.  Otherwise, searches for every 
*	occurrence of word[], and removes that word of the list, returns 
*	the number of words removed.
*	
*/
int removeWord(Words *p_w, const char word[])
{
	if(p_w == NULL)
		return -1;

	int num_removed = 0;

	while(findWord(p_w, word) != NULL) {

		for (unsigned int i = 0; i < p_w -> num_words; i++) {

			if(strcmp(p_w -> list[i], word) == 0) {

				num_removed++;
				p_w -> list[i] = new char[MAX_WORD_SIZE];
				for (int j = 0; j < MAX_WORD_SIZE; j++) {

					p_w -> list[i][j] = '\0';

				}

				unsigned int move = i;
				for(;move + 1 < p_w -> num_words; move++) {

					char * temp = p_w -> list [move];
					p_w -> list [move] = p_w -> list[move + 1];
					p_w -> list [move + 1] = temp;

				}

			}

		}

	}

	return num_removed;
}
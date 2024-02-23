/*	
	Student Name	:	Deepthi Jibu Valahery
	Student ID		:	[Redacted]
	Course Code		:	COMP1602
	Course Name		:	Computer Programming II
	Assignment		:	2
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define NUMROWS 10				// for drawing hangman diagram
#define NUMCOLS 12				// for drawing hangman diagram

struct Word {
	char word [25];
	char category [25];
	bool used;
};

int randomNumber (int max) {//Given
	return rand() % max;
}

int readCharacters(char data[]) {//Given
 
    ifstream fin;     
	char ch;     
	int i;             
	
	fin.open("words.txt");     
	
	if (!fin.is_open()) {         
		cout << "Error -- words.txt could not be opened." << endl;         
		return -1;
	}         
	
	i = 0;
	
	fin >> noskipws;          
	fin >> ch;  
	   
	while (!fin.eof()) {           
		data[i] = ch;
		cout << data[i];      
		i = i + 1;          
		fin >> ch;     
	}          
	
	data[i] = '\0';          
	fin.close();
	                
	return i; 

} 

bool isLetter (char c) {//Given
	if ((c >= 'A' && c <= 'Z') ||
	    (c >= 'a' && c <= 'z'))
		return true;
	else
		return false;
}

int getWord (char words[], int start, char word[]) {//Given
 
    int i, j, length;         
	
	length = strlen (words);			// find how many characters in words
	
	i = start;
	while (i < length && !isLetter(words[i]))
		i = i + 1;             
		
	if (i == length)					// there are no more words
		return -1;						
		
	j = 0;     							// copy characters to word
	while (isLetter(words[i])) {
		word[j]= words[i];
		i = i + 1;
		j = j + 1;     
	}       
 
    word[j]= '\0';          
    
	return i;							// starting position to look for next word
}

int getWords (char allWords[], Word words[]) {
    int i=0, wordCount=0;
    
    while (i < strlen(allWords)) {
		i = getWord(allWords, i, words[wordCount].word);
		i = getWord(allWords, i, words[wordCount].category);
		wordCount = wordCount + 1;
    }
    return wordCount;
}

void drawWord (char displayWord[]){
	int wordLength = strlen(displayWord);
	
	for(int i=0; i<wordLength; i++){
		cout << " " << displayWord[i] << " ";
	}
}

void setWordToUsed (Word words[], int numWords, char wordSelected[]) {
	if (words[numWords].word == wordSelected){
		words[numWords].used = true;
	}
}

bool findCategoryWord (Word words[], int numWords, char category[], char wordSelected []) {	
	int i=0, j=0, k=0, cat=0;
	Word repeatWord[1000];
	
	while(k<numWords){
		if (strcmp(words[k].category, category) == 0 && words[k].used == false){
			cat++;
		}
		k++;
	}
	if (cat == 0){
		return false;
	}
	
	while (i<numWords){
		if (strcmp(words[i].category, category) == 0 && words[i].used == false){
			strcpy(repeatWord[j].word, words[i].word);
			j++;
		}
		i++;
	}	
	int r = randomNumber (j);
	strcpy(wordSelected, repeatWord[r].word);
	
	return true;
 }
 
bool checkLetter (char guessWord[], char displayWord[], char letter) {
	bool found=false;
	int guessLen = strlen(guessWord);
	
	if (letter>='A' && letter<='Z')
		letter = letter + 32;
	
	for (int i=0; i<guessLen; i++){
		if (guessWord[i]==letter){
			displayWord[i] = letter;
			found = true;
		}
		else if (!isLetter(displayWord[i])){
			displayWord[i] = '_';
		}
	}
	return found;
}

void initWord (char guessWord[], char displayWord[]){
	char reveal[] = "rstlne";
	
	for (int j = 0; j < strlen(guessWord);j++){
		for (int i = 0; i < strlen(reveal); i++){
		if (guessWord[j] == reveal[i]){
			cout << reveal[i];
		}
	}
		cout<< displayWord;
		cout << " ";
	}
	cout << endl;
}

int lettersMissing (char displayWord[]) {
	int count = 0;
	
	for (int i=0; i<strlen(displayWord); i++){
		if (displayWord[i] == '_')
			count++;
	}
	return count;
}

void prepareGallows(char drawing[NUMROWS][NUMCOLS]) {//Given for
	int i, j;
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			drawing[i][j] = ' ';
		}
	}
		
	for (j=3; j<7; j++)
		drawing[0][j] = '_';

	for (i=1; i<7; i++)
		drawing[i][2] = '|';
	
	for (j=5; j<11; j++)
		drawing[7][j] = '_';
			
	for (j=1; j<11; j++)
		drawing[9][j] = '_';
	
	drawing[1][7] = '|';
	
	drawing[6][1] = '_';
	drawing[6][3] = '_';
	
	drawing[7][0] = '|';
	drawing[8][0] = '|';
	drawing[9][0] = '|';

	drawing[7][4] = '|';	

	drawing[8][11] = '|';	
	drawing[9][11] = '|';	
}

// The following is the new version of the drawHangman function.
//  It calls the prepareGallows function above.

void drawHangman (int livesLost) {//Given
	char drawing [NUMROWS][NUMCOLS];
	int i, j;
	int lives;
	
	prepareGallows(drawing);
		
	if (livesLost >= 1)
		drawing[2][7] = 'o';

	if (livesLost >= 2) {
		drawing[3][7] = 'X';
		drawing[4][7] = 'X';				
	}

	if (livesLost >= 3)
		drawing[3][6] = '/';

	if (livesLost >= 4)
		drawing[3][8] = '\\';

	if (livesLost >= 5)
		drawing[5][6] = '/';

	if (livesLost == 6)
		drawing[5][8] = '\\';
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			cout << drawing[i][j];
		}
		cout << endl;
	}
	cout << endl;

	if (livesLost == 6)					// sound the alarm if player loses
		cout << "\a" << endl;
		
}

int playGame() {
	Word words[1000];
	char data[1000], wordSelected [25], catChoice[25], displayWord[100] = {'_'};
	char drawing [NUMROWS][NUMCOLS];
	int numWords, livesLost=0, cat, g=0, tries = 6;
	char yn, guess;
	string name;
	bool character, check;
	srand(time(NULL));					// for better random number generation
	
	cout << "Let's play the game Hangman!" << endl;
	cout << "=============================" << endl;
	cout << "Do you wish to start?(y/n): " ;
	cin >> yn;
	
	readCharacters(data);
	
	while (yn == 'y'){
		cout << "Please enter your name: ";
		cin >> name;
		cout << "Hello " << name << ", ";
		cout << "Please choose a category from the list below:" << endl << endl;
		cout << "science\t\tpalindrome\nanimal\t\tspice\nfood\t\tfeelings\ncountry\t\tcooking\ninsect\t\treptile\n\n";
		cin >> catChoice;
		
		cat = getWords(data, words);
		
		drawHangman(livesLost);
		
		findCategoryWord(words, cat, catChoice, wordSelected);
		setWordToUsed(words, cat, wordSelected);
		
		initWord(wordSelected, displayWord);
		
		cout << "Guess a letter: ";
		cin >> guess;
		g++;
		cout << endl<< endl;

		int count = lettersMissing(displayWord);
		
		check = checkLetter(wordSelected, displayWord, guess);
		
		if (count!=0){
			drawHangman(livesLost);
			check;
			if (!check){
				livesLost++;
			}
		}
			
		
		
		
		
		
		cout << "Do you want to play again? ";
		cin  >> yn;
	}

cout << "You have guessed " << g << " times.";
}

int main() {
	playGame();
return 0;
}


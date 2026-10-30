#include <iostream>
#include <conio.h>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;

void creatingFile(void);
char* takingInputFile(void);
void wordCounter(char*);

int main()
{
	wordCounter(takingInputFile());

	_getch();
	return 0;
}// --------------------------------------------------------------END MAIN-------------------------------------------------------------

void creatingFile()
{
	ofstream fout;
	fout.open("Shtupid.txt");
	fout << "is the is and the is and the and is and only that is";
	fout.close();
}//--------------------------------------------------------Creates sample input file----------------------------------------------------

char* takingInputFile(void)
{
	ifstream fin;
	ofstream fout;
	fin.open("Shtupid.txt");
	if (!fin)                              //If the file could not be opened it creates a file with the sample input
	{
		creatingFile();
		fin.open("Shtupid.txt");
		if (!fin)                          //If the file still could not be opened the program exits
		{
			cout << "File could not be opened";
			exit(0);
		}
	}

	int lineCount = 0;
	int characterCount = 1;
	while (!fin.eof())                     //Checks the total number of lines and characters
	{
		char tempArray[1100] = "";
		fin.getline(tempArray, 1100);
		characterCount += strlen(tempArray);
		lineCount++;
	}
	fin.close();                           //Closes so I can start taking input from the file

	fin.open("Shtupid.txt");
	char* array1 = new char[characterCount+1];
	array1[0] = {'\0'};
	for (int loop = 0; loop < lineCount; loop++) //Takes input from the file and adds a space after every line 
	{
		const char* spaceString = " ";
		char tempArray[1100] = "";
		fin.getline(tempArray, 1100);
		strcat_s(array1,strlen(array1) + strlen(tempArray) + 1,tempArray);
		strcat_s(array1,strlen(array1) + strlen(spaceString) + 1,spaceString);
	}
	return array1;
}//-------------------------------------------------------Gets the String from the file---------------------------------------------------------

void wordCounter(char* mainString)
{
	char* copyString = new char[strlen(mainString) + 1];    //Makes two copy Strings for me to brutalize :)
	char* copyString2 = new char[strlen(mainString) + 1];
	strcpy_s(copyString,strlen(mainString)+1,mainString);
	strcpy_s(copyString2, strlen(mainString) + 1, mainString);

	int wordCount = 0;
	char* token;
	char* nextToken;
	const char* delimeters = " \n.,";
	token = strtok_s(copyString,delimeters,&nextToken);
	while (token != NULL)             //Gets me the word count of the input
	{
		if (token != NULL)
		{
			token = strtok_s(NULL, delimeters, &nextToken);
			wordCount++;
		}
	}

	char** wordArray = new char* [wordCount];      //Storing the words in an array for me to work on later
	int* counterArray = new int[wordCount];
	wordArray[0] = strtok_s(copyString2, delimeters, &nextToken);
	for (int loop = 1; loop < wordCount; loop++)
	{
		wordArray[loop] = strtok_s(NULL, delimeters, &nextToken);
	}

	for (int loop = 0; loop < wordCount; loop++)    //Initializing the counter array for me to increment or decrement
	{
		counterArray[loop] = 0;
	}

	for (int loop = 0; loop < wordCount; loop++)    //Checks how many times a word is repeated
	{
		for (int loop2 = 0; loop2 < wordCount; loop2++)
		{
			if (!strcmp(wordArray[loop], wordArray[loop2]))
			{
				if (loop2 < loop)
				{
					counterArray[loop] = -1000000;
				}
				else
				{
					counterArray[loop] += 1;
				}
			}
		}
	}

	ofstream fout;                    //Writes the output in the file and the terminal
	fout.open("ShtupidOutput.txt");
	if (!fout)
	{
		cout << "File could not be opened.";
		exit(0);
	}
	cout << "The input string was:\n" << mainString << endl << "\nYour word counts are:\n";
	fout << "The input string was:\n" << mainString << endl << "\nYour word counts are:\n";
	for (int loop = 0; loop < wordCount; loop++)
	{
		if (counterArray[loop] >= 1)
		{
			cout << wordArray[loop] << "\t" << counterArray[loop] << endl;
			fout << wordArray[loop] << "\t" << counterArray[loop] << endl;
		}
	}
	fout.close();

	delete[] copyString,wordArray,counterArray;
}//-------------------------------------------------------------Counts all the words-------------------------------------------------------------

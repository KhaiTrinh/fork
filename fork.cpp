#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

string retrieveData();
int validInput();
int wordCount(string, int);

int main()
{
    string doc = retrieveData();
    long childPID;
    while (true)
    {
        int userInput = validInput();
        if (userInput == 0)
        {
            cout << "\nTerminating Program. Goodbye.\n"
                 << endl;
            exit(0);
        }
        else
        {
            int status;
            childPID = fork();
            if (childPID > 0)
            {
                cout << "Parent Process: pid " << getpid()
                     << ", ppid " << getppid()
                     << ", child " << childPID << endl;
                pid_t pid = wait(&status);
                cout << "Returning PID: " << pid << ", Status: " << status << endl << endl;
            }
            else if (childPID == 0)
            {
                cout << "Child Process: pid " << getpid()
                     << ", ppid " << getppid()
                     << ", child " << childPID << endl;
                while (true)
                {
                    int count = 0;
                    count = wordCount(doc, userInput);
                    if (count > 0)
                    {
                        cout << "Number of words of length " << userInput
                             << " are: " << count << endl;
                        exit(0);
                    }
                    else
                    {
                        cout << ".\nChildPID: " << getpid() << endl;
                    }
                }
            }
            else
            {
                cout << "Child Spawn Error Has Occurred. "
                     << "Terminating Program." << endl;
                exit(0);
            }
        }
    }
}

/******************************************************
This function returns a string containing 300 words
or more by opening a text file in the source directory
named "doc.txt" and appending each line of text to
a string.
*******************************************************/
string retrieveData()
{
    string doc;
    ifstream file("doc.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            doc.append(line);
        }
        file.close();
    }
    else
    {
        cout << "Open file error has occurred!" << endl;
        exit(0);
    }
    return doc;
}

/**********************************************
This function returns a valid integer by
preventing the user from entering an unwanted
value such as a negative number or a character.
***********************************************/
int validInput()
{
    int num;
    char userInput[10];
    bool invalid = true;
    while (invalid)
    {
        cout << "Enter the length of a word to search for or 0 to quit: ";
        cin.getline(userInput, 10);
        int isnum = true;
        for (int i = 0; userInput[i] != '\0'; i++)
        {
            if (!isdigit(userInput[i]))
            {
                isnum = false;
                break;
            }
        }
        if (isnum)
        {
            num = atoi(userInput);
            invalid = false;
        }
        else
        {
            cout << "\nInvalid input. Please try again.\n\n";
        }
    }
    return num;
}

/**************************************************************
This function takes two parameters, the document and the length 
of a word to search for. Then it returns the number of 
occurrences of words with that length in the document.
**************************************************************/
int wordCount(string doc, int length)
{
    int count = 0;
    stringstream ss(doc);
    string word;
    while (ss >> word)
    {
        if (word.length() == length)
            count++;
    }
    return count;
}
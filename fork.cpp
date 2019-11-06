#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string retrieveData();
int validInput();

int main() {
    string data = retrieveData();
    cout << data;

    return 0;
}

/******************************************************
This function returns a string containing 300 words
or more by opening a text file in the source directory
named "doc.txt" and appending each line of text to
a string.
*******************************************************/
string retrieveData() {
    string doc;
    ifstream file("doc.txt");
    if(file.is_open()) {
        string line;
        while(getline(file, line)) {
            doc.append(line);
        }
        file.close();
    } else {
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
int validInput() {
    int num;
    char userInput[10];
    bool invalid = true;
    while(invalid) {
        cout << "Enter the length of a word to search for: ";
        cin.getline(userInput, 10);
        int isnum = true;
        for(int i = 0; userInput[i] != '\0'; i++) {
            if(!isdigit(userInput[i])) {
                isnum = false;
                break;
            }
        }
        if(isnum) {
            num = atoi(userInput);
            invalid = false;
        } else {
            cout << "\nInvalid input. Please try again.\n\n";
        }
    }
    return num;
}
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: LoginApp.cpp
// Last Modification Date: 15/05/2022
// Author1 and ID and Group: Merna Islam 20210500
// Author2 and ID and Group: Maria Ehab  20210312
// Author3 and ID and Group: Jana  Wael  20211026
// Teaching Assistant: Eng/ Afaf
// Purpose: To practice mapping into files, using struct, and regex library to form this app.

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstring>

using namespace std;

void startMenu();
void addingContent();
void displayContent();
void emptyFile();
void encryptFile();
void decryptFile();
void mergeFile();
void countWords();
void countCharacters();
void countLines();
void searchWord();
void wordRepeatNumber();
void capitalizeFile();
void decapitalizeFile();
void firstCaps();
void save(string);

string fileName;
fstream myFile;
ifstream inFile;

//__________________________
int main(){
    // The program starts by taking the name of the file from the user
    cout << "Please enter the name of the file you want to deal with: " << endl;
    cin >> fileName;
    // then adding .txt at the end of the name
    fileName += ".txt";

    // If the file doesn't exist then the program creates a new one
    myFile.open(fileName);
    if (myFile.is_open()) {
        cout << "This File Already Exists" << endl;
    } else {
        cout << "This is a new file. I created it for you! " << endl;
    }
    myFile.close();
    startMenu();
}
//__________________________
void startMenu(){

    // Displaying the start menu for the user to choose from
    int choice;
    cout << "Choose the option you want from the following: " << endl;
    cout << "1. Add new text to the end of the file\n"
            "2. Display the content of the file\n"
            "3. Empty the file\n"
            "4. Encrypt the file content\n"
            "5. Decrypt the file content\n"
            "6. Merge another file\n"
            "7. Count the number of words in the file.\n"
            "8. Count the number of characters in the file\n"
            "9. Count the number of lines in the file\n"
            "10. Search for a word in the file\n"
            "11. Count the number of times a word exists in the file\n"
            "12. Turn the file content to upper case.\n"
            "13. Turn the file content to lower case.\n"
            "14. Turn file content to 1st caps (1st char of each word is capital)\n"
            "15. Save\n"
            "16. Exit" << endl;
    cin >> choice;

    // Based on the user's choice, a corresponding function is called
    switch(choice){
        case 1:
            addingContent();
            break;
        case 2:
            displayContent();
            break;
        case 3:
            emptyFile();
            break;
        case 4:
            encryptFile();
            break;
        case 5:
            decryptFile();
            break;
        case 6:
            mergeFile();
            break;
        case 7:
            countWords();
            break;
        case 8:
            countCharacters();
            break;
        case 9:
            countLines();
            break;
        case 10:
            searchWord();
            break;
        case 11:
            wordRepeatNumber();
            break;
        case 12:
            capitalizeFile();
            break;
        case 13:
            decapitalizeFile();
            break;
        case 14:
            firstCaps();
            break;
        case 15:
            save(fileName);
            break;
        case 16:
            cout << "Thank you! The program ends here. " << endl;
        default:
            cout << "Invalid number entered, please choose from 1 to 16 only: " << endl;
            startMenu();
    }
    // for each function is main menu is re-called to allow the user to choose various options until he exits
}
//__________________________
void addingContent(){
    string text;
    cin.ignore(INT_MAX, '\n');
    cout << "Write the text you want to append in that file: " << endl;
    // Get the line from the user he wants to append
    getline(cin, text);
    // open the file in the append mode
    myFile.open(fileName, ios::app);
    myFile << text << endl;
    myFile.close();
    startMenu();
}
//__________________________
void displayContent(){
        string line;
        // open the file in the read mode
        myFile.open(fileName, ios::in);
        // creating a loop that runs as long as there is a line to read, then display that line in the terminal
        while(getline(myFile, line)){
            cout << line << endl;
        }
        myFile.close();
        startMenu();
    }
//__________________________
void emptyFile(){
    // open the file in the truncate mode that clear all the content in the file
    myFile.open(fileName, ios:: out | ios::trunc);
    myFile.close();
    startMenu();
}
//__________________________
void encryptFile(){
    string line;
    int temp;
    // open the file in the read mode once and in the write mode once
    inFile.open(fileName, ios::in);
    myFile.open(fileName);

    // while not end of the file
    while(!inFile.eof()){
        // it reads a line from the reading file
        getline(inFile, line);
        // run over each character in that line
        for(char letter : line){
            // then incrementing the character by using the ascii value
            temp = int(letter) + 1;
            letter = char(temp);
            // write that letter in the writing file
            myFile << letter;
        }
        // At the end of each line a new line is added in the writing file
        myFile << endl;
    }

    inFile.close();
    myFile.close();
    startMenu();
}
//__________________________
void decryptFile(){
    string line;
    int temp;
    // open the file in the read mode once and in the write mode once
    inFile.open(fileName, ios::in);
    myFile.open(fileName);

    // while not end of the file
    while(!inFile.eof()){
        // it reads a line from the reading file
        getline(inFile, line);
        // run over each character in that line
        for(char letter : line){
            // then decrementing the character by using its ascii value
            temp = int(letter) - 1;
            letter = char(temp);
            // write that letter in the writing file
            myFile << letter;
        }
        // At the end of each line a new line is added in the writing file
        myFile << endl;
    }

    inFile.close();
    myFile.close();
    startMenu();
}
//__________________________
void mergeFile(){
    fstream myFileMerged;
    string mergedFile, text;
    cout << "Please write the name of the file you want to merge with the original: " << endl;
    cin >> mergedFile;
    mergedFile += ".txt";
    while(mergedFile == fileName){
        cout << "Error: it cannot be the same filename of the original one! Please try again: " << endl;
        cin >> mergedFile;
        mergedFile += ".txt";
    }
    // open the merged file chosen by the user in the read mode
    myFileMerged.open(mergedFile, ios::in);
    // open the original file in the append mode
    myFile.open(fileName, ios::app);
    // check if the merged file already exists
    if(myFileMerged.is_open()){
        // creating a loop that runs as long as there is a line to read, then write that line in the original file
        while(getline(myFileMerged, text)){
            myFile << text << endl;
        }
    }else{
        // if it does not exist then the user is asked to enter the filename again
        cout << "Invalid File Name, please try again: " << endl;
        mergeFile();
    }
    myFile.close();
    myFileMerged.close();
    startMenu();
}
//__________________________
void countWords(){
    string word;
    int count = 0;
    // open the file in the read mode
    myFile.open(fileName, ios::in);
    // while it's not the end of file
    while(!myFile.eof()){
        // we read each word in that file and increment the counter by one
        myFile >> word;
        count++;
    }
    cout << "The number of words in this file is: " << count << endl;
    myFile.close();
    startMenu();
}
//__________________________
void countCharacters(){
    string word;
    int count = 0;
    myFile.open(fileName, ios::in);
    while(!myFile.eof()){
        myFile >> word;
        // we read each word in that file and then run over each character in that word to increment the counter by one
        for(char letter : word){
            count++;
        }
        // incrementing the counter again by one by the end of each word for the space or new line character
        count++;
    }
    count--;
    cout << "The number of characters in this file is: " << count << endl;
    myFile.close();
    startMenu();
}
//__________________________
void countLines(){
    int count = 0;
    string text;
    myFile.open(fileName, ios::in);
    // creating a loop that runs as long as there is a line to read, then increment the counter by one for each line
    while(getline(myFile, text)){
        count++;
    }
    cout << "The number of lines in this file is: " << count << endl;
    myFile.close();
    startMenu();
}
//__________________________
void searchWord() {
    string word;
    string searchWord;
    int count = 0;
    cout << "Please enter the word you want to search for: " << endl;
    cin >> searchWord;
    // Take an input from the user for the word searched for
    // Then transform this word to lowercase
    transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    // open the file in the read mode
    myFile.open(fileName, ios::in);
    // while not at the end of the file
    while (!myFile.eof()) {
        myFile >> word;
        // read each word from the file and transform it to lowercase for insensitive case
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // if it matches then the counter in incremented by one
        if (word == searchWord) {
            count++;
        }
    }
    // checking if the count increased then searched word exists in that file
    if(count > 0){
        cout << "Word was found in the file :)" << endl;
        cout << "It's been found " << count << " times. " << endl;
    } else {
        cout << "Word was not found in the file :(" << endl;
    }
    myFile.close();
    startMenu();
}
//__________________________
void wordRepeatNumber() {
    string word;
    string temp;
    int count = 0;
    ifstream inFile(fileName);
    cout << "Enter the word to get number of existence: ";
    cin >> word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    while (inFile >> temp){
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (temp == word)
            ++count;
    }
    cout << "The repeated number of this word is: " << count << endl;
    inFile.close();
    startMenu();
}
//__________________________
void capitalizeFile(){
    stringstream str_stream;
    string str;
    int i=0;
    myFile.open(fileName);
    str_stream<<myFile.rdbuf();
    myFile.close();
    str = str_stream.str();
    while(str[i]){
        str[i] = toupper(str[i]);
        i++;
    }
    myFile.open(fileName);
    myFile<<str;
    myFile.close();
    startMenu();
}
//__________________________
void decapitalizeFile(){
    stringstream str_stream;
    string str;
    int i=0;
    myFile.open(fileName);
    str_stream<<myFile.rdbuf();
    myFile.close();
    str = str_stream.str();
    while(str[i]){
        str[i] = tolower(str[i]);
        i++;
    }
    myFile.open(fileName);
    myFile<<str;
    myFile.close();
    startMenu();
}
//__________________________
void firstCaps(){
    stringstream str_stream;
    string str;
    int i=0, temp=0;

    myFile.open(fileName);
    str_stream<<myFile.rdbuf();
    myFile.close();
    str = str_stream.str();
    while(str[i])
    {
        if(temp==0)
        {
            str[i] = toupper(str[i]);
            temp = 1;
        }
        else if(isspace(str[i]))
            temp = 0;
        i++;
    }
    myFile.open(fileName);
    myFile<<str;
    myFile.close();
    startMenu();
}
//__________________________
void save(string oldNameString) {
    int choice;
    char newName[] = " ";

    int nameLength = oldNameString.length();
    char oldNameChar[nameLength + 1];
    strcpy(oldNameChar, fileName.c_str());

    cout << "would you like to rename your file?\n 1) rename\n 2)same name" << endl;
    cin >> choice;
    if (choice == 2) {
        myFile.close();

    }

    if (choice == 1) {
        cout << "please enter the new name" << endl;
        cin >> newName;
        if (rename(oldNameChar, newName) != 0)
            perror("Error renaming file");
        else
            cout << "File renamed successfully";

    }

}
//__________________________
//The program ends here!
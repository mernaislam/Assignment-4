#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cctype>
#include <algorithm>
#include <sstream>

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
void save();

string fileName;
fstream myFile;
ifstream inFile;

//__________________________
int main(){
    cout << "Please enter the name of the file you want to deal with: " << endl;
    cin >> fileName;
    fileName += ".txt";
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
            save();
            break;
        case 16:
            cout << "Thank you! The program ends here. " << endl;
        default:
            cout << "Invalid number entered, please choose from 1 to 16 only: " << endl;
            startMenu();
    }
}
//__________________________
void addingContent(){
    string text;
    cin.ignore(INT_MAX, '\n');
    cout << "Write the text you want to append in that file: " << endl;
    getline(cin, text);
    myFile.open(fileName, ios::app);
    myFile << text << endl;

    myFile.close();
    startMenu();
}
//__________________________
void displayContent(){
        string line;
        myFile.open(fileName, ios::in); //modes: in -- read // out -- write // app -- append // trunc -- clear
        while(getline(myFile, line)){
            cout << line << endl;
        }
        myFile.close();
        startMenu();
    }
//__________________________
void emptyFile(){
    myFile.open(fileName, ios:: out | ios::trunc);
    myFile.close();
    startMenu();
}
//__________________________
void encryptFile(){
    string line;
    int temp;
    inFile.open(fileName, ios::in);
    myFile.open(fileName);

    while(!inFile.eof()){
        getline(inFile, line);
        for(char letter : line){
            temp = int(letter) + 1;
            letter = char(temp);
            myFile << letter;
        }
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
    inFile.open(fileName, ios::in);
    myFile.open(fileName);

    while(!inFile.eof()){
        getline(inFile, line);
        for(char letter : line){
            temp = int(letter) - 1;
            letter = char(temp);
            myFile << letter;
        }
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
    myFileMerged.open(mergedFile, ios::in);
    myFile.open(fileName, ios::app);
    if(myFileMerged.is_open()){
        while(getline(myFileMerged, text)){
            myFile << text << endl;
        }
    }else{
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
    myFile.open(fileName, ios::in);
    while(!myFile.eof()){
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
        for(char letter : word){
            count++;
        }
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
    transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    myFile.open(fileName, ios::in);
    while (!myFile.eof()) {
        myFile >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word == searchWord) {
            count++;
        }
    }
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
void save(){
    startMenu();
}
//__________________________

//The program ends here!
#include <iostream>

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
void wordNumber();
void upperCase();
void lowerCase();
void firstCaps();
void save();
void exit();

int main(){
    string fileName;
    cout << "Please enter the name of the file you want to deal with: " << endl;
    cin >> fileName;
    //test if such a file exists or not. If it does, it will display a message: "This File Already
    //Exists" and it will open it for read and write. If it does not exist, it will create a file with the given name and will
    //print a message: "This is a new file. I created it for you "
    startMenu();
}

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
        case 2:
            displayContent();
        case 3:
            emptyFile();
        case 4:
            encryptFile();
        case 5:
            decryptFile();
        case 6:
            mergeFile();
        case 7:
            countWords();
        case 8:
            countCharacters();
        case 9:
            countLines();
        case 10:
            searchWord();
        case 11:
            wordNumber();
        case 12:
            upperCase();
        case 13:
            lowerCase();
        case 14:
            firstCaps();
        case 15:
            save();
        case 16:
            exit();
        default:
            cout << "Invalid number entered, please choose from 1 to 16 only: " << endl;
            startMenu();
    }
}
void addingContent(){

}
void displayContent(){

}
void emptyFile(){

}
void encryptFile(){

}
void decryptFile(){

}
void mergeFile(){

}
void countWords(){

}
void countCharacters(){

}
void countLines(){

}
void searchWord(){

}
void wordNumber(){

}
void upperCase(){

}
void lowerCase(){

}
void firstCaps(){

}
void save(){

}
void exit(){

}
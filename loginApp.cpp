#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <unordered_map>
#include <list>
#include <regex>

using namespace std;

void registration();
void login();
void changePassword();
void verifyPassword();
void verifyName();
void verifyMobile();
void verifyEmail();
void read();

fstream myFile;
string userEmail;
unordered_map<string, list<string>> userProfile; // store email as key and list of details as value
list<string> userDetails {}; // store list of details {mobile , name , password}

int main(){
    int choice;
    cout << "Welcome! This is a login application, please choose your option: " << endl;
    cout << " 1. Register \n 2. Login \n 3. Change Password \n 4. Exit" << endl;
    cin >> choice;
    while(choice > 4 || choice < 1){
        cout << "Invalid number entered please choose a number between 1 and 4: " << endl;
        cin >> choice;
    }
    if(choice == 1){
        registration();
    } else if(choice == 2){
        login();
    } else if(choice == 3){
        changePassword();
    } else if (choice == 4) {
        cout << "Thank you for using the application! The program ends here. " << endl;
    } else if (choice == 5) {
        read();
    } else {
        cout << "Invalid number, please try again!" << endl;
    }
}

void registration(){

    string line;
    int ID = 20220000;
    myFile.open("Database.txt", ios::in);
    while(!myFile.eof()) {
        myFile >> line;
        if(line.substr(line.length()-4, line.length()) == ".com"){
            userProfile.insert(pair<string, list<string>>(line, userDetails));
            ID++;
        }
    }
    myFile.close();
    // 1. add his profile  (with personal information) to the system and select a username and a password
    // 2. user's email and email should not be previously registered
    // 3. Ensure email follows proper email format
    verifyEmail();
    myFile.open("Database.txt", ios::app);
    myFile << userEmail << endl;
    myFile.close();
    // 4. Verify mobile format
    verifyMobile();
    // 5. Ensure that the name follows proper format
    verifyName();
    // 6. Display a message to the user
    cout << "Passwords must contain:\n"
            "\n"
            "ْ  a minimum of 1 lower case letter [a-z] and\n"
            "ْ  a minimum of 1 upper case letter [A-Z] and\n"
            "ْ  a minimum of 1 numeric character [0-9] and\n"
            "ْ  a minimum of 1 special character: ~`!@#$%^&*()-_+={}[]|\\;:\"<>,./?\n"
            "ْ  Passwords must be at least 10 characters in length, but can be much longer." << endl;

    verifyPassword();
    cout << "Thank you, you have completed your registration: " << endl;
    myFile.open("Database.txt", ios::app);
    myFile << ID << endl << endl;
    myFile.close();
    userProfile.insert(pair<string, list<string>>(userEmail, userDetails));
    cout << "Your Personal ID is: " << ID << endl;
    main();
}

void read() {
    ifstream myFile2("Database.txt");

    main();
}

void login() {
    int countPass = 0, countId = 0;
    string userPassword, userId;
    string line;
    string idsArr[30], passwordsArr[30];
    cout << "please enter ID and password" << endl;
    cout << "ID:";
    cin >> userId;
    cout << "password:";
    cin >> userPassword;

    ifstream input("Database.txt");

    //for loop to read all lines in the file
    for (int lineNo = 1; getline(input, line); lineNo++) {

        //ID always in line 6 and incremented 6 lines to each user
        if (lineNo % 6 == 0) {
            idsArr[countId] = line;
            countId++; //counter for id array
        }

        //Password always in line 5 and incremented 6 lines to each user
        if (lineNo % 6 == 5) {
            passwordsArr[countPass] = line;
            countPass++; //counter for password array
        }
    }

    for (int i = 0; i < countPass; i++) {
        if (userPassword == passwordsArr[i] && userId == idsArr[i]) {
            cout << "Welcome to the system" << endl;
            main();
            break;
        }
    }

    cout << "invalid id or password" << endl;
    main();


//    while (input >> ID2 >> password2){
//        if (ID1 == ID2 and password1 == password2){
//            count = 1;
//            system("cls");
//        }
//    }
//
//    input.close();
//    if (count == 1){
//        cout << ID2 <<"\n your login was sucessful";
//        main();
//    }
//    else{
//        cout << "failed to login, please check your ID. ";
//        main();
//    }
}

void changePassword(){

}

void verifyPassword(){

    string password1, password2;
    int masking1, masking2;
    cout << "Please enter your password: " << endl;
    // 9. Cover the password with ***** while the user is entering it.
    masking1 = _getch();
    while(masking1 != 13){
        password1.push_back(masking1);
        cout << '*';
        masking1 = _getch();
    }
    cout << endl;
    // 8. Verify that the password is a strong one.
    string lowerCase = "(?=.*[a-z])";
    string upperCase = "(?=.*[A-Z])";
    string numbers = "(?=.*[0-9])";
    string specialChar = "(?=.*[@_!#$%^&*:;\\/\"\'|.,~`<>?])";
    string minChar = "(?=.{8,})";
    string fullPattern2 = lowerCase + upperCase + numbers + specialChar + minChar;
    regex regexRule2(fullPattern2);

    bool isValid = regex_search(password1, regexRule2);
    if(isValid){
        cout << "Password is valid" << endl;
        // 10. If registration is valid, the user profile, ID and password are added to the list of system users and stored in the user file
        myFile.open("Database.txt", ios::app);
        myFile << password1 << endl;
        myFile.close();
        cout << "Please enter your password again: " << endl;
        masking2 = _getch();
        while(masking2 != 13){
            password2.push_back(masking2);
            cout << '*';
            masking2 = _getch();
        }
        cout << endl;
        // 7- Ask the user to repeat the password and make sure it was entered the same twice.
        while(password1 != password2) {
            cout << "The two passwords are not the same, please re-enter the second password: " << endl;
            cin >> password2;
            if (password1 == password2) {
                userDetails.push_back(password1);
                break;
            }
        }
    } else {
        cout << "Password is NOT valid " << endl;
        verifyPassword();
    }
}

void verifyName(){
    string name;
    cout << "Please enter your name :" << endl;
    cin >> name;
    string namePattern = "^[a-zA-Z_]+$";
    regex nameRule(namePattern);
    bool isValid = regex_search(name, nameRule);

    if(!isValid){
        cout << "Invalid name, please enter letters or _ only: " << endl;
        verifyName();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << name << endl;
        myFile.close();
        userDetails.push_back(name);
    }
}


void verifyMobile(){
    string mobile;
    cout << "Please enter your mobile number: " << endl;
    cin >> mobile;

    string regexPattern = "01[0-9]*";
    regex regexRule(regexPattern);
    bool isValid = regex_match(mobile, regexRule);
    if(mobile.length() != 11 || !isValid){
        cout << "Invalid mobile number, it must be 11 digits starts with 01: " << endl;
        verifyMobile();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << mobile << endl;
        myFile.close();
        userDetails.push_back(mobile);
    }

}

void verifyEmail(){
    string email;
    string regexPattern = "\\w+\\.?\\w+@\\w+\\.com";
    regex regexRule(regexPattern);
    cout << "Please enter your email: " << endl;
    cin >> email;
    bool isValid = regex_match(email, regexRule);
    if(!isValid){
        cout << "Invalid email address format: [ohndoe@company.com] \nPlease try again! " << endl;
        verifyEmail();
    } else {
        userEmail = email;
        for(auto word : userProfile){
            if(email == word.first){
                cout << "This email has been registered before, please choose another one: " << endl;
                verifyEmail();
                break;
            }
        }
    }
}
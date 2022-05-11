#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

void registration();
void login();
void changePassword();
void verifyPassword();
void verifyName();
void verifyMobile();
void verifyEmail();

fstream myFile;

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
    } else if(choice == 4){
        cout << "Thank you for using the application! The program ends here. " << endl;
    } else {
        cout << "Invalid number, please try again!" << endl;
    }
}

void registration(){

    string email, mobile, name;
    // 1. add his profile  (with personal information) to the system and select a username and a password
    cout << "Please enter your email: " << endl;
    cin >> email;
    verifyEmail();
    // 2. user's email and email should not be previously registered
    // 3. Ensure email follows proper email format
    myFile.open("Database.txt", ios::app);
    myFile << email << endl;
    myFile.close();


    cout << "Please enter your mobile number: " << endl;
    cin >> mobile;
    verifyMobile();
    // 4. Verify mobile format
    myFile.open("Database.txt", ios::app);
    myFile << mobile << endl;
    myFile.close();
    cout << "Please enter your name :" << endl;
    cin.ignore();
    getline(cin, name);
    verifyName();
    // 5. Ensure that the name follows proper format
    myFile.open("Database.txt", ios::app);
    myFile << name << endl;
    myFile.close();
    // 6. Display a message to the user
    cout << "Passwords must contain:\n"
            "\n"
            "ْ  a minimum of 1 lower case letter [a-z] and\n"
            "ْ  a minimum of 1 upper case letter [A-Z] and\n"
            "ْ  a minimum of 1 numeric character [0-9] and\n"
            "ْ  a minimum of 1 special character: ~`!@#$%^&*()-_+={}[]|\\;:\"<>,./?\n"
            "ْ  at least 1 upper case, numeric, and special character must be EMBEDDED somewhere in the middle of the password, and not just be the first or the last character of the password string.\n"
            "ْ  Passwords must be at least 10 characters in length, but can be much longer." << endl;

    cout << "Please enter your password: " << endl;

    verifyPassword();
}

void login(){

}

void changePassword(){

}

void verifyPassword(){

    string password1, password2;
    int countUpper = 0, countLower = 0, countNum = 0, countSpecial = 0, countLetters = 0;
    int masking1, masking2;
    // 9. Cover the password with ***** while the user is entering it.
    masking1 = _getch();
    while(masking1 != 13){
        password1.push_back(masking1);
        cout << '*';
        masking1 = _getch();
    }
    cout << endl;
    // 8. Verify that the password is a strong one.
    for(char letter : password1){
        if(int(letter) > 96 && int(letter) < 123){
            countLower++;
        } else if(int(letter) > 64 && int(letter) < 91){
            countUpper++;
        } else if(int(letter) > 47 && int(letter) < 58){
            countNum++;
        } else if(int(letter) > 32){
            countSpecial++;
        }
        countLetters++;
    }
    if(countLetters >= 10 && countSpecial >= 1 && countUpper >= 1 && countLower >= 1 && countNum >= 1){
        cout << "Your password is strong enough! " << endl;
        // 10. If registration is valid, the user profile, ID and password are added to the list of system users and stored in the user file
        myFile.open("Database.txt", ios::app);
        myFile << password1 << endl << endl;
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
                cout << "Thank you, you have completed your registration: " << endl;
                break;
            }
        }
    } else {
        while(countLetters < 10 || countSpecial == 0 || countUpper == 0 || countLower == 0 || countNum == 0) {
            cout << "The password is not strong enough. " << endl;
            if(countLetters < 10){
                cout << "You need to use more characters in your password." << endl;
                cout << "You must use at least " << (10-countLetters) << " more characters." << endl;
            }if(countSpecial == 0){
                cout << "You must use at least 1 special character from: ~`!@#$%^&*()-_+={}[]|\\;:\"<>,./?" << endl;
            }  if(countLower == 0){
                cout << "You must use at least 1 lowercase letter: [a-z] " << endl;
            } if(countUpper == 0){
                cout << "You must use at least 1 uppercase letter: [A-Z] " << endl;
            } if(countNum == 0){
                cout << "You must use at least 1 number from [0-9] " << endl;
            }
            cout << "Please re-enter your password: " << endl;
            verifyPassword();
            break;
        }
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
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: TextEditor.cpp
// Last Modification Date: 13/05/2022
// Author1 and ID and Group: Merna Islam 20210500
// Author2 and ID and Group: Maria Ehab  20210312
// Author3 and ID and Group: Jana  Wael  20211026
// Teaching Assistant: Eng/ Afaf
// Purpose: To practice more functions using file handling in c++

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

fstream myFile;
string userEmail;
unordered_map<string, list<string>> userProfile; // store email as key and list of details as value
list<string> userDetails{}; // store list of details {mobile , name , password}

// Creating a struct for storing the UserData
struct userData {
    int startIndex;
    string name;
    string email;
    string password;
    string phone;
    string id;
};

userData activeUser;
const int MAX_USERS = 30;

int main() {
    // Creating the start menu for the user to choose from:
    int choice, masking1;
    string oldPass;
    cout << "Welcome! This is a login application, please choose your option: " << endl;
    cout << " 1. Register \n 2. Login \n 3. Change Password \n 4. Exit" << endl;
    cin >> choice;
    // Validating the users' choice and calling the corresponding function based on it.
    while (choice > 5 || choice < 1) {
        cout << "Invalid number entered please choose a number between 1 and 4: " << endl;
        cin >> choice;
    }
    if (choice == 1) {
        registration();
    } else if (choice == 2) {
        login();
    } else if (choice == 3) {
        cout << "You must login first: " << endl;
        login();
        cout << "please enter your old password :" << endl;
        masking1 = _getch();
        while (masking1 != 13) {
            oldPass.push_back(masking1);
            cout << '*';
            masking1 = _getch();
        }
        cout << endl;
        changePassword();
    } else if (choice == 4) {
        cout << "Thank you for using the application! The program ends here. " << endl;
    } else {
        cout << "Invalid number, please try again!" << endl;
    }
}

void registration() {

    string line;
    // Initializing the ID for the first user to be = 20220000
    int ID = 20220000;
    // Opening the file in which users' data are stored, and run over each line inside
    myFile.open("Database.txt", ios::in);
    while (!myFile.eof()) {
        myFile >> line;
        // If this line ends with ".com" [for storing emails]
        // Then we store that email as the key of the map [to be unique]
        // We increment the ID for each email read to make sure the new register has a new ID
        if (line.substr(line.length() - 4, line.length()) == ".com") {
            userProfile.insert(pair<string, list<string>>(line, userDetails));
            ID++;
        }
    }
    myFile.close();
    verifyEmail();
    // Verify email and store it in the file.
    myFile.open("Database.txt", ios::app);
    myFile << userEmail << endl;
    myFile.close();
    // 4. Verify mobile format
    verifyMobile();
    // 5. Ensure that the name follows proper format
    verifyName();
    // 6. Display a message to the user for the rules of password.
    cout << "Passwords must contain:\n"
            "\n"
            "ْ  a minimum of 1 lower case letter [a-z] and\n"
            "ْ  a minimum of 1 upper case letter [A-Z] and\n"
            "ْ  a minimum of 1 numeric character [0-9] and\n"
            "ْ  a minimum of 1 special character: ~`!@#$%^&*()-_+={}[]|\\;:\"<>,./?\n"
            "ْ  Passwords must be at least 10 characters in length, but can be much longer." << endl;

    verifyPassword();
    // After taking inputs for all data and verifying it, registration is completed and the user is given an ID.
    cout << "Thank you, you have completed your registration: " << endl;
    myFile.open("Database.txt", ios::app);
    myFile << ID << endl << endl;
    myFile.close();
    // Inserting all the data in a map, email is the key and the rest is stored in a list as its value.
    userProfile.insert(pair<string, list<string>>(userEmail, userDetails));
    cout << "Your Personal ID is: " << ID << endl;
    main();
}

void login() {
    int count = 0, temp, masking;
    string userPassword, userId, passEncrypted;
    string line;
    bool isValid = false;
    static int countAccess = 1;
    userData userData[MAX_USERS];

    cout << "Please enter ID and password" << endl;
    cout << "ID:";
    cin >> userId;
    cout << "Password:";
    // Password masking using library #include <conio.h>
    masking = _getch();
    while (masking != 13) {
        userPassword.push_back(masking);
        cout << '*';
        masking = _getch();
    }
    cout << endl;
    // Encrypting this password
    for (char letter: userPassword) {
        temp = int(letter);
        temp++;
        passEncrypted += char(temp);
    }

    ifstream input("Database.txt");

    //for loop to read all lines in the file
    for (int lineNo = 1; getline(input, line); lineNo++) {

        //Password always in line 5 and incremented 6 lines to each user
        if (lineNo % 6 == 2) {
            userData[count].startIndex = lineNo;
            userData[count].email = line;
        } else if (lineNo % 6 == 3) {
            userData[count].phone = line;
        } else if (lineNo % 6 == 4) {
            userData[count].name = line;
        } else if (lineNo % 6 == 5) {
            userData[count].password = line;
        } else if (lineNo % 6 == 0) {
            userData[count].id = line;
            count++;
        }
    }
    // If password encrypted matches the one stored in the file and ID matches that one stored in the file, then user login successfully
    for (int i = 0; i < count; i++) {
        if (passEncrypted == userData[i].password && userId == userData[i].id) {
            activeUser.startIndex = userData[i].startIndex ;
            activeUser.id = userData[i].id ;
            activeUser.name = userData[i].name ;
            activeUser.email = userData[i].email ;
            activeUser.password = userData[i].password ;
            activeUser.phone= userData[i].phone;
            cout << "Welcome to the System!" << endl;
            isValid = true;
            break;
        }
    }
    // If login is not correct then the user available trials is incremented
    // User is allowed to re-enter again until he reaches his max 3 trails
    // If it exceeds the 3 trials then the user is directed to the main menu again.
    if(!isValid){
        countAccess++;
        if(countAccess > 3){
            cout << "You have exceeded your available three trials. So you are denied from accessing the system: " << endl;
            main();
        } else {
            cout << "invalid ID or Password. Try Again: " << endl;
            login();
        }
    }
}

void changePassword() {

    userData userData;
    string newPass, passEncrypted;
    int masking2, temp;
    string line;
    cout << "please enter your new password :" << endl;
    masking2 = _getch();
    // Password masking for the new password entered
    while (masking2 != 13) {
        newPass.push_back(masking2);
        cout << '*';
        masking2 = _getch();
    }
    cout << endl;
    // Regex rule created from the regex patter
    string validation = "(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@_!#$%^&*:;\\/\"\'|.,~`<>?])(?=.{8,})";
    regex regexRulePass(validation);

    // If the user password matches the rules:
    bool isValid = regex_search(newPass, regexRulePass);
    if (isValid) {
        cout << "Password is valid" << endl;
        // Password is encrypted
        for (char letter: newPass) {
            temp = int(letter);
            temp++;
            passEncrypted += char(temp);
        }
            const char *file_name = "Database.txt";
            ifstream originalFile(file_name);

            ofstream tempFile;
            tempFile.open("temp.txt", ofstream::app);

            char c;
            int line_no = 1;
            while (originalFile.get(c)) {
                // file content not to be deleted
                if (line_no < activeUser.startIndex || line_no > activeUser.startIndex + 5)
                    tempFile << c;

                // if a newline character skip this line
                if (c == '\n')
                    line_no++;
            }
            // Storing data in a new temp file
            tempFile << activeUser.email<<endl;
            tempFile << activeUser.phone<<endl;
            tempFile << activeUser.name<<endl;
            activeUser.password = passEncrypted;
            tempFile << activeUser.password<<endl;
            tempFile << activeUser.id<<endl;
            tempFile << '\n';

            tempFile.close();
            originalFile.close();

            remove(file_name);
            rename("temp.txt", file_name);

            main();
    } else {
        // Otherwise, if the user entered an invalid regex match then he is asked to re-enter again.
        cout << "Password is NOT valid \nPlease try again! " << endl;
        changePassword();
    }


}


void verifyPassword() {

    string password1, password2, passEncrypted = "";
    int masking1, masking2, temp;
    cout << "Please enter your password: " << endl;
    // 9. Cover the password with ***** while the user is entering it.
    masking1 = _getch();
    while (masking1 != 13) {
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
    regex regexRulePass(fullPattern2);

    // checking if it matches the rule given above
    bool isValid = regex_search(password1, regexRulePass);
    if (isValid){
        // Encrypting this password
        cout << "Password is valid" << endl;
        for (char letter: password1) {
            temp = int(letter);
            temp++;
            passEncrypted += char(temp);
        }
        // Then this encrypted password is stored in the file
        myFile.open("Database.txt", ios::app);
        myFile << passEncrypted << endl;
        myFile.close();
        cout << "Please enter your password again: " << endl;
        // Re-entering the password and use password masking
        masking2 = _getch();
        while (masking2 != 13) {
            password2.push_back(masking2);
            cout << '*';
            masking2 = _getch();
        }
        cout << endl;
        // 7- Ask the user to repeat the password and make sure it was entered the same twice.
        while (password1 != password2) {
            cout << "The two passwords are not the same, please re-enter the second password: " << endl;
            cin >> password2;
            if (password1 == password2) {
                // Storing the password in the list, to use it as the value of the map
                userDetails.push_back(password1);
                break;
            }
        }
    } else {
        cout << "Password is NOT valid " << endl;
        verifyPassword();
    }
}

void verifyName() {
    string name;
    cout << "Please enter your name :" << endl;
    cin >> name;

    // creating a regex rule for the name format
    string namePattern = "^[a-zA-Z_]+$";
    regex nameRule(namePattern);
    bool isValid = regex_search(name, nameRule);

    // If the name format is valid then it's stored in the file, otherwise the user is asked to re-enter
    if (!isValid) {
        cout << "Invalid name, please enter letters or _ only: " << endl;
        verifyName();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << name << endl;
        myFile.close();
        userDetails.push_back(name);
    }
}

void verifyMobile() {
    string mobile;
    cout << "Please enter your mobile number: " << endl;
    cin >> mobile;

    // Creating a regex rule for the mobile format, contain only numbers and starts with 01
    string regexPattern = "01[0-9]*";
    regex regexRule(regexPattern);
    bool isValid = regex_match(mobile, regexRule);

    // storing mobile in the file if the length of the mobile is exactly 11 AND matches the regex rule above
    // Otherwise, the user is asked to re-enter
    if (mobile.length() != 11 || !isValid) {
        cout << "Invalid mobile number, it must be 11 digits starts with 01: " << endl;
        verifyMobile();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << mobile << endl;
        myFile.close();
        // Storing the mobile in the list, to use it as the value of the map
        userDetails.push_back(mobile);
    }
}

void verifyEmail() {
    string email;
    cout << "Please enter your email: " << endl;
    cin >> email;

    // Creating a regex rule for the email format, and ends with ".com"
    string regexPattern = "\\w+\\.?\\w+@\\w+\\.com";
    regex regexRule(regexPattern);
    bool isValid = regex_match(email, regexRule);

    // Checking if valid. Otherwise, the user is asked to re-enter the email
    if (!isValid) {
        cout << "Invalid email address format: [ohndoe@company.com] \nPlease try again! " << endl;
        verifyEmail();
    } else {
        userEmail = email;
        // Checking if this email has been already stored in the map before, if yes then the user is asked to enter another one
        for (auto word: userProfile) {
            if (email == word.first) {
                cout << "This email has been registered before, please choose another one: " << endl;
                verifyEmail();
                break;
            }
        }
    }
}
#include <limits>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#define COL_WIDTH 100000
using namespace std;
//Function used to clear the input

void clearingInput () {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

//Function used to save the data of a file before it gets wiped
void savingFile(string str, char* line, int *num){
    //Creating an ifstream object with the string as the file name
    ifstream object(str);
    //If the file does not exist, exit the program
    if(!object){
        //To fix spacing in the files at the beginning
        *num += 1;
        return;
    }

    //Start a loop to store the data to line, stops when it is the end of the file
    while(!object.eof()){
        object.getline(line,COL_WIDTH);
    }
    //Close the file 
    object.close();
}

string saveAnotherFile(string str,int decision){
    ifstream object;
    object.open(str);
    string output,output2;
    int count = 0;
    while(object.good()){
        getline(object,output,'\n');
        if(count > 0 || decision == 1){
            output2 = output2 + output; 
        }
       count++;
    }
    return output2;
}

//Check if the username or password is strong enough
bool string_leng(string str) {
    if(str.length() >= 8){
        return true;
    }
    return false;
}

class Admin {
    public:
        Admin() {password = "password";}
        string getPassword();
        void userRegisteration();
        void printDatabase();
        void CreatingAndTrainSchedule();
        void editUsernameOrPassword();
        void displayPassengerInfo();
    private:
        bool verifyUsername(string fileName,string username, int *counter);
        string password; 
        void printSpecificInfo(int counter, char* lines, string header);
        void editFiles(string fileName,string input, int counter);
        ofstream createFiles(string fileName);
};

ofstream Admin::createFiles(string fileName) {
    ofstream object;
    object.open(fileName);
    return object;
}

void Admin::CreatingAndTrainSchedule() {
    ofstream trainSchedule = createFiles("Week25_TrainSchedule.csv");
    //Populating the location array with train stations
    string location[] = {"Waterloo","Victoria","Liverpool Street","London Bridge","Charing Cross","Euston","Paddington","Birmingham New Street","King's Cross","Glasgow Central","Leeds","St.Pancras","Edinburgh","Clapham Junction","Stratford","Glasgow Queen Street","East Croydon","Cannon Street","Manchester Piccadilly","Wimbledon","Vauxhall","Fenchurch Street","Brighton","Reading","Gatwick Airport","Gatwick Airport","Marylebone","Liverpool Central","Ilford","St.Albans City","Balham","Nottingham","Oxford","Sutton","Bath Spa","Kingston","Earlsfield","City Thameslink"};
    //Calculating the size of location
    int size = *(&location + 1) - location;
    int seats = 500;
    trainSchedule << "Depart" << "," << "Dest" << "," << "Time" << "," << "Platform" << "," <<"Capacity" << endl;
    //Random number
    srand(time(0));
    //Time slot array
    string time[] = {"10:00","10:10","10:20","10:30","10:40","10:50","11:00"};
    //Two pointers array
    for(int i = 0; i < size; i++){
        //Generating a new random number in every iterlation, a random number from 0 to 7
        for(int j = i + 1; j < size; j++){
            int randomNumber = rand() % 6;
            //Displaying the info
            trainSchedule <<  location[i] << "," << location[j] << "," << time[randomNumber] << "," << randomNumber << "," << 500 << endl;
        }
    }
    trainSchedule.close();
}


//A private method that verifies the username
bool Admin::verifyUsername(string fileName,string username, int *counter){
    //character arrays to store the data from the files 
    char lines[COL_WIDTH+1];
    //Saving the file
    savingFile(fileName,lines,0);
    //converting lines to a string
    string s_a = lines, check;
    //stringstream used to parse s_a
    stringstream check1(s_a);
    //if it hits a space, tokenize it
    while(getline(check1,check,' ')){
        //increament counter by 1 
        *counter+=1;
        //if it finds the username
        if(check == username){
            return true;
        }
    }
    cout << "This user does not exist.\n";
    return false;
}


//A private method that edits whatever files at whatever positions
void Admin::editFiles(string fileName, string input, int counter) {
    //character arrays to store the data from the files
    char lines[COL_WIDTH + 1];
    //saving the file
    savingFile(fileName,lines,0);
    //Creating an ofstream object with the filename
    ofstream object(fileName);
    //converting lines to a string
    string s_a = lines,check;
    stringstream check1(s_a);
    while(getline(check1,check,' ')){
        counter--;
        if(counter == 0){
            check = input;  
        }
        object << check << " ";
    }
    object.close();
}
//A public method to edit the username,password,or both
void Admin::editUsernameOrPassword() {
    //clearing all previous user inputs
    clearingInput();
    string username_ori,username, password,decision;
    char username_line[COL_WIDTH+1], password_line[COL_WIDTH+1];
    int counter = 0;
    //Asking for the username
    cout << "Please enter the username:\n";
    getline(cin,username_ori);
    //if the username exists within the username.txt file
    if(verifyUsername("Username.txt",username_ori,&counter)){
        //Ask if they want to change the username as well
        cout << "Would you like to change the username(Y/N):" << endl;
        getline(cin,decision);
        if(decision == "Y" || decision == "y"){
            while(true){
                //Ask for new username
                cout << "Please enter the new username:" << endl;
                getline(cin,username);
                //if it is 8 characters or longer, that means its strong enough
                if(string_leng(username)){
                    break;
                }
                //if the new username is the same as the old username, try again
                else if(username_ori == username){
                    cout << "The new username cannot be the same as the old username.\n";
                }
                //The username is not strong enough
                else {
                    cout << "It has to be 8 characters or longer."<< endl;
                }
            }
        }
        while(true) {
            //Now ask for new password
            cout << "Please enter the new password:" << endl;
            getline(cin,password);
            //8 characters or longer
            if(string_leng(password)){
                break;
            }
            //Using verifyUsername to see if it is the same password
            else if(verifyUsername("Password.txt",password,0)) {
                cout << "The new password cannot be the same as the old password.\n";
            }
            //Password is simply not strong enough
            else {
                cout << "It has to be 8 characters or longer." <<endl;
            }
        }
    }
    //the username changes
    if(decision == "Y" || decision == "y"){
        //uSe private method editFiles() to change the username at the correct positions
        editFiles("Username.txt",username,counter);
    }
    //same for the password
    editFiles("Password.txt",password,counter);
}
//A private method working in sync with displayPassengerInfo()
void Admin::printSpecificInfo(int counter, char* lines, string header) {
    //to check if counter2 is equal to counter
    int counter2 = 0;
    //same thing as displayPassengerInfo()
    string s_a = lines, check;
    stringstream check1(s_a);
    while(getline(check1, check, ' ')){
        counter2++;
        //Arrive the appropriate data
        if(counter2 == counter){
            //Make it look good
            cout << header << ":" << check << endl;
        }
    }
}

//Method to print out a specific passenger's info
void Admin::displayPassengerInfo() {
    clearingInput();
    string fileName[] = {"Username.txt","Password.txt","Name.txt","Age.txt","City.txt"};
    string header[] = {"Username ","Password ","Name ", "Age ", "City "};
    char lines[COL_WIDTH+1];
    string name,check;
    while(true){
        //Asking for passenger's name
        cout << "Please enter the name of the passenger you would like to inspect:\n";
        getline(cin,name);
        //storing all the info from Name.txt to lines in order to parse it later
        int counter = 0;
        if(verifyUsername(fileName[2],name,&counter)) {
            //Now getting the username,password, name, age, and city of the specific passenger
            for(int i = 0; i < 5; i++){
                //getting all the data from the specific files
                savingFile(fileName[i],lines,0);
                //using a private method to print out the correct info
                printSpecificInfo(counter, lines,header[i]);
            }
            //ending
            break;
        }
        else {
            return;
        }
    }
}
//Method is used to print out the data from the files
void Admin::printDatabase(){
    clearingInput();
    //String array storing file names
    string fileName[] = {"Username.txt","Password.txt","Name.txt","Age.txt","City.txt"};
    //String array storing the header
    string header[] = {"Username ","Password ","Name ", "Age ", "City "};
    //To store the data from the files
    char lines[COL_WIDTH + 1];
    for(int i = 0; i < 5; i++){
        cout << "-------------------------------------------------------------------------------------------\n";
        //Storing the lines in character array lines
        savingFile(fileName[i],lines,0);
        //Convert from char array to string
        string str = lines;
        //Printint out the lines
        cout << header[i] << "|";
        for(int j = 0; j < str.length(); j++){
            if(str[j] == ' '){
                cout << "|";
            }
            else {
                cout << str[j];
            } 
        }
        cout << "|" << endl;
        
    }
    cout << "-------------------------------------------------------------------------------------------\n";
}

// //This admin method is for creating user and passenger info

void Admin::userRegisteration() {
    //Clearing inputs
    clearingInput();
    //for spacing at the beginning of the files
    int num = 0;
    string username, password, passengerName, age, city, username_file = "Username.txt", password_file = "Password.txt", Passenger_Name_File = "Name.txt", Age_file = "Age.txt", City_File = "City.txt";
    //To store pre-existing data within the files
    char username_line[COL_WIDTH + 1],password_line[COL_WIDTH+1], passenger_line[COL_WIDTH + 1], name_line[COL_WIDTH + 1], age_line[COL_WIDTH + 1], city_line[COL_WIDTH + 1];
    //while loop to check whether the username and passwords are 8 characters or longer
    while(true){
        cout << "Please enter your username(8 characters or longer):";
        getline(cin,username);
        cout << "Please enter your password(8 characters or longer):";
        getline(cin,password);
        if(string_leng(username) && string_leng(password)){
            break;
        }
        cout << "Username and password has to be 8 characters or longer.\n";
    }
    //Asking for name, age, and city
    cout << "Please enter your first name:";
    getline(cin,passengerName);
    cout << "Please enter your age:";
    getline(cin,age);
    cout << "Please enter the city where you reside:";
    getline(cin,city);
    //Saving all the files and putting the data in the character arrays 
    savingFile(username_file,username_line,&num);
    savingFile(password_file,password_line,&num);
    savingFile(Passenger_Name_File,passenger_line,&num);
    savingFile(Age_file,age_line,&num);
    savingFile(City_File,city_line,&num);
    //Wiping the files and creating ofstream objects
    ofstream fUser(username_file), fPassword(password_file), fName(Passenger_Name_File),fAge(Age_file),fCity(City_File);
    if(!fUser || !fPassword || !fName || !fAge || !fCity){
        cout << "The file does not exist.Exiting\n";
        return;
    }
    //if num is not zero, that means those files do not exist, therefore these lines are not required. Else they will paste all the pre-existing data into the corresponding files
    if(num == 0){
        fUser << username_line << " ";
        fPassword << password_line << " ";
        fName << passenger_line << " ";
        fAge << age_line << " ";
        fCity << city_line << " ";
    }
    //Putting all the data into the corresponding files
    fUser << username;
    fPassword << password;
    fName << passengerName;
    fAge << age;
    fCity << city;
    //Closing the files
    fUser.close();
    fPassword.close();
    fName.close();
    fAge.close();
    fCity.close();
}
//Since password is private, then a password getter is needed
string Admin::getPassword() {
    return password;
}

//A Main menu class
class Menu {
  public:
    void showMenu();  
    void adminMenu();
    void userMenu();
};

void Menu::userMenu() {
    clearingInput();

}
//This is an Admin Menu
void Menu::adminMenu() {
    clearingInput();
    int login_count = 0,decision;
    string str;
    //Creates an admin object
    Admin admin = Admin();
    //The function will exit if the user tries to login three times and fails
    while(login_count != 3){
        //Ask for admin password
        cout << "Please enter the admin password:\n";
        getline(cin,str);
        if(str == admin.getPassword()) {
            cout << "Login Complete\n";
            break;
        }
        else {
            //Increment login_count everytime the user gets the password wrong
            login_count++;
            if(login_count == 3){
                cout << "Login Fail. Please try again later.\n";
                return;
            }
        }
    }
    //Login phase has been completed
    while(true){
        cout << "                                 Menu                                               \n";
        cout << "1. User Registeration\n";
        cout << "2. Print Database\n";
        cout << "3. Data Entry\n";
        cout << "4. Change Username or Password\n";
        cout << "5. Display Passenger Detail\n";
        cin >> decision;
        //Jumps to userRegisteration()
        if(decision == 1){
            admin.userRegisteration();
            break;
        }
        else if(decision == 2){
            admin.printDatabase();
            break;
        }
        else if(decision == 3){
            admin.CreatingAndTrainSchedule();
            break;
        }
        else if(decision == 4){
            admin.editUsernameOrPassword();
            break;
        }
        else if(decision == 5){
            admin.displayPassengerInfo();
            break;
        }
        else {
            cout << "Please type in 1,2,3,4,or 5\n";
        }
    }
}
//Main menu

void Menu::showMenu() {
    int decision;
    cout << "Welcome to Railway Registeration System (Version 1.0.0) Brax's Production\n";
    while(true){
        cout << "                                 Menu                                               \n";
        cout << "1. Administrator Mode\n";
        cout << "2. User Mode\n";
        cin >> decision;
        if(decision == 1){
            //Jumps to admin menu
            adminMenu();
            break;
        }
        else if(decision == 2){
            userMenu();
            break;
        }
        else {
            cout << "Please type in either 1 for admin mode or 2 for user mode.\n";
        }
    }
}
int main () {
    //Creating menu object
    Menu menu;
    //Showing the menu
    menu.showMenu();
    //exit the program
    return 0;
}
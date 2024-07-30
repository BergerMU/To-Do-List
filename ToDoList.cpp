#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Function for initializing new file
void InitToDo() {
    //Intro string that serves as the header to the program
    string intro = "ToDo List - Berger\n--------------------\n";
    ifstream file("ToDo.txt", ios::in);

    //Checks to see if file is open
    if (file.is_open()) {
        //Uses seekg to go to the end of the file and uses tellg to return the position, in total, gets the size of the txt
        file.seekg(0, ios::end);
        size_t size = file.tellg();

        //Checks to see if it's a empty list to see if it needs to append the header at the top
        if (size == 0) {
            ofstream file("ToDo.txt");
            file<<intro;
            file.close();
        } else {
            file.close();
        }
    //Tells user file can't open
    } else {
        cout<<"Error, file isn't open"<<endl;
    }
}

void add() {
    //Takes user input
        cout<<"Enter what you would like to add: ";
        string input;
        getline(cin, input);
    
    //opens file and checks to see if it worked
    ofstream outputfile("ToDo.txt", ios::app);
    if (outputfile.is_open()) {
        //Appends the user input to the bottom of the list
        outputfile<<input<<"\n";
        outputfile.close();
    } else {
        cout<<"Error, file isn't open"<<endl;
    }
}

void check() {
    ifstream file("ToDo.txt", ios::in);
    
    //Checks to see if file is open
    if (file.is_open()) {
        string input;
        string line;
        vector <string> vector_file;
        
        //Takes user input
        cout<<"Enter the number of the line you want to check/uncheck: ";
        getline(cin,input);
        int index = stoi(input);

        //Converts the txt document to a vector string so we can index through it and make adjustments
        while (getline(file, line)) {
            vector_file.push_back(line);
        }
        file.close();
        
        index += 1;

        //Checks to see if user input a number not in list
        if (index < 2 || index > vector_file.size()) {
            cout<<"Number not in list"<<endl;
            check();
            return;
        }
        
        //Creates string named "item" that represents the different items in the vector
        string &item = vector_file[index];
        string checkmark = " ✓";

        //Checks to see if the checkmark is in the string
        if (item.find(checkmark) != string::npos) {
            item.erase(item.size() - checkmark.size(), checkmark.size());
    } 
    //Adds a check mark if there isn't already one
    else {
        item += checkmark;
    }
        //Appends everything from the vector file back into the txt file
        ofstream outputfile("ToDo.txt", ios::out | ios::trunc);
        for (int i = 0; i < vector_file.size(); i++) {
            outputfile<<vector_file[i]<<"\n";
        }
        outputfile.close();
    } else {
        cout<<"Error, file isn't open"<<endl;
    }
}

void update() {
    ifstream file;
    file.open("ToDo.txt", ios::in);
    
    //Checks to see if file is open
    if (file.is_open()) {
        int input;
        string line;
        string updated_string;
        vector <string> vector_file;
        
        //Gets user input
        cout<<"Enter the number of the line you want to update: ";
        cin>>input;
        cin.ignore();

        //Checks to see if user put in number not in list
        if (input < 1 || input > vector_file.size() - 1) {
            cout<<"Number not in list"<<endl;
            update();
            return;
        }

        //Takes updated string
        cout<<"Enter text: ";
        getline(cin, updated_string);

        //Converts txt file to vector so we can index through it and do cool things
        while (getline(file, line)) {
            vector_file.push_back(line);
        }
        file.close();
        
        //Adjusts input for the header and replaces the part in the vector with our updated string
        input += 1;
        vector_file[input] = updated_string;

        //Appends everything back into the ToDo.txt file from our vector
        ofstream outputfile("ToDo.txt", ios::out | ios::trunc);
        for (int i = 0; i < vector_file.size(); i++) {
            outputfile<<vector_file[i]<<endl;
        }
        outputfile.close();
    } else {
        cout<<"Error, file isn't open"<<endl;
    }
}

void remove() {
    ifstream file("ToDo.txt", ios::in);
    
    //Checks to see if file is open
    if (file.is_open()) {
        string input;
        string line;
        vector <string> vector_file;
        
        //Gets user input
        cout<<"Enter the number of the line you want to remove: ";
        getline(cin, input);
        int index = stoi(input);

        //rewrites entire todo list to the vector
        while (getline(file, line)) {
            vector_file.push_back(line);
        }
        file.close();

        //Checks to see if input is withing the available range
        if (index < 1 || index > vector_file.size() - 2) {
            cout<<"Number not in list"<<endl;
            remove();
            return;
        }

        //Adjust input for header and appends everything to the text file except for the line we want removed
        index += 1;
        ofstream outputfile("ToDo.txt", ios::out);
        for (int i = 0; i < vector_file.size(); i++) {
            if (i != index) {
                outputfile<<vector_file[i]<<endl;
            }
        }
    } else {
        cout<<"Error, file isn't open"<<endl;
    }
}

void read() {
    //Opens file and checks to see if it worked
    ifstream file("ToDo.txt", ios::in);
    if (file.is_open()) {
        string str;
        int count = -1;
        
        //Loops through and skips the header to start numbering the items
        while (getline(file, str)) {
            if (count <= 0) {
                cout<<str<<"\n";
            } else {
                cout<<"["<<count<<"] "<<str<<"\n";
            }
            count += 1;
        }
    } else {
        cout<<"File already open"<<endl;
    }
    file.close();
}

// void password() {
//     string line;
//     vector <string> vector_file;
//     ifstream file("ToDo.txt", ios::in);
//     if (file.is_open()) {
//         //Converts the txt document to a vector string so we can index through it and make adjustments
//         while (getline(file, line)) {
//             vector_file.push_back(line);
//         }

//         string input;
//         cout<<"New Password: ";
//         getline(cin, line);
        
//         string &item = vector_file[-1];
//         if (item.find("Password") != string::npos) {
//             cout<<"awesomesauce";
//         } else {
//             cout<<"Bruh";
//         }
//         //print password
//         // string password = "temp123";
//         // cout<<"New password: ";
//         // getline(cin, password);

//     } else {
//         cout<<"Error, file couldn't open"<<endl;
//     }
// }


void ask() {
    while (true) {
        read();
        cout<<"Would you like to add(1), check/uncheck(2), update(3), remove(4), leave(5) from the list?"<<endl;
        string input;
        getline(cin, input);
        
        if (input == "1") {
            add();
        } else if (input == "2") {
            check();
        } else if (input == "3") {
            update();
        } else if (input == "4") {
            remove();
        } else if (input == "5") {
            break;
        // } else if (input == "6") {
        //     password();
        } else {
            cout<<"Not a valid input, enter a number 1-5"<<endl;
        }
    }
}

int main() {
    // string key = "maryville is awesome sauce";
    // string input;
    // cout<<"Enter password: ";
    // getline(cin, input);
    // if (input == key) {
    InitToDo();
    ask();
    // } else {
    //     cout<<"Try again"<<endl;
    //     main();
    // }
    return 0;
}
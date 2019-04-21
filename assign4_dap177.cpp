//Drew Post
//CS2308
//A04842758
//Assignment 4

#include "Contact.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <limits>


using namespace std;


void displayMenu(); //displays menu

int getUserChoice(); //gets user's choice from the menu options

Contact** pushback(Contact**, int); //dynamically allocates one more obj into array

Contact** loadInContacts(Contact**, int&, string); //creates database.txt or loads preexisting one, returns pointer to new array

Contact** bubbleSort(Contact**, int); //sorts the contact array, returns pointer to sorted array

void displayContact(Contact**, int); //displays a contact

PhoneType stringToPhoneType(string); //converts string to PhoneType

Contact** addNewContact(Contact**, int&); //adds new contact, returns pointer to new array

void searchForContact(Contact**, int); //searches for contact by first or last name

int deleteFunctionErrorChecking(); // gets user input for delete function and checks for errors

bool isEqual(Contact*, Contact*); //returns true if two contact pointers are equal

Contact** popback(Contact**,int, Contact*); //dynamically deallocates one less obj out of array

Contact** deleteContact(Contact**, int&); //deletes contact from array, returns pointer to new array

Contact** editContact(Contact**, int); //edits the information of an existing contact

void updateProgram(Contact**, int); //writes from array to the database

string toLower(string); //converts uppercase to lowercase







int main()
{

    cout << "       **CONTACTS**        " << endl;
    cout << endl;


    int userChoice = 0;

    int size = 1;

    string emptyString = "";

    string fileName = "database.txt";

    Contact **contactBook = new Contact*[size];
    *(contactBook) = new Contact(emptyString, emptyString);

    size--;

    contactBook = loadInContacts(contactBook, size, fileName); //since we change the array each time we load in a contact, the book is set to the new pointer in main

    contactBook = bubbleSort(contactBook, size); //since we change the array each time we sort the array, the book is set to the new pointer in main

    while(userChoice != 6) //loops the menu and takes user choice until the user wishes to exit
    {

        displayMenu();

        userChoice = getUserChoice();

        if(userChoice == 1) //display all contacts or tell the user there aren't any contacts yet
        {
            cout << "---------------------------------------------" << endl;
            cout << endl;
            cout << "               **CONTACTS**" << endl;
            cout << endl << endl;

            if(size == 0)
            {
                cout << "   NO CONTACTS" << endl;
            }

            for(int i = 0; i < size; i++)
            {
                if((*(contactBook + i)) -> getPhoneType() != UNKNOWN)
                {
                    displayContact(contactBook, i);
                }

                cout << endl;
            }


            cout << endl;
            cout << "---------------------------------------------" << endl;
            cout << endl;
        }

        if(userChoice == 2) //add new contact
        {
            contactBook = addNewContact(contactBook, size); //since we change the array each time we add in a contact, the book is set to the new pointer in main

            contactBook = bubbleSort(contactBook, size); //since we change the array each time we sort it, the book is set to the new pointer in main
        }

        if(userChoice == 3) //search w first or last name
        {
            searchForContact(contactBook, size);

        }

        if(userChoice == 4) //delete
        {
            contactBook = deleteContact(contactBook, size); //since we change the array each time we delete a contact, the book is set to the new pointer in main

            contactBook = bubbleSort(contactBook, size); //since we change the array each time we sort it, the book is set to the new pointer in main
        }

        if(userChoice == 5) //edit
        {
            contactBook = editContact(contactBook, size);

            contactBook = bubbleSort(contactBook, size); //user could edit last name, changing the alpha order
        }


    }

    if(userChoice == 6) //update and exit
    {
        updateProgram(contactBook, size);

        for(int i = 0; i < size; i++)
        {
            delete *(contactBook + i);

        }

        delete [] contactBook;

        return 0;
    }



    return 0;
}

Contact** pushback(Contact **contact, int size)
{

    string emptyString = "";

    if(size != 0)
    {
        Contact **temp = new Contact*[size + 1];

        for(int i = 0; i < size; i++)
        {
            (*(temp + i)) = new Contact(emptyString, emptyString);

            (*(temp + i)) -> setFirstName((*(contact + i)) -> getFirstName());
            (*(temp + i)) -> setLastName((*(contact + i)) -> getLastName());
            (*(temp + i)) -> setPhoneNumber((*(contact + i)) -> getPhoneNumber());
            (*(temp + i)) -> setPhoneType((*(contact + i)) -> getPhoneType());

        }

        *(temp + (size)) = new Contact(emptyString, emptyString);

        for(int i = 0; i < size; i++)
        {
            delete *(contact + i);

        }

        delete [] contact;

        return temp;

    }

    else
    {
        return contact;
    }

}

Contact** loadInContacts(Contact **contacts, int& size, string fileName) //loads in from database.txt or creates database.txt
{
    ifstream inFile;
    inFile.open(fileName);

    const char delimeter = '~';

    if(!inFile)
    {
        inFile.close();

        ofstream outFile;
        outFile.open(fileName);
        outFile.close();

    }
    else if(inFile)
    {
        string tempPhoneNumber;
        string phoneNumber;
        string type;
        string firstName;
        string lastName;
        PhoneType phoneType;
        string emptyString = "";


        Contact *set = new Contact(emptyString, emptyString);

        while(getline(inFile, firstName, delimeter)) //doesnt even get into the while loop
        {

            contacts = pushback(contacts, size);

            size++;

            getline(inFile, lastName, delimeter);

            getline(inFile, phoneNumber, delimeter);

            getline(inFile, type);

            if(type == "0")
            {
                phoneType = CELL;
            }
            else if(type == "1")
            {
                phoneType = HOME;
            }
            else if(type == "2")
            {
                phoneType = WORK;
            }
            else
            {
                phoneType = UNKNOWN;
            }

            set = (*(contacts + (size - 1)));

            set -> setFirstName(firstName);
            set -> setLastName(lastName);
            set -> setPhoneNumber(phoneNumber);
            set -> setPhoneType(phoneType);

        }
    }

    inFile.close();

    return contacts;
}

Contact** bubbleSort(Contact **contacts, int size) //sorts array by first name
{
    bool isSorted = false;
    int ii;
    string lastName1, lastName2;
    string emptyString = "";
    Contact *temp = new Contact(emptyString, emptyString);

    while(!isSorted)
    {
        isSorted = true;

        for(int i = 0; i < size - 1; i++)
        {
            lastName1 = toLower((*(contacts + i)) -> getLastName());

            ii = i + 1;

            lastName2 = toLower((*(contacts + ii)) -> getLastName());

            if(lastName1.compare(lastName2) > 0)
            {
                Contact *contactA = *(contacts + i);
                Contact *contactB = *(contacts + ii);

                *temp = *contactA;
                *contactA = *contactB;
                *contactB = *temp;

                isSorted = false;
            }
        }

        size--;
    }

    return contacts;

}

void displayMenu() //displays menu for user
{
    cout << "   1. DISPLAY ALL CONTACTS " << endl;
    cout << "   2. ADD NEW CONTACT " << endl;
    cout << "   3. SEARCH FOR A GIVEN FIRST OR LAST NAME " << endl;
    cout << "   4. DELETE CONTACT " << endl;
    cout << "   5. EDIT CONTACT " << endl;
    cout << "   6. EXIT PROGRAM " << endl;
    cout << endl;
}

int getUserChoice() //gets the menu choice from the user
{
    int choice = 0;

    cout << "   ENTER MENU CHOICE (1 - 6): ";
    cin >> choice;
    cout << endl;

    while((choice < 1 && choice > 6) || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "   **ERROR: ENTER VALID MENU CHOICE**" << endl;
        cout << endl;
        cout << "   ENTER MENU CHOICE (1 - 6): ";
        cin >> choice;
        cout << endl;
    }

    return choice;
}

void displayContact(Contact **contacts, int index) //displays contents of the contacts array (MENU OPTION 1 & USED IN SEARCH)
{

    cout << "   " << (index + 1) << ". " << (*(contacts + index)) -> getFirstName() << " " << (*(contacts + index)) -> getLastName();

    if((*(contacts + index)) -> getPhoneType() == CELL)
    {
        cout << ", Cell ";
    }

    else if((*(contacts + index)) -> getPhoneType() == HOME)
    {
        cout << ", Home ";
    }

    else if((*(contacts + index)) -> getPhoneType() == WORK)
    {
        cout << ", Work ";
    }
    else if((*(contacts + index)) -> getPhoneType() == UNKNOWN)
    {
        cout << ", Unknown ";
    }

    string tempPhoneNumber = (*(contacts + index)) -> getPhoneNumber();

    if(tempPhoneNumber == "Unknown")
    {
        cout << "Unknown ";
    }
    else
    {
         cout << "(" << tempPhoneNumber[0] << tempPhoneNumber[1] << tempPhoneNumber[2] << ") ";

        for(int i = 3; i < tempPhoneNumber.size(); i++)
        {
            if(i == 6)
            {
                cout << "-" << tempPhoneNumber[i];
            }
            else
            {
                cout << tempPhoneNumber[i];
            }
        }
    }


    cout << endl;

}

string toLower(string a) //converts uppercase to lowercase
{
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    return a;
}

PhoneType stringToPhoneType(string type) //turns a string into the PhoneType enum (for addNewContact)
{
    if(type == "CELL" || type == "cell" || type == "Cell")
    {
        return CELL;
    }

    else if(type == "HOME" || type == "home" || type == "Home")
    {
        return HOME;
    }

    else if(type == "WORK" || type == "work" || type == "Work")
    {
        return WORK;
    }
    else
    {
        return UNKNOWN;
    }


}

Contact** addNewContact(Contact **contacts, int& size) //adds new contact to the contacts array (MENU OPTION 2)
{
    string phoneNumber;
    string tempPhoneType;
    string firstName;
    string lastName;


    contacts = pushback(contacts, size);

    size++;


    cout << "---------------------------------------------" << endl;
    cout << endl;
    cout << "   - Enter contact first name: ";

    cin >> firstName;
    cout << endl;

    cout << "   - Enter contact last name: ";

    cin >> lastName;
    cout << endl;

    cout << "   - Enter contact phone number: ";

    cin >> phoneNumber;

    (*(contacts + (size - 1))) -> setPhoneNumber(phoneNumber);

    cout << endl;

    cout << "   - Enter contact phone type (CELL, HOME, WORK, UNKNOWN): ";
    cin >> tempPhoneType;

    while((tempPhoneType != "CELL" && tempPhoneType != "Cell" && tempPhoneType != "cell" && tempPhoneType != "HOME" &&  tempPhoneType != "Home" &&  tempPhoneType != "home"
           && tempPhoneType != "WORK" && tempPhoneType != "Work" && tempPhoneType != "work" && tempPhoneType != "UNKNOWN" && tempPhoneType != "Unknown" && tempPhoneType != "unknown")
           || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cout << "   **ERROR : ENTER VALID PHONE TYPE** " << endl;
        cout << endl;
        cout << "   - Enter contact phone type (CELL, HOME, WORK, UNKNOWN): ";
        cin >> tempPhoneType;
    }

    cout << endl;


    PhoneType phoneType = stringToPhoneType(tempPhoneType);

    (*(contacts + (size - 1))) -> setFirstName(firstName);
    (*(contacts + (size - 1))) -> setLastName(lastName);
    (*(contacts + (size - 1))) -> setPhoneType(phoneType);


    cout << "   **CONTACT ADDED**" << endl;
    cout << endl;
    cout << "---------------------------------------------" << endl;

    cout << endl;

    return contacts;
}

void searchForContact(Contact **contacts, int size) //searches for contact specified by the user using last names (MENU OPTION 3)
{
    int first = 0;
    int middle;
    int last = size - 1;

    string nameToFind;

    cout << "---------------------------------------------" << endl;
    cout << endl;

    cout << "   ENTER LAST NAME: ";
    cin >> nameToFind;
    cout << endl;

    while(first <= last)
    {
        middle = (first + last) / 2;

        string contactMiddle = toLower((*(contacts + middle)) -> getLastName());
        string nameToFindLowercase = toLower(nameToFind);

        if((contactMiddle.compare(nameToFindLowercase) == 0))
        {
            displayContact(contacts, middle);

            for(int i = first; i < middle; i++) //searches for duplicates on both sides
            {
                string contactI = toLower((*(contacts + i)) -> getLastName());

                if((contactI.compare(nameToFindLowercase) == 0))
                {
                    displayContact(contacts, i);
                }
            }

            for(int j = last; j > middle; j--) //searches for duplicates on both sides
            {
                string contactJ = toLower((*(contacts + j)) -> getLastName());

                if((contactJ.compare(nameToFindLowercase) == 0))
                {
                    displayContact(contacts, j);
                }
            }


            break;
        }

        else if((contactMiddle.compare(nameToFindLowercase) > 0))
        {
            last = middle - 1;
        }

        else if((contactMiddle.compare(nameToFindLowercase) < 0))
        {
            first = middle + 1;
        }

    }

    cout << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;


}

Contact** editContact(Contact** contactList, int size) //edits information of existing contact (MENU OPTION 5)
{
    int userChoice;
    int toEdit;

    searchForContact(contactList, size);

    cout << "   **NOTE: Index is the number in front of the contact's first name**" << endl;
    cout << endl;
    cout << "   ENTER THE INDEX OF THE CONTACT YOU WANT TO EDIT: ";
    cin >> userChoice;
    cout << endl;

    cout << endl;

    int index = userChoice - 1;

    cout << "   WHICH COMPONENT WOULD YOU LIKE TO EDIT?" << endl;
    cout << endl;
    cout << "   1. First Name " << endl;
    cout << "   2. Last Name " << endl;
    cout << "   3. Phone Number " << endl;
    cout << "   4. Phone Type " << endl;
    cout << endl;
    cout << "   CHOOSE (1 - 4): ";

    cin >> toEdit;
    cout << endl;

    while(toEdit < 1 || toEdit > 5)
    {
        cout << "   **ERROR: INVALID OPTION** " << endl;
        cout << endl;
        cout << "   CHOOSE (1 - 4): ";
        cin >> toEdit;
        cout << endl;
    }

    if(toEdit == 1)
    {
        string newFirstName;

        cout << "---------------------------------------------" << endl;
        cout << endl;
        cout << "   Enter new first name: ";

        cin >> newFirstName;
        cout << endl;

        (*(contactList + index)) -> setFirstName(newFirstName);

        cout << endl;

        cout << "   NEW: " << endl;
        displayContact(contactList, index);

        cout << endl;
        cout << "   **CONTACT EDITED**" << endl;
        cout << endl;
        cout << "---------------------------------------------"  << endl;
        cout << endl;

    }

    else if(toEdit == 2)
    {
        string newLastName;

        cout << "---------------------------------------------" << endl;
        cout << endl;
        cout << "   Enter new last name: ";
        cin >> newLastName;
        cout << endl;

        (*(contactList + index)) -> setLastName(newLastName);

        cout << "   NEW: " << endl;
        displayContact(contactList, index);

        cout << endl;
        cout << "   **CONTACT EDITED**" << endl;
        cout << endl;
        cout << "---------------------------------------------"  << endl;
        cout << endl;




    }

    else if(toEdit == 3)
    {
        string newPhoneNumber;

        cout << "---------------------------------------------"  << endl;
        cout << endl;
        cout << "   Enter new phone number: ";
        cin >> newPhoneNumber;
        cout << endl;

        (*(contactList + index)) -> setPhoneNumber(newPhoneNumber);

        cout << "   NEW: " << endl;
        displayContact(contactList, index);

        cout << endl;
        cout << "   **CONTACT EDITED**" << endl;
        cout << endl;
        cout << "---------------------------------------------"  << endl;
        cout << endl;


    }

    else if(toEdit == 4)
    {
        string tempPhoneType;
        PhoneType newPhoneType;

        cout << "---------------------------------------------" << endl;
        cout << endl;
        cout << "   **PHONETYPES** " << endl;
        cout << endl;
        cout << "   1. CELL " << endl;
        cout << "   2. HOME " << endl;
        cout << "   3. WORK " << endl;
        cout << "   4. UNKNOWN " << endl;
        cout << endl;
        cout << "   Enter new phone type (CELL, HOME, WORK, UNKNOWN): ";
        cin >> tempPhoneType;
        cout << endl;

        while((tempPhoneType != "CELL" && tempPhoneType != "Cell" && tempPhoneType != "cell" && tempPhoneType != "HOME" &&  tempPhoneType != "Home" &&  tempPhoneType != "home"
           && tempPhoneType != "WORK" && tempPhoneType != "Work" && tempPhoneType != "work") || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "   **ERROR : ENTER VALID PHONE TYPE** " << endl;
            cout << endl;
            cout << "   - Enter new phone type (CELL, HOME, WORK, UNKNOWN): ";
            cin >> tempPhoneType;
            cout << endl;
        }

        newPhoneType = stringToPhoneType(tempPhoneType);

        (*(contactList + index)) -> setPhoneType(newPhoneType);

        cout << "   NEW: "<< endl;
        displayContact(contactList, index);

        cout << endl;
        cout << "   **CONTACT EDITED**" << endl;
        cout << endl;
        cout << "---------------------------------------------"  << endl;
        cout << endl;




    }

    return contactList;


}

int deleteFunctionErrorChecking() //prompts user and does error checking - used in delete function
{
    int userChoice;

    cout << endl;
    cout << "   DO YOU WANT TO DELETE THIS CONTACT? (0 for NO, 1 for YES): ";
    cin >> userChoice;
    cout << endl;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(userChoice!= 0 && userChoice!= 1 && cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "   **ERROR: PLEASE TYPE IN 0 (NO) OR 1 (YES)**" << endl;
        cout << endl;

        cout << "   DO YOU WANT TO DELETE THIS CONTACT? (0 for NO, 1 for YES): ";
        cin >> userChoice;

    }

    return userChoice;
}

bool isEqual(Contact *contactA, Contact *contactB) //checks if contact pointers are equal - used in popback
{
    bool isEqualTo = false;

    if((contactA -> getFirstName() == contactB -> getFirstName())&& (contactA -> getLastName() == contactB -> getLastName())
       && (contactA -> getPhoneNumber() == contactB -> getPhoneNumber()) && (contactA -> getPhoneType() == contactB -> getPhoneType()))
    {

        isEqualTo = true;
    }

    return isEqualTo;

}

Contact** popback(Contact **contact , int size, Contact *target){

    Contact **temp = new Contact*[size - 1];

    int place = 0;

    for(int i = 0; i < size; i++)
    {

        if((isEqual(target, *(contact + i))) == false
           && ((*(contact + i)) -> getFirstName() != target -> getFirstName())) //checks first name to avoid deleting duplicates
        {

            *(temp + place) = *(contact + i);

            place++;

        }

    }

    for(int i = 0; i < size; i++)
    {

        if((isEqual(target, *(contact + i))) == true &&
           ((*(contact + i)) -> getFirstName() != target -> getFirstName())) //checks first name to avoid deleting duplicates
        {
            delete *(contact + i);
        }

    }


    return temp;
}

Contact** deleteContact(Contact **contacts, int& size) //deletes contact specified by the user using last name (**assumes you will delete someone**)(MENU OPTION 4)
{

    string nameToFind;

    int first = 0;
    int middle;
    int last = size - 1;

    int userChoice;


    cout << "---------------------------------------------" << endl;
    cout << endl;

    cout << "   ENTER LAST NAME: ";
    cin >> nameToFind;
    cout << endl;

    while(first <= last)
    {
        middle = (first + last) / 2;

        string contactMiddle = toLower((*(contacts + middle)) -> getLastName());
        string nameToFindLowercase = toLower(nameToFind);

        if((contactMiddle.compare(nameToFindLowercase) == 0))
        {
            displayContact(contacts, middle);

            userChoice = deleteFunctionErrorChecking();

            if(userChoice == 1)
            {

                contacts = popback(contacts, size, *(contacts + middle));

                size--;

                cout << "   **CONTACT DELETED** " << endl;
                cout << endl;
                cout << "---------------------------------------------" << endl;
                cout << endl;

                return contacts;
            }

            for(int i = first; i < middle; i++) //searches for duplicates on both sides
            {
                string contactI = toLower((*(contacts + i)) -> getLastName());

                if((contactI.compare(nameToFindLowercase) == 0))
                {
                    displayContact(contacts, i);

                    userChoice = deleteFunctionErrorChecking();

                    if(userChoice == 1)
                    {

                        contacts = popback(contacts, size, *(contacts + middle));

                        size--;


                        cout << "   **CONTACT DELETED** " << endl;
                        cout << endl;
                        cout << "---------------------------------------------" << endl;
                        cout << endl;

                        return contacts;
                    }


                }
            }

            for(int j = last; j > middle; j--)
            {
                string contactJ = toLower((*(contacts + j)) -> getLastName());

                if((contactJ.compare(nameToFindLowercase) == 0))
                {
                    displayContact(contacts, j);

                    userChoice = deleteFunctionErrorChecking();

                    if(userChoice == 1)
                    {

                        contacts = popback(contacts, size, *(contacts + middle));


                        size--;

                        cout << "   **CONTACT DELETED** " << endl;
                        cout << endl;
                        cout << "---------------------------------------------" << endl;
                        cout << endl;

                        return contacts;

                    }

                }

            }
        }

        else if((contactMiddle.compare(nameToFindLowercase) > 0))
        {
            last = middle - 1;
        }

        else if((contactMiddle.compare(nameToFindLowercase) < 0))
        {
            first = middle + 1;
        }

    }


    cout << "   **CONTACT NOT FOUND**" << endl;
    cout << endl;
    cout << "---------------------------------------------" << endl;
    cout << endl;


    return contacts;
}

void updateProgram(Contact **updatedContacts, int size) //updates the database using the array of contacts
{
    ofstream outFile;
    string fileName = "database.txt";
    outFile.open(fileName);

    for(int i = 0; i < size; i++)
    {
        outFile << (*(updatedContacts + i)) -> getFirstName() << "~";
        outFile << (*(updatedContacts + i)) -> getLastName() << "~";
        outFile << (*(updatedContacts + i)) -> getPhoneNumber() << "~";
        outFile << (*(updatedContacts + i)) -> getPhoneType() << endl;
    }

    outFile.close();
}



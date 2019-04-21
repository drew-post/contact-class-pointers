//Drew Pos
//A04842758
//CS2308
//Assignment 4


#include "Contact.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

Contact::Contact(string firstName, string lastName)
{
    this -> firstName = firstName;
    this -> lastName = lastName;
    phoneNumber = "Unknown";
    phoneType = UNKNOWN;
}

void Contact::setFirstName(string firstName)
{
    this -> firstName = firstName;
}

string Contact::getFirstName() const
{
    return (this -> firstName);
}

void Contact::setLastName(string lastName)
{
    this -> lastName = lastName;
}

string Contact::getLastName() const
{
    return (this -> lastName);
}

void Contact::setPhoneNumber(string phoneNumber)
{
    if(phoneNumber == "Unknown")
    {
        this -> phoneNumber = phoneNumber;

    }

    else
    {
        while(stoll(phoneNumber) < 999999999 || stoll(phoneNumber) > 10000000000 || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "   **ERROR: PLEASE ENTER A VALID PHONE NUMBER**" << endl;
            cout << endl;
            cout << "   - Enter contact phone number: ";
            cin >> phoneNumber;
            cout << endl;
        }

        this -> phoneNumber = phoneNumber;
    }




}

string Contact::getPhoneNumber() const
{
    return (this -> phoneNumber);
}

void Contact::setPhoneType(PhoneType phoneType)
{
    this -> phoneType = phoneType;
}

PhoneType Contact::getPhoneType() const
{
    return (this -> phoneType);
}

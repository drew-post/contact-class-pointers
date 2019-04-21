//Drew Post
//CS2308
//A04842758
//Assignment 4


#ifndef CONTACT_H
#define CONTACT_H


#include <string>
using namespace std;

enum PhoneType {
    CELL,
    HOME,
    WORK,
    UNKNOWN
};

class Contact {

private:
    string firstName;
    string lastName;
    string phoneNumber;
    PhoneType phoneType;

public:
    Contact(string firstName, string lastName);
    void setFirstName(string firstName);
    string getFirstName() const;
    void setLastName(string lastName);
    string getLastName() const;
    void setPhoneNumber(string phoneNumber);
    string getPhoneNumber() const;
    void setPhoneType(PhoneType phoneType);
    PhoneType getPhoneType() const;
};

#endif // CONTACT_H

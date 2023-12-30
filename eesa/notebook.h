#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <qstring.h>
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

// Universal Funcs
bool isValidEmail(const string &email);
bool isValidPhoneNumber(const string &number);


enum PhoneType
{
    Main = 1,
    Home,
    Work,
    Office,
    Fax
};

// QString phoneTypeToString(PhoneType type)
// {
//     switch (type)
//     {
//     case PhoneType::Main:
//         return "Main";
//     case PhoneType::Home:
//         return "Home";
//     case PhoneType::Work:
//         return "Work";
//     case PhoneType::Office:
//         return "Office";
//     case PhoneType::Fax:
//         return "Fax";
//     default:
//         return "Unknown";
//     }
// }

class user
{
private:
    string firstName;
    string lastName;
    string email;
    vector<pair<string, PhoneType>> numbers;

public:
    void setFname(string Fname);
    void setLname(string Lname);
    void setEmail(string Email);
    void setUser(string Fname, string Lname, string Email);
    void addNumber(const vector<pair<string, PhoneType>> &numbers)
    {
        this->numbers.insert(this->numbers.end(), numbers.begin(), numbers.end());
    }
    string getFirstName() const
    {
        return firstName;
    }

    string getLastName() const
    {
        return lastName;
    }

    string getEmail() const
    {
        return email;
    }
    const vector<pair<string, PhoneType>> &getNumbers() const
    {
        return numbers;
    }
};

class List
{
private:
    vector<user> notebook;

public:
    void addUser(user User);
    void removeUser(int index);
    List search(string entry);
    void sort();
    void deleteAll();
    const vector<user> $getNoteBook() const {
        return notebook;
    }
};

#endif // NOTEBOOK_H

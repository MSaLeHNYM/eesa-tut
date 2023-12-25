#ifndef NOTEBOOK_H
#define NOTEBOOK_H

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
    void addNumber(pair<string, PhoneType> number);
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
};

#endif // NOTEBOOK_H

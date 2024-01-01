#include "notebook.h"
#include <fstream>
#include<QDir.h>

// Universal Funcs
bool isValidEmail(const string &email)
{
    const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, pattern);
}
bool isValidPhoneNumber(const string &number)
{
    return !number.empty() && all_of(number.begin(), number.end(), ::isdigit);
}
bool isValidName(const string &name)
{
    return !name.empty() && all_of(name.begin(), name.end(), ::isalpha);
}
bool IsThisNotRepetitiveNumber(List NoteBook ,string number)
{
    vector<user> notebook=NoteBook.getnotebook();
    for (const user &u :notebook )
    {
        for (const auto &entry : u.getNumbers())
        {
            if (entry.first == number)
            {
                return false;
            }
        }
    }
    return true;
}
bool IsThisNotRepetitiveEmail(List NoteBook, string Email)
{
    vector<user> notebook=NoteBook.getnotebook();
    for ( const user &u :notebook )
    {
        if (Email == u.getEmail())
        {
            return false;
        }

    }
    return true;

}
string phoneTypeToString(PhoneType type)
{
    switch (type)
    {
    case PhoneType::Main:
        return "Main";
    case PhoneType::Home:
        return "Home";
    case PhoneType::Work:
        return "Work";
    case PhoneType::Office:
        return "Office";
    case PhoneType::Fax:
        return "Fax";
    default:
        return "Unknown";
    }
}
int stringToIntPhoneType(string type)
{
    if (type=="Main")
        return 1;
    else if(type=="Home")
        return 2;
    else if (type=="work")
        return 3;
    else if (type=="office")
        return 4;
    else if (type=="Fax")
        return 5;
    else
        return -1;
}


// bool saveAll(List NoteBook.)
// {//    file_obj.open("Input.txt", ios::app);

//     ofstream outFile;
//     outFile.open("db.txt",ios::out);
//     if (outFile.is_open())
//     {
//         for (const user &user : notebook)
//         {
//             outFile << user.getFirstName() << " " << user.getLastName() << " " << user.getEmail() << "\n";
//             for (const auto &entry : user.getNumbers())
//             {
//                 outFile << entry.first << " " << static_cast<int>(entry.second) << "\n";
//             }
//             outFile << "---\n";
//         }
//         outFile.close();
//         return true;
//         // cout << "All users saved to db.txt.\n";
//     }
//     else
//     {
//         return false;
//         // cout << "Error opening db.txt for writing.\n";
//     }
// }


// user stuff
void user::setFname(string Fname)
{
    firstName = Fname;
}

void user::setLname(string Lname)
{
    lastName = Lname;
}

void user::setEmail(string Email)
{
    email = Email;
}

void user::setUser(string Fname, string Lname, string Email)
{
    setFname(Fname);
    setLname(Lname);
    setEmail(Email);
}

void user::addNumber(pair<string, PhoneType> number)
{
    numbers.push_back(number);
}

// notebook stuff

void List::addUser(user User)
{
    notebook.push_back(User);
}

void List::removeUser(int index)
{
    notebook.erase(notebook.begin() + index);
}

List List::search(string entry)
{
    List res;
    for (size_t i = 0; i < notebook.size(); i++)
    {
        user User = notebook[i];
        if (User.getFirstName() == entry || User.getLastName() == entry)
        {
            res.addUser(User);
        }
        else if ( User.getEmail() == entry)
        {
            res.addUser(User);
            return res;
        }
        else
        {
            for (const auto &number : User.getNumbers())
            {
                if (number.first == entry)
                {
                    res.addUser(User);
                    return res;
                }
            }
        }
    }
    return res;
}

void List::sort()
{
    for (size_t i = 0; i < notebook.size() - 1; ++i)
    {
        for (size_t j = 0; j < notebook.size() - i - 1; ++j)
        {
            if (notebook[j].getFirstName() + notebook[j].getLastName() >
                notebook[j + 1].getFirstName() + notebook[j + 1].getLastName())
            {
                swap(notebook[j], notebook[j + 1]);
            }
        }
    }
}

void List::deleteAll()
{
    notebook.clear();
}









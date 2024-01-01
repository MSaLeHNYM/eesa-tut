#include "fileop.h"
#include"notebook.h"
#include<fstream>
#include<iostream>

bool saveAll(List NoteBook)
{
    ofstream outFile("./db.txt");
    if (outFile.is_open())
    {
        for (const user &user : NoteBook.getnotebook())
        {
            outFile << user.getFirstName() << " " << user.getLastName() << " " << user.getEmail() << "\n";
            for (const auto &entry : user.getNumbers())
            {
                outFile << entry.first << " " << static_cast<int>(entry.second) << "\n";
            }
            outFile << "---\n";
        }
        outFile.close();
        return true;
        // cout << "All users saved to db.txt.\n";
    }
    else
    {
        return false;
        // cout << "Error opening db.txt for writing.\n";
    }
}

List loadAll()
{
    ifstream inFile("./db.txt");
    if (inFile.is_open())
    {
        List NoteBook;
        while (!inFile.eof())
        {
            user user;
            string Fname,Lname,Email;
            inFile >> Fname >>Lname >>Email;
            user.setUser(Fname,Lname,Email);
            if (user.getFirstName().empty() && user.getLastName().empty() && user.getEmail().empty())
            {
                break;
            }

            string number;
            int category;
            while (true)
            {
                inFile >> number;
                if (number == "---")
                {
                    break;
                }
                inFile >> category;
                user.addNumber(make_pair(number, static_cast<PhoneType>(category)));
            }
            NoteBook.addUser(user);
        }

        inFile.close();
        return NoteBook;
        // cout << "Data loaded from db.txt.\n";
    }
    else
    {
        List fake;
        user fakeuser;
        fakeuser.setUser("null","null","null@n.com");
        fake.addUser(fakeuser);
        return fake;
        // cout << "No db.txt found or error opening db.txt for reading.\n";
    }
}

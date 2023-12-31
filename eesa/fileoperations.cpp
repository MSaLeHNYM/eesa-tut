#include "fileoperations.h"
#include "mainwindow.h"
#include <qdir.h>

void saveAll(List notebook)
{
    ofstream outFile((QDir::currentPath()+"/db.txt").toStdString());
    if (outFile.is_open())
    {
        for (const auto &user : notebook.$getNoteBook())
        {
            outFile << user.getFirstName() << " " << user.getLastName() << " " << user.getEmail() << "\n";
            for (const auto &entry : user.getNumbers())
            {
                outFile << entry.first << " " << static_cast<int>(entry.second) << "\n";
            }
            outFile << "---\n";
        }
        outFile.close();
        // cout << "All users saved to db.txt.\n";
    }
    else
    {
        // cout << "Error opening db.txt for writing.\n";
    }
}

List loadAll()
{
    List res;
    ifstream inFile((QDir::currentPath()+"/db.txt").toStdString());
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            user User;
            std::string ff, ll, ee;

            inFile >> ff >> ll >> ee;
            User.setFname(ff);
            User.setLname(ll);
            User.setEmail(ee);

            if (ff.empty() && ll.empty() && ee.empty())
            {
                break;
            }

            vector<pair<string, PhoneType>> numbers;

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
                numbers.push_back(make_pair(string(number), static_cast<PhoneType>(category)));
            }

            User.addNumber(numbers);
            res.addUser(User);
        }

        inFile.close();
        // cout << "Data loaded from db.txt.\n";
    }
    else
    {
        // cout << "No db.txt found or error opening db.txt for reading.\n";
    }
    return res;
}

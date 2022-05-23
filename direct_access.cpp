/*
Implementation of a direct access file- Insertion and deletion of a record from a direct access file.
*/

#include <bits/stdc++.h>
using namespace std;

class direct_access
{
    struct student
    {
        char name[20];
        int roll_no;
        int division;
        char address[50];
    };
    student records;
    int size = 10;

public:
    int hash(int key)
    {
        return key % size;
    }

    void create()
    {
        fstream dafile;
        // open file
        dafile.open("class.dat", ios::in | ios::out | ios::binary);
        for (int i = 0; i < size; i++)
        {
            strcpy(records.name, "");
            records.roll_no = -1;
            records.division = -1;
            strcpy(records.address, "");
            dafile.write((char *)&records, sizeof(records));
        }
        // close file
        dafile.close();
    }

    void display()
    {
        fstream dafile;
        dafile.open("student.dat", ios::in | ios::out | ios::binary);
        // positioning the file pointer in the beginning
        dafile.seekg(0, ios::beg);
        cout << "\nThe contents of the file are.....";
        // reading records sequentially
        while (dafile.read((char *)&records, sizeof(records)))
        {
            if (records.roll_no != -1)
            {
                cout << "\n Name: " << records.name;
                cout << "\n Roll Number: " << records.roll_no;
                cout << "\n Division: " << records.division;
                cout << "\n Address: " << records.address;
                cout << "\n";
            }
        }
        dafile.close();
    }

    void search()
    {
        int id;
        fstream dafile;
        cout << "\nEnter the roll number of the record to be searched for: ";
        cin >> id;
        dafile.open("class.dat", ios::in | ios::out | ios::binary);
        int offset = (hash(id)) * sizeof(records);
        dafile.seekg(offset);
        if (records.roll_no == id)
            cout << "\n Record is present!";
        else
            cout << "\n Record is absent!";
        dafile.close();
    }

    void delete_record()
    {
        int id;
        fstream dafile;
        cout << "\nEnter the roll number of the record to be deleted: ";
        cin >> id;
        dafile.open("class.dat", ios::in | ios::out | ios::binary);
        int offset = (hash(id)) * sizeof(records);
        dafile.seekp(offset);
        if (records.roll_no == id)
        {
            strcpy(records.name, "");
            records.roll_no = -1;
            records.division = -1;
            strcpy(records.address, "");
            dafile.write((char *)&records, sizeof(records)) << flush;
        }
        else
            cout << "\n Record is absent!";
        dafile.close();
    }

    void add_record()
    {
        fstream dafile;
        dafile.open("class.dat", ios::in | ios::out | ios::binary);
        char ch = 'y';
        do
        {
            cout << "\n Enter name: ";
            cin >> records.name;
            cout << "\n Enter roll number: ";
            cin >> records.roll_no;
            cout << "\n Enter division: ";
            cin >> records.division;
            cout << "\n Enter address: ";
            cin >> records.address;
            int offset = (hash(records.roll_no)) * sizeof(records);
            dafile.seekp(offset);
            dafile.write((char *)&records, sizeof(records)) << flush;
            cout << "\n Do you want to enter more records? ";
            cin >> ch;
        } while (ch == 'y');
        dafile.close();
    }

    void update()
    {
        int id;
        fstream dafile;
        cout << "\nEnter the roll number of the record to be updated: ";
        cin >> id;
        dafile.open("class.dat", ios::in | ios::out | ios::binary);
        int offset = (hash(id)) * sizeof(records);
        dafile.seekp(offset);
        if (records.roll_no == id)
        {
            cout << "\n Enter name: ";
            cin >> records.name;
            cout << "\n Enter roll number: ";
            cin >> records.roll_no;
            cout << "\n Enter division: ";
            cin >> records.division;
            cout << "\n Enter address: ";
            cin >> records.address;
            dafile.write((char *)&records, sizeof(records)) << flush;
        }
        else
            cout << "\n Record is absent!";
        dafile.close();
    }
};

int main()
{
    direct_access file;
    char ans = 'y';
    int choice, key;

    do
    {
        cout << "\n\t\t\tMain Menu";
        cout << "\n1. Create\n2. Display\n3. Delete\n4. Search\n5. Add\n6. Update\n7. Exit\n";
        cout << "\n Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            file.create();
            break;
        case 2:
            file.display();
            break;
        case 3:
            file.delete_record();
            break;
        case 4:
        {
            file.search();
        }
        break;
        case 5:
            file.add_record();
            break;
        case 6:
            file.update();
            break;
        case 7:
            exit(0);
        }
        cout << "\n Do you want to go back to Main Menu? ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
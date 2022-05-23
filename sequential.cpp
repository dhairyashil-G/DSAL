/*
Department maintains a student information. The file contains roll  number, name, division
and address. Allow user to add, delete information of student. Display information of particular
employee. If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use sequential file to main the data.
*/

#include <bits/stdc++.h>
using namespace std;

class sequential
{
    struct student
    {
        char name[20];
        int roll_no;
        int division;
        char address[50];
    };
    student records;

public:
    void create()
    {
        char ch = 'y';
        fstream seqfile;
        // open file
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
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
            // write to file
            seqfile.write((char *)&records, sizeof(records));
            cout << "\n Do you want to enter more records? ";
            cin >> ch;
        } while (ch == 'y');
        // close file
        seqfile.close();
    }

    void display()
    {
        fstream seqfile;
        int n;
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
        // positioning the file pointer in the beginning
        seqfile.seekg(0, ios::beg);
        cout << "\nThe contents of the file are.....";
        // reading records sequentially
        while (seqfile.read((char *)&records, sizeof(records)))
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
        seqfile.close();
    }

    int search()
    {
        fstream seqfile;
        int id, pos;
        cout << "\nEnter the roll number of the record to be searched for: ";
        cin >> id;
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
        seqfile.seekg(0, ios::beg);
        pos = -1;
        int i = 0;
        while (seqfile.read((char *)&records, sizeof(records)))
        {
            if (id == records.roll_no)
            {
                pos = i;
                break;
            }
            i++;
        }
        return pos;
    }

    void del()
    {
        int pos;
        cout << "\n For deletion";
        fstream seqfile;
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
        seqfile.seekg(0, ios::beg);
        pos = search();
        if (pos == -1)
        {
            cout << "\n The record is not present in the file";
            return;
        }
        // calculate offset to locate the desired record in the file
        int offset = pos * sizeof(records);
        seqfile.seekp(offset);
        strcpy(records.name, "");
        records.roll_no = -1;
        records.division = -1;
        strcpy(records.address, "");
        seqfile.write((char *)&records, sizeof(records)) << flush;
        seqfile.seekg(0);
        seqfile.close();
        cout << "\nThe record has been deleted successfully";
    }

    void append()
    {
        fstream seqfile;
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
        // reaching end of file
        seqfile.seekg(0, ios::end);
        // turning off EOF flag
        seqfile.clear();
        cout << "\n Enter the record for appending: ";
        cout << "\n Enter name: ";
        cin >> records.name;
        cout << "\n Enter roll number: ";
        cin >> records.roll_no;
        cout << "\n Enter division: ";
        cin >> records.division;
        cout << "\n Enter address: ";
        cin >> records.address;
        seqfile.write((char *)&records, sizeof(records));
        seqfile.seekg(0);
        seqfile.close();
        cout << "\n The record is appended";
    }

    void update()
    {
        int pos;
        cout << "\n For updation";
        fstream seqfile;
        seqfile.open("student.dat", ios::in | ios::out | ios::binary);
        seqfile.seekg(0, ios::beg);
        pos = search();
        if (pos == -1)
        {
            cout << "\n The record is not present in the file";
            return;
        }
        // calculate offset to locate the desired record in the file
        int offset = pos * sizeof(records);
        seqfile.seekp(offset);
        cout << "\n Enter values for updation.....";
        cout << "\n Enter name: ";
        cin >> records.name;
        cout << "\n Enter roll number: ";
        cin >> records.roll_no;
        cout << "\n Enter division: ";
        cin >> records.division;
        cout << "\n Enter address: ";
        cin >> records.address;
        seqfile.write((char *)&records, sizeof(records)) << flush;
        seqfile.seekg(0);
        seqfile.close();
        cout << "\n The record is updated";
    }
};

int main()
{
    sequential file;
    char ans = 'y';
    int choice, key;

    do
    {
        cout << "\n\t\t\tMain Menu";
        cout << "\n1. Create\n2. Display\n3. Delete\n4. Search\n5. Append\n6. Update\n7. Exit\n";
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
            file.del();
            break;
        case 4:
        {
            int key = file.search();
            if (key < 0)
                cout << "\n Record is not present in the file";
            else
                cout << "\n Record is present in the file";
        }
        break;
        case 5:
            file.append();
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
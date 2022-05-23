/*
Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two collision
handling techniques and compare them using number of comparisons required to find a set of
telephone numbers
*/

#include <bits/stdc++.h>
using namespace std;
#define max 10

struct client
{
    long int num;
};

class hashtable
{
    client ht[max];

public:
    int method = 0;
    hashtable()
    {
        for (int i = 0; i < max; i++)
        {
            ht[i].num = 0;
        }
    }
    void insert();
    void display();
    int search(long int);
    void del();
    int hash(long int);
    int linearProbing(long int);
    int quadraticProbing(long int);
};

void hashtable::insert()
{
    int pos;
    char ans;
    do
    {
        client c;
        cout << "\n Enter Phone Number:";
        cin >> c.num;

        if (search(c.num) == 1)
        {
            cout << "\n Phone Number already present!";
        }
        else
        {
            pos = hash(c.num);

            if (ht[pos].num == 0)
            {
                ht[pos] = c;
            }
            else
            {
                if (method == 1)
                {
                    int new_pos = linearProbing(pos);
                    if (new_pos == -1)
                        cout << "\nHash Table full!";
                    else
                        ht[new_pos] = c;
                }
                else
                {
                    int new_pos = quadraticProbing(pos);
                    if (new_pos == -1)
                        cout << "\nHash Table full!";
                    else
                        ht[new_pos] = c;
                }
            }
        }
        cout << "\n Add More:";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

int hashtable::hash(long int key)
{
    return (key % max);
}

void hashtable::display()
{
    cout << "------------------------------------";
    cout << "\nSrno\tPhone number\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < max; i++)
    {
        cout << i << "\t" << ht[i].num << endl;
    }
    cout << "------------------------------------\n";
}

int hashtable::search(long int x)
{
    int pos = hash(x);
    if (method == 1)
    {
        if (ht[pos].num == x)
            return 1;
        for (int i = pos + 1; i < max; i++)
        {
            if (ht[i].num == x)
                return 1;
        }
        for (int i = 0; i < pos; i++)
        {
            if (ht[i].num == x)
                return 1;
        }
    }
    else
    {
        for (int i = 0; i < max; i++)
        {
            int new_pos = (pos + (i * i)) % max;
            if (ht[new_pos].num == x)
                return 1;
        }
    }
    return -1;
}

void hashtable::del()
{
    int x;
    cout << "\n Enter phone number to be deleted:";
    cin >> x;
    int found = search(x);
    if (found == 1)
    {
        int pos = hash(x);
        if (method == 1)
        {
            if (ht[pos].num == x)
                ht[pos].num = 0;
            for (int i = pos + 1; i < max; i++)
            {
                if (ht[i].num == x)
                    ht[pos].num = 0;
            }
            for (int i = 0; i < pos; i++)
            {
                if (ht[i].num == x)
                    ht[pos].num = 0;
            }
        }
        else
        {
            for (int i = 0; i < max; i++)
            {
                int new_pos = (pos + (i * i)) % max;
                if (ht[new_pos].num == x)
                    ht[pos].num = 0;
            }
        }
        cout << "\n Phone number found and deleted";
    }
    else
        cout << "\n Phone number not found";
}

int hashtable::linearProbing(long int num)
{
    int pos = hash(num);
    for (int i = pos + 1; i < max; i++)
    {
        if (ht[i].num == 0)
            return i;
    }
    for (int i = 0; i < pos; i++)
    {
        if (ht[i].num == 0)
            return i;
    }
    return -1;
}

int hashtable::quadraticProbing(long int num)
{
    int pos = hash(num);
    for (int i = 0; i < max; i++)
    {
        int new_pos = (pos + (i * i)) % max;
        if (ht[new_pos].num == 0)
            return new_pos;
    }
    return -1;
}

int main()
{
    int ch;
    int m;
    hashtable h;
    cout << "\nWhich method do you want to use\n1. Linear Probing\n2. Quadratic Probing\n";
    cin >> m;
    h.method = m;
    do
    {
        cout << "\n---------------LIST---------------\n";
        cout << "\n1.INSERT\n2.DISPLAY\n3.SEARCH\n4.DELETE\n5.EXIT\n\n";
        cout << "Enter your choice:";
        cin >> ch;
        cout << "\n";

        switch (ch)
        {
        case 1:
            h.insert();
            cout << "\n";
            break;

        case 2:
            h.display();
            cout << "\n";
            break;

        case 3:
            int x1;
            int r1;
            cout << "\n Enter phone number to be searched:";
            cin >> x1;
            r1 = h.search(x1);
            if (r1 == 1)
                cout << "\n Phone number found";
            else
                cout << "\n Phone number not found";
            cout << "\n";
            break;

        case 4:
            h.del();
            cout << "\n";
            break;

        case 5:
            break;
        }
    } while (ch != 5);
    return 0;
}
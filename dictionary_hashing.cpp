/*
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using
chaining with / without replacement. Data: Set of (key, value) pairs, Keys are mapped to values,
Keys must be comparable, Keys must be unique. Standard Operations: Insert(key, value),
Find(key), Delete(key)
*/

#include <bits/stdc++.h>
using namespace std;
#define size 10

struct dict{
    string key, value;
};
class dictionary{
private:
    dict ht[size];
    int chain[size];int method = 0;
public:
    dictionary(){
        for (int i = 0; i < size; i++){
            ht[i].key = "-";
            chain[i] = -1;
        }
    }
    void setmethod(int m){
        method=m;
    }
    void insert();
    void display();
    int search(string);
    void del();
    int hash(string);
    void chaining_with_replacement(dict);
    void chaining_without_replacement(dict);
};

int dictionary::hash(string s){
    return s.length() % size;
}

void dictionary::insert(){
    int pos;
    char ans;
    do{
        dict d;
        cout << "\n Enter Word: ";
        getline(cin >> ws, d.key);
        if (search(d.key) == 1){
            cout << "\n Word already present!";
        }
        else
        {
            cout << "\n Enter its meaning: ";
            getline(cin >> ws, d.value);
            pos = hash(d.key);
            if (ht[pos].key == "-"){
                ht[pos] = d;
            }
            else{
                if (method == 1){
                    chaining_without_replacement(d);
                }
                else{
                    chaining_with_replacement(d);
                }
            }
        }
        cout << "\n Add More(Enter y/Y to continue or n to not):";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

void dictionary::display(){
    cout << "------------------------------------";
    cout << "\nKey\tValue\tChain\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < size; i++){
        cout << ht[i].key << "\t" << ht[i].value << "\t" << chain[i] << endl;
    }
    cout << "------------------------------------\n";
}

void dictionary::chaining_without_replacement(dict x){
    int pos = hash(x.key);
    if (ht[pos].key == "-"){
        ht[pos] = x;
    }
    else{
        for (int i = 1; i < size; i++){
            int new_pos = (pos + i) % size;
            if (ht[new_pos].key == "-"){
                if (chain[pos] == -1)
                    chain[pos] = new_pos;
                else{
                    int curr = pos;
                    while (chain[curr] != -1)
                        curr = chain[curr];
                    chain[curr] = new_pos;
                }
                ht[new_pos] = x;
                return;
            }
        }
    }
}

void dictionary::chaining_with_replacement(dict x){
    int pos = hash(x.key);
    for (int i = 0; i < size; i++){
        int new_pos = (pos + i) % size;
        // replacement
        if (ht[new_pos].key != "-"){
            if (hash(ht[new_pos].key) != hash(x.key)){
                dict z = ht[new_pos];
                chaining_with_replacement(z); //this can be done even before the return
                chain[new_pos] = -1;
                ht[new_pos] = x;
                return;
            }
        }
        // wo replacement
        if (ht[new_pos].key == "-"){
            if (chain[pos] == -1)
                chain[pos] = new_pos;
            else{
                int curr = pos;
                while (chain[curr] != -1)
                    curr = chain[curr];
                chain[curr] = new_pos;
            }
            ht[new_pos] = x;
            return;
        }
    }
}

int dictionary::search(string x){
    int pos = hash(x);
    if (ht[pos].key == x)
        return 1;
    else{
        int curr = pos;
        while (chain[curr] != -1){
            curr = chain[curr];
            if (ht[curr].key == x)
                return 1;
        }
    }
    return -1;
}

void dictionary::del()
{
    dict d;
    cout << "\n Enter Word: ";
    getline(cin >> ws, d.key);
    if (search(d.key) == -1)
    {
        cout << "\n Word not present!";
    }
    else
    {
        int pos = hash(d.key);
        if (ht[pos].key == d.key)
        {
            ht[pos].key = "-";
            ht[pos].value = "";
            chain[pos] = -1;
        }
        else
        {
            int prev;
            int curr = pos;
            while (chain[curr] != -1)
            {
                prev = curr;
                curr = chain[curr];
                if (ht[curr].key == d.key)
                {
                    ht[curr].key = "-";
                    ht[curr].value = "";
                    chain[prev] = chain[curr];
                    chain[curr] = -1;
                    return;
                }
            }
        }
    }
}

int main()
{
    int ch;
    int m;
    dictionary h;
    cout << "\nWhich method do you want to use\n1. Chaining without replacement\n2. Chaining with replacement\n";
    cin >> m;
    h.setmethod(m);
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
        {
            string s;
            cout << "\n Enter Word to be searched: ";
            getline(cin >> ws, s);
            int found = h.search(s);
            if (found == 1)
                cout << "\n Word found";
            else
                cout << "\n Word not found";
            cout << "\n";
        }
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

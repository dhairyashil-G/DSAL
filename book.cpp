/*
A book consists of chapters, chapters consist of sections and sections consist of
subsections. Construct a tree and print the nodes. Find the time and space requirements
of your method.

time complexity - O(no_chapters*max(no_sections)*max(no_subsections))
nested for loops
space complexity - O(1)
no auxilary space needed
*/

#include <iostream>
using namespace std;

class node
{
    string label;
    int ch_count;
    node *child[10];
    friend class GenericTree;
};

class GenericTree
{
public:
    node *root;
    int nchapts, nsects, nsubsects;
    GenericTree()
    {
        root = NULL;
    }

    void create()
    {

        root = new node;
        cout << "Enter name of book: ";
        cin >> root->label;
        cout << "Enter number of chapters in book: ";
        cin >> nchapts;
        root->ch_count = nchapts;

        for (int i = 0; i < nchapts; i++)
        {
            root->child[i] = new node;

            cout << "Enter chapter name: ";
            cin >> root->child[i]->label;
            cout << "Enter number of sections in chapter '" << root->child[i]->label << "' ";
            cin >> root->child[i]->ch_count;
            nsects = root->child[i]->ch_count;

            for (int j = 0; j < nsects; j++)
            {
                root->child[i]->child[j] = new node;
                cout << "Enter name of section " << j + 1 << ": ";
                cin >> root->child[i]->child[j]->label;
                cout << "Enter number of subsections in " << root->child[i]->child[j]->label << ": ";
                cin >> root->child[i]->child[j]->ch_count;
                nsubsects = root->child[i]->child[j]->ch_count;

                for (int k = 0; k < nsubsects; k++)
                {
                    root->child[i]->child[j]->child[k] = new node;
                    cout << "Enter name of subsection " << k + 1 << ": ";
                    cin >> root->child[i]->child[j]->child[k]->label;
                }
            }
        }
    }

    void display()
    {
        if (root != NULL)
        {
            cout << endl
                 << endl;
            cout << "Book Heirarchy:-" << endl
                 << endl;
            cout << "Book Title: " << root->label << endl
                 << endl;
            root->ch_count = nchapts;
            for (int i = 0; i < nchapts; i++)
            {

                cout << "Chapter name: ";
                cout << root->child[i]->label << endl;
                cout << "Number of sections in chapter '" << root->child[i]->label << "': ";
                cout << root->child[i]->ch_count << endl
                     << endl;
                nsects = root->child[i]->ch_count;

                for (int j = 0; j < nsects; j++)
                {
                    cout << "Name of section " << j + 1 << ": ";
                    cout << root->child[i]->child[j]->label << endl
                         << endl;
                    cout << "Number of subsections in " << root->child[i]->child[j]->label << ": ";
                    cout << root->child[i]->child[j]->ch_count << endl;
                    nsubsects = root->child[i]->child[j]->ch_count;

                    for (int k = 0; k < nsubsects; k++)
                    {
                        cout << "Name of subsection " << k + 1 << ": ";
                        cout << root->child[i]->child[j]->child[k]->label << endl
                             << endl;
                    }
                }
            }
            cout << endl;
        }
    }
};

int main()
{

    GenericTree tree;
    tree.create();
    tree.display();

    return 0;
}
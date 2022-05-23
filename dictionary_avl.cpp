/*
A  Dictionary stores keywords and its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data sorted
in ascending / descending order. Also find how many maximum comparisons may require for finding
any keyword. Use Height balance tree and find the complexity for finding a keyword.
*/

#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    string key, value;
    node *left, *right;
    int height;
};

node *new_node(string k, string val)
{
    node *n = new node();
    n->key = k;
    n->value = val;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return (n);
}

int height(node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int get_balance_factor(node *n)
{
    if (n == NULL)
        return 0;
    return (height(n->left) - height(n->right));
}

node *right_rotate(node *pivot)
{
    node *x = pivot->left;
    node *t = x->right;

    x->right = pivot;
    pivot->left = t;

    pivot->height = max(height(pivot->left), height(pivot->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *left_rotate(node *pivot)
{
    node *x = pivot->right;
    node *t = x->left;

    x->left = pivot;
    pivot->right = t;

    pivot->height = max(height(pivot->left), height(pivot->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *insert_node(node *root, string k, string val)
{
    if (root == NULL)
        return new_node(k, val);
    if (k < root->key)
        root->left = insert_node(root->left, k, val);
    else if (k > root->key)
        root->right = insert_node(root->right, k, val);

    root->height = 1 + max(height(root->left), height(root->right));

    int balance_factor = get_balance_factor(root);

    // ll
    if (balance_factor > 1 && k < root->left->key)
        return (right_rotate(root));
    // rr
    if (balance_factor < -1 && k > root->right->key)
        return (left_rotate(root));
    // lr
    if (balance_factor > 1 && k > root->left->key)
    {
        root->left = left_rotate(root->left);
        return (right_rotate(root));
    }
    // rl
    if (balance_factor < -1 && k < root->right->key)
    {
        root->right = right_rotate(root->right);
        return (left_rotate(root));
    }
    return root;
}

node *min_value(node *n)
{
    node *current = n;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node *delete_node(node *root, string k)
{
    if (root == NULL)
        return NULL;
    if (k < root->key)
        root->left = delete_node(root->left, k);
    else if (k > root->key)
        root->right = delete_node(root->right, k);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                root = temp;
            free(temp);
        }
        else
        {
            node *temp = min_value(root->right);
            root = temp;
            root->right = delete_node(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance_factor = get_balance_factor(root);

    // ll
    if (balance_factor > 1 && get_balance_factor(root->left) >= 0)
        return (right_rotate(root));
    // rr
    if (balance_factor < -1 && get_balance_factor(root->right) <= 0)
        return (left_rotate(root));
    // lr
    if (balance_factor > 1 && get_balance_factor(root->left) > 0)
    {
        root->left = left_rotate(root->left);
        return (right_rotate(root));
    }
    // rl
    if (balance_factor < -1 && get_balance_factor(root->left) > 0)
    {
        root->right = right_rotate(root->right);
        return (left_rotate(root));
    }
    return root;
}

void get_value(node *root, string k)
{
    if (root->key == k)
        cout << "Value of " << k << " is: " << root->value << endl;
    if (k < root->key)
        get_value(root->left, k);
    else if (k > root->key)
        get_value(root->right, k);
}

node *update_value(node *root, string k, string val)
{
    if (root->key == k)
    {
        root->value = val;
        return root;
    }
    if (k < root->key)
        update_value(root->left, k, val);
    else if (k > root->key)
        update_value(root->right, k, val);
    return root;
}

void inorder(node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << "Word: " << root->key << " Meaning: " << root->value << " Number of comparisons needed: "
         << "(" << root->height << ")" << endl;
    inorder(root->right);
}

int main()
{
    node *root = NULL;
    root = insert_node(root, "a", "means a");
    root = insert_node(root, "d", "means d");
    root = insert_node(root, "c", "means c");
    root = insert_node(root, "b", "means b");
    root = insert_node(root, "f", "means f");

    cout << "Time complexity is: " << height(root) << endl;

    get_value(root, "a");
    root = update_value(root, "a", "means AAA");

    inorder(root);

    root = delete_node(root, "f");
    inorder(root);

    return 0;
}
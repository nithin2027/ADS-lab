#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node *right;
    Node *left;
    int height;
    int size;
    int median;
    Node(int val)
    {
        this->val = val;
        right = NULL;
        left = NULL;
        height = 1;
        size = 1;
        median = val;
    }
};

int totalSize = 0;

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int getHeight(Node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}
int getSize(Node *root)
{
    if (root == NULL)
        return 0;

    return root->size;
}

Node *rightRotation(Node *y)
{
    // Node* x=root;
    Node *x = y->left;
    Node *t2 = x->right;

    // x->left=y->right;
    x->right = y;
    y->left = t2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);

    return x;
}
Node *leftRotation(Node *x)
{
    // Node* x=root;
    Node *y = x->right;
    x->right = y->left;

    y->left = x;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    x->size = 1 + getSize(x->left) + getSize(x->right);
    y->size = 1 + getSize(y->left) + getSize(y->right);
    return y;
}
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}
Node *insert(Node *root, int val)
{
    if (root == NULL)
    {
        Node *newNode = new Node(val);
        return newNode;
    }

    if (root->val > val)
    {
        root->left = insert(root->left, val);
    }
    else if (root->val < val)
    {
        root->right = insert(root->right, val);
        // cnt = cnt + 1 + getSize(root->left);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->size = 1 + getSize(root->left) + getSize(root->right);

    int balance = getBalance(root);

    if (balance > 1 && root->left->val > val)
    {
        cout << "LL" << endl;
        return rightRotation(root);
    }
    if (balance > 1 && root->left->val < val)
    {
        cout << "LR" << endl;
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    if (balance < -1 && root->right->val < val)
    {
        cout << "RR" << endl;
        return leftRotation(root);
    }
    if (balance < -1 && root->right->val > val)
    {
        cout << "RL" << endl;
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

void preorder(Node *root)
{
    if (root == NULL)
        return;

    cout << endl;
    preorder(root->left);
    preorder(root->right);
}

// void smallElements(int count[])
// {
//     cout << endl;
//     for (int i = 0; i < 7; i++)
//     {
//         cout << count[7 - i - 1] << " ";
//     }
// }
int preorderSUCC(Node *root)
{
    if (root == NULL)
        return 0;
    while (root->right != NULL)
        root = root->right;
    return root->val;
}
int inorder(Node *root)
{
    if (root == NULL)
        return 0;
    while (root->left != NULL)
        root = root->left;
    return root->val;
}
int main()
{
    Node *root = NULL;
    // int count[7] = {0};

    int arr[] = {5, 15, 1, 3};

    for (int i = 0; i < 4; i++)
    {
        root = insert(root, arr[i]);
        totalSize++;
        if (totalSize % 2 == 0)
        {
            if (root->val > arr[i])
            {
                root->median = (root->val + preorderSUCC(root->left)) / 2;
            }
            else
            {
                root->median = (root->val + inorder(root->right)) / 2;
            }
        }
        else
        {
            root->median = root->val;
        }

        cout << "Median is:" << root->median << endl;
    }

    // root = insert(root, 2, count[4]);
    // root = insert(root, 1, count[5]);
    // root = insert(root, 12, count[6]);

    preorder(root);
    // smallElements(count);
    return 0;
}

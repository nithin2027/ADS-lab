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
    Node(int val)
    {
        this->val = val;
        right = NULL;
        left = NULL;
        height = 1;
        size = 1;
    }
};

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
Node *insert(Node *root, int val, int &cnt)
{
    if (root == NULL)
    {
        Node *newNode = new Node(val);
        return newNode;
    }

    if (root->val > val)
    {
        root->left = insert(root->left, val, cnt);
    }
    else if (root->val < val)
    {
        root->right = insert(root->right, val, cnt);
        cnt = cnt + 1 + getSize(root->left);
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

    if (root->left != NULL)
    {
        cout << root->val << "->"
             << "Smaller elements are:" << root->left->size;
    }
    else
    {
        cout << root->val << "->"
             << "Smaller elements are:" << 0;
    }
    cout << endl;
    preorder(root->left);
    preorder(root->right);
}

void smallElements(int count[])
{
    cout << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << count[7 - i - 1] << " ";
    }
}

int main()
{
    Node *root = NULL;
    int count[7] = {0};
    root = insert(root, 4, count[0]);
    root = insert(root, 11, count[1]);
    root = insert(root, 0, count[2]);
    root = insert(root, 3, count[3]);
    root = insert(root, 2, count[4]);
    root = insert(root, 1, count[5]);
    root = insert(root, 12, count[6]);

    preorder(root);
    smallElements(count);
    return 0;
}

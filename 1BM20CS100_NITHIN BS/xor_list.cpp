#include <iostream>

using namespace std;

class node
{
public:
    int data;
    node *npx;
    node(int val)
    {
        data = val;
        npx = NULL;
    }
};
node *head = NULL;

node *XOR(node *x, node *y)
{
    return (node *)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void insert(int val)
{
    node *newNode = new node(val);
    newNode->npx = head;

    if (head != NULL)
    {
        head->npx = XOR(newNode, head->npx);
    }
    head = newNode;
}

void insert_after_given_node(int k, int val)
{
    // insert after node k
    node *prev = NULL;
    node *next;

    node *curr = head;

    while (curr != NULL)
    {
        // cout<<curr->data<<"->";
        if (curr->data == k)
        {
            next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
            node *newNode = new node(val);
            newNode->npx = XOR(curr, prev);
            prev->npx = XOR(newNode, XOR(prev->npx, curr));
            if (curr != NULL)
            {
                curr->npx = XOR(newNode, XOR(curr->npx, prev));
            }

            break;
        }
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
}

void remove()
{
    node *ptr = head;
    head = XOR(NULL, head->npx);
    head->npx = XOR(NULL, XOR(ptr, head->npx));
    free(ptr);
}

void displayList()
{
    node *prev = NULL;

    node *curr = head;
    node* next;
    while (curr != NULL)
    {
        cout << curr->data << "->";
        next = XOR(curr->npx,prev);
        prev = curr;
        curr = next;
    }
    cout << "\n";
}

int main()
{
    int ch = 1;
    int val, key;
    cout << "press 1 to insert begging\n2.to insert after key\n3.to display\n 4.delete\n5.exit\n";
    while (ch != 5)
    {
        cout << "Enter the choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nenter to insert at beggining:";
            cin >> val;
            insert(val);
            break;
        case 2:
            cout << "enter the value:";
            cin >> val;
            cout << "enter key to insert the given value:";
            cin >> key;
            insert_after_given_node(key, val);
            break;
        case 3:
            displayList();
            break;
        case 4:
            remove();
            break;
        case 5:
            exit(1);
        }
    }

    return 0;
}

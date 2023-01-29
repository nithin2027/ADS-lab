#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;

    Node **forward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;

    forward = new Node *[level + 1];

    memset(forward, 0, sizeof(Node *) * (level + 1));
};

class SkipList
{

    int MAXLVL;

    float P;

    int level;

    Node *header;

public:
    SkipList(int, float);
    int randomLevel();
    Node *createNode(int, int);
    void insertElement(int);
    void deleteElement(int);
    void searchElement(int);
    void displayList();
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;

    header = new Node(-1, MAXLVL);
};

int SkipList::randomLevel()
{
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

Node *SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

void SkipList::insertElement(int key)
{
    Node *current = header;

    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node *) * (MAXLVL + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
               current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->key != key)
    {

        int rlevel = randomLevel();

        if (rlevel > level)
        {
            for (int i = level + 1; i < rlevel + 1; i++)
                update[i] = header;

            level = rlevel;
        }

        Node *n = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        cout << "Successfully Inserted key " << key << "\n";
    }
};

void SkipList::deleteElement(int key)
{
    Node *current = header;

    Node *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node *) * (MAXLVL + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
               current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL and current->key == key)
    {

        for (int i = 0; i <= level; i++)
        {

            if (update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        while (level > 0 &&
               header->forward[level] == 0)
            level--;
        cout << "Successfully deleted key " << key << "\n";
    }
};

void SkipList::searchElement(int key)
{
    Node *current = header;

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
    }

    current = current->forward[0];

    if (current and current->key == key)
        cout << "Found key: " << key << "\n";
};

void SkipList::displayList()
{
    cout << "\n*****Skip List*****"
         << "\n";
    for (int i = 0; i <= level; i++)
    {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};

int main()
{
    SkipList lst(3, 0.5);

    srand((unsigned)time(0));
    int choice, n;
    while (1)
    {
        cout << "1.Insert Element" << endl;
        cout << "2.Delete Element" << endl;
        cout << "3.Search Element" << endl;
        cout << "4.Display List " << endl;
        cout << "5.Exit " << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the element to be inserted: ";
            cin >> n;
            lst.insertElement(n);
            break;
        case 2:
            cout << "Enter the element to be deleted: ";
            cin >> n;
            lst.deleteElement(n);
            break;
        case 3:
            cout << "Enter the element to be searched: ";
            cin >> n;
            lst.searchElement(n);
        case 4:
            cout << "The List is: ";
            lst.displayList();

            break;
        case 5:
            exit(1);
            break;
        default:
            cout << "Wrong Choice" << endl;
        }
    }
    return 0;
}
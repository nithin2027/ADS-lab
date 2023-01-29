#include <bits/stdc++.h>

using namespace std;

class node
{
public:
    int key;
    node **forward;


    node(int key, int maxlvl)
    {
        this->key = key;
        forward = new node *[maxlvl + 1];

        memset(forward, 0, sizeof(node *) * (maxlvl + 1));
    }
};

class SkipList
{
    int level;
    int maxlvl;
    float P;
    node *head;

public:
    SkipList(int l, float p)
    {
        maxlvl = l;
        P = p;

        level = 0;
        head = new node(-999, maxlvl);
    }

    int randomLevel(float P)
    {
        int lvl = 0;
        float r = (float)rand() / RAND_MAX;
        while (r < P && lvl < maxlvl)
        {
            lvl++;
            r = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    void InsertElement(int val)
    {
        node *curr = head;

        node *update[maxlvl + 1];
        memset(update, 0, sizeof(node *) * (maxlvl + 1));

        for (int i = level; i >= 0; i--)
        {
            while (curr->forward[i] != NULL && curr->forward[i]->key < val)
                curr = curr->forward[i];
            update[i] = curr;
        }

        curr = curr->forward[0];

        if (curr == NULL || curr->key != val)
        {
            int rlevel = randomLevel(P);
            node *newNode = new node(val, rlevel);

            if (rlevel > level)
            {
                for (int i = level + 1; i <= rlevel; i++)
                {
                    update[i] = head;
                }
            }
            level = rlevel;

            for (int i = 0; i <= level; i++)
            {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }

            cout << "SuccessFully Created:" << val << endl;
        }
    }

    void display()
    {
        cout << level << " " << maxlvl << endl;
        for (int i = 0; i <= level; i++)
        {
            node *temp = head->forward[i];
            while (temp != NULL)
            {
                cout << temp->key << " ";
                temp = temp->forward[i];
            }
            cout << endl;
        }
    }

    bool search(int ele)
    {
        node *temp = head;
        for (int i = level; i >= 0; i--)
        {

            while (temp != NULL && temp->forward[i]->key < ele)
            {
                temp = temp->forward[i];
            }
            if (temp->forward[i]->key == ele)
                return true;
        }
        return false;
    }

    void rem(int val)
    {
        node *update[maxlvl + 1];
        memset(update, 0, sizeof(node *) * (maxlvl + 1));
        node *curr = head;
        for (int i = level; i >= 0; i--)
        {

            while (curr != NULL && curr->forward[i]->key < val)
            {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }

        curr = curr->forward[0];

        if (curr != NULL && curr->key == val)
        {
            for (int i = 0; i <= level; i++)
            {
                if (update[i]->forward[i] != curr)
                    break;
                update[i]->forward[i] = curr->forward[i];
            }

            delete (curr);

            while (level > 0 && head->forward[level] == 0)
            {
                level--;
            }
            cout << "Deleted Successfully" << endl;
        }
    }
};

int main()
{
    SkipList s(3, 0.5);

    s.InsertElement(3);
    s.InsertElement(1);
    s.InsertElement(5);
    s.InsertElement(7);
    s.InsertElement(17);
    s.InsertElement(72);
    s.InsertElement(23);
    s.InsertElement(34);
    s.InsertElement(8543);
    s.InsertElement(128);
    s.InsertElement(83);
    s.InsertElement(123);
  /*  if (s.search(98))
        cout << "Yes";
    else
        cout << "No";*/
    s.display();

    s.rem(17);
    s.rem(123);
    s.rem(128);
    s.display();
    return 0;
}

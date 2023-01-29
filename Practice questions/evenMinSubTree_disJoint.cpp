#include <bits/stdc++.h>
using namespace std;

class disJoint
{

public:
    vector<int> parent;
    vector<int> size;
    disJoint(int n)
    {
        parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    void join(int x, int y)
    {
        int upx = find(x);
        int upy = find(y);

        if (upx == upy)
            return;
        else
        {
            if (size[upx] > size[upy])
            {
                parent[upy] = upx;
                size[upx] += size[upy];
                // size[upy] = 0;
            }
            else
            {
                parent[upx] = upy;
                size[upy] += size[upx];
                // size[upx] = 0;
            }
        }
    }
};

int main()
{
    int W[] = {1, 2, 6, 4, 2, 0, 3};

    // Number of nodes in a tree
    int n = 7;

    // Initializing every node as
    // a tree with single node.
    disJoint *ds = new disJoint(n);

    int arr[6][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {4, 6}, {6, 7}};

    for (int i = 0; i < 6; i++)
    {
        if (W[--arr[i][0]] % 2 == 0 && W[--arr[i][1]] % 2 == 0)
        {
            ds->join(arr[i][0], arr[i][1]);
        }
    }
    int ans = INT_MIN;
    for (int i = 0; i < 7; i++)
    {
        cout << ds->size[i] << " ";
        if (W[i] % 2 == 0)
            ans = max(ans, ds->size[i]);
    }
    // Find maximum size of DSU tree.
    // int maxi = findMax(n, W);

    // printf("Maximum size of the subtree with ");
    // printf("even weighted nodes = %d\n", maxi);
    // cout << ans;
    return 0;
}

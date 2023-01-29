#include<bits/stdc++.h>
using namespace std;
class Island {
	int p[100];
	public:
		int count;
		Island(int n)
		{
			for(int i = 0; i < n; i++)
				p[i] = i;
			count = 0;
		}
		int findparent(int x)
		{
			if(p[x] == x)
				return x;
			else
				return p[x] = findparent(p[x]);
		}
		void makeunion(int x, int y) {
			int rootx = findparent(x);
			int rooty = findparent(y);
			if(rootx != rooty)
			{
				p[rootx] = rooty;
				count--;
			}
		}
		void setcount(int n) {
			count = n;
		}
		int setcount() {
			return count;
		}
};
int numislands(vector<vector<int> >mat) {
	int count = 0;
	int m = mat.size();
	int n = mat[0].size();
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			if(mat[i][j] != 0)
				count++;
		}
	}
	Island is(m*n);
	is.setcount(count);
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			if(mat[i][j] != 0) {
				if(i > 0 && mat[i-1][j] != 0)
					is.makeunion(n*(i+j), n*(i-1)+j);
				if(i < m-1 && mat[i+1][j] != 0)
					is.makeunion(n*i+j, n*(i+1)+j);
				if(j > 0 && mat[i][j-1] != 0)
					is.makeunion(n*i+j, n*i+j-1);
				if(j < n-1 && mat[i][j+1] != 0)
					is.makeunion(n*i+j, n*i+j+1);
				if(i > 0 && j > 0 && mat[i-1][j-1] != 0)
					is.makeunion(n*i+j, n*(i-1)+j-1);
				if(i < m-1 && j < n-1 && mat[i+1][j+1] != 0)
					is.makeunion(n*i+j, n*(i+1)+j+1);
				if(i > 0 && j < n-1 && mat[i-1][j+1] != 0)
					is.makeunion(n*i+j, n*(i-1)+j+1);
				if(i < m-1 && j > 0 && mat[i+1][j-1] != 0)
					is.makeunion(n*i+j, n*(i+1)+j-1);
			}
		}
	}
	return is.count;
}
int main() {
	int k,m,n,res;
	vector<vector<int> >mat;
	cout<<"Enter the number of rows and columns\n";
	cin>>m>>n;
	cout<<"Enter 0 or 1 for each position in the matrix\n";
	for(int i = 0; i < m; i++) {
		vector<int>m1;
		for(int j = 0; j < n; j++) {
			cin>>k;
			m1.push_back(k);
		}
		mat.push_back(m1);
	}
	res = numislands(mat);
	cout<<"\nThe number of islands in the entered matrix = "<<res<<endl;
	return 0;
}

/*
Enter the number of rows and columns
4 3
Enter 0 or 1 for each position in the matrix
1 0 0
0 0 1
1 1 0
0 0 0

The number of islands in the entered matrix = 2
*/
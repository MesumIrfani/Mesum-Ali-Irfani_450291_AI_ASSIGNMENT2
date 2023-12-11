#include <iostream>
#include <vector>
#include <iterator> 
#include <map> 
#include <string>
#include <bits/stdc++.h>
#include <functional>
#include <utility>
#include <queue>
#include <fstream>

using namespace std;

map<vector<vector<int> > , bool> visited;
map<vector<vector<int> > , vector<vector<int> > > parent;
vector<vector<int> > goal(3,vector<int> (3)); 

bool visit(vector<vector<int> > a)
{
    if(visited[a] == true)
        return true;
    
    return false;
}

int misplacedTiles(vector<vector<int>> a)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] != goal[i][j] )
            {
                count++;
            }
        }
    }
    return count;
}

bool isGoal(vector<vector<int> > a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}

bool safe(int i, int j)
{
    if (i >= 0 && i <= 2 && j >= 0 && j <= 2)
        return true;
    
    return false;
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

vector<vector<vector<int> > > neighbours(vector<vector<int> > a)
{
    pair<int, int> pos;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == 0)
            {
                pos.first = i;
                pos.second = j;
                break;
            }
        }
    }

    vector<vector<vector<int> > > ans;
    for (int k = 0; k < 4; k++)
    {
        int cx = pos.first;
        int cy = pos.second;
        vector<vector<int> > n = a;
        if (safe(cx + dx[k], cy + dy[k]))
        {
            swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
            ans.push_back(n);
        }
    }

    return ans;
}

typedef pair<vector<vector<int> > , int> state;

struct cmp
{
    bool operator()(state &a, state &b)
    {
        int am = misplacedTiles(a.first);
        int bm = misplacedTiles(b.first);
        return am > bm;
    }
};

void print_path(vector<vector<int> > s)
{
    if (parent.count(s))
        print_path(parent[s]);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void print(vector<vector<int> > s)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
}

void solve(vector<vector<int> > a)
{
    priority_queue<state, vector<state>, cmp> Q;
    Q.push(state(a, 0));
    while (!Q.empty())
    {
        vector<vector<int> > s = Q.top().first;
        Q.pop();
        visited[s] = true;
        if (isGoal(s))
        {
            print_path(s);
            break;
        }
        vector<vector<vector<int> > > ns = neighbours(s);
        vector<vector<vector<int> > >::iterator it;
        for (it = ns.begin(); it != ns.end(); it++)
        {
            vector<vector<int> > temp = *it;
            if (!visit(temp))
            {
                parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp, s));
                Q.push(state(temp, 0));
            }
        }
    }
    return;
}

int main()
{
    vector<vector<int> > a(3, vector<int>(3));
    a[0][0] = 8;
    a[0][1] = 0;
    a[0][2] = 6;
    a[1][0] = 5;
    a[1][1] = 4;
    a[1][2] = 7;
    a[2][0] = 2;
    a[2][1] = 3;
    a[2][2] = 1;
    cout << "\nPlease wait while the puzzle is solving...\n";
    goal[0][0] = 0;
    goal[0][1] = 1;
    goal[0][2] = 2;
    goal[1][0] = 3;
    goal[1][1] = 4;
    goal[1][2] = 5;
    goal[2][0] = 6;
    goal[2][1] = 7;
    goal[2][2] = 8;
    solve(a);

}

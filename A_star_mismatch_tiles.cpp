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

map<vector<vector<int> > , bool> visited; //declaring a map named "visited" that takes vector(which stores vectors that takes integer values) as its key, and a boolean as its value
map<vector<vector<int> > , vector<vector<int> > > parent; //declaring a map named "parent" that takes vectors as its both key and value to keep track of the nodes
vector<vector<int> > goal(3,vector<int> (3)); 

bool visit(vector<vector<int> > a)  //boolean to see if node is visited
{
	if(visited[a]==true)
		return true;
	
	return false;
}


//Missing Tiles with cost. 
int mismatch (vector<vector<int> > a , int moves)
{
	int H1 = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j]!= goal[i][j])
            {
                H1++;
            }
        }
    }
	return H1+moves;	
}

bool isGoal (vector<vector<int> > a){  //boolean to see if we've reached our goal state
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(a[i][j] != goal[i][j]) return 0; //if our puzzle tiles aren't same with the goal position. For eg. we want a[0][0] = 1, a[0][1] = 2, a[2][2] = 0, etc.
			
		}
	}
	
	return 1;	
}

bool safe(int i,int j) //boolean safe to see if grid is 3x3
{
	if(i>=0 && i<=2 && j>=0 && j<=2)
		return true;
	
	return false;
}


int dx[]={-1,1,0,0}; //array named "dx", with 4 length
int dy[]={0,0,1,-1};

vector<vector<vector<int> > > neighbours(vector<vector<int> > a) 
{
	pair<int,int> pos; //vector of pairs named "pos" (pairs an integer to another integer)
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++){
			if(a[i][j] == 0) 
			{
				pos.first=i;
				pos.second=j;
				break;
			 } 												
		}		
		
	}
	
	vector<vector<vector<int> > > ans; //"answer" vector to add the correct values by pushing back
	for (int k=0; k<4; k++) // 4, not 3, since our dx and dy arrays have 4 length
	{
		int cx = pos.first; //to keep track of the "i" values
		int cy = pos.second; //to keep track of the "j" values
		vector<vector<int> > n = a;
		if(safe(cx+dx[k], cy+dy[k]))
		{
			swap(n[cx+dx[k]][cy+dy[k]], n[cx][cy]); //swap tiles(or we can say swap arrays)
			ans.push_back(n);			
		}
	}
		
	return ans; //result vector
		
}

typedef pair<vector<vector<int> > , int> state; // new type defined named "state" that's a vector of pairs (which is a vector to integer pair)
	
struct cmp 
{
	bool operator() (state &a, state &b) // overloading the unary operator "()"
	{
		int am = mismatch(a.first,a.second);
		int bm = mismatch(b.first,b.second);
		return am>bm;		
	}	
};

void print_path(vector<vector<int> > s) {
  vector<vector<int> > temp; // new temporary variable to store the path
  if (parent.count(s)) { // check if parent exists
    temp = s; // store current state
    print_path(parent[s]); // recursively call print_path with parent state
  }

  // print current state only after reaching the initial state
  if (!temp.empty()) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        printf("%d ", s[i][j]);
      }
      cout << endl;
    }
    cout << endl;
  }
}

void print(vector<vector<int> > s)
{
	for(int i=0;i<3;i++)
   {
	 for(int j=0;j<3;j++)
	 {
		printf("%d ",s[i][j]);
	 }
	cout<<endl;
   }
}


void solve(vector<vector<int>> a, int moves)
{
    priority_queue<state, vector<state>, cmp> Q;
    Q.push(state(a, moves));
    while (!Q.empty())
    {
        vector<vector<int>> s = Q.top().first;
        moves = Q.top().second;  // Update moves from the current state
        Q.pop();
        visited[s] = true;
        if (s == goal)
        {
            print_path(s);
            break;
        }
        vector<vector<vector<int>>> ns = neighbours(s);
        for (const auto &temp : ns)
        {
            if (!visit(temp))
            {
                parent.insert(pair<vector<vector<int>>, vector<vector<int>>>(temp, s));
                Q.push(state(temp, moves + 1 + mismatch(temp, moves + 1)));
            }
        }
    }
    return;
}

int main()
{


//Initial State
	vector<vector<int> > a(3,vector<int> (3));	
	a[0][0] = 8;
    a[0][1] = 0;
    a[0][2] = 6;
    a[1][0] = 5;
    a[1][1] = 4;
    a[1][2] = 7;
    a[2][0] = 2;
    a[2][1] = 3;
    a[2][2] = 1;
//Goal State
    goal[0][0] = 0;
    goal[0][1] = 1;
    goal[0][2] = 2;
    goal[1][0] = 3;
    goal[1][1] = 4;
    goal[1][2] = 5;
    goal[2][0] = 6;
    goal[2][1] = 7;
    goal[2][2] = 8;
//Solution
	solve(a,0);



}


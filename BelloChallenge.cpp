#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define oo UINT_MAX //infinite

using namespace std;

void addRelation(vector<int>* &L, int a, int b) {
    L[a].push_back(b);
    L[b].push_back(a);
}

int readFile(int &nUsers, vector<int>* &L) {
    ifstream fin("input1.txt");
    if (!fin.is_open()) {
        cout << "Cannot open the input file!";
        return 1;
    }

    fin >> nUsers;

    L = new vector<int>[nUsers];
    int a, b;
    while (fin >> a >> b) {
        if (a >= nUsers || b >= nUsers) {
            cout << "Wrong input file!";
            return 1;
        }
        addRelation(L, a, b);
    }

    fin.close();
    return 0; //no errors
}

void print(int nUsers, vector<int>* L) {
    cout << "Number of users in the network: " << nUsers << "\n";
    for (int i = 0; i < nUsers; ++i) {
        cout << "Node " << i << ": ";
        vector<int>::iterator it;
        for (it = L[i].begin(); it != L[i].end(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }
}

void solve(int nUsers, vector<int>* L) {
    cout << "Get the length between user A and user B:\nA = ";
    int a, b, currNode;
    cin >> a;
    cout << "B = ";
    cin >> b;

    if (a >= nUsers || b >= nUsers) {
        cout << "Wrong input!";
        return;
    }

    int* dist = new int[nUsers]; //also used as visited array
    for (int i = 0; i < nUsers; ++i) {
        dist[i] = oo; //or visited[i] = 0
    }
    dist[a] = 0; //a to a

    queue<int> q;
    q.push(a);

    while (!q.empty()) {
        currNode = q.front();
        q.pop();
        vector<int>::iterator it;

        for (it = L[currNode].begin(); it != L[currNode].end(); ++it)
            if (dist[*it] == oo) { //not visited
                dist[*it] = dist[currNode] + 1;
                q.push(*it);
            }         
    }

    int length = dist[b];

    if (length == oo) {
        cout << "There is no chain of friends between " << a << " and " << b<<"\n";
    }
    else {
        cout << "length = " << length << "\n";
    }

}

int main()
{
    int nUsers;
    vector<int>* L;

    if (!readFile(nUsers, L)) {
        print(nUsers, L);
        solve(nUsers, L);
    }

    return 0;
}
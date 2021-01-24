#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

#define MAX_N 1005

vector<int> adj[MAX_N];
int n;

// verificam daca e 2-colorabil
bool bipartit()
{
    queue<int> coada;
    vector<int> culoare(n+1, -1);

    for (int i = 1; i <= n; i++)
    {
        if (culoare[i] == -1) // nevizitat
        {
            coada.push(i);
            culoare[i] = 0;
            while (!coada.empty())
            {
                int x = coada.front();
                coada.pop();

                for (int y : adj[x])
                {
                    if (culoare[y] == -1)
                    {
                        culoare[y] = culoare[x] ^ 1; // XOR, colorez cu 0 sau 1
                        coada.push(y);
                    }
                    else
                    {
                        if (culoare[x] == culoare[y])
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

int main()
{
    int m, x, y;
    ifstream f("bipartit.in");

    f >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        f >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    if (bipartit())
        cout << "E bipartit!\n";
    else
        cout << "Nu e bipartit!\n";

    return 0;
}

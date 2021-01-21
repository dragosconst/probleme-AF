/* Punti.
   Puncte Critice.
   Componente biconexe.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define MAX_N 101

int n;
int m;
vector<int> adj[MAX_N];
int tata[MAX_N];
bool viz[MAX_N];
int nivel[MAX_N];
int low[MAX_N];
bool ok;
int nr_fii_radacina;
stack<pair<int, int>> stiva;

void clean()
{
    for (int i = 1; i <= n; i++)
    {
        tata[i] = 0;
        viz[i] = 0;
        nivel[i] = 0;
        low[i] = 0;
    }
}

int nr_fii(int x)
{
    int nr = 0;

    for (int i = 1; i <= n; i++)
    {
        if (tata[i] == x && i != x)
            nr++;
    }

    return nr;
}
void dfs_legaturi_critice(int x)
{
    viz[x] = true;
    low[x] = nivel[x];
    for (int y : adj[x])
    {
        if (!viz[y])
        {
            tata[y] = x;
            nivel[y] = nivel[x] + 1;
            dfs_legaturi_critice(y);
            low[x] = min(low[x], low[y]);
            if (nivel[x] < low[y])
            {
                cout << x << ' ' << y << '\n';
                ok = true;
            }
        }
        else if (tata[x] != y)
        {
            low[x] = min(low[x], nivel[y]);
        }

    }
}

/* Punti */
void legaturi_critice()
{
    int start = 1;

    tata[start] = start;
    nivel[start] = 1;
    ok = false;
    cout << "Legaturi critice: \n";

    dfs_legaturi_critice(start);
    if (!ok)
        cout << "retea 2 muchie-conexa\n";

}

void dfs_noduri_vulnerabile(int x)
{
    viz[x] = true;
    low[x] = nivel[x];
    for (int y : adj[x])
    {
        if (!viz[y])
        {
            tata[y] = x;
            nivel[y] = nivel[x] + 1;
            dfs_noduri_vulnerabile(y);
            low[x] = min(low[x], low[y]);
            if ((tata[x] == x && nr_fii_radacina > 1) || (tata[x] != x && nivel[x] <= low[y]))
            {
                cout << x << '\n';
                ok = true;
            }
        }
        else if (tata[x] != y)
        {
            low[x] = min(low[x], nivel[y]);
        }

    }
}

/* Puncte critice */
void noduri_vulnerabile()
{
    int start = 1;

    tata[start] = start;
    nivel[start] = 1;
    ok = false;
    nr_fii_radacina = nr_fii(start);
    cout << "Noduri vulnerabile: \n";

    dfs_noduri_vulnerabile(start);
    if (!ok)
        cout << "retea biconexa\n";
}

void dfs_comp_biconexe(int x)
{
    viz[x] = true;
    low[x] = nivel[x];

    for (int y : adj[x])
    {
        if (!viz[y])
        {
            stiva.push(make_pair(x, y));

            tata[y] = x;
            nivel[y] = nivel[x] + 1;
            dfs_comp_biconexe(y);
            low[x] = min(low[x], low[y]);
            if ((tata[x] == x && nr_fii(x) > 1) || (tata[x] != x && nivel[x] <= low[y]))
            {
                while (stiva.top().first != x || stiva.top().second != y)
                {
                    cout << stiva.top().first << "--" << stiva.top().second << ' ';
                    stiva.pop();
                }
                cout << stiva.top().first << "--" << stiva.top().second << '\n'; // afisam de pe stiva toate muchiile pana la (x, y) inclusiv
                stiva.pop();
            }
        }
        else if (tata[x] != y)
        {
            low[x] = min(low[x], nivel[y]);
            if (nivel[y] < nivel[x])
                stiva.push(make_pair(x, y));
        }

    }
}


void comp_biconexe()
{
    int start = 1;

    tata[start] = start;
    nivel[start] = 1;
    ok = false;
    cout << "Comp biconexe: \n";

    dfs_comp_biconexe(start);
    while (!stiva.empty())
    {
        cout << stiva.top().first << "--" << stiva.top().second << ' ';
        stiva.pop();
    }
    cout << '\n';
}

int main()
{
    int x, y;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }


    noduri_vulnerabile();
    clean();
    legaturi_critice();
    clean();
    comp_biconexe();
    clean();
}

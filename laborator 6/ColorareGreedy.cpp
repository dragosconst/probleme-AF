/* O(n^2) */

#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

#define MAX_N 1005

vector<int> adj[MAX_N];
int culoare[MAX_N];
int d[MAX_N]; // grade
int n;

/* Intoarce cea mai mica culoare disponibila */
int culoare_disponibila(set<int> &culori)
{
    int cul = 1;

    while (true)
    {
        if (culori.find(cul) == culori.end()) // daca n-a fost folosita culoarea
            return cul;

        cul++;
    }
}

/* Determina o colorare a grafului pornind de la o ordonare a varfurilor */
void colorare(vector<int> &lista)
{
    for (int x : lista)
    {
        set<int> culori_vecini;

        for (int y : adj[x])
        {
             if (culoare[y]) // daca vecinul este colorat
                culori_vecini.insert(culoare[y]);
        }

        culoare[x] = culoare_disponibila(culori_vecini);
    }
}


/* Ordoneaza varfurile dupa criteriul "Smallest Last" */
void smallest_last(vector<int> &lista)
{
    int nr = n - 1;

    lista.resize(n);
    while (nr >= 0)
    {
        pair<int, int> minim(0, n); // first - nodul, second - gradul

        for (int x = 1; x <= n; x++)
        {
            if (d[x] >= 0 && d[x] < minim.second)
            {
                minim.first = x;
                minim.second = d[x];
            }
        }

        lista[nr] = minim.first;
        d[minim.first] = -1; // scoatem varful cu grad minim din graf
        for (int y : adj[minim.first])
            d[y]--; // scadem gradele varfurilor adiacente

        nr--;
    }
}

int main()
{
    int m, x, y;
    vector<int> lista;
    ifstream f("graf.in");

    f >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        f >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        d[x]++;
        d[y]++;
    }

    smallest_last(lista);
    colorare(lista);

    for (int i = 1; i <= n; i++)
        cout << i << ' ' << culoare[i] << '\n';

    return 0;
}

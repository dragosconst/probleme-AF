#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_N 1005
#define INF 1e9

/* E incredibil cat de multa memorie folosesc.. */

int adj[MAX_N][MAX_N]; // matricea de adiacenta a grafului
vector<int> v[MAX_N]; // lista de adiacenta a grafului
int flux[MAX_N][MAX_N]; // fluxul din graf
vector<int> rez[MAX_N]; // lista de adiacenta a grafului rezidual
int cap[MAX_N][MAX_N]; // capacitatea din graful rezidual
int inout[MAX_N]; // pt verificarea conservarii fluxului
int tata[MAX_N]; // pentru construirea drumului
int n, m, s, t;


int bfs_graf_rezidual()
{
    queue<pair<int, int>> coada;

    for (int i = 1; i <= n; i++)
        tata[i] = 0;

    tata[s] = s;
    coada.push({s, INF});

    while (!coada.empty())
    {
        int x = coada.front().first;
        int fl = coada.front().second;
        coada.pop();

        for (int y : rez[x])
        {
            if (!tata[y] && cap[x][y] > 0) // daca n-are parinte, inseamna ca nu a fost vizitat
            {
                tata[y] = x;
                int flux_nou = min(fl, cap[x][y]);
                //printf("x: %d, y: %d, flux_nou: %d\n", x, y, flux_nou);

                if (y == t)
                    return flux_nou; // va intoarce capacitatea minima a unui arc din drum

                coada.push({y, flux_nou});
            }
        }
    }

    return 0;
}

bool flux_corect()
{
    for (int x = 1; x <= n; x++)
    {
        if (x != s && x != t && inout[x] != 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int x, y, i, m, c, fl, flux_nou, val_flux = 0;

    ifstream f("retea.in");

    f >> n >> s >> t >> m;
    for (i = 1; i <= m; i++)
    {
        f >> x >> y >> c >> fl;

        adj[x][y] = 1;
        v[x].push_back(y);
        flux[x][y] = fl;
        if (x == s)
            val_flux += flux[x][y];

        /* Construieste graful rezidual*/
        if ((c - fl) != 0)
        {
            rez[x].push_back(y);
            cap[x][y] = c - fl;
        }
        if (fl)
        {
            rez[y].push_back(x);
            cap[y][x] = fl;
        }

        /* Aduna fluxul care iese si scade fluxul care intra */
        inout[x] += fl;
        inout[y] -= fl;
    }

    if (flux_corect())
    {
        cout << "flux corect.\n";
    }
    else
    {
        cout << "flux incorect.\n";
        return 0;
    }

    while ((flux_nou = bfs_graf_rezidual()))
    {
        //printf("flux_nou: %d\n", flux_nou);
        val_flux += flux_nou;
        y = t;
        while (y != s)
        {
            x = tata[y];
            if (adj[x][y])
                flux[x][y] += flux_nou;
            else
                flux[y][x] -= flux_nou;

            cap[x][y] -= flux_nou;
            cap[y][x] += flux_nou;
            y = x;
        }

    }
    cout << "Fluxul maxim: " << val_flux << '\n';

    /* Determinarea taieturii minime */
    cout << "Taietura minima:\n";
    for (x = 1; x <= n; x++)
    {
        if (tata[x]) // varf accesibil din s
        {
            for (int y : v[x])
            {
                if (!tata[y]) // varf inaccesibil din s
                {
                    cout << x << ' ' << y << '\n';
                    //cap_taietura_min += 1;
                }

            }
        }
    }
    cout <<"\n\nFluxul pe fiecare arc:\n";
    for (x = 1; x <= n; x++)
    {
        for (int y : v[x])
        {
            printf("%d %d %d\n", x, y, flux[x][y]);
        }
    }

    return 0;
}

/*
	Nr din pdf: 1
	Observatii: Nu vad vreo optimizare imediat evidenta de spatiu care sa nu sacrifice timp. Daca am avea o garantie de
				genu ca intre doua noduri poate fi o singura muchie (pe orice directie), am putea renunta la matricea de
				adiacenta. Eventual am putea implementa array-ul tata ca un queue, dar pe worst case cred ca ar fi aceiasi
				complexitate de spatiu ca un array. Flux ca map iarasi e o optimizare aparent posibila, dar se sacrifica 
				timp de accesare de la O(1) cu matrice la O(logm) cu map. 
				Pt ca worst case pe vector<int> g e O(n), am putea renunta total la el si sa parcurgem mereu matricea de adiacenta instead.
*/

#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const size_t MAXN = 101, INF=1000000000;
int n, s, t, m;
int flux[MAXN][MAXN], a[MAXN][MAXN], capf[MAXN][MAXN];
int totalFlux[MAXN], tata[MAXN];
vector<int> g[MAXN];
vector<int> rez[MAXN];

void revisionAndUpdateGf(int fx);
int edmondBfsGf();
int ffek();
int main()
{
    int alreadySent = 0;
    in >> n >> s >> t >> m;
    bool wellDef = true;
    for(int i = 1; i <= m; ++i)
    {
        int x, y, f, cap;
        in >> x >> y >> cap >> f;
        if(x == s)
            alreadySent += f;

        g[x].push_back(y);
        a[x][y] = 1;

        // graf rezidual
        if(cap - f > 0)
        {
            rez[x].push_back(y);
            capf[x][y] = cap - f;
        }
        if(f > 0)
        {
            rez[y].push_back(x);
            capf[y][x] = f;
        }

        flux[x][y] = f;
        if(f > cap || f < 0)//prima cerinta
            wellDef = false;

        totalFlux[x] += f;
        totalFlux[y] -= f;
    }
    for(int i = 1; wellDef && i <= n; ++i)
        if(s != i && t != i && totalFlux[i])
        {
            wellDef = false;
        }

    // punctul a
    if(wellDef)
        out << "DA\n";
    else
    {
        out << "NU";
        return 0;
    }

    //punctul b
    int all = ffek() + alreadySent;
    out << all << '\n';
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < g[i].size(); ++j)
        {
            out << i << ' ' << g[i][j] << ' ' << flux[i][g[i][j]] << '\n';
        }
    }
    out << all << '\n';
    for(int i = 1; i <= n; ++i)
    {
        if(tata[i])
        {
            for(int j: g[i])
            {
                if(!tata[j])
                    out << i << ' ' << j << '\n';
            }
        }
    }
    return 0;
}

void
revisionAndUpdateGf(int fx)
{
    int tmp = t;
    while(tmp != tata[tmp])
    {
        int prev = tata[tmp];

        if(a[prev][tmp])
            flux[prev][tmp] += fx;
        else
            flux[tmp][prev] -= fx;

        capf[prev][tmp] -= fx;
        capf[tmp][prev] += fx;
        if(!(capf[tmp][prev] - fx))
            rez[tmp].push_back(prev);

        tmp = tata[tmp];
    }
}


int
edmondBfsGf()
{
	memset(tata, 0, (n+1) * sizeof(int));

    queue<pair<int, int>> coada;
    coada.push({s, INF});
    int maxFlow = INF;
    tata[s] = s;

    while(!coada.empty())
    {
        int u = coada.front().first;
        maxFlow = coada.front().second;
        coada.pop();
        if(u == t)
        {
            return maxFlow;
        }

        for(int i = 0; i < rez[u].size(); ++i)
        {
            int v = rez[u][i];
            if(!tata[v] && capf[u][v] > 0) // a doua conditie marcheaza daca am "sters" din graful rezidual muchia
            {
                tata[v] = u;

                int bottleNeck = min(maxFlow, capf[u][v]);

                coada.push({v, bottleNeck});
            }
        }
    }
    return 0; //daca nu ajung la t in coada, inseamna ca t nu mai e accesibil => nu mai avem drumuri s-t in graful rezidual
}

int
ffek()
{
    int fx, totes = 0;
    while(fx = edmondBfsGf())
    {
        totes += fx;
        revisionAndUpdateGf(fx);
    }
    return totes;
}



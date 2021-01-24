/*
	Nr din pdf: 3
	Observatii: nimic special, e algoritmul de secventa de grade, scris poate un pic urat
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

const size_t MAXN = 2 * 103, INF=1000000000;
int n, s, t, m;
int flux[MAXN][MAXN], a[MAXN][MAXN], capf[MAXN][MAXN];
int totalFlux[MAXN], tata[MAXN], viz[MAXN];
int gint[MAXN], gext[MAXN];
vector<int> retea[MAXN], rez[MAXN];

void revisionAndUpdateGf(int fx);
int edmondBfsGf();
int ffek();
int main()
{
    in >> n;
    int sum = 0;
    for(int i = 1; i <= n; ++i)
    {
        in >> gint[i];
        sum += gint[i];
    }
    for(int i = 1; i <= n; ++i)
    {
        in >> gext[i];
        sum += gext[i];
    }
    if(sum % 2)
    {
        out << "NU";
        return 0;
    }

    n = 2 * n;
    s = 0, t = n + 1;
    // constructia retelei
    for(int i = 1; i <= n / 2; ++i)
    {
        a[s][i] = 1;
        retea[s].push_back(i);
        rez[s].push_back(i);
        capf[s][i] = gext[i];

        for(int j = n / 2 + 1; j <= n; ++j)
        {
            if(i != j - n / 2)
            {
                a[i][j] = 1;
                retea[i].push_back(j);
                rez[i].push_back(j);
                capf[i][j] = 1;
            }

            if(!a[j][t])
            {
                a[j][t] = 1;
                retea[j].push_back(t);
                rez[j].push_back(t);
                capf[j][t] = gint[j - n / 2];
            }
        }
    }

    int all = ffek();
    if(all < sum / 2) // check
    {
        out << "NU";
        return 0;
    }

    // afisez graful nou obtinut
    for(int i = 1; i <= n / 2; ++i)
    {
        for(int j = n / 2 + 1; j <= n; ++j)
        {
            if(flux[i][j])
                out << i <<  ' ' << j - n /2 << '\n';
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
    for(int i = 0; i <= n + 1; ++i)
        viz[i] = tata[i] = 0;

    queue<pair<int, int>> coada;
    coada.push({s, INF});
    int maxFlow = INF;
    tata[s] = s;
    viz[s] = 1;

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
            if(!viz[v] && capf[u][v] > 0) // a doua conditie marcheaza daca am "sters" din graful rezidual muchia
            {
                viz[v] = 1;
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


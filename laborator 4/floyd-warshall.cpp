/*
	Nr din pdf: 5 a)
	Observatii: e fw standard cu detectie + afisare de circuite negative
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

const size_t MAXN = 101, MAXM = 401, INF = 100000000;
int d[MAXM][MAXN], w[MAXN][MAXN], p[MAXN][MAXN];
int n, m;

void fw();
void drum(int i, int j);
int main()
{
    in >> n >> m;
    for(int i = 1; i <= n; ++i)
    {   // init weights
        for(int j = 1; j <= n; ++j)
        {
            if(i == j)
                w[i][j] = 0;
            else
                w[i][j] = INF;
        }
    }
    for(int i = 1; i <= m; ++i)
    {
        int x, y, ct;
        in >> x >> y >> ct;
        w[x][y] = ct;
    }

    fw();
    return 0;
}

void
drum(int i, int j)
{
    if(i != j)
    {
        drum(i, p[i][j]);
    }
    out << j << ' ';
}

void
fw()
{
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {   // init stuff
            d[i][j] = w[i][j];
            if(w[i][j] == INF)
                p[i][j] = 0;
            else
                p[i][j] = i;
        }
    }

    //floyd warshall
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }

    int wherei = -1, wherej = -1;
    // detectez cicluri negative
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(d[i][k] + d[k][j] < d[i][j])
                {
                    out << "Circuit negativ detectat:\n";
                    wherei = i;
                    wherej = j;
                    j = i = k = n + 1;
                }
            }
        }
    }

    //afisari
    if(wherei > 0)
    {   // afisare de circuit negativ, ca de obicei, e afisat in ordine inversa
        int tempi = wherei, tempj = wherej;
        out << tempj << ' ';
        tempj = p[wherei][tempj];
        while(tempj != wherej)
        {
            out << tempj << ' ';
            tempj = p[wherei][tempj];
        }
        out << tempj << '\n';
    }
    else
    {
        out << "Matricea drumurilor este:\n";
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                out << d[i][j] << ' ';
            }
            out << '\n';
        }
    }
}


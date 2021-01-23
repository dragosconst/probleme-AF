/*
	Nr din pdf: 5 B
	Observatii: nu mi e clar daca poti avea excentritatea egala cu 0 sau nu (probabil ca da)
				In rest, e doar un Floyd-Warshall inversat, asemanator cu problema de DAG
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
                w[i][j] = -INF;
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
    int e[MAXN], radius = INF, diam = -INF; // excentritati
    for(int i = 1; i <= n; ++i)
        e[i] = -INF;

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {   // init stuff
            d[i][j] = w[i][j];
            if(w[i][j] == -INF)
                p[i][j] = 0;
            else
                p[i][j] = i;

            if(d[i][j] != -INF && d[i][j] > e[i])
                e[i] = d[i][j];
        }
    }

    //floyd warshall
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(d[i][k] != -INF && d[k][j] != -INF && d[i][j] < d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];

                    // calculul excentritatilor si a razei
                    if(d[i][j] > e[i])
                        e[i] = d[i][j];
                }
            }
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        if(e[i] < radius)
            radius = e[i];
        if(e[i] > diam)
            diam = e[i];
    }
    // afisari
    out << "Raza grafului este " << radius << '\n';
    out << "Diametrul grafului este " << diam << '\n';
    out << "Centrul grafului este ";
    for(int i = 1; i <= n; ++i)
        if(e[i] == radius)
            out << i << ' ';
    out << '\n';
    out << "Excentritatile sunt: \n";
    for(int i = 1; i <= n; ++i)
        out << "Varful " << i <<" = " << e[i] << '\n';
}


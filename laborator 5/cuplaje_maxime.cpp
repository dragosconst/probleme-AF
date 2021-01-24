/*
	Nr din pdf: 2
	Observatii: am folosit un algoritm de gasire a ciclurilor mai destept decat ala de l am folosit la lab1 de pe g4g
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

const size_t MAXN = 103, INF=1000000000;
int n, s, t, m;
int flux[MAXN][MAXN], a[MAXN][MAXN], capf[MAXN][MAXN];
int totalFlux[MAXN], tata[MAXN];
int col[MAXN], viz[MAXN], af[MAXN]; // specifice problemei
vector<int> g[MAXN], retea[MAXN];
vector<int> rez[MAXN];

bool twoColorare(int st);
void dfsNeor(int st);
void revisionAndUpdateGf(int fx);
int edmondBfsGf();
int ffek();
int main()
{
    in >> n >> m;
    s = 0;
    t = n + 1;
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        in >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // verificare bipartit
    if(!twoColorare(1))
    {
        out << "Graful nu e bipartit\n";
        dfsNeor(1);
        return 0;
    }

    // construiesc reteaua de fluxuri
    // la col[i] == 1 il pun in partitia lui s, si la col[i] == 2 in a lui t
    for(int i = 1; i <= n; ++i)
    {
        if(col[i] == 1)
            for(int j: g[i])
            {
                retea[i].push_back(j);
                a[i][j] = 1;
                flux[i][j] = 0;
                capf[i][j] = 1;
                rez[i].push_back(j);
            }

        if(col[i] == 1)
        {
            retea[s].push_back(i);
            a[s][i] = 1;
            flux[s][i] = 0;
            capf[s][i] = 1;
            rez[s].push_back(i);
        }
        else
        {
            retea[i].push_back(t);
            a[i][t] = 1;
            flux[i][t] = 0;
            capf[i][t] = 1;
            rez[i].push_back(t);
        }
    }


    int all = ffek(); // ford fulkerson pe o retea simpla
    out << "Avem un cuplaj de cardinal " << all << '\n';
    for(int i = 1; i <= n; ++i)
        for(int j: retea[i])
            if(flux[i][j] && j != t) // e practic un caz special pt taietura minima, pt ca deja stim partitiile
                out << i << ' ' << j << '\n';
    return 0;
}

void
dfsNeor(int u)
{
    viz[u] = 1;
    for(int v: g[u])
    {
        if(!viz[v])
        {
            tata[v] = u;
            dfsNeor(v);
        }
        else if(v != tata[u])
        {
            int ctr = 0;
            tata[v] = u;
            int x = u;
            while(x != v)
            {
                af[ctr++] = x;
                x = tata[x];
            }
            af[ctr++] = v;
            if(ctr % 2) // daca la final am un nr impar de varfuri in ciclu, right?
            {
                for(int i = 0; i < ctr; ++i)
                    out << af[i] << ' ';
                out << af[0] << '\n';
                return;
            }
        }
    }
}

bool
twoColorare(int st)
{
    queue<int> coada;
    coada.push(st);
    col[st] = 1;

    while(!coada.empty())
    {
        int u = coada.front();
        coada.pop();

        for(int v: g[u])
        {
            if(!col[v])
            {
                col[v] = col[u] == 1 ? 2 : 1;
                coada.push(v);
            }
            else if(col[v] == col[u])
                return false;
        }
    }

    for(int u = 1; u <= n; ++u) // nu s sigur daca e necesara inca o parcurgere la final
    {
        for(int v: g[u])
        {
            if(col[u] == col[v])
                return false;
        }
    }
    return true;
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

        tmp = tata[tmp];
    }
}


int
edmondBfsGf()
{
    memset(tata, 0, (n+2) * sizeof(int)); // chipurile memset e mai rapid ca un for simplu, oricum e mai convenabil de scris imo

    queue<int> coada;
    coada.push(s);
    int maxFlow = INF;
    tata[s] = s;

    while(!coada.empty())
    {
        int u = coada.front();
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

                if(capf[u][v] < maxFlow)
                    maxFlow = capf[u][v];

                coada.push(v);
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


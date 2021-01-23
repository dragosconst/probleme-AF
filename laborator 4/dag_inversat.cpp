/*
	Nr din pdf: 1
	Observatii: e un DAG inversat, pt ca calculeaza drumurile maxime, in loc de minime
				foloseste implementarea mea de la sortare topologica cu liste statice, deci again nu l as recomanda
				mai mult decat un eventual model pt o mai buna intelegere a problemei
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

const int MAXN = 50003, MAXM = 200002, INF = 1000000000;

int lst[MAXN], vf[MAXM], urm[MAXM], cost[MAXM], cost_nod[MAXN], viz[MAXN], af[MAXN], d[MAXN], tata[MAXN];
int n, m, nr, cnt;

void adauga(int, int, int);
void dfsTop(int x);
void basicDfs(int x);
void inserSandT();
void dga();
void critical();
void findIntervals();
int main()
{
    in >> n;
    for(int i = 1; i <= n; ++i)
    {
        in >> cost_nod[i];
    }
    in >> m;
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        in >> x >> y;
        adauga(x, y, cost_nod[x]);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!viz[i])
            dfsTop(i);
    }

    // punctul a)
    dga();
    critical();
    //punctul b)
    findIntervals();
    return 0;
}

void critical()
{
    out << "Activitati critice: ";
    int fin = tata[af[0]];
    while(fin)
    {
        out << fin << ' ';
        fin = tata[fin];
    }
    out <<'\n';
}

void findIntervals()
{
    struct interval{
        int a, b;
    }nodes[MAXN];

    nodes[0] = {0, 0};
    for(int i = n + 1; i >= 1; --i)
    {
        int p = lst[af[i]];
        while(p)
        {
            int y = vf[p];
            if(nodes[y].a <= nodes[af[i]].b) // vreau mereu sa incep cat mai tarziu posibil
            {
                nodes[y].a = nodes[af[i]].b;
                nodes[y].b = nodes[y].a + cost_nod[y];
            }
            p = urm[p];
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        out << i <<": "<< nodes[i].a << ' ' << nodes[i].b << '\n';
    }
}

void basicDfs(int nod)
{
    viz[nod] = 1;
    int p = lst[nod];
    if(!p)//nod terminal, il legam la t
    {
        adauga(nod, n + 1, cost_nod[nod]);
    }
    while(p)
    {
        int y = vf[p];
        if(!viz[y])
        {
            basicDfs(y);
        }
        p = urm[p];
    }
}

void inserSandT()
{
    memset(viz, 0, (m+1) * sizeof(int));

    for(int i = 1; i <= n; ++i)
    {
        cout << af[i] << ' ';
        if(!viz[i]) // s o sa fie nodul 0 si t nodul n + 1
        {
            adauga(0, i, 0); // leg s de toate componentele conexe la inceput
            basicDfs(i);
        }
    }
    cout << endl;
}

void dga()
{
    inserSandT();

    for(int i = 1; i <= n + 1; ++i)
    {
        d[i] = -INF;
        tata[i] = 0;
    }
    af[n + 1] = 0;
    //d[0] = 0;
    af[0] = n + 1;
    //d[n+1] = 0; -> le am comentat pentru ca sunt implicit intializate cu 0 din declaratia globala

    for(int i = n + 1; i >= 0; --i)
    {   // sortarea e stocata in af
        int p = lst[af[i]];
        while(p)
        {
            int y = vf[p];
            if(d[af[i]] + cost[p] > d[y])
            {
                d[y] = d[af[i]] + cost[p];
                tata[y] = af[i];
            }
            p = urm[p];
        }
    }

    out << "Timp minim " << d[n + 1] << '\n';
}

void adauga(int x, int y, int w)
{
    ++nr;
    vf[nr] = y;
    urm[nr] = lst[x];
    cost[nr] = w;
    lst[x] = nr;
}



void dfsTop(int x)
{
    int p, y;
    viz[x] = 1;
    p = lst[x];
    while(p)
    {
        y = vf[p];
        if(!viz[y])
        {
            dfsTop(y);
        }
        p = urm[p];
    }
    af[++cnt] = x;
}

/*
	6-colorare folosind min-heap
	Observatii: e O(n+m)*, stergerea e O(logn) 
	*sau nu? idk
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

const size_t MAXN = 101, MAXM = 501, INF = 1e9;
int col[MAXN], deg[MAXN], h[MAXM], poz[MAXM];
vector<int> g[MAXN];
int n, m, nh;

int cmp(int a, int b)
{
    return deg[a] < deg[b];
}
void urca(int p);
void sterge(int p);
void coboara(int p);
void adauga(int val);
void six_col();
int main()
{
    in >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        in >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }

    six_col();
    for(int i = 1; i <= n; ++i)
        out << col[i] << ' ';
    return 0;
}

void
six_col()
{
    for(int i = 1; i <= n; ++i)
    {
        adauga(i);
    }

    while(nh > 0)
    {
        int u = h[1];
        deg[u] = INF; // not sure if needed

        int pos_col[7] = {0}; // 7 ca sa fie frumos cu indicii
        for(int v: g[u])
        {
            if(col[v])
                pos_col[col[v]] = 1;
            deg[v]--;
        }
        for(int i = 1; i <= 6; ++i)
            if(!pos_col[i])
            {
                col[u] = i;
                break;
            }

        sterge(1); // sterg la final, ca sa fac update-urile pe degrees full
    }
}

void urca(int p)
{
    while(p > 1 && deg[h[p]] < deg[h[p / 2]])
    {
        swap(h[p], h[p / 2]);
        poz[h[p]] = p;
        poz[h[p / 2]] = p / 2;
        p /= 2;
    }
}

void coboara(int p)
{
    int fs = p * 2, fd = p * 2 + 1, bun = p;

    if(fs <= nh && deg[h[fs]] < deg[h[bun]])
    {
        bun = fs;
    }

    if(fd <= nh && deg[h[fd]] < deg[h[bun]])
    {
        bun = fd;
    }

    if(bun != p)
    {
        swap(h[bun], h[p]);
        poz[h[p]] = p;
        poz[h[bun]] = bun;
        coboara(bun);
    }
}

void adauga(int val)
{
    h[++nh] = val;
    urca(nh);
}

void sterge(int p)
{
    swap(h[p], h[nh--]);
    poz[h[p]] = p;
    poz[h[nh + 1]] = nh + 1;
    urca(p);
    coboara(p);
}

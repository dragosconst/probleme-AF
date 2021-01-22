/*
	Nr din pdf: 5
	Complexitate: O(n) la a) si O(1) la b, daca nu luam a in considerare (altfel e O(n))
	Observatii: Destul de usor, daca ai algorimtul de gasit cicluri bine pus la punct.
*/
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int DIM = 200002;
struct speci //EDIT: no idea de la ce mi a venit in liceu sa i zic speci? poate special? idk
{
    int nx, ny, cost;
} v[DIM * 2];


int viz[DIM], mark[DIM], tata[DIM];
vector<pair<int, int>> g[DIM];
int t[DIM], h[DIM];
speci af[DIM];
int n, m, S, global = 1;

void uniune(int x, int y);
int rad(int x);
bool isSame(int x, int y);
bool cmp(speci a, speci b)
{
    return a.cost < b.cost;
}

void dfs(int st, int old, vector<pair<int, int>> g[DIM]);
int main()
{

    in >> n >> m;
    for(int i = 1; i <= m; ++i)
		in >> v[i].nx >> v[i].ny >> v[i].cost;
    sort(v + 1, v + m + 1, cmp);
    int ct = 1;
    for(int i = 1; i <= m && ct <= n - 1; ++i)
    {
        if(!isSame(v[i].nx, v[i].ny))
        {
            uniune(v[i].nx, v[i].ny);
            af[ct].nx = v[i].nx;
            af[ct].cost = v[i].cost;
            af[ct++].ny = v[i].ny;
            S += v[i].cost;
        }
    }
    out << "Muchiile apcm in G:\n";
    for(int i = 1; i < ct; ++i)
        out << af[i].nx << ' ' << af[i].ny << '\n';
    out <<"Cost " << S << '\n';
    //punctul a
    speci a;
    cin >> a.nx >> a.ny >> a.cost;// construiesc un graf care are doar arborele
    for(int i = 1; i < ct; ++i)
    {
        g[af[i].nx].push_back({af[i].ny, af[i].cost});
        g[af[i].ny].push_back({af[i].nx, af[i].cost});
    }
    g[a.nx].push_back({a.ny, a.cost});
    g[a.ny].push_back({a.nx, a.cost});
    dfs(a.nx, 0, g); // O(n + n) = O(n), pentru ca avem doar n muchii


    int maxi = -1, atLeastBigger = -1;
    int cx, cy, atx, aty;
    for(int i = 1; i <= n; ++i)
    {   // for u asta nu e O(n^2) pt ca se intra in if doar odata
        if(mark[i] > 0)
        {
            for(int j = i; j <= n; ++j)
            {
                if(mark[j] == mark[i])
                {
                    for(int k = 0; k < g[j].size(); ++k)
                    {
                        if(mark[g[j][k].first] == mark[i])
                        {
                             if(g[j][k].second > maxi)
                            {
                                maxi = g[j][k].second;
                                cx = j;
                                cy = g[j][k].first;
                            }
                            if(g[j][k].second > a.cost && g[j][k].second > atLeastBigger)
                            {   // pt punctul b), memorez muchia cea mai mare, mai mare decat a.cost din ciclu
                                atLeastBigger = g[j][k].second;
                                atx = j;
                                aty = g[j][k].first;
                            }
                        }
                    }
                }
            }

            break;
        }
    }

    out << "Muchia de cost maxim din ciclul inchis de " << a.nx << ' ' << a.ny << " in apcm este " << cx << ' ' << cy << " de costul " << maxi << '\n';

    // subpunctul b in O(1)
    if(atLeastBigger == -1)
    {
        out << "Adaugarea muchiei nu produce nicio diferenta";
    }
    else
    {
        out << "Dupa adaugarea muchiei apcm are costul " << S - atLeastBigger + a.cost;
    }
    return 0;
}

void
dfs(int st, int old, vector<pair<int, int>> g[DIM])
{
    if(viz[st] == 2) return;

    if(viz[st] == 1)
    {
        int temp = old;
        mark[temp] = global;
        while(temp != st)
        {
            temp = tata[temp];
            mark[temp] = global;
        }
        global++;
        return;
    }

    viz[st] = 1;
    tata[st] = old;

    for(int j = 0; j < g[st].size(); ++j)
    {
        if(g[st][j].first == tata[st])
            continue;
        dfs(g[st][j].first, st, g);
    }

    viz[st] = 2;
}

int rad(int x)
{
    if(t[x] == 0)
        return x;
    t[x] = rad(t[x]);
    return t[x];
}

bool isSame(int x, int y)
{
    if(rad(x) == rad(y))
        return true;
    return false;
}

void uniune(int x, int y)
{
    int rx = rad(x), ry = rad(y);
    if(h[rx] < h[ry])
    {
        t[rx] = ry;
    }
    else
    {
        t[ry] = rx;
        if(h[ry] == h[rx])
            ++h[ry];
    }
}

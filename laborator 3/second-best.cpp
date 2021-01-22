/*
	Nr din pdf: 6
	Complexitate: O(n^2)*
	Observatii: Nu prea am pus comentarii pt ca e foarte bine explicat in primul pdf de seminar cu apcm
	
	*s-ar putea sa fie O(n^3), dar am niste dubii
*/

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int DIM = 2002;
struct speci //EDIT: no idea de la ce mi a venit in liceu sa i zic speci? poate special? idk
{
    int nx, ny, cost;
} v[DIM * 2];

int t[DIM], h[DIM];
vector<pair<int, int>> g[DIM];
vector<pair<int, int>> apcm[DIM];
int maxi[DIM][DIM];

speci af[DIM];
int n, m, S, global = 1;
int viz[DIM];

void uniune(int x, int y);
int rad(int x);
bool isSame(int x, int y);
bool cmp(speci a, speci b)
{
    return a.cost < b.cost;
}

void bfs(int start);
int main()
{

    in >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
		in >> v[i].nx >> v[i].ny >> v[i].cost;
		g[v[i].nx].push_back({v[i].ny, v[i].cost}); // trebuie sa construiesc graful, ca sa am O(n^2) la second best
		g[v[i].ny].push_back({v[i].nx, v[i].cost});
    }
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
    out << "Primul\n";
    out <<"Cost " << S << '\n';
    out << "Muchii:\n";
    for(int i = 1; i < n; ++i)
    {
        out << af[i].nx << ' ' << af[i].ny << '\n';
        apcm[af[i].nx].push_back({af[i].ny, af[i].cost});
        apcm[af[i].ny].push_back({af[i].nx, af[i].cost});
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int i = 1; i <= n; ++i)
            viz[i] = 0;
        bfs(i);
    }

    long long S2 = 9999999999;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < g[i].size(); ++j)
        {
            bool cont = false;
            for(int k = 0; k < apcm[i].size(); ++k) // nu mi e clar daca pasul asta duce in O(n^3) sau nu, tinand cont ca tot apcm-ul are n-1 muchii
                if(apcm[i][k].first == g[i][j].first)
                {
                    cont = true;
                    break;
                }

            if(cont) continue;
            S2 = (S2 > S - maxi[i][g[i][j].first] + g[i][j].second ? S - maxi[i][g[i][j].first] + g[i][j].second : S2);
        }
    }
    out << "Al doilea\n";
    out << "Cost: " << S2 << '\n'; // mi a fost lene sa si salvez apcm-ul pt afisare
    return 0;
}

void bfs(int st)
{   //determin max[x, y] pt fiecare lant
    queue<int> coada;
    coada.push(st);

    while(!coada.empty())
    {
        int cr = coada.front();
        coada.pop();
        viz[cr] = 1;

        for(int i = 0; i < apcm[cr].size(); ++i)
        {
            if(!viz[apcm[cr][i].first])
            {
                coada.push(apcm[cr][i].first);
                maxi[st][apcm[cr][i].first] = max(maxi[st][cr], apcm[cr][i].second);
            }
        }
    }
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

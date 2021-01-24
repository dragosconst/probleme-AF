/*
	Nr din pdf: 1 de la euler
	Observatii: O(n + m), e algoritmul ala cu nume de neamt cu H
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
int deg[MAXN], af[MAXN];
int a[MAXN][MAXN], cycle[MAXN][MAXN];
vector<int> g[MAXN];
int n, m, nh = 1;

int extractNode();
void hierholzer();
int main()
{
    in >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        in >> x >> y;
        g[x].push_back(y);
        a[x][y] = a[y][x] = 1;
        g[y].push_back(x);
        deg[x]+=2;
        deg[y]+=2;
    }

    // check eulerian
    for(int i = 1; i <= n; ++i)
    {
        if(deg[i] % 2)
        {
            out << "nu e eulerian";
            return 0;
        }
    }

    hierholzer();
    return 0;
}

int
extractNode()
{
    for(int i = 1; i <= n; ++i)
        if(deg[i])
            return i;
}

void
hierholzer()
{
    int totalMuchii = 0;
    int x;
    while(totalMuchii < m)
    {
        x = extractNode();
        int st = x;
        do{
            for(int j: g[x])
            {
                if(a[x][j] && !cycle[x][j])
                {
                    cycle[x][j] = cycle[j][x] = 1;
                    af[nh++] = x;
                    deg[x] -= 2;
                    deg[j] -= 2;
                    x = j;
                    break;
                }
            }
            totalMuchii++;
        }while(x != st);
    }

    int st = x;
    for(int i = 1; i < nh; ++i)
        out << af[i] << ' ';
    out << af[1] << '\n';
}

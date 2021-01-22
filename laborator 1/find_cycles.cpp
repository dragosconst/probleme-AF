/*
	Nr din pdf: 1 C, dar 2 C se face aproape identic cred
	Observatii: am luat shamelessly ideea de aici https://www.geeksforgeeks.org/print-all-the-cycles-in-an-undirected-graph/
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const size_t MAXN = 101;
vector<int> g[MAXN];
int viz[MAXN], mark[MAXN], tata[MAXN];
int n, m, global = 1;

void dfs(int st, int old);
int main()
{
    in >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        int x, y;
        in >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    bool noCycle = true;
    for(int i = 1; i <= n; ++i)
    {
        for(int i = 1; i <= n; ++i)
        {
            tata[i] = 0;
            viz[i] = 0;
        }
        dfs(i, 0);
    }

    for(int i = 1; i <= n; ++i)
    {
        if(mark[i] > 0)
        {
            noCycle = false;
            for(int j = i; j <= n; ++j)
            {
                if(mark[j] == mark[i]) out << j << ' ';
            }
            out << i;
            break;
        }
    }

    if(noCycle)
        out << "nu avem cicluri";
	return 0;
}

void
dfs(int st, int old)
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
        if(g[st][j] == tata[st])
            continue;
        dfs(g[st][j], st);
    }

    viz[st] = 2;
}

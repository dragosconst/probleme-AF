/*
	Nr din pdf: 4 B
	Observatii: Am rezolvat-o cu doua dfs-uri mai ciudate, mai intai aflu lungimea minima si dupa ma plimb prin toate drumurile
				posibile, si cand ajung in varful in care voiam, verific daca am facut atatia pasi cat e minimul. Am un vector
				de tati, care e schimbat constant, pentru a putea afisa lanturile intregi.
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
int tata[MAXN], len[MAXN];
int trueLen = 100000000;
bool viz[MAXN], vn[MAXN];
int n, m;

void findMaxLen(int st, int fin);
void dfs(int st, int fin);
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

    int s, t;
    in >> s >> t;
    findMaxLen(s, t); // mai intai, determin cel mai scurt drum (oricare dintre ele)
    trueLen = len[t];
    for(int i = 1; i <= MAXN; ++i) //o sa folosesc vectoru asta cand calculez toate drumurile posibile in dfs
        len[i] = 0;
    tata[s] = 0;
    viz[s] = 1;
    dfs(s,t);
	return 0;
}

void findMaxLen(int st, int fin)
{
    for(int j = 0; j < g[st].size(); ++j)
    {
        if(len[g[st][j]] == 0
           || len[st] + 1 < len[g[st][j]])
        { // in loc de vector de vizualizari, ma uit pe lungimi, ca sa pot trece, daca e nevoie, de mai multe ori prin acelasi loc
            len[g[st][j]] = len[st] + 1;
            findMaxLen(g[st][j], fin);
        }
    }
}

void
dfs(int st, int fin)
{
    viz[st] = 1;
    if(st == fin && len[st] == trueLen)
    {
        int temp = st;
        while(temp)
        {
            out << temp << ' ';
            temp = tata[temp];
        }
        out << '\n';
    }
    for(int i = 0; i < g[st].size(); ++i)
    {
        if(!viz[g[st][i]])
        {
            tata[g[st][i]] = st;
            len[g[st][i]] = len[st] + 1;
            dfs(g[st][i], fin);
            viz[g[st][i]] = 0;
        }
    }
}

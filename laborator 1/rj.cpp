/*
	Problema:https://www.infoarena.ro/problema/rj
	Nr in pdf: 3 B
	Punctaj: 100
	Observatii: Nimic special, o problema simpla
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

ifstream in("rj.in");
ofstream out("rj.out");

const size_t MAXN = 101, MAXM = 101;
int oras[MAXN][MAXM], r[MAXN][MAXM], jul[MAXN][MAXM];
const int dx[] = {1, 1, 0, -1, -1, -1,  0,   1};
const int dy[] = {0, 1, 1,  1,  0, -1, -1, -1};
int n, m;
int ri, rj, ji, jj;


void parcurge(int i, int j, int (*dist)[MAXM]);
void check();
int main()
{
    in >> n >> m;
    char dummy[MAXM];
    in.getline(dummy, MAXM);
    /*
     -100 = inpasabil
     0 = se poate trece\romeo\julieta
    */
    for(int i = 1; i <= n; ++i)
    {
        char linie[MAXM];
        in.getline(linie, (size_t)(m+1) * sizeof(char));
        for(int j = 0; j < m; ++j)
        {
            if(linie[j] == 'R')
            {
                ri = i;
                rj = j + 1;
                oras[i][j + 1] = 0;
            }
            else if(linie[j] == 'J')
            {
                ji = i;
                jj = j + 1;
                oras[i][j + 1] = 0;
            }
            else if(linie[j] == ' ')
            {
                oras[i][j + 1] = 0;
            }
            else if(linie[j] == 'X')
            {
                oras[i][j + 1] = -100;
            }
        }
    }

    parcurge(ri, rj, r);
    parcurge(ji, jj, jul);
    check();
	return 0;
}

void parcurge(int si, int sj, int (*dist)[MAXM])
{
    queue<pair<int, int>> coada;
    coada.push({si, sj});
    dist[si][sj] = 1; // for some reason, in problema si prima casuta e luata in calculul distantei

    while(!coada.empty())
    {
        pair<int, int> cur = coada.front();
        coada.pop();

        for(int i = 0; i < 8; ++i)
        {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx > 0 && ny > 0 && nx <= n && ny <= m)
            {
                if(oras[nx][ny] == 0 && dist[nx][ny] == 0)
                {
                    dist[nx][ny] = dist[cur.first][cur.second] + 1;
                    coada.push({nx, ny});
                }
            }
        }
    }
}

void check()
{
    int minim = 1000000;
    int x, y;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(r[i][j] > 0 && r[i][j] == jul[i][j] && r[i][j] < minim)
            {
                minim = r[i][j];
                x = i;
                y = j;
            }
        }
    }

    out << minim << ' ' << x << ' '<< y;
}

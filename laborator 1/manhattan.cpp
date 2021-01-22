/*
	Nr din pdf: 2 B
	Complexitate: O(p * n * m) -> s-ar putea sa fie un pic mai mica, pt ca in realitate doar primul p face n * m
	Observatii: Ideea e simpla, doar merg din fiecare 1 si actualizez la fiecare 0 distanta, daca e mai mica decat cea curenta.
				Orice idee care nu da raspuns instant la query e clar mai lenta, pt ca q e deja imens.
				p * q = p * n * m, deci orice idee care face p pasi la un query, e la fel de eficienta
				Cred ca se poate face un O(q * logp), dar n-am chef sa o implementez ca oricum sunt sanse mici sa pice asta la examen.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int MAXN = 1001, MAXM = 1001;
int man[MAXN][MAXM], d[MAXN][MAXM]; // in d e distanta pana la cel mai apropiat 1
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int n, m;

void parcurgere(int xi, int xj);
void reconstruct(int xi, int xj);
int main()
{
    in >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            in >> man[i][j];
            if(man[i][j] == 1) d[i][j] = 0;
            else d[i][j] = 20001; // nu putem avea o distanta mai mare, fara ciclaje
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(man[i][j] == 1)
                parcurgere(i, j);
        }
    }

    int reqi, reqj;
    while(in >> reqi >> reqj)
    {
        out << d[reqi][reqj] << ' ';
        reconstruct(reqi, reqj);
    }
	return 0;
}

void parcurgere(int xi, int xj)
{
    queue<pair<int, int>> coada;
    coada.push({xi, xj});

    while(!coada.empty())
    {
        pair<int, int> curent = coada.front();
        coada.pop();

        for(int i = 0; i < 4; ++i) // merg catre toti vecinii
        {
            int nx = curent.first + dx[i];
            int ny = curent.second + dy[i];
            if(nx > 0 && ny > 0 && nx <= n && ny <= m) // locatie valida
            {
                if(d[nx][ny] > d[curent.first][curent.second] + 1)
                {
                    d[nx][ny] = d[curent.first][curent.second] + 1;
                    coada.push({nx, ny});
                }
            }
        }
    }
}

void reconstruct(int xi, int xj)
{
    while(d[xi][xj])
    {
        for(int i = 0; i < 4; ++i)
        {
            int nx = xi + dx[i];
            int ny = xj + dy[i];
            if(nx > 0 && ny > 0 && nx <= n && ny <= m)
            {
                if(d[nx][ny] == d[xi][xj] - 1)
                {
                    xi = nx;
                    xj = ny;
                    break; // kill for
                }
            }
        }
    }
    out << '[' << xi << ", " << xj <<']';
    out << '\n';
}
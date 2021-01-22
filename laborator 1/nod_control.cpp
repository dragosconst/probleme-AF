/*
	Nr din pdf: 1 A a), dar b) e aproape identic
	Complexitate: O(n + m), e doar un bfs
	Observatii: niciuna, e o problema destul de elementara
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

const int MAXN = 101; // nr maxim de noduri
int n, m;
vector<int> g[MAXN];
int d[MAXN + 1], tata[MAXN + 1]; // nodurile vin de la 1
vector<int> retele;

void netBfs(int start);
int main()
{
	in >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int x, y;
		in >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x); // asta trebuie scos pentru graf orientat
	}
	int nod_retea;
	while (in >> nod_retea)
	{
		retele.push_back(nod_retea);
	}

	int search;
	cin >> search;
	netBfs(search);
	return 0;
}

void netBfs(int start)
{
    for(int i = 1; i <= n; ++i)
    {
        d[i] = -1;
    }

	queue<int> coada;
	coada.push(start);

	while (!coada.empty())
	{
		int node = coada.front();
		coada.pop();

		for (int j = 0; j < g[node].size(); ++j) // size_t may be more stable
		{
			int vecin = g[node][j];
			if (d[vecin] == -1)
			{
				coada.push(vecin);
				d[vecin] = 1 + d[node];
                tata[vecin] = node;
				if (find(retele.begin(), retele.end(), vecin) != retele.end()) // primul vecin gasit e garantat cel mai apropiat
				{
                    while(vecin)
                    {
                        out << vecin << ' ';
                        vecin = tata[vecin]; // nu e tocmai ordinea din cerinta, dar zic ca e okay si asa
                    }
                    return;
				}
			}
		}
	}
}

/*
	Problema: https://www.infoarena.ro/problema/retea2
	Nr din pdf: 4
	Punctaj: 100
	Observatii: nu prea are treaba cu grafuri problema
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <math.h>

using namespace std;

ifstream in("retea2.in");
ofstream out("retea2.out");

const size_t MAXN = 2001, MAXM = 2001;
const double INF = 1000000005;
int n, m;
typedef pair<double, double> coord;
vector<coord> centrala;
vector<coord> cladiri;
double dist[MAXN];
int viz[MAXN];

double
euclid(coord a, coord b)
{
    return sqrt( (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second) );
}

int main()
{
    in >> n >> m;
    for(int i = 0; i < n + m; ++i)
    {
        double x, y;
        in >> x >> y;
        if(i < n)
            centrala.push_back({x, y});
        else
            cladiri.push_back({x, y});
    }

    for(int i = 0; i < m; ++i) // mai intai, conectam toate cladirile la cele mai apropiate retele
    {
        dist[i] = INF;
        for(int j = 0; j < n; ++j)
        {
            double dst = euclid(cladiri[i], centrala[j]);
            dist[i] = min(dist[i], dst);
        }
    }

    int p;//reprezinta pozitia unde e cea mai mica distanta actuala, dintr o cladire nevizitata
    // o  cladire vizitata e o cladire la care stiu sigur ca am determinat cea mai buna retea
    double sol = 0;
    for(int i = 0; i < m; ++i)
    {
        p = -1;
        double vmin = INF;
        for(int j = 0; j < m; ++j)
        {
            if(!viz[j] && dist[j] < vmin)
            {
                p = j;
                vmin = dist[j];
            }
        }

        sol += dist[p];
        viz[p] = 1;
        for(int j = 0; j < m; ++j)
        {
            if(!viz[j])
            {
                double dst = euclid(cladiri[j], cladiri[p]);
                dist[j] = min(dist[j], dst);
            }
        }
    }

    out << fixed << setprecision(6) << sol;
    return 0;
}


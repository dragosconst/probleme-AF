/*
	Nr din pdf: 6
	Observatii: e scris exact cum e descris in curs + are si detectare si afisare de circuite negative
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

const size_t MAXN = 101, MAXM = 401, INF = 100000000;
typedef struct truple{
    int first, second, third;
} truple;
vector<truple> muchii;
int d[MAXN], tata[MAXN];
int n, m;

void belfo(int st);
int main()
{
    in >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        int x, y, ct;
        in >> x >> y >> ct;
        muchii.push_back({x, y, ct});
    }

    int x;
    cin >> x;
    belfo(x);
    return 0;
}

void
belfo(int st)
{
    for(int i = 1; i <= n; ++i)
    {
        d[i] = INF;
        tata[i] = 0;
    }
    d[st] = 0;

    int cn = n - 1;
    while(cn)
    { // bellman-ford
        for(truple x: muchii)
        {
            if(d[x.first] + x.third < d[x.second])
            {
                d[x.second] = d[x.first] + x.third;
                tata[x.second] = x.first;
            }
        }
        cn--;
    }

    //detectez circuite
    int cycle = -1;
    for(truple x: muchii)
    {
        if(d[x.first] + x.third < d[x.second])
        {
            d[x.second] = d[x.first] + x.third;
            //tata[x.second] = x.first;
            cycle = x.second;
            break; // am detectat circuit
        }
    }

    if(cycle > 0)
    {
        for(int i = 1; i <=n; ++i) // nu inteleg de ce trebuie sa fac asta
            cycle = tata[cycle];
        out << "Avem circuit: "; // circuitul e afisat in ordine inversa
        int temp = cycle;
        out << temp << ' ';
        temp = tata[temp];
        while(cycle != temp)
        {
            out << temp << ' ';
            temp = tata[temp];
        }
        out << temp << ' ';
    }
    else
    {
        for(int i = 1; i <= n; ++i)
        {
            if(i == st) continue;
            if(tata[i] == 0)
            {
                out << i << " este inaccesibil.\n";
                continue;
            }
            out << "Drum minim pana la " << i <<" : ";
            int temp = i;
            while(temp)
            {
                out << temp << ' ';
                temp = tata[temp];
            }

            out << '\n';
        }
    }
}


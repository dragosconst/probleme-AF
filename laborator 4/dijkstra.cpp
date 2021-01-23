/*
	Problema: https://www.infoarena.ro/problema/dijkstra
	Nr din pdf: 2
	Punctaj: 100
	Observatii: e f asemenator cu Prim
*/

#include <fstream>
#include <vector>
	
using namespace std;
	
ifstream cin("dijkstra.in");
ofstream cout("dijkstra.out");
	
const int DIM = 50001;
const int INF = 100000;
vector<int> a[DIM], c[DIM];	
int poz[DIM], h[DIM], d[DIM], pred[DIM];
int nh, n;

void urca(int p);
void sterge(int p);
void coboara(int p);
void adauga(int val);
void dijkstra(int x0);
	
int main()	
{
    int m;
    cin >> n >> m;
	
    for(int i = 1; i <= m; ++i)
    {
        int x, y, cst;
        cin >> x >> y >> cst;
        a[x].push_back(y);
        c[x].push_back(cst);
    }
	
    dijkstra(1);
    for(int i = 2; i <= n; ++i)
        cout << (d[i] == INF ? 0 : d[i]) << ' ' ;
    return 0;	
}	
 
	
void dijkstra(int x0)	
{
    int x, y, cost;
    for(int i = 1; i <= n; ++i)
    {
        d[i] = INF;
        h[i] = i;
        poz[i] = i;
    }
	
    d[x0] = 0;
    urca(poz[x0]);
    nh = n;
	
    while(nh > 0 && d[h[1]] != INF)
    {
        x = h[1];
        sterge(1);
		
        for(int i = 0; i < a[x].size(); ++i)
        {
            y = a[x][i];
            cost = c[x][i];
            if(d[x] + cost < d[y])
            {
                d[y] = d[x] + cost;
                pred[y] = x;
                urca(poz[y]);
            }
        }
    }
}
	
	
void urca(int p)
{
    while(p > 1 && d[h[p]] < d[h[p / 2]])
    {
        swap(h[p], h[p / 2]);
        poz[h[p]] = p;
        poz[h[p / 2]] = p / 2;
        p /= 2;
    }	
}
	
void coboara(int p)	
{
    int fs = p * 2, fd = p * 2 + 1, bun = p;
	
    if(fs <= nh && d[h[fs]] < d[h[bun]])
    {
        bun = fs;
    }
	
    if(fd <= nh && d[h[fd]] < d[h[bun]])
    {
        bun = fd;
    }
	
    if(bun != p)
    {
        swap(h[bun], h[p]);
        poz[h[p]] = p;
        poz[h[bun]] = bun;
        coboara(bun);
    }	
}
	
void adauga(int val)	
{
    h[++nh] = val;
    urca(nh);
}
	
void sterge(int p)	
{
    swap(h[p], h[nh--]);
    poz[h[p]] = p;
    poz[h[nh + 1]] = nh + 1;
    urca(p);
    coboara(p);	
}
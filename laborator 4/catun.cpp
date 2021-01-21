/*
	Problema: https://www.infoarena.ro/problema/catun
	Punctaj: 100
	Nr in pdf: 4
	Observatii: Am rezolvat-o in liceu, deci imi cer scuze in avans daca sunt unele ciudatenii in cod\ar putea fi optimizat.
				Aveam prostul obicei sa definesc milioane de variabile globale.
*/
#include <fstream>
#include <vector>
	
using namespace std;
	
const int DIM = 36001;
const int INF = 100000;
	
ifstream cin("catun.in");
ofstream cout("catun.out");
	
vector<int> a[DIM], c[DIM];
int poz[DIM], h[DIM], d[DIM], pred[DIM], fort[DIM], af[DIM];	
bool no[DIM];
int nh, n, k;

void urca(int p);
void sterge(int p);
void coboara(int p);
void adauga(int val);
int src(int x);
void dijkstra();
	
int main()	
{
    int m;
    cin >> n >> m >> k;
	
    for(int i = 1; i <= k; ++i)
    {
        cin >> fort[i];
        no[fort[i]] = true;
        af[fort[i]] = fort[i];
    }
    for(int i = 1; i <= m; ++i)
    {
        int x, y, cos;
        cin >> x >> y >> cos;
	
        a[x].push_back(y);
        a[y].push_back(x);
        c[x].push_back(cos);
        c[y].push_back(cos);
    }
	
    dijkstra();
    for(int i = 1; i <= n; ++i)
    {
        if(!no[i])
            cout << af[i] << ' ';
        else
            cout << 0 << ' ';
    }
    return 0;	
}
	
int src(int x)	
{
    if(pred[x] == 0)
        return x;
    return src(pred[x]);
}	
	
void dijkstra()	
{
    int x, y, cost;
	
    for(int i = 1; i <= n; ++i)
    {
        d[i] = INF;
        h[i] = i;
        poz[i] = i;
    }
	
    for(int i = 1; i <= k; ++i)
    {
        d[fort[i]] = 0;
        urca(poz[fort[i]]);
    }
	
    nh = n;
    while(nh > 0 && d[h[1]] != INF)
    {
        x = h[1];
        sterge(1);
        for(int i = 0; i < a[x].size(); ++i)
        {
            y = a[x][i];
            cost = c[x][i];
            if(d[x] + cost < d[y] || (d[x] + cost == d[y] && af[y] > af[x]))
            {
                d[y] = d[x] + cost;
                pred[y] = x;
                af[y] = af[x];
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
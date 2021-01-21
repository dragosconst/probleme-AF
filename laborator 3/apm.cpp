/*
	Problema: https://www.infoarena.ro/problema/apm
	Punctaj: 100
	Nr in pdf: 2
	Observatii: Am rezolvat-o in liceu, deci imi cer scuze in avans daca sunt unele ciudatenii in cod\ar putea fi optimizat.
				Aveam prostul obicei sa definesc milioane de variabile globale.
*/

#include <fstream>
#include <algorithm>
	
using namespace std;
	
ifstream cin("apm.in");
ofstream cout("apm.out");
	
const int DIM = 200001;
struct speci //EDIT: no idea de la ce mi a venit in liceu sa i zic speci? poate special? idk
{
    int nx, ny, cost;
} v[DIM * 2];
	
int t[DIM], h[DIM];
speci af[DIM];
int n, m, S;
	
void uniune(int x, int y);
int rad(int x);
bool isSame(int x, int y);
bool cmp(speci a, speci b)	
{
    return a.cost < b.cost;	
}	
int main()
{
	
    cin >> n >> m;
    for(int i = 1; i <= m; ++i)
		cin >> v[i].nx >> v[i].ny >> v[i].cost;
    sort(v + 1, v + m + 1, cmp);
    int ct = 1;
    for(int i = 1; i <= m && ct <= n - 1; ++i)
    {
        if(!isSame(v[i].nx, v[i].ny))
        {
            uniune(v[i].nx, v[i].ny);
            af[ct].nx = v[i].nx;
            af[ct++].ny = v[i].ny;
            S += v[i].cost;
        }
    }
    cout << S << '\n';
    cout << ct - 1 << '\n';
    for(int i = 1; i < ct; ++i)
        cout << af[i].nx << ' ' << af[i].ny << '\n';
    return 0;	
}
	
int rad(int x)	
{
    if(t[x] == 0)
        return x;
    t[x] = rad(t[x]);
    return t[x];	
}
	
bool isSame(int x, int y)	
{
    if(rad(x) == rad(y))
        return true;
    return false;
}
	
void uniune(int x, int y)	
{
    int rx = rad(x), ry = rad(y);
    if(h[rx] < h[ry])
    {
        t[rx] = ry;
    }
    else
    {
        t[ry] = rx;
        if(h[ry] == h[rx])
            ++h[ry];
    }
}
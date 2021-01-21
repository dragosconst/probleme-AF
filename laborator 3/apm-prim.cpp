/*
	Problema: https://www.infoarena.ro/problema/apm
	Punctaj: 100
	Nr in pdf: 2, dar cu Primm, in loc de Kruskal
	Observatii: Am rezolvat-o in liceu, deci imi cer scuze in avans daca sunt unele ciudatenii in cod\ar putea fi optimizat.
				Aveam prostul obicei sa definesc milioane de variabile globale.
	Implementare: E varianta cu min-heap. Min-heap ul efectiv este h[], iar poz[] e un vector folosit sa tin minte unde in heap
				  se afla fiecare varf din graf, pt ca heap-ul e tinut in memorie ca un vector.
				  "nh" se refera la cate varfuri am in heap, adica cate mai trebuie extrase in arbore.
				  "kt" e folosit pentru vectorul de afisare.
				  "S" vine de la solutie, e costul total al apcm-ul
				  "coboara" si "urca" sunt functii standard de min-heap, schimbate un pic pt Prim in mod specific.
*/
#include <fstream>
#include <vector>
	
using namespace std;
	
ifstream cin("apm.in");
ofstream cout("apm.out");
	
const int DIM = 200001, INF = 10000;
vector<int> a[DIM], c[DIM];
struct afis
{
	
    int nx, ny;
	
} af[DIM];
int h[DIM], d[DIM], poz[DIM], pred[DIM];
bool viz[DIM];
int nh, n, kt = 1;
long long S;
	
void urca(int p);
void sterge(int p);
void coboara(int p);
void adauga(int val);
void prim(int x0);
	
int main()
{
	
    int m;
    cin >> n >> m;
	
    for(int i = 1; i <= m; ++i)
    {
        int x, y, cost;
        cin >> x >> y >> cost;
	
        a[x].push_back(y);
        a[y].push_back(x);
        c[x].push_back(cost);
        c[y].push_back(cost);	
    }

    prim(1);
    cout << S << '\n' << n - 1 << '\n';
	
    for(int i = 1; i < n; ++i)
        cout << af[i].nx << ' ' << af[i].ny << '\n';
    return 0;	
}
	
void prim(int x0)	
{
    int x;
    for(int i = 1; i <= n; ++i)
    {
        d[i] = INF;
        h[i] = i;
        poz[i] = i;
    }
	
    d[x0] = 0;
    urca(poz[x0]);
    nh = n;
	
    while(nh > 0)
    {
        x = h[1];
	
        viz[x] = true;
        if(nh < n)
        {
            af[kt].nx = x;
            af[kt].ny = pred[x];
           // cout << d[x] << endl;
            S += d[x];
            kt++;
        }
	
        sterge(1);
        for(int i = 0; i < a[x].size(); ++i)
        {
            int y = a[x][i];
            if(viz[y]) continue;
	
            int cost = c[x][i];
            if(pred[x] != y && cost < d[y])
            {
                d[y] = cost;
                pred[y] = x;
                urca(poz[y]);
            }
        }
    }	
}
	
void urca(int p)	
{
    while(p > 1 && d[h[p]] < d[h[p / 2]]) // p / 2 e parintele intr-un min-heap
    {
        swap(h[p], h[p / 2]);
        poz[h[p]] = p;
        poz[h[p / 2]] = p / 2;
        p /= 2;
    }	
}
	
void coboara(int p)	
{
    int fs = p * 2, fd = p * 2 + 1, bun = p; // fs = fiu stang, fd = fiu drept
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
	
void sterge(int p)	// stergere standard in min-heap
{
    swap(h[p], h[nh--]);
    poz[h[p]] = p;
    poz[h[nh + 1]] = nh + 1;
    urca(p);
    coboara(p);
}
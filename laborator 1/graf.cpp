/*
	Problema: https://www.infoarena.ro/problema/graf
	Punctaj: 100
	Nr in pdf: 5 de la B
	Observatii: Am rezolvat-o in liceu, deci imi cer scuze in avans daca sunt unele ciudatenii in cod\ar putea fi optimizat.
				Aveam prostul obicei sa definesc milioane de variabile globale.
*/

#include <fstream>
#include <vector>
	
using namespace std;
	
ifstream cin("graf.in");
ofstream cout("graf.out");
	
const int DIM = 100001;
vector<int> a[DIM];	
int m, n, x, y, s, q[DIM], nrx[DIM], dx[DIM], nry[DIM], dy[DIM], st, dr = -1;
void bfs(int s, int d[DIM], int nr[DIM]); //EDIT: aici ar fi mai elegant int* d si int* nr
void citire();
int main()
{
    citire(); 
	
    bfs(x, dx, nrx);
    bfs(y, dy, nry);
    int rez = 0;
    for(int i = 1; i <= n; i++)
    {
        if(dx[i] + dy[i] == dy[x] && nrx[i] * nry[i] == nrx[y]) rez++;
    }
    cout << rez << '\n';
    for(int i = 1; i <= n; i++)
    {
        if(dx[i] + dy[i] == dy[x] && nrx[i] * nry[i] == nrx[y]) cout << i << ' ';
    }
    return 0;	
}
	
 
void citire()	
{
    int b, c;
    cin >> n >> m >> x >> y;
    for(int i = 0; i < m; ++i)
    {
        cin >> b >> c;
        a[b].push_back(c);
        a[c].push_back(b);
    }
}

	
void bfs(int s, int d[DIM], int nr[DIM])	
{	
    int x, y;	
    for(int i = 0; i <= n; ++i)	
    {	
        d[i] = -1;	
    }	
    st = 0;	
    dr = -1;	
    q[++dr] = s;	
    d[s] = 0;	
    nr[s] = 1;
    while(st <= dr)
    {
        x = q[st++];
        for(int i = 0; i < a[x].size(); ++i)
        {
            y = a[x][i];
            if(d[y] == -1)
            {
                q[++dr] = y;	
                d[y] = 1 + d[x];
                nr[y] = nr[x];
            }
            else if(d[y] == 1 + d[x])
            {
                nr[y] += nr[x];
            }
        }
    }
}
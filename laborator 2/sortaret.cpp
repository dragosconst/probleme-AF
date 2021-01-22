/*
	Problema: https://www.infoarena.ro/problema/sortaret
	Punctaj: 100
	Nr in pdf: 1 de la ultima sectiune din pdf
	Observatii: Am rezolvat-o in liceu, deci imi cer scuze in avans daca sunt unele ciudatenii in cod\ar putea fi optimizat.
				Aveam prostul obicei sa definesc milioane de variabile globale.
*/

#include <fstream>
	
using namespace std;
	
ifstream cin("sortaret.in");
ofstream cout("sortaret.out");
	
const int MAXN = 50001, MAXM = 100001;
	
int lst[MAXN], vf[MAXM], urm[MAXM], viz[MAXN],  af[MAXN];
int n, m, nr, cnt;
	
void adauga(int, int);
void dfsTop(int x);
int main()	
{
    cin >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        adauga(x, y);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!viz[i])
            dfsTop(i);
    }
    for(int i = cnt; i >= 1; --i)
    {
        cout << af[i] << ' ';
    }
    return 0;	
}
	

// lst o sa pointeze la "cel mai din dreapta" varf adiacent, stocat in vf, in ordinea intrarilor
// folosind urm, care mai bine era denumit pred, putem merge inapoi pe lista de adiacenta (care e vf)
// 0 in urm inseamna ca e ultimul varf in care putem ajunge
// avantajul implementarii statice e eficienta de spatiu si timp, pentru ca nu se mai face overhead la 
// adaugarea de muchii noi (decat cu vectorul urm, dar o atribuire e nesemnificativa in comparatie
// cu operatii de tip malloc), ca la vector sau alocare dinamica
// castigam spatiu prin numarul minim de metadate necesare (un vector sau o structura alocata dinamic
// consuma mai mult ca un simplu array) 

void adauga(int x, int y)	
{
    ++nr;
    vf[nr] = y;
    urm[nr] = lst[x];
    lst[x] = nr;	
}
 

	
void dfsTop(int x)	
{
    int p, y;
    viz[x] = 1;
    p = lst[x];
    while(p)
    {
        y = vf[p];	
        if(!viz[y])
        {
            dfsTop(y);
        }
        p = urm[p];
    }
    af[++cnt] = x;
}
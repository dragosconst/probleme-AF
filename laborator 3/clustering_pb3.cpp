#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 200005
#define MAX_LEN 105

ifstream f("cuvinte.in");
ofstream g("cuvinte.out");

struct muchie
{
    int c, x, y;
};

int tata[MAX_N], rang[MAX_N], dp[MAX_LEN][MAX_LEN];

int distLev(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
        }
    }

    return dp[n][m];
}


bool comp(muchie i, muchie j)
{
    return i.c < j.c;
}

int Find(int x)
{
    while (tata[x] != x)
        x = tata[tata[x]];
    return x;
}

/* True daca s-a facut reuniunea
   False daca apartin aceleasi multimi
*/
bool Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x != y)
    {
        if (rang[x] <= rang[y])
        {
            tata[x] = y;
            rang[y] += rang[x];
        }
        else
        {
            tata[y] = x;
            rang[x] += rang[y];
        }

        return true;
    }

    return false;
}

int main()
{
    int n, m, x, y, c;
    int cost = 0, k = 3, nr, sep = INT_MAX; // k e numarul de clase
    string cuv;
    vector<muchie> muchii;
    vector<string> cuvinte;

    while (f >> cuv)
    {
        cuvinte.push_back(cuv);
    }
    n = cuvinte.size();

    //muchii.resize(m);
    for (size_t i = 0; i < cuvinte.size(); i++)
    {
        for (size_t j = i + 1; j < cuvinte.size(); j++)
        {
            muchii.push_back({distLev(cuvinte[i], cuvinte[j]), i, j});
        }
    }
    sort(muchii.begin(), muchii.end(), comp);
    for (int i = 0; i < n; i++)
    {
        tata[i] = i;
        rang[i] = 1;
    }

    nr = n;
    for (muchie m : muchii)
    {
        x = m.x;
        y = m.y;
        if (Union(x, y))
        {
            cost += m.c;
            nr--;
            if (nr == k)
                break;
        }
    }

    for (muchie m : muchii)
    {
        x = m.x;
        y = m.y;

        if (Find(x) != Find(y))
            sep = min(sep, distLev(cuvinte[x], cuvinte[y]));
    }

    cout << "Gradul de separabilitate: " << sep << '\n';
    for (int i = 0; i < n; i++)
    {
        if (tata[i] == i)
        {
            for (int j = 0; j < n; j++)
            {
                if (Find(j) == i)
                {
                    cout << cuvinte[j] << ' ';
                }
            }
            cout << '\n';
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long a, b;
    cin >> a >> b;

    vector<long long> path;

    while(b > a)
    {
        path.push_back(b);

        if(b % 10 == 1)
        {
            b /= 10;
        }
        else if(b % 2 == 0)
        {
            b /= 2;
        }
        else
        {
            cout << "NO\n";
            return 0;
        }
    }

    if(b != a)
    {
        cout << "NO\n";
        return 0;
    }

    path.push_back(a);

    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << "\n";

    for(long long x : path)
        cout << x << " ";

    cout << "\n";
}
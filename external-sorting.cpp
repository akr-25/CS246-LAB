#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

void merge_array(vvll &runs, vll &temp)
{
    vll pointer;
    ll num = 0;
    for (ll i = 0; i < runs.size(); i++)
    {
        pointer.push_back(0);
        num += runs[i].size();
    }

    for (ll i = 0; i < num; i++)
    {
        ll min = INT_MAX;
        ll k = 0;
        for (ll j = 0; j < pointer.size(); j++)
        {
            if (pointer[j] < runs[j].size() && runs[j][pointer[j]] < min)
            {
                min = runs[j][pointer[j]];
                k = j;
            }
        }
        temp.push_back(min);
        pointer[k]++;
    }
}

void XternalSort(vvll &runs, ll B)
{
    // Intially sorting each page
    for (ll i = 0; i < runs.size(); i++)
    {
        sort(runs[i].begin(), runs[i].end());
    }

    while (runs.size() > 1)
    {
        vvll newruns;
        ll k = 0;
        ll i = 0;
        while (i < runs.size())
        {
            vvll temp;
            for (k = 0; k < B - 1 && i + k < runs.size(); k++)
            {
                temp.push_back(runs[i + k]);
            }
            vll temp1;
            // Merging B-1 runs
            merge_array(temp, temp1);
            newruns.push_back(temp1);
            i += k;
        }
        runs = newruns;
    }
}

int main()
{
    ll B, bucketSize, records;
    cin >> B >> bucketSize >> records;
    vvll runs;
    ll k = 0;
    ll i = 0;
    while (i < records)
    {
        vll v;
        for (k = 0; k < bucketSize && i + k < records; k++)
        {
            ll a;
            cin >> a;
            v.push_back(a);
        }
        runs.push_back(v);
        i += k;
    }

    XternalSort(runs, B);
    for (ll i = 0; i < runs[0].size(); i++)
    {
        cout << runs[0][i] << endl;
    }
    return 0;
}

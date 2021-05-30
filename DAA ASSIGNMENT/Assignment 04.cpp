#include<bits/stdc++.h>
using namespace std;

bool comparator(const vector<int> &a, const vector<int> &b)
{
    return (int)a.size() < (int)b.size();
}

int Cin()
{
    int n;
    char c;

    while (1)
    {
        if (scanf("%d", &n) != 1)
        {
            while ((c = getchar()) != EOF && c != '\n');
            cout << ("Invalid Input.Re-enter : ");
        }
        else
            break;
    }
    return n;
}

void print(map<int, vector<int>> p, map<map<int, vector<int>>, map<int, vector<int>>> *path)
{
    map<int, vector<int>>::iterator i;

    for (i = p.begin(); i != p.end(); i++)
    {
        int st = i->first;
        cout << st << "->";
        vector<int> t = i->second;
        if (!t.size())
            return;
        map<int, vector<int>> tt = path->at(p);
        print(tt, path);
    }
}

void tsp(vector<int> cities, vector<vector<int>>cost_mat, map<map<int, vector<int>>, int> *dp, map<map<int, vector<int>>, map<int, vector<int>>> *path)
{
    vector<vector<int>> all_subsets; //to store all the all_subsets of cities
    vector<int> ss, copy, fv;
    int current_city, cost, l, temp, fst;
    int n = cities.size();

    for (int i = 0; i < (int)pow(2, n); i++)
    {
        vector<int> set;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                set.push_back(cities[j]);
        }
        all_subsets.push_back(set);
    }

    sort(all_subsets.begin(), all_subsets.end(), comparator);

    int set_size = -1;

    for (int i = 0; i < all_subsets.size(); i++)
    {
        if ((int)all_subsets[i].size() != set_size)
        {
            set_size = (int)all_subsets[i].size();
            cout << "\n |S| = " << set_size << "\n";
        }

        for (int j = 0; j < n; j++)
        {
            current_city = cities[j];
            ss = all_subsets[i];

            if (ss.size() == n) //when reached the final of all_subsets
            {
                current_city = 1;

                if (j != 0)
                    break;
            }

            if (find(ss.begin(), ss.end(), current_city) == ss.end())
            {
                map<int, vector<int>> subpath;
                subpath.insert({current_city, ss});

                cost = INT_MAX;
                fst = current_city;
                if (ss.size() == 0) //from a city to NULL set
                {
                    if (cost_mat[current_city - 1][0] != -1)
                        cost = cost_mat[current_city - 1][0];
                }
                else
                {
                    for (int k = 0; k < ss.size(); k++)
                    {
                        copy = ss;
                        l = ss[k];

                        copy.erase(copy.begin() + k);

                        map<int, vector<int>> cc;
                        cc.insert({l, copy});

                        if (cost_mat[current_city - 1][l - 1] == -1 || dp->at(cc) == INT_MAX)
                            temp = INT_MAX;
                        else
                            temp = cost_mat[current_city - 1][l - 1] + dp->at(cc);

                        if (temp < cost)
                        {
                            cost = temp;
                            fst = l;
                            fv = copy;
                        }
                    }
                }

                cout << "g(" << current_city << ",{ ";

                for (int k = 0; k < (int)ss.size(); k++)
                    cout << ss[k] << " ";

                if (cost == INT_MAX)
                    cout << "}) = INF" << endl;
                else
                    cout << "}) = " << cost << endl;

                map<int, vector<int>> m;
                m.insert({fst, fv});

                path->insert({subpath, m});
                dp->insert({subpath, cost});
            }
        }
    }
}

int main()
{
    map<map<int, vector<int>>, int> dp;
    map<map<int, vector<int>>, map<int, vector<int>>> path;
    vector<int> cities;

    int no_of_cities, i, j;

    cout << "\nEnter number of cities : ";
    no_of_cities = Cin();

    while (no_of_cities <= 0)
    {
        no_of_cities = Cin();
    }

    vector< vector<int> > cost_mat(no_of_cities , vector<int> (no_of_cities , 0));

    cout << "\nEnter Adjacency matrix row wise (-1 for INF )\n";

    for (i = 0; i < no_of_cities; i++)
    {
        for (j = 0; j < no_of_cities; j++)
        {
            cost_mat[i][j] = Cin();
        }
    }

    for (i = 2; i <= no_of_cities; i++)
        cities.push_back(i);

    tsp(cities, cost_mat, &dp, &path);

    map<int, vector<int>> hh, hh1;

    hh.insert({1, cities});

    if (dp.at(hh) >= INT_MAX)
        cout << endl
             << "Tour not possible" << endl;
    else
    {
        cout << endl
             << "Cost :: " << dp.at(hh) << endl;
        hh1 = path.at(hh);
        cout << "\nPATH\n"
             << 1 << "->";
        print(hh1, &path);
        cout << 1 << "\n";
    }

    return 0;
}

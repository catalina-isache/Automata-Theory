#include <bits/stdc++.h>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

map<int, int> noduri;
vector<pair<int, char> > G[1000];

bool F[1000];

bool bfs(int nod_inceput, string cuvant);

int main() {
    int N, M, x, y, S, nrF, nrCuv, i;
    char l;
    string c;
    fin >> N;
    for (i = 1; i <= N; i++) {
        fin >> x;
        noduri.insert({x, i});
    }
    fin >> M;
    for (i = 1; i <= M; i++) {
        fin >> x >> y >> l;
        x = noduri[x];
        y = noduri[y];
        G[x].push_back({y, l});
    }
    fin >> S;
    S = noduri[S];
    fin >> nrF;
    for (i = 1; i <= nrF; i++) {
        fin >> x;
        x = noduri[x];
        F[x] = 1;
    }
    fin >> nrCuv;
    for (i = 1; i <= nrCuv; i++) {
        fin >> c;
        reverse(c.begin(), c.end());
        if (bfs(S, c)) {
            fout << "DA\n";
        } else {
            fout << "NU\n";
        }
    }
    return 0;
}


bool bfs(int nod_inceput, string cuvant) {
    int nod;
    string cuv, cuvant_nou;
    char litera;

    queue<pair<int, string>> Q;
    Q.push({nod_inceput, cuvant});

    while (!Q.empty()) {
        nod = Q.front().first;
        cuv = Q.front().second;
        Q.pop();
        if (cuv.empty() && F[nod])
            return 1;
        if (cuv.empty())
            continue;

        litera = cuv.back();
        cuv.pop_back();
        cuvant_nou = cuv;

        for (int i = 0; i < G[nod].size(); i++) {
            if (G[nod][i].second == litera) {
                Q.push({G[nod][i].first, cuvant_nou});
            }
        }
    }
    return 0;
}

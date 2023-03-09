#include <bits/stdc++.h>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

map<int, int> noduri;
vector<pair<int, char> > G[1000];
string cuvant;
bool F[1000];

bool dfs(int node, string word);

int main() {
    int N, M, x, y, S, nrF, nrCuv, i;
    char l;
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
        fin >> cuvant;
        reverse(cuvant.begin(), cuvant.end());
        if (dfs(S, cuvant)) {
            fout << "DA\n";
        } else {
            fout << "NU\n";
        }
    }
    return 0;
}

bool dfs(int nod, string cuvant) {
    if (!cuvant.length()) {
        if (F[nod])
            return 1;
        else return 0;
    } else {
        bool ok = 0;

        string cuvant_nou;
        char litera = cuvant.back();
        cuvant.pop_back();
        cuvant_nou = cuvant;

        for (int i = 0; i < G[nod].size(); i++) {
            if (G[nod][i].second == litera) {
                ok = dfs(G[nod][i].first, cuvant_nou);
            }
        }
        return ok;
    }
}

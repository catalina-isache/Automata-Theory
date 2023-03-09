#include <bits/stdc++.h>

using namespace std;
//ifstream cin("input.txt");
//ofstream cout("output.txt");

vector<pair<int, char> > G[1000];
vector<int> traseu;
vector<int> tata;
bool F[1000];
bool fr[1000][1000];

bool bfs(int nod_inceput, string cuvant);

int main() {
    int N, M, x, y, S, nrF, nrCuv, i;
    char l;
    string c;
    cin >> N;
    for (i = 1; i <= N; i++) {
        tata.push_back(-1);
    }
    cin >> M;
    for (i = 1; i <= M; i++) {
        cin >> x >> y >> l;
        G[x].push_back({y, l});
    }
    cin >> S;
    cin >> nrF;
    for (i = 1; i <= nrF; i++) {
        cin >> x;
        F[x] = 1;
    }
    cin >> nrCuv;
    for (i = 1; i <= nrCuv; i++) {
        cin >> c;
        int lg=c.size();
        reverse(c.begin(), c.end());
        if (bfs(S, c)) {
            cout << "DA\n";
            for (int i = traseu.size() - 1; i >= 0; --i) {
                cout<<traseu[i]<<" ";
            }
            cout<<'\n';
        } else {
            cout << "NU\n";
        }
        for(int k=0;k<N;k++)
            for(int j=0;j<=lg;j++)
                fr[k][j]=0;
    }
    return 0;
}


bool bfs(int nod_inceput, string cuvant) {
    int nod;
    string cuv, cuvant_nou;
    char litera;
    traseu.clear();
    queue<pair<int, string>> Q;
    vector < pair <int,int> > tata;
    tata.push_back({0,nod_inceput});
    Q.push({nod_inceput, cuvant});
    int numar_stare=-1;
    while (!Q.empty()) {
        numar_stare++;
        nod = Q.front().first;
        cuv = Q.front().second;
        //cout<<nod<<" "<<cuv<<'\n';
        Q.pop();
        if (cuv.empty() && F[nod]) {
            int stare_anterioara=tata[numar_stare].first;
            int nod_curent=tata[numar_stare].second;
            traseu.push_back(nod_curent);
            while (stare_anterioara != 0) {
                nod_curent=tata[stare_anterioara].second;
                traseu.push_back(nod_curent);
                stare_anterioara=tata[stare_anterioara].first;

            }
            traseu.push_back(nod_inceput);
            return 1;
        }
        int lg=cuv.size();
        fr[nod][lg]=1;
        if (!cuv.empty()) {

            litera = cuv.back();
            cuv.pop_back();
            cuvant_nou = cuv;
        }
        else{
            litera= NULL;
            cuvant_nou="";
        }
        for (int i = 0; i < G[nod].size(); i++) {
            if (G[nod][i].second == litera && !fr[G[nod][i].first][lg-1]) {
                tata.push_back( {numar_stare,G[nod][i].first} ) ;
                Q.push({G[nod][i].first, cuvant_nou});
            }
            else if(G[nod][i].second == '0' && !fr[G[nod][i].first][lg]){
                tata.push_back( {numar_stare,G[nod][i].first} ) ;
                Q.push({G[nod][i].first, cuvant_nou+litera});
            }
        }
    }
    return 0;
}
/*
6
10
0 1 a
0 2 0
1 1 b
1 3 0
2 2 b
2 4 c
3 5 c
3 2 0
2 1 0
4 5 c
0
1 5
5
bbbbcc
cc
baaaabac
ac
ababaaa

*/

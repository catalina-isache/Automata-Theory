#include <iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;
vector<int> traseu;

class Automat {
protected:
    int nr_noduri;
    vector<vector<pair<int, char> > >G;
    int nr_muchii;
    int nr_stari_finale;
    int stare_initiala;
    vector<int> stari_finale;

public:
     Automat (int nr_noduri_=0, int nr_muchii_=0, int nr_stari_finale_=0){
        this->nr_noduri=nr_noduri_;
        this->nr_muchii=nr_muchii_;
        this->nr_stari_finale=nr_stari_finale_;
        G.resize(nr_noduri_);
        stari_finale.resize(nr_noduri);
    }
     Automat (const Automat  &A){
         this->nr_noduri=A.nr_noduri;
         this->nr_muchii=A.nr_muchii;
         this->nr_stari_finale=A.nr_stari_finale;
         this->stare_initiala=A.stare_initiala;
         G.resize(A.nr_noduri);
         for(int i=0; i<A.nr_noduri; i++)
             for(int j=0;j< A.G[i].size(); j++)
                 G[i][j]=A.G[i][j];
         stari_finale.resize(A.nr_stari_finale);
         for(int i=0; i<A.stari_finale.size(); i++)
             stari_finale[i]=A.stari_finale[i];
    }
     ~Automat (){
    }

    void   set_nr_noduri(int nr_noduri_) {
        nr_noduri = nr_noduri_;
    }

    void  set_nr_stari_finale(int nr_stari_finale_) {
        nr_stari_finale = nr_stari_finale_;
    }
    void  set_stare_initiala(int stare_initiala_) {
        stare_initiala = stare_initiala_;
    }
    void   set_nr_muchii(int nr_muchii_){
        nr_muchii= nr_muchii_;
    }

    int get_nr_noduri() const {
        return nr_noduri;
    }
    int get_nr_stari_finale() const {
        return nr_stari_finale;
    }
    int  get_stare_initiala() const {
        return stare_initiala;
    }
    int get_nr_muchii() const{
        return nr_muchii;
    }

    Automat  & operator=(const Automat  &A) {
        this->nr_noduri=A.nr_noduri;
        this->nr_muchii=A.nr_muchii;
        this->nr_stari_finale=A.nr_stari_finale;
        this->stare_initiala=A.stare_initiala;
        G.resize(A.nr_noduri);
        for(int i=0; i<A.nr_noduri; i++)
            for(int j=0;j< A.G[i].size(); j++)
                G[i][j]=A.G[i][j];
        stari_finale.resize(A.nr_stari_finale);
        for(int i=0; i<A.stari_finale.size(); i++)
            stari_finale[i]=A.stari_finale[i];
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os,const Automat  &A) {
        os<<"Nr noduri: "<<A.nr_noduri<<'\n'<<"Nr muchii: "<<A.nr_muchii<<'\n'<<"Stare_initiala: "<<A.stare_initiala<<'\n'<<"Stari finale: ";
        for(int i=0; i<A.stari_finale.size(); i++)
            os<<A.stari_finale[i]<<" ";
        os<<'\n';
        os<<"Muchii: "<<'\n';
        for(int i=0; i<A.nr_noduri; i++)
            for(int j=0;j< A.G[i].size(); j++)
                os<<i<<" "<<A.G[i][j].first<<" "<<A.G[i][j].second<<'\n';
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Automat  &A) {
        cout<<"Nr noduri: ";
        is>>A.nr_noduri;
        A.G.resize(A.nr_noduri);
        cout<<'\n'<<"Nr muchii: ";
        is>>A.nr_muchii;
        cout<<'\n'<<"Muchii:";
        int x,y;
        char l;
        for (int i = 1; i <= A.nr_muchii; i++) {
            cin >> x >> y >> l;
            A.G[x].push_back({y, l});
        }

        cout<<"Stare_initiala: ";
        is>>A.stare_initiala;
        cout<<'\n';
        cout<<"Nr stari finale: ";
        is>>A.nr_stari_finale;
        for(int i=0; i<A.nr_noduri; i++)
            A.stari_finale.push_back(0);
        cout<<'\n'<<"Stari finale: ";
        for(int i=0; i<A.nr_stari_finale; i++){
            is>>x;
            A.stari_finale[x]=1;
        }
        return is;
    }

    void verificare(string c){
        reverse(c.begin(), c.end());
        if (parcurgere(c)){
            cout << "DA\n";
            for (int i = traseu.size() - 1; i >= 0; --i) {
                cout<<traseu[i]<<" ";
            }
            cout<<'\n';
        }
        else cout << "NU\n";

     }
     virtual bool parcurgere(string c){

     }
};


class NFA: public Automat {
public:
    bool parcurgere(string cuvant){
        return bfs(cuvant);
    }
    bool bfs(string cuvant){
        traseu.clear();
        int nod;
        string cuv, cuvant_nou;
        char litera;
        bool fr[1000][1000];
        for(int k=0;k<nr_noduri;k++)
            for(int j=0;j<=cuvant.size();j++)
                fr[k][j]=0;

        queue<pair<int, string>> Q;
        vector < pair <int,int> > tata;
        tata.push_back({0,stare_initiala});
        Q.push({stare_initiala, cuvant});
        int numar_stare=-1;
        while (!Q.empty()) {
            numar_stare++;
            nod = Q.front().first;
            cuv = Q.front().second;
            //cout<<nod<<" "<<cuv<<'\n';
            Q.pop();
            if (cuv.empty() && stari_finale[nod]) {
                int stare_anterioara=tata[numar_stare].first;
                int nod_curent=tata[numar_stare].second;
                traseu.push_back(nod_curent);
                while (stare_anterioara != 0) {
                    nod_curent=tata[stare_anterioara].second;
                    traseu.push_back(nod_curent);
                    stare_anterioara=tata[stare_anterioara].first;

                }
                traseu.push_back(stare_initiala);
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
                else if(G[nod][i].second == '$' && !fr[G[nod][i].first][lg]){
                    tata.push_back( {numar_stare,G[nod][i].first} ) ;
                    Q.push({G[nod][i].first, cuvant_nou+litera});
                }
            }
        }
        return 0;
    }
};

class DFA: public Automat{
public:
    bool parcurgere(string cuvant){
        return dfs(stare_initiala,cuvant);
    }
    bool dfs(int nod, string cuvant) {
        if (!cuvant.length()) {
            if (stari_finale[nod])
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

};



int main() {
    int nrCuv;
    string c;
    NFA automat_NFA;
    cin >> reinterpret_cast<Automat &>(automat_NFA);
    cout<<"Nr cuvinte: ";
    cin>>nrCuv;
    cout<<'\n'<<"Cuvinte: ";
    for (int i = 1; i <= nrCuv; i++) {
        cin >> c;
        automat_NFA.verificare(c);
    }
    return 0;
}

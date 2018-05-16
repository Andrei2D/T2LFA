#include "de_inclus.h"

using namespace std;

///ALT+156 - SIMBOLUL PENTRU LAMBDA
///aka LIRA ELVETIANA £
///...
///BAA NU... $ E LAMBDA ACUM..
class Stare
{
    vector <int> id;
    vector< vector <int> > Functie;
    bool fin;
public:
    Stare();
    ~Stare();
    ///SET
    void set_alfabet(int,int);
    void set_fin (){fin=1;}
    void set_nume(int,int);
    ///GET
    vector <int>& get_id() {return id;}
    vector<int> operator[] (int x) {return Functie[x];}
    void afisare();
    ///OPERATORI
    Stare& operator+= (Stare& st);
    bool operator== (Stare& st);
    bool operator== (vector<int>&);
    bool operator!=(Stare& st);
    bool operator!= (vector<int>&);
    Stare& operator= (const Stare& st);
    ///ALTELE
    int st_nevida(){if(id[0]!=0)return 1; else return 0;}
    vector<int> reuniune (vector<int>& v1,vector<int>& v2);
};

Stare::Stare()
{

    Functie.resize(1);
    Functie[0].resize(1);
    Functie[0][0]=0;
    id.resize(1);
    id[0]=0;
    fin=0;
}

void Stare::set_nume(int ord=0, int nr_ab=0)
{///DACA E STARE NOUA, O SETEAZA
 ///DACA E STARE CE DEJA ARE UN NUME, ATUNCI II ADAUGA CELALALT NUME
    ///SI ACTUALIZEAZA CELELALTE DATE
    if(id.size()==1 && id[0]==0)
    {

        Functie.resize(nr_ab);
        for(int i=0;i<Functie.size();i++)
            Functie[i].resize(1,0);
        id[0]=ord;
    }
    else
    {
        id.push_back(ord);
        sort(id.begin(),id.end());
    }
}

///MERGE SUPRAINCARCATA CU (char*, int)
void Stare::set_alfabet(int prin_litera, int in_stare)
{
    if(prin_litera!=-1)
    {
    if(Functie[prin_litera][0]==0) Functie[prin_litera][0]=in_stare;
    else
        {
        Functie[prin_litera].resize(Functie[prin_litera].size()+1);
        Functie[prin_litera][Functie[prin_litera].size()-1]=in_stare;
        }
    }
    sort(Functie[prin_litera].begin(),Functie[prin_litera].end());
}

/*
Stare& Stare::operator+= (Stare& st)
{//////////////////////////
    vector < int > aux;
    int k=0;

    if(st.id[0]!=0)
    for(int j=0;j<id.size();j++)
    {
        if(id[j]>st.id[k])
            {
                aux.push_back(st.id[k++]);
                j--;
            }
            if(id[j]==st.id[k]) k++;
    }

    if(st.id[k]>id[id.size()-1])
        for(;k<st.id.size();k++) aux.push_back(st.id[k]);
///
    aux.clear();
    for(int i=1;i<Functie.size();i++)
    {
        if(Functie[i][0]!=0)
        for(int j=0;j<Functie[i].size();j++)
            aux.push_back(Functie[i][j]);

        if(st.Functie[i][0]!=0)
        k=0;
        for(int j=0;j<Functie[i].size();j++)
        {
            if(Functie[i][j]>st.Functie[i][k])
                {
                    aux.push_back(st.Functie[i][k++]);
                    j--;
                }
                if(Functie[i][j]==st.Functie[i][k]) k++;
        }

        if(st.Functie[i][k]>Functie[i][Functie[i].size()-1])
            for(;k<st.Functie[i].size();k++) aux.push_back(st.Functie[i][k]);

        sort(aux.begin(),aux.end());
        Functie[i].clear();
        Functie[i]=aux;
    }

}*/

vector<int> Stare::reuniune (vector<int>& v1,vector<int>& v2)
{
    vector<int> R=v1;
    for(int i=0;i<v2.size();i++) R.push_back(v2[i]);
    sort(R.begin(),R.end());
    int cate=0;
    for(int i=1;i<R.size();i++)
        if(R[i-1]==0)
            {
                R[i-1]=INT_MAX;
                cate++;
                continue;
            }
        else
        if(R[i-1]==R[i])
        {
            R[i]=INT_MAX;
            cate++;
        }
    sort(R.begin(),R.end());
    R.resize(R.size()-cate);
    return R;
}

Stare& Stare::operator+= (Stare& st)
{
    if(Functie.size()==1)
    {
        *this = st;
        return *this;
    }

    if(id[0]==0) id=st.id;
    else id=reuniune(id,st.id);


    for(int i=1;i<Functie.size();i++)
    {
        Functie[i]=reuniune(Functie[i],st.Functie[i]);
    }
    if(fin || st.fin) fin=true;
    return *this;
}

void Stare::afisare()
{
cout<<"Id-ul: "<<id[0];
for(int i=1;i<id.size();i++)
    cout<<", "<<id[i];
cout<<"\n";
    cout<<"Functiile: \n";
    for(int i=1;i<Functie.size();i++)
    {   cout<<i<<" : ";
        for(int j=0;j<Functie[i].size();j++)
            cout<<Functie[i][j]<<" ";
        cout<<"\n";
    }
    if(fin)cout<<"FINALA!\n";
    cout<<"\n";
}

bool Stare::operator==(vector<int>& vc)
{
    if(id.size()!=vc.size()) return false;
    for(int i=0;i<id.size();i++)
        if(id[i]!=vc[i]) return false;
    return true;
}

bool Stare::operator==(Stare& st)
{
    return *this == st.id;
}

bool Stare::operator!=(vector<int>& vc)
{
    return !(*this == vc);
}

bool Stare::operator!=(Stare& st)
{
    return !(*this == st.id);
}

Stare& Stare::operator= (const Stare& st)
{

    id=st.id;
    Functie.resize(st.Functie.size());
    for(int i=0;i<Functie.size();i++)
        Functie[i]=st.Functie[i];
    fin=st.fin;
    return *this;
}

Stare::~Stare()
{
    id.clear();
    for(int i=0;i<Functie.size();i++)
        Functie[i].clear();
    Functie.clear();
}


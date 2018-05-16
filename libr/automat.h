
#include "stare.h"


class Automat
{
    vector <Stare> Q;
    vector <vector <string> > Nume;
    vector<string> Alfabet;
    int start;
public:
    Automat(char*,char*);
    ~Automat();
    Automat& AFD (Automat& A);
    bool nu_exista (Stare&);
    void afis();
};

Automat::Automat(char* f_autom=NULL, char* f_muchii=NULL)
{
    Q.resize(1);    ///STAREA NULA, PE Q[0]
    Nume.resize(1);
    Nume[0].push_back("Stare_vida");
    Alfabet.resize(1);
    Alfabet[0]="$\0";
    start=0;
if(f_autom!=NULL)
{
    ifstream fin (f_autom);
    char *sttr=new char[200];
    char *alfab=new char[200];
    char *stin=new char[50];
    char *stfin=new char[200];
    fin.getline(sttr,199);/// \n
    fin.getline(alfab,199);
    fin.getline(stin,49);
    fin.getline(stfin,199);
    fin.close();

    char *p;
    p=strtok(sttr," \n,");
    int k=0;
    while(p!=NULL)
    {
        Nume.resize(Nume.size()+1);
        Nume[++k].push_back(p);
        p=strtok(NULL," \n,");
    }

    Q.resize(k+1);                  ///STARI NUMARATE + STAREA NULA

    p=strtok(alfab," \n,");
    while(p!=NULL)                  ///ALFABETUL;
    {                               ///IMI TREBUIE LUNGIMEA PENTRU
                                    ///TABELELE CU FUNCTII ALE STARILOR
        Alfabet.resize(Alfabet.size()+1);
        Alfabet[Alfabet.size()-1]=p;
        p=strtok(NULL," \n,");
    }
/*    int ord=0;
    p=strtok(sttr," \n,");
    while(p!=NULL)              ///STARILE
    {ord++;
        Q[ord].set_nume(ord,Alfabet.size());
        if(strcmp(p,stin)==0) start=ord;
        p=strtok(NULL," \n,");
    }
*/
    for(int i=1;i<Nume.size();i++)      ///CLS STARE SI INIT
    {
        Q[i].set_nume(i,Alfabet.size());
        if(Nume[i][0]==stin) start=i;
    }

                    ///STARI FINALE SI INIT
    p=strtok(stfin," \n,");
    while(p!=NULL)
    {
        for(int i=Nume.size()-1;i>=1;i--)           ///DE INCEPUT DE LA 0 PENTRU LAMBDA
                if(p==Nume[i][0])
                    {
                        Q[i].set_fin();
                        break;
                    }
        p=strtok(NULL," \n,");

    }


delete[] sttr;
delete[] alfab;
delete[] stin;
delete[] stfin;

}

if(f_muchii!=NULL)
{
    ifstream fi (f_muchii);
    string v;
    getline(fi,v);

    while(!fi.eof() && v[0]!='\0')
    {
        istringstream bucati(v);

        string din, in, prin;
        getline(bucati,din,' ');

//        din=new char[strlen(p)+1];
//        strcpy(din,p);
//        p=strtok(NULL," ");

        getline(bucati,prin,' ');

//        prin=new char[strlen(p)+1];
//        strcpy(prin,p);
//        p=strtok(NULL," \n\0");

        getline(bucati,in,' ');

//        in=new char[strlen(p)+1];
//        strcpy(in,p);

        int id_din=0, id_in=0, id_prin=-1;
        for(int i=1;i<Q.size();i++)
            {
                if(id_din==0 && Nume[i][0]==din)
                    id_din=i;
                if(id_in==0 && Nume[i][0]==in)
                    id_in=i;
                if(id_din!=0 && id_in!=0) break;
            }

        for(int i=0;i<Alfabet.size();i++)
            if(prin==Alfabet[i])
                {id_prin=i;break;}

        Q[id_din].set_alfabet(id_prin,id_in);


        getline(fi,v);
}
v.erase();
fi.close();
}
}

Automat::~Automat()
{
    Q.clear();
    Alfabet.clear();
    start=0;
}

void Automat::afis()
{
    cout<<"Starile sunt:\n";
    for(int i=1;i<Q.size();i++)
        {
            cout<<"Starea: "<<i<<") ";
            for(int j=0;j<Nume[i].size();j++) cout<<Nume[i][j]<<" ";
            cout<<"\n";
            Q[i].afisare();
        }
    cout<<"\n";
    cout<<"Alfabetul este: ";
    for(int i=0;i<Alfabet.size();i++)
        cout<<Alfabet[i]<<" ";
    cout<<"\nStarea intiala este :"<<Nume[start][0];
    cout<<"\n\n";
}

bool Automat::nu_exista (Stare& st)
{
    for(int i=1;i<Q.size();i++)
        if(Q[i]==st) return false;
    return true;
}

Automat& Automat::AFD (Automat& A)
{
    start=A.start;
    Alfabet=A.Alfabet;
    Nume.resize(2);
    Nume[1].push_back(A.Nume[start][0]);

    queue < Stare > coada;
    coada.push(A.Q[start]);
    Q.resize(2);
    Q[1]=coada.front();
    int CARD=1;
    while(!coada.empty())
    {
        Stare curr=coada.front(); coada.pop();
        for(int i=1;i<A.Alfabet.size();i++)
        {
            if(curr[i].size()==1 && curr[i][0]==0) continue;
            Stare NOU;                          ///GENERARE NOU
            for(int j=0;j<curr[i].size();j++)
                NOU+=A.Q[curr[i][j]];

            if(nu_exista(NOU))            ///VERIFICARE EXISTENTA
                {
                    coada.push(NOU);       ///ADAUGARE
                    Q.push_back(NOU);
                    CARD++;
                }
        }
    }
    Nume.resize(Q.size());
    for(int i=2;i<Q.size();i++)
    {
        vector<int> numele=Q[i].get_id();
        for(int j=0;j<numele.size();j++)
            Nume[i].push_back(A.Nume[numele[j]][0]);
    }
    ///NUME LA FINAL IN URMA GENERARILOR!
    return *this;
}

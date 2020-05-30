#include <bits/stdc++.h>
using namespace std;

//// BILETE

class Bilet
{
protected:
    static int index;
    int stPlecare, stSosire;
    int zi, luna, an;
    int ora, minut;
    int codTren, durata, distanta;
    float pret;
    int cod;
public:
    Bilet(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0):
        stPlecare(_sp), stSosire(_ss), zi(_z), luna(_l), an(_a), ora(_h), minut(_m), codTren(_c), durata(_du), distanta(_di), pret(_p){index++; cod = index;}
    static inline int getIndex(){return index;}
    inline int getCodTren() const {return codTren;}
    inline int getDistanta() const {return distanta;}
    virtual string getSerie() = 0;
    virtual void setPret() = 0;
    virtual void citire(istream& in);
    virtual void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Bilet& b);
    friend ostream& operator << (ostream& out, Bilet& b);
    virtual ~Bilet(){}

};

int Bilet::index = 0;

void Bilet::citire(istream& in)
{
    cout << "Introduceti urmatoarele date: \n";
    cout << "Statie plecare: ";
    in >> stPlecare;
    cout << "Statie sosire: ";
    in >> stSosire;
    cout << "Data plecarii (zi/luna/an): ";
    in >> zi >> luna >> an;
    cout << "Ora plecarii: ";
    in >> ora >> minut;
    cout << "Cod tren: ";
    in >> codTren;
    cout << "Durata calatorie: ";
    in >> durata;
    cout << "Distanta calatorie: ";
    in >> distanta;
}

istream& operator >> (istream& in, Bilet& b)
{
    b.citire(in);
    return in;
}

void Bilet::afisare(ostream& out) const
{
    out << "Date bilet: \n";
    out << "Statie plecare: " << stPlecare << '\n';
    out << "Statie sosire: " << stSosire << '\n';
    out << "Data plecarii (zi/luna/an): " << zi << " " << luna << " " << an << '\n';
    out << "Ora plecarii: " << ora << " " << minut << '\n';
    out << "Cod tren: " << codTren << '\n';
    out << "Durata calatorie: " << durata << '\n';
    out << "Distanta calatorie: " << distanta << '\n';
}

ostream& operator << (ostream& out, Bilet& b)
{
    b.afisare(out);
    return out;
}
///////////

class BiletRegio: virtual public Bilet
{
public:
    BiletRegio(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0):
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p){}
    virtual ~BiletRegio(){}

};

///////////

class BiletInterRegio: virtual public Bilet
{
protected:
    int loc;
public:
    BiletInterRegio(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0):
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), loc(_lo){}
    virtual ~BiletInterRegio(){}
};

///////////

class Bilet1: virtual public Bilet
{
protected:
    string meniu;
public:
    Bilet1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, string _me = ""):
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), meniu(_me){}
    virtual ~Bilet1(){}

};

///////////

class Bilet2: virtual public Bilet
{
public:
    Bilet2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0):
        Bilet(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p){}
    virtual ~Bilet2();


};

///////////

class BiletRegio1: public BiletRegio, public Bilet1
{
public:
    BiletRegio1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, string _me = ""):
        BiletRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), Bilet1(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _me){}
    string inline getSerie(){return "RI-" + to_string(cod);}
    void setPret(){pret = 0.39 * distanta; pret += pret/5;}
    void citire(istream& in);
    void afisare(ostream& out) const;
    virtual ~BiletRegio1(){}
};

void BiletRegio1::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Meniu: ";
    in >> meniu;
}

void BiletRegio1::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Meniu: " << meniu << '\n';
}

///////////

class BiletRegio2: public BiletRegio, public Bilet2
{
public:
    BiletRegio2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0):
        BiletRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p), Bilet2(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p){}
    string inline getSerie(){return "RII-" + to_string(cod);}
    void setPret(){pret = 0.39 * distanta;}
    void citire(istream& in);
    void afisare(ostream& out) const;
    virtual ~BiletRegio2(){}
};



void BiletRegio2::citire(istream& in)
{
    Bilet::citire(in);
}

void BiletRegio2::afisare(ostream& out) const
{
    Bilet::afisare(out);

}

///////////

class BiletInterRegio1: public BiletInterRegio, public Bilet1
{
public:
    BiletInterRegio1(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0, string _me = ""):
        BiletInterRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _lo), Bilet1(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _me){}
    string inline getSerie(){return "IRI-" + to_string(cod);}
    void setPret(){pret = 0.7 * distanta; pret += pret/5;}
    void citire(istream& in);
    void afisare(ostream& out) const;
    virtual ~BiletInterRegio1(){}
};

void BiletInterRegio1::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Meniu: ";
    in >> meniu;
    cout << "Loc: ";
    in >> loc;
}

void BiletInterRegio1::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Meniu: " << meniu << '\n';
    out << "Loc: " << loc << '\n';
}

///////////

class BiletInterRegio2: public BiletInterRegio, public Bilet2
{
public:
    BiletInterRegio2(int _sp = 0, int _ss = 0, int _z = 0, int _l = 0, int _a = 0, int _h = 0, int _m = 0, int _c = 0, int _du = 0, int _di = 0, float _p = 0, int _lo = 0):
         BiletInterRegio(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p, _lo), Bilet2(_sp, _ss, _z, _l, _a, _h, _m, _c, _du, _di, _p){}
    string inline getSerie(){return "IRII-" + to_string(cod);}
    void setPret(){pret = 0.7 * distanta;}
    void citire(istream& in);
    void afisare(ostream& out) const;
    virtual ~BiletInterRegio2(){}
};


void BiletInterRegio2::citire(istream& in)
{
    Bilet::citire(in);
    cout << "Loc: ";
    in >> loc;
}

void BiletInterRegio2::afisare(ostream& out) const
{
    Bilet::afisare(out);
    out << "Loc: " << loc << '\n';
}

///////////

class Manager
{
private:
    static Manager* instance;
    Manager(){}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    vector<Bilet*> bilete;
public:
    static Manager* getInstance();
    void adaugareBilet();
    void afisareBileteTren();
    void afisareBileteDistanta();
    void anulareBilet();
    void freeBilete();
    ~Manager();

};

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Manager();
    }
    return instance;
}

void Manager::adaugareBilet()
{
    string s;
    Bilet* b;
    cout << "Introdu tip bilet: ";
    cin >> s;
    if(s == "Regio1")
        b = new BiletRegio1;
    else if(s == "Regio2")
        b = new BiletRegio2;
    else if(s == "InterRegio1")
        b = new BiletInterRegio1;
    else if(s == "InterRegio2")
        b = new BiletInterRegio2;
    cin >> (*b);
    bilete.push_back(b);
}

void Manager::afisareBileteTren()
{
    int cod, i;
    cout << "Introduceti cod tren: ";
    cin >> cod;
    for(i = 0; i < bilete.size(); i++)
        if(bilete[i]->getCodTren() == cod)
            cout << *(bilete[i]);
}

void Manager::afisareBileteDistanta()
{
    int distanta, i;
    cout << "Introduceti distanta: ";
    cin >> distanta;
    for(i = 0; i < bilete.size(); i++)
        if(bilete[i]->getDistanta() > distanta)
            cout << *(bilete[i]);
}

void Manager::anulareBilet()
{
    int i;
    string serie;
    cout << "Introduceti serie bilet: ";
    cin >> serie;
    for(i = 0; i < bilete.size(); i++)
        if(bilete[i]->getSerie() == serie)
            bilete.erase(bilete.begin() + i);
}

void Manager::freeBilete()
{
    if(bilete.size() != 0)
    {   for(int i = 0; i <  bilete.size(); i++)
            delete bilete[i];
        bilete.clear();
    }

}

Manager::~Manager()
{
    freeBilete();
}


int main()
{

    int cereri, i, cerere;
    Manager *M = M->getInstance();
    cout << "Introduceti numar cereri: ";
    cin >> cereri;
    cout << "Optiuni: \n 1. Eliberare bilet nou \n 2. Listare bilete dupa cod tren \n 3. Listare bilete mai mare decat o distanta \n 4. Anulare bilet\n";
    for(i = 0; i < cereri; i++)
    {
        cout << "Introduceti cerere: ";
        cin >> cerere;
        if(cerere == 1)
            M->adaugareBilet();
        else if(cerere == 2)
            M->afisareBileteTren();
        else if(cerere == 3)
            M->afisareBileteDistanta();
        else if(cerere == 4)
            M->anulareBilet();
        else cout << "Tasta gresita";
    }

    return 0;
}
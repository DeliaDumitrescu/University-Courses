#include <bits/stdc++.h>
using namespace std;

class RW { // read/write
public:
    virtual void citire(istream &in) = 0;
    virtual void afisare(ostream &out) = 0;

    friend istream &operator >> (istream &in, RW &r)
    {
        r.citire(in);
        return in;
    }
    friend ostream &operator << (ostream &out, RW &w)
    {
        w.afisare(out);
        return out;
    }
    virtual ~RW() {}
};

/////////////

class Zbor: public RW
{
protected:
    int id, durata, zi, luna, an;
    string oras, destinatie;
public:
    Zbor(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = ""):
        id(_id), durata(_durata), zi(_zi), luna(_luna), an(_an), oras(_oras), destinatie(_destinatie){}
    void citire(istream&) override;
    void afisare(ostream&) override;
    inline int getZi() const {return zi;}
    inline int getLuna() const {return luna;}
    inline int getAn() const {return an;}
    string getType() {return "zbor";}
    virtual ~Zbor(){}
};

void Zbor::citire(istream& in)
{
    cout << "Introduceti urmatoarele date: \n";
    cout << "Id: ";
    in >> id;
    cout << "Durata: ";
    in >> durata;
    cout << "Data plecarii (zi/luna/an): ";
    in >> zi >> luna >> an;
    cout << "Oras plecare: ";
    in >> oras;
    cout << "Destinatie: ";
    in >> destinatie;
}

void Zbor::afisare(ostream& out)
{
    out << "Date zbor: \n";
    out << "Id: " << id << '\n';
    out << "Durata: " << durata << '\n';
    out << "Data plecarii (zi/luna/an): " << zi << " " << luna << " " << an << '\n';
    out << "Oras plecare: " << oras << '\n';
    out << "Destinatie: " << destinatie << '\n';
}

/////////////

class ZborTemporar: virtual public Zbor
{
protected:
    int perioadaActiva;
public:
    ZborTemporar(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _perioadaActiva = 0):
        Zbor(_id, _durata, _zi, _luna, _an, _oras, _destinatie), perioadaActiva(_perioadaActiva){}
    void citire(istream&) override;
    void afisare(ostream&) override;
    string getType() {return "zborTemporar";}
    virtual ~ZborTemporar(){}
};

void ZborTemporar::citire(istream& in)
{
    Zbor::citire(in);
    cout << "Perioada activa: ";
    in >> perioadaActiva;
}

void ZborTemporar::afisare(ostream& out)
{
    Zbor::afisare(out);
    out << "Perioada activa: " << perioadaActiva << '\n';
}

/////////////

class ZborPromotie: virtual public Zbor
{
protected:
    int discount; //20 (%)
public:
    ZborPromotie(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _discount = 0):
        Zbor(_id, _durata, _zi, _luna, _an, _oras, _destinatie), discount(_discount){}
    void citire(istream&) override;
    void afisare(ostream&) override;
    string getType() {return "zborPromotie";}
    virtual ~ZborPromotie(){}

};

void ZborPromotie::citire(istream& in)
{
    Zbor::citire(in);
    cout << "Discount: ";
    in >> discount;
}

void ZborPromotie::afisare(ostream& out)
{
    Zbor::afisare(out);
    out << "Discount: " << discount << '\n';
}

/////////////

class ZborTemporarPromotie: public ZborTemporar, public ZborPromotie
{
public:
    ZborTemporarPromotie(int _id = 0, int _durata = 0, int _zi = 0, int _luna = 0, int _an = 0, string _oras = "", string _destinatie = "", int _perioadaActiva = 0, int _discount = 0):
        ZborTemporar(_id, _durata, _zi, _luna, _an, _oras, _destinatie, _perioadaActiva),
        ZborPromotie(_id, _durata, _zi, _luna, _an, _oras, _destinatie, _discount){}
    void citire(istream&) override;
    void afisare(ostream&) override;
    string getType() {return "zborTemporarPromotie";}
    virtual ~ZborTemporarPromotie(){}
};

void ZborTemporarPromotie::citire(istream& in)
{
    ZborTemporar::citire(in);
    cout << "Discount: ";
    in >> discount;
}

void ZborTemporarPromotie::afisare(ostream& out)
{
    ZborTemporar::afisare(out);
    out << "Discount: " << discount << '\n';
}

/////////////

class Rute: public RW
{
private:
    string plecare, destinatie; //segm zbor
    int nrCurse, pretEconomic;
    vector <Zbor*> zboruri;
public:
    Rute(string _plecare = "", string _destinatie = "", int _nrCurse = 0, int _pretEconomic = 0):
        plecare(_plecare), destinatie(_destinatie), nrCurse(_nrCurse), pretEconomic(_pretEconomic){}
    void adaugaZbor();
    void citire(istream&) override;
    void afisare(ostream&) override;
    void freeZboruri();
    void afiseazaZborData();
    inline string getPlecare() const {return plecare;}
    inline string getDestinatie() const {return destinatie;}
    bool neverDiscount();
    //Rute(const Rute&); //daca avem timp se iau de la Marian
    //Rute& operator = (const Rute&);
    virtual ~Rute();
};

void Rute::citire(istream& in)
{
    cout << "Introduceti date ruta: \n";
    cout << "Plecare: ";
    in >> plecare;
    cout << "Destinatie: ";
    in >> destinatie;
    cout << "Nr curse: ";
    in >> nrCurse;
    cout << "Pret clasa economic: ";
    in >> pretEconomic;
    //cout << "Pentru a adauga zboruri, accesati opriunea 3";

}

void Rute::afisare(ostream& out)
{
    out << "Date despre ruta: ";
    out << "Plecare: " << plecare << '\n';
    out << "Destinatie: " << destinatie << '\n';
    out << "Numar curse: " << nrCurse << '\n';
    out << "Pret clasa economic: " << pretEconomic << '\n';
    out << "Zboruri: \n";
    for(int i = 0; i < zboruri.size(); i++)
        cout << *(zboruri[i]) << '\n';
}

void Rute::adaugaZbor()
{
    string s;
    Zbor* z;
    cout << "Introdu tip zbor:(zbor, zborTemporar, zborPromotie, zborTemporarPromotie)";
    cin >> s;

    if(s == "zbor")
        z = new Zbor;
    else if(s == "zborTemporar")
        z = new ZborTemporar;
    else if(s == "zborPromotie")
        z = new ZborPromotie;
    else if(s == "zborTemporarPromotie")
        z = new ZborTemporarPromotie;

    cin >> (*z);
    zboruri.push_back(z);
}

void Rute::afiseazaZborData()
{
    int zi1, luna1, an1, zi2, luna2, an2;
    cout << "Introduceti cele 2 date: ";
    cin >> zi1 >> luna1 >> an1 >> zi2 >> luna2 >> an2;
    for(int i = 0; i < zboruri.size(); i++)
    {
        int zi = zboruri[i]->getZi();
        int luna = zboruri[i]->getLuna();
        int an = zboruri[i]->getAn();
        if( (an > an1) || (an == an1 && luna > luna1) || (an == an1 && luna == luna1 && zi > zi1) )
            if((an < an2) || (an == an2 && luna < luna2) || (an == an2 & luna == luna2 && zi < zi2))
                cout << (*zboruri[i]) << '\n';
    }

}

void Rute::freeZboruri()
{
    if(zboruri.size() != 0)
    {   for(int i = 0; i <  zboruri.size(); i++)
            delete zboruri[i];
        zboruri.clear();
    }
}

bool Rute::neverDiscount()
{
    for(int i = 0; i < zboruri.size(); i++)
       if(dynamic_cast<ZborPromotie*>(zboruri[i]) || dynamic_cast<ZborTemporarPromotie*>(zboruri[i]))
            return 0;
    return 1;
}


Rute::~Rute()
{
    freeZboruri();
}

/////////////

class Manager
{
private:
    static Manager* instance;
    Manager(){}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    vector<Rute*> rute;
public:
    static Manager* getInstance();
    void freeRute();
    ~Manager();
    void adaugaRuta();
    void afiseazaRute();
    void afiseazaRuteData();
    void adaugaCursapeRuta();
    void afiseazaRuteFaraDiscount();

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

void Manager::freeRute()
{
    if(rute.size() != 0)
    {   for(int i = 0; i <  rute.size(); i++)
            delete rute[i];
        rute.clear();
    }
}

void Manager::adaugaRuta()
{
    Rute* r = new Rute;
    //r->citire(cin);
    cin >> (*r);
    rute.push_back(r);
}

void Manager::afiseazaRute()
{
    for(int i = 0; i < rute.size(); i++)
       // rute[i]->afisare(cout);
        cout << *(rute[i]) << '\n';
}

void Manager::afiseazaRuteData()
{
    for(int i = 0; i < rute.size(); i++)
        rute[i]->afiseazaZborData();
}

void Manager::adaugaCursapeRuta()
{
    string plecare, destinatie;
    cout << "Introduceti plecarea si destinatia rutei: ";
    cin >> plecare >> destinatie;
    for(int i = 0; i < rute.size(); i++)
        if(rute[i]->getPlecare() == plecare && rute[i]->getDestinatie() == destinatie)
            rute[i]->adaugaZbor();

}

void Manager::afiseazaRuteFaraDiscount()
{
    for(int i = 0; i < rute.size(); i++)
        if(rute[i]->neverDiscount())
            cout << (*rute[i]) << '\n';
}

Manager::~Manager()
{
    freeRute();
}

int main()
{
    int nrcereri, cerere, i;
    Manager *M = M->getInstance();
    cout << "Introduceti numar cereri: ";
    cin >> nrcereri;
    cout << "Optiuni: \n 1. Adauga ruta noua \n 2. Afiseaza toate rutele \n 3. Adauga cursa pe o anumita ruta \n 4. Afiseaza toate cursele dintre 2 date\n 5.Afiseaza rute fara discount\n 6.Inchide\n";
    for(i = 0; i < nrcereri; i++)
    {
        cin >> cerere;
        if(cerere == 1)
            M->adaugaRuta();
        else if(cerere == 2)
            M->afiseazaRute();
        else if(cerere == 3)
            M->adaugaCursapeRuta();
        else if(cerere == 4)
            M->afiseazaRuteData();
        else if( cerere == 5)
            M->afiseazaRuteFaraDiscount();
        else if(cerere == 6)
            break;
        else cout << "Cerere invalida.";
        cout << "\n\nOptiuni: \n 1. Adauga ruta noua \n 2. Afiseaza toate rutele \n 3. Adauga cursa pe o anumita ruta \n 4. Afiseaza toate cursele dintre 2 date\n 5.Afiseaza rute fara discount\n 6.Inchide\n";

    }


    return 0;
}
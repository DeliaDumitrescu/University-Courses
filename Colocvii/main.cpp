#include <bits/stdc++.h>
using namespace std;
/// PRODUSE PERISABILE ETC
///Partea cu AN LUNA etc

class Produs
{
protected:
    string nume;
public:
    Produs(string _n = ""):nume(_n){}
    virtual void citire(istream& in);
    virtual void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Produs& p);
    friend ostream& operator << (ostream& out, const Produs& p);
    inline string getNume() const {return nume;}
    virtual ~Produs(){}
};

void Produs::citire(istream& in)
{
    cout << "Nume produs: ";
    in >> nume;
}

istream& operator >> (istream& in, Produs& p)
{
    p.citire(in);
    return in;
}

void Produs::afisare(ostream& out) const
{
    out << "Nume produs: " << nume << '\n';
}

ostream& operator << (ostream& out, const Produs& p)
{
    p.afisare(out);
    return out;
}

//////////////////

class Perisabil: virtual public Produs
{
protected:
    int valabilitate;
public:
    Perisabil(string _n = "", int _v = 0): Produs(_n), valabilitate(_v){}
    void citire(istream& in);
    void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Perisabil& p);
    friend ostream& operator << (ostream& out, const Perisabil& p);
    inline int getValabilitate()const{return valabilitate;}
    virtual ~Perisabil(){}

};

void Perisabil::citire(istream& in)
{
    Produs::citire(in);
    cout << "Valabilitate: ";
    in >> valabilitate;
}

istream& operator >> (istream& in, Perisabil& p)
{
    p.citire(in);
    return in;
}

void Perisabil::afisare(ostream& out) const
{
    Produs::afisare(out);
    out << "Valabilitate: " << valabilitate << '\n';

}

ostream& operator << (ostream& out, const Perisabil& p)
{
    p.afisare(out);
    return out;
}

//////////////////


class Promotie: virtual public Produs
{
protected:
    int discount;
public:
    Promotie(string _n = "", int _d = 0): Produs(_n), discount(_d){}
    void citire(istream& in);
    void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Promotie& p);
    friend ostream& operator << (ostream& out, const Promotie& p);
    virtual ~Promotie(){}
};

void Promotie::citire(istream& in)
{
    Produs::citire(in);
    cout << "Discount: ";
    in >> discount;
}

istream& operator >> (istream& in, Promotie& p)
{
    p.citire(in);
    return in;
}

void Promotie::afisare(ostream& out) const
{
    Produs::afisare(out);
    out << "Discount: " << discount << '\n';

}

ostream& operator << (ostream& out, const Promotie& p)
{
    p.afisare(out);
    return out;
}

//////////////

class PerisabilPromotie: public Promotie, public Perisabil
{
public:
    PerisabilPromotie(string _n = "", int _v = 0, int _d = 0): Perisabil(_n, _v), Promotie(_n, _d) {}
    void citire(istream& in);
    void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, PerisabilPromotie& p);
    friend ostream& operator << (ostream& out, const PerisabilPromotie& p);
    virtual ~PerisabilPromotie(){}
};

void PerisabilPromotie::citire(istream& in)
{
    Perisabil::citire(in);
    cout << "Discount: ";
    in >> discount;
}

istream& operator >> (istream& in, PerisabilPromotie& p)
{
    p.citire(in);
    return in;
}

void PerisabilPromotie::afisare(ostream& out) const
{
    Perisabil::afisare(out);
    out << "Discount: " << discount << '\n';

}

ostream& operator << (ostream& out, const PerisabilPromotie& p)
{
    p.afisare(out);
    return out;
}

/////////////////////////

class Lot
{
private:
    string unitate;
    int cantitate, pretUnitate, zi, luna, an;
    Produs* produs;
public:
    Lot(string _u = "", int _c = 0, int _pu = 0, int _z = 0, int _l = 0, int _a = 0): unitate(_u), cantitate(_c), pretUnitate(_pu), zi(_z), luna(_l), an(_a){}
    void citire(istream& in);
    void afisare(ostream& out) const;
    friend istream& operator >> (istream& in, Lot& l);
    friend ostream& operator << (ostream& out, const Lot& l);
    inline int getAn() const {return an;}
    inline int getLuna() const {return luna;}
    inline int getZi() const {return zi;}
    inline int getCantitate() const {return cantitate;}
    inline int getPret(){return pretUnitate*cantitate;}
    inline Produs* getProdus() const {return produs;} //nu scriem inline
    void scadeCantitate(int _cantitate){cantitate -= _cantitate;}
    //~Lot(){delete produs;}
};

void Lot::citire(istream& in)
{
    bool per = 0, prom = 0;
    string rasp;
    cout << "Perisabil? (da/nu)";
    in >> rasp;
    if(rasp == "da")
        per = 1;
    cout << "Promotie? (da/nu)";
    in >> rasp;
    if(rasp == "da")
        prom = 1;
    if(per && prom)
        produs = new PerisabilPromotie;
    else if(per)
        produs = new Perisabil;
    else if(prom)
        produs = new Promotie;
    else
        produs = new Produs;
    in >> *produs;

    cout << "Unitate: ";
    in >> unitate;
    cout << "Cantitate: ";
    in >> cantitate;
    cout << "Pret unitate: ";
    in >> pretUnitate;
    cout << "Data(zi/luna/an)";
    in >> zi >> luna >> an;

}

istream& operator >> (istream& in, Lot& l)
{
    l.citire(in);
    return in;
}

void Lot::afisare(ostream& out) const
{
    out << *produs;
    out << "Unitate: " << unitate << '\n';
    out << "Cantitate: " << cantitate << '\n';
    out << "Pret unitate: " << pretUnitate << '\n';
    out << "Data: " << zi << " " << luna << " " << an << '\n';
}

ostream& operator << (ostream& out, const Lot& l)
{
    l.afisare(out);
    return out;
}
////////////////

class Manager
{
private:
    static Manager* instance;
    Manager(){}
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    vector<Lot*> loturi;
    //vector<Produs*> produse;
public:
    static Manager* getInstance();
    void adaugareLot();
    void afisareLoturi();
    void afisareLoturiPerioada();
    void afisareLoturiDisponibile();
    void vindeProdus();
    void freeLoturi();
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

void Manager::adaugareLot()  //option1()//option3()
{
    Lot* l = new Lot;
    cin >> (*l);
    loturi.push_back(l);
}

void Manager::afisareLoturi()  //option2()
{
    for(int i = 0; i < loturi.size(); i++)
        cout << *(loturi[i]) << '\n';
}

void Manager::afisareLoturiPerioada() //option 4
{
    int zi1, zi2, luna1, luna2, an1, an2;
    cout << "Introdu prima data: (zi/luna/an):";
    cin >> zi1 >> luna1 >> an1;
    cout << "Introdu a doua data: (zi/luna/an):";
    cin >> zi2 >> luna2 >> an2;
    for(int i = 0; i < loturi.size(); i ++)
    {
        int an = loturi[i]->getAn();
        int luna = loturi[i]->getLuna();
        int zi = loturi[i]->getZi();

     if(an > an1 || (an == an1 && luna > luna1) || (an == an1 && luna == luna1 && zi > zi1) ) //limita inf
        if(an < an2 || (an == an2 && luna < luna2) || (an == an2 && luna == luna2 && zi < zi2)) //limita sup
            cout << *(loturi[i]) << '\n';

    }

}

void Manager::afisareLoturiDisponibile() //option 5
{
    int ziCur, lunaCur, anCur, val = 0;
    cout << "Introdu data curenta(zi/luna/an): ";
    cin >> ziCur >> lunaCur >> anCur;
    for(int i = 0; i < loturi.size(); i++)
    {
        int an = loturi[i]->getAn();
        int luna = loturi[i]->getLuna();
        int zi = loturi[i]->getZi();

        if(Perisabil* p = dynamic_cast<Perisabil*> (loturi[i]->getProdus())) //produse perisabile/ perisabile&promotie
            val = p->getValabilitate();
        else if(PerisabilPromotie* p2 = dynamic_cast<PerisabilPromotie*> (loturi[i]->getProdus()))
            val = p2->getValabilitate();

        if(val == 0 && loturi[i]->getCantitate() != 0) //produse simple/promotie
            cout << *loturi[i] << '\n';
        else
            if(an < anCur || (an == anCur && luna < lunaCur) || (an == anCur && luna == lunaCur && zi + val < ziCur)) //nu e exp(consideram valabilitate cateva zile)
                if(loturi[i]->getCantitate() != 0) //nevide
                    cout << *(loturi[i]) << '\n';
    }
}

void Manager::vindeProdus()
{
    bool exista = 0;
    int lot, pret = 10000, val, cantitate;
    string nume;

    cout << "Introduceti nume produs: ";
    cin >> nume;
    cout << "Introduceti cantitate produs: ";
    cin >> cantitate;

    for(int i = 0; i < loturi.size(); i ++)
        if((loturi[i]->getProdus())->getNume() == nume)
        {
            if(loturi[i]->getCantitate() > cantitate)
            {
                exista = 1;
                if(loturi[i]->getPret() < pret)
                {
                    pret = loturi[i]->getPret();
                    lot = i;
                }
            }
            if(Perisabil* p = dynamic_cast<Perisabil*> (loturi[i]->getProdus())) //produse perisabile/ perisabile&promotie
                val = p->getValabilitate();
            else if(PerisabilPromotie* p2 = dynamic_cast<PerisabilPromotie*> (loturi[i]->getProdus()))
                val = p2->getValabilitate();
            if(val > 0)
            {
                int ziCur, lunaCur, anCur, val = 0;
                cout << "Introdu data curenta(zi/luna/an): ";
                cin >> ziCur >> lunaCur >> anCur;
                if (!(loturi[i]->getAn() < anCur || (loturi[i]->getAn() == anCur && loturi[i]->getLuna() < lunaCur) || (loturi[i]->getAn() == anCur && loturi[i]->getLuna() == lunaCur && loturi[i]->getZi() + val < ziCur)))
                    lot = -1;
            }
        }
    if(lot != -1)
        loturi[lot]->scadeCantitate(cantitate); //vind doar cel mai ieftin produs

}


void Manager::freeLoturi()
{
    if(loturi.size() != 0)
    {   for(int i = 0; i <  loturi.size(); i++)
            delete loturi[i];
        loturi.clear();
    }

}

Manager::~Manager()
{
    freeLoturi();
}

int main()
{
   int nrCereri, cerere;
   Manager *M = M->getInstance();
   cout << "Introduceti numar cereri: ";
   cin >> nrCereri;
   for(int i = 0; i < nrCereri; i++)
   {
        cout << "Introduceti 1 pt adaugare produs si introduceti cantitate 0: \n";
        cout << "Introduceti 2 pt afisare loturi \n";
        cout << "Introduceti 3 pt adaugare lot  \n";
        cout << "Introduceti 4 pt afisare loturi dintr-o perioada: \n";
        cout << "Introduceti 5 pt a afisare loturi disponibile \n";
        cout << "Introduceti 6 pt a cumpara un produs\n";
        cin >> cerere;
        if(cerere == 1 || cerere == 3)
            M->adaugareLot();
        else if (cerere == 2)
            M->afisareLoturi();
        else if(cerere == 4)
            M->afisareLoturiPerioada();
        else if(cerere == 5)
            M->afisareLoturiDisponibile();
        else if(cerere == 6)
            M->vindeProdus();
   }


    return 0;
}
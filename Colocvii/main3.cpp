#include <bits/stdc++.h>
using namespace std;

class RW { // clasa pt citire si afisare, inspirata din lab <3
public:
    virtual void citire(istream& in) = 0;
    virtual void afisare(ostream& out) const = 0;

    friend istream& operator >> (istream& in, RW& r)
    {
        r.citire(in);
        return in;
    }
    friend ostream& operator << (ostream& out, const RW& w)
    {
        w.afisare(out);
        return out;
    }
    virtual ~RW() {}
};

//////
template<class T>
bool isValid(T val)
{
    if(val < 0 || val > 6)
        throw std::runtime_error("Tasta gresita!");
}

//////

class Contract: public RW
{
protected:
    std::string numeClient;
public:
    Contract(std::string n = ""):numeClient(n){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
    virtual ~Contract(){}
};

void Contract::citire(istream& in)
{
    cout << "Nume client: ";
    in >> numeClient;
}

void Contract::afisare(ostream& out) const
{
    out << "Nume client: " << numeClient << '\n';
}

//////

class ContractInchiriere: public Contract
{
private:
    int anStart, lunaStart, anEnd, lunaEnd;
public:
    ContractInchiriere(std::string n = "", int as = 0, int ls = 0, int ae = 0, int le = 0): Contract(n), anStart(as), anEnd(ae), lunaStart(ls), lunaEnd(ls){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
    inline int getLunaStart() const { return lunaStart;}
    inline int getLunaEnd() const { return lunaEnd;}
    inline int getAnStart() const { return anStart;}
    inline int getAnEnd() const { return anEnd;}
};

void ContractInchiriere::citire(istream& in)
{
    Contract::citire(in);
    cout << "Introduceti perioada inchiriere:(ex 11 2019 10 2020)";
    in >> lunaStart >> anStart >> lunaEnd >> anEnd;
}

void ContractInchiriere::afisare(ostream& out) const
{
    Contract::afisare(out);
    out << "Perioada inchiriere: " << lunaStart << " " << anStart << " - " << lunaEnd << " " << anEnd << '\n';
}

//////

class ContractVanzare: public Contract
{
private:
    int lunaTranz, anTranz, lunaAch, anAch;
public:
    ContractVanzare(std::string n = "", int lt = 0, int at = 0, int la = 0, int aa = 0): Contract(n), lunaTranz(lt), anTranz(at), lunaAch(la), anAch(aa){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
    inline int getLunaTranz() const { return lunaTranz;}
    inline int getAnTranz() const { return anTranz;}
};

void ContractVanzare::citire(istream& in)
{
    Contract::citire(in);
    cout << "Data tranzactie(ex 9 2020): ";
    in >> lunaTranz >> anTranz;
    cout << "Data achitare(analog): ";
    in >> lunaAch >> anAch;
}

void ContractVanzare::afisare(ostream& out) const
{
    Contract::afisare(out);
    out << "Data tranzactie: " << lunaTranz << " " << anTranz << '\n';
    out << "Data achitare: " << lunaAch << " " << anAch << '\n';
}

//////

class Proprietate: public RW
{
protected:
    std::string adresa;
    int suprLoc, chirie;
    vector<Contract*> contracte;
public:
    Proprietate(std::string a = "", int s = 0, int c = 0): adresa(a), suprLoc(s), chirie(c){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
    void adaugaContract();
    void afiseazaContracteInchiriere();
    void afiseazaContracteVanzare();
    bool libera(int, int);
    bool inchiriata(int, int);
    bool vanduta(int, int);
    void adaugaContract(Contract*);
    //copiere egal
    Proprietate(const Proprietate&);
    Proprietate& operator = (const Proprietate&);
    Proprietate& operator += (Contract*);
    void freeContracte();
    virtual ~Proprietate();
};

void Proprietate::citire(istream& in)
{
    cout << "Adresa: ";
    in >> adresa;
    cout << "Supr loc: ";
    in >> suprLoc;
    cout << "Chirie pe mp";
    in >> chirie;
}

void Proprietate::afisare(ostream& out) const
{
    out << "Adresa: " << adresa << '\n';
    out << "Supr loc: " << suprLoc << '\n';
    out << "Chirie: " << chirie << '\n';
}

void Proprietate::adaugaContract()
{
    string s;
    Contract* c;
    cout << "Introdu tip contract(inchiriere/vanzare): ";
    cin >> s;

    try
    {
    if(s == "inchiriere")
        c = new ContractInchiriere;
    else if(s == "vanzare")
        c = new ContractVanzare;
    else
        throw runtime_error("Invalid\n");
    }

    catch(const exception& except)
    {
        cout << except.what() << '\n';
        return;
    }

    cin >> (*c);
    contracte.push_back(c);
}

void Proprietate::afiseazaContracteInchiriere()
{
    for(int i = 0; i < contracte.size(); i++)
        if(dynamic_cast<ContractInchiriere*>(contracte[i]))
            cout << (*contracte[i]) << '\n';
}

void Proprietate::afiseazaContracteVanzare()
{
    for(int i = 0; i < contracte.size(); i++)
        if(dynamic_cast<ContractVanzare*>(contracte[i]))
            cout << (*contracte[i]) << '\n';
}

bool Proprietate::inchiriata(int luna, int an)
{
    for(int i = 0; i < contracte.size(); i++)
        if(ContractInchiriere* c = dynamic_cast<ContractInchiriere*>(contracte[i])) //daca are contract de inch
            if(an > c->getAnStart() && an < c->getAnEnd()) //tb verif si luna dar lene
                return 1;
    return 0;
}

bool Proprietate::vanduta(int luna, int an)
{
    for(int i = 0; i < contracte.size(); i++)
        if(ContractVanzare* c = dynamic_cast<ContractVanzare*>(contracte[i])) //daca are contract de vanz
           if(c->getAnTranz() < an) //tb si luna
                return 1;
    return 0;
}

bool Proprietate::libera(int luna, int an)
{
    return (Proprietate::inchiriata(luna, an) == 0 && Proprietate::vanduta(luna, an) == 0);
}

//copiere egal
void Proprietate::adaugaContract(Contract* contract)
{
    if (ContractInchiriere* c = dynamic_cast<ContractInchiriere*>(contract))
            contracte.push_back(new ContractInchiriere(*c));
    else if (ContractVanzare* c = dynamic_cast<ContractVanzare*>(contract))
            contracte.push_back(new ContractVanzare(*c));
}


Proprietate::Proprietate(const Proprietate& proprietate): adresa(proprietate.adresa), suprLoc(proprietate.suprLoc), chirie(proprietate.chirie)
{
    for(auto ptr: proprietate.contracte)
        adaugaContract(ptr);
}

Proprietate& Proprietate::operator = (const Proprietate& proprietate)
{
    if(this == &proprietate)
        return *this;
    freeContracte();
    adresa = proprietate.adresa;
    chirie = proprietate.chirie;
    suprLoc = proprietate.suprLoc;

    for(auto ptr: proprietate.contracte)
        adaugaContract(ptr);
        return *this;
}  //tb si in celelalte tho

Proprietate& Proprietate::operator += (Contract* contract)
{
    contracte.push_back(contract);
    return *this;
}

void Proprietate::freeContracte()
{
      if(contracte.size() != 0)
    {   for(int i = 0; i <  contracte.size(); i++)
            delete contracte[i];
        contracte.clear();
    }
}

Proprietate::~Proprietate()
{
    freeContracte();
}

//////

class Casa: public Proprietate
{
private:
    int niveluri, suprCurte;
public:
    Casa(std::string a = "", int s = 0, int c = 0, int n = 0, int sc = 0): Proprietate(a, s, c),
                                                                            niveluri(n),
                                                                            suprCurte(sc){}
    //copiere
    Casa(const Casa& casa): Proprietate(casa), niveluri(casa.niveluri), suprCurte(casa.suprCurte){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
};

void Casa::citire(istream& in)
{
    Proprietate::citire(in);
    cout << "Niveluri: ";
    in >> niveluri;
    cout << "Supr curte: ";
    in >> suprCurte;
}

void Casa::afisare(ostream& out) const
{
    Proprietate::afisare(out);
    cout << "Niveluri: " << niveluri << '\n';
    cout << "Supr curte: " << suprCurte << '\n';
}

//////

class Apartament: public Proprietate
{
private:
    int etaj, camere;
public:
     Apartament(std::string a = "", int s = 0, int c = 0, int e = 0, int ca = 0 ): Proprietate(a, s, c),
                                                                                   etaj(e), camere(ca){}

    Apartament(const Apartament& apartament): Proprietate(apartament), etaj(apartament.etaj), camere(apartament.camere){}
    void citire(istream&) override;
    void afisare(ostream&) const override;
};

void Apartament::citire(istream& in)
{
    Proprietate::citire(in);
    cout << "Etaj: ";
    in >> etaj;
    cout << "Nr camere: ";
    in >> camere;
}

void Apartament::afisare(ostream& out) const
{
    Proprietate::afisare(out);
    cout << "Etaj: " << etaj << '\n';
    cout << "Nr camere: " << camere << '\n';
}

//////

class Manager //clasa Singleton pt rezolvarea cerintelor
{
private:
    static Manager* instance;
    Manager(){}
    //Manager(const Manager&) = delete;
    //Manager& operator=(const Manager&) = delete;
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager(Manager&&) noexcept = delete;
    Manager& operator=(Manager&&) = delete;
    vector<Proprietate*> proprietati;
public:
    static Manager* getInstance();
    void adaugaProprietate();
    void adaugaContract();
    void afiseazaProprietati();
    void afiseazaContracte();
    void afiseazaProprietatiData();
    void freeProprietati();
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

void Manager::adaugaProprietate()
{
    string s;
    Proprietate* p = nullptr;
    cout << "Introdu tip proprietate(casa/apartament): ";
    cin >> s;
    if(s == "casa")
        p = new Casa;
    else if(s == "apartament")
        p = new Apartament;
    else
    {   cout << "Tip invalid\n";
        delete p;
        return;
    }

    cin >> (*p);
    proprietati.push_back(p);
}

void Manager::adaugaContract()
{
    int i;
    cout << "Introduceti id proprietate: "; //id = poz in vector
    cin >> i;
    proprietati[i]->adaugaContract();
}

void Manager::afiseazaProprietati()
{
    //afis propr grup pe tip
    cout << "Case:\n";
    for(int i = 0; i < proprietati.size(); i++)
        if(dynamic_cast<Casa*>(proprietati[i]))
            cout << (*proprietati[i]) << '\n';

    cout << "Apartamente";
    for(int i = 0; i < proprietati.size(); i++)
        if(dynamic_cast<Apartament*>(proprietati[i]))
            cout << (*proprietati[i]) << '\n';
}

void Manager::afiseazaContracte()
{
    //afis contracte dupa tip
    cout << "Contracte inchiriere: \n";
    for(int i = 0; i < proprietati.size(); i++)
        proprietati[i]->afiseazaContracteInchiriere();

    cout << "Contracte vanzare:\n";
    for(int i = 0; i < proprietati.size(); i++)
        proprietati[i]->afiseazaContracteVanzare();
}

void Manager::afiseazaProprietatiData()
{
    int an, luna;
    cout << "Introduceti luna si an de verificat: ";
    cin >> luna >> an;

    cout << "Proprietati vandute: ";
    for(int i = 0; i < proprietati.size(); i++)
        if(proprietati[i]->vanduta(luna, an))
            cout << (*proprietati[i]) << '\n';

    cout << "Proprietati inchiriate: ";
    for(int i = 0; i < proprietati.size(); i++)
        if(proprietati[i]->inchiriata(luna, an))
            cout << (*proprietati[i]) << '\n';

    cout << "Proprietati libere: ";
    for(int i = 0; i < proprietati.size(); i++)
        if(proprietati[i]->libera(luna, an))
            cout << (*proprietati[i]) << '\n';
}


void Manager::freeProprietati()
{
    if(proprietati.size() != 0)
    {   for(int i = 0; i <  proprietati.size(); i++)
            delete proprietati[i];
        proprietati.clear();
    }
}

Manager::~Manager()
{
    freeProprietati();
}

int main()
{
    int nrcereri, cerere, i;
    Manager *M = M->getInstance();
    cout << "Introduceti numar cereri: ";
    cin >> nrcereri;
    for(i = 0; i < nrcereri; i++)
    {
        try
        {
            cout << "Introduceti cerere: ";
            cin >> cerere;
            isValid(cerere);
        }
        catch(const std::exception &except)
        {
            cout << "Tasta gresita!";
            i--;
            continue;
        }
        if(cerere == 1)
            M->adaugaProprietate();
        else if(cerere == 2)
            M->adaugaContract();
        else if(cerere == 3)
            M->afiseazaProprietati();
        else if(cerere == 4)
            M->afiseazaContracte();
       else if( cerere == 5)
            M->afiseazaProprietatiData();
        else if(cerere == 6)
            break;
        //else cout << "Cerere invalida.";
        cout << "Optiuni: \n";

    }


    return 0;
}
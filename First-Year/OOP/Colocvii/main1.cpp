#include <bits/stdc++.h>
using namespace std;

// PIZZA

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

//////

class Ingredient: public RW
{
protected:
    string nume, masura;
    int pret, cantitate;
public:
    Ingredient(string _nume = "", string _masura = "", int _pret = 0, int _cantitate = 0): nume(_nume), masura(_masura), pret(_pret), cantitate(_cantitate){}
    void citire(istream&) override;
    void afisare(ostream&) override;
    int getPret() const {return pret;}
    virtual ~Ingredient(){}
};

void Ingredient::citire(istream& in)
{
    cout << "Introduceti date ingredient:\n";
    cout << "Nume: ";
    in >> nume;
    cout << "Unitate masura: ";
    in >> masura;
    cout << "Pret: ";
    in >> pret;
    cout << "Cantitate: ";
    in >> cantitate;
}

void Ingredient::afisare(ostream& out)
{
    out << "Date despre ingredient:\n";
    out << "Nume: " << nume << '\n';
    out << "Masura: " << masura << '\n';
    out << "Pret: " << pret << '\n';
    out << "Cantitate: " << cantitate << '\n';
}

//////

class Pizza: public RW
{
protected:
    static int cnt;
    int cod, nrIngrediente, pret;
    string nume;
    bool veg;
    vector<Ingredient*> ingrediente;
public:
    Pizza(int _nrIngrediente = 0, string _nume = "", bool _veg = 0, int _pret = 0): nrIngrediente(_nrIngrediente), nume(_nume), veg(_veg), pret(_pret){ cod = cnt++;}
    vector<Ingredient*> getIngrediente(){return ingrediente;}
    int getPret() const {return pret;}
    void adaugaIngredient();
    void citire(istream& in);
    void afisare(ostream& out);
    virtual ~Pizza();
};

void Pizza::citire(istream& in)
{
    cout << "Introdu date despre pizza: \n";
    cout << "Nume: ";
    in >> nume;
    cout << "Veg(0/1): ";
    in >> veg;
    cout << "Nr ingrediente: ";
    in >> nrIngrediente;
    for(int i = 0; i < nrIngrediente; i++)
    {   cin >> (*ingrediente[i]);
        pret += ingrediente[i]->getPret();
    }
}


void Pizza::afisare(ostream& out)
{
    out << "Nume: " << nume << '\n';
    out << "Cod: " << cod << '\n';
    out << "Vegetariana: " << veg << '\n';
    out << "Nr ingrediente: " << nrIngrediente << '\n';
    for(int i = 0 ; i < nrIngrediente; i++)
        cout << (*ingrediente[i]) << " ";
}

void Pizza::adaugaIngredient()
{
    Ingredient* i;
    cin >> (*i);
    ingrediente.push_back(i);
    nrIngrediente++;
    pret += i->getPret();
}


Pizza::~Pizza()
{
    if(ingrediente.size() != 0)
    {   for(int i = 0; i <  ingrediente.size(); i++)
            delete ingrediente[i];
        ingrediente.clear();
    }
}

//////

class PizzaSpec: public Pizza
{
private:
    vector<Ingredient*> ingredienteExtra;
    int nrIngredienteExtra;
public:
    PizzaSpec(int _nrIngrediente = 0, string _nume = "", bool _veg = 0, int _nrIngredienteExtra = 0):
        Pizza( _nrIngrediente, _nume, _veg), nrIngredienteExtra(_nrIngredienteExtra){}
    void citire(istream&);
    void afisare(ostream&);
    virtual ~PizzaSpec();
};

void PizzaSpec::citire(istream& in)
{
    Pizza::citire(in);
    cout << "Nr ingrediente speciale: ";
    in >> nrIngredienteExtra;
    for(int i = 0; i < nrIngredienteExtra; i++)
        in >> (*ingredienteExtra[i]);
}

void PizzaSpec::afisare(ostream& out)
{
    out << "Pizza speciala: " << '\n';
    Pizza::afisare(out);
    out << "Nr ingrediente speciale: " << nrIngredienteExtra << '\n';
    for(int i = 0; i < nrIngredienteExtra; i++)
        cout << (*ingredienteExtra[i]) << " ";
}

PizzaSpec::~PizzaSpec()
{
    if(ingredienteExtra.size() != 0)
    {   for(int i = 0; i <  ingredienteExtra.size(); i++)
            delete ingredienteExtra[i];
        ingredienteExtra.clear();
    }
}

//////

class Bautura: public RW
{
protected:
    string nume;
    int pret;
public:
    Bautura(string _nume = "", int _pret = 0): nume(_nume), pret(_pret){}
    int getPret() const { return pret;}
    void citire(istream& in);
    void afisare(ostream& out);
};

void Bautura::citire(istream& in)
{
    in >> nume;
    in >> pret;
}

void Bautura::afisare(ostream& out)
{
    out << nume;
    out << pret;
}

////////

class Oferta: public RW
{
private:
    Pizza* p;
    Bautura* b;
    int pret;
public:
    Oferta(int _pret = 0):pret(_pret){}
    void citire(istream& in);
    void afisare(ostream& out);
};

void Oferta::citire(istream& in)
{
    in >> (*p);
    in >> (*b);
    pret += p->getPret()*0.75;
    pret += b->getPret()*0.75;
}

void Oferta::afisare(ostream& out)
{
    out << "Pret: " << pret << '\n';
    out << (*p) << '\n';
    out << (*b) << '\n';
}

//////

class Manager
{
private:
    static Manager* instance;
    Manager(){}
    Manager(const Manager&) = delete;
    vector<Pizza*> pizza;
    vector<Ingredient*> ingrediente;
    vector<Oferta*> oferte;
public:
    static Manager* getInstance();
    void adaugaPizza();
    void adaugaOferta();
    void afisareIngrediente();
    void afisarePizze2();
    void afisarePizze();
    void afisareOferte();
    ~Manager();

};

int Pizza::cnt  = 1;

Manager* Manager::instance = nullptr;

Manager* Manager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Manager();
    }
    return instance;
}

void Manager::adaugaPizza()
{
    string s;
    Pizza* p;
    cout << "Introdu tip pizza:(clasic/special)";
    cin >> s;
    if(s == "clasic")
        p = new Pizza;
    else if(s == "special")
        p = new PizzaSpec;
    cin >> (*p);
    //moral?:))))
    for(int i = 0; i < p->getIngrediente().size(); i++)
        ingrediente.push_back(p->getIngrediente()[i]);
    pizza.push_back(p);
}

void Manager::adaugaOferta()
{
    Oferta* o;
    cin >> (*o);
    oferte.push_back(o);
}

void Manager::afisareIngrediente()
{
    for(int i = 0; i < ingrediente.size(); i++)
        cout << (*ingrediente[i]) << '\n';
}

void Manager::afisarePizze()
{
    for(int i = 0; i < pizza.size(); i++)
        cout << (*pizza[i]) << '\n';
}

void Manager::afisarePizze2()
{
}

void Manager::afisareOferte()
{
    for(int i = 0; i < oferte.size(); i++)
        cout << (*oferte[i]) << '\n';
}

Manager::~Manager()
{
    if(pizza.size() != 0)
    {   for(int i = 0; i <  pizza.size(); i++)
            delete pizza[i];
        pizza.clear();
    }

     if(oferte.size() != 0)
    {   for(int i = 0; i <  oferte.size(); i++)
            delete oferte[i];
        oferte.clear();
    }

}

int main()
{
     int cereri, i, cerere;
    Manager *M = M->getInstance();
    cout << "Introduceti numar cereri: ";
    cin >> cereri;

    for(i = 0; i < cereri; i++)
    {
        cout << "Introduceti cerere: ";
        cin >> cerere;

        if(cerere == 1)
            M->afisareIngrediente();
        else if(cerere == 2)
            M->afisarePizze();
        else if(cerere == 4)
            M->afisareOferte();

        else if(cerere == 5)
            M->adaugaPizza();
        else if(cerere == 6)
            M->adaugaOferta();
        else cout << "Tasta gresita";
    }

    return 0;

}
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

class Persoana: public RW    //nemembru
{
protected:
    string nume, prenume;
    int cnp;
public:
    Persoana(string _nume = "", string _prenume = "", int _cnp = 0):nume(_nume), prenume(_prenume), cnp(_cnp){}
};

class Membru: public Persoana
{
protected:
    int data, cheltuieli;
    const int plafon = 3000;
    string tip;
    string mail;
public:
    Membru(string _nume = "", string _prenume = "", int _cnp = 0, int _data = 0, int _cheltuieli = 0, string _tip = "", string _mail = ""): Persoana(_nume, _prenume, _cnp), data(_data), cheltuieli(_cheltuieli), tip(_tip), mail(_mail){}
};

class Femeie: public Membru
{
public:
    Femeie(string _nume = "", string _prenume = "", int _cnp = 0, int _data = 0, int _cheltuieli = 0, string _tip = "", string _mail = ""):
        Membru(_nume, _prenume, _cnp, _data, _cheltuieli, tip, mail){}

};

class Barbat: public Membru
{
public:
    Barbat(string _nume = "", string _prenume = "", int _cnp = 0, int _data = 0, int _cheltuieli = 0, string _tip = "", string _mail = ""):
        Membru(_nume, _prenume, _cnp, _data, _cheltuieli, tip, mail){}
};

class Nemembru: public Persoana
{
public:
    Nemembru(string _nume = "", string _prenume = "", int _cnp = 0): Persoana(_nume, _prenume, _cnp){}
};

class Activitate: public RW
{
protected:
    string nume, restrictii, categorie;
    int pret;
public:
    Activitate(string _nume = "", string _restrictii = "", string _categorie = "", int pret = 0):
        nume(_nume), restrictii(_restrictii), categorie(_categorie), pret(_pret){}
};

int main()
{
    return 0;
}
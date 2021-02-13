#ifndef NFA_H
#define NFA_H
//#include "DFA.h"
#include <bits/stdc++.h>

struct elem{
    int st;
    char c;
};

class NFA{

protected:
    int n, m, q0, f;
    const char lambda;
    std::vector <bool> qf;  ///vector in care retinem stari e finale
    std::vector <bool> qi;
    std::vector <elem> a[101];  ///in a[i] avem perechi de forma < stare adiacenta cu i, caracter muchie >
    std::vector <int> lambdaTransitions[101];

public:
    friend class DFA;
    NFA(int n = 0, int m = 0, int q0 = 0, int f = 0, char lambda = '#'):n(n), m(m), q0(q0), f(f), lambda(lambda){};
    friend std::istream& operator>> (std::istream&, NFA&);
    friend std::ostream& operator << (std::ostream&, const NFA&);
    void BFS(int);
    void addNewTransitions();
    void removeLambdaTransitions();
};

















#endif //NFA_H
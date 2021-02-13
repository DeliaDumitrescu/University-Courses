#ifndef DFA_H
#define DFA_H
#include <bits/stdc++.h>
#include "NFA.h"

const std::string letters = "abcdefgh";

class DFA{
public:
    int n, q0;
    std::vector <elem> a[101];
    std::vector <int> finalStates;
public:
    DFA(NFA& nfa);
    friend std::ostream& operator << (std::ostream &out, const DFA&);
    void removeUnreachableStates();
    void removeUselessStates();
    void minimize();
    int  eqClass(int x, std::vector < std::vector <int> > pi[]);

};





#endif //DFA_H
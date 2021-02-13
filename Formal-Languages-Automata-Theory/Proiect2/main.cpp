#include <bits/stdc++.h>
#include "NFA.h"
#include "DFA.h"

std::ifstream fin("date.in");
std::ofstream fout("date.out");



int main(){

    NFA nfa;
    fin >> nfa;

    nfa.removeLambdaTransitions();
    fout << "Lamba-NFA transformed into NFA: \n" << nfa << "\n\n";

    DFA dfa(nfa);
    fout << "NFA transformed into DFA:\n" << dfa <<"\n\n";

    dfa.minimize();
    fout << "DFA minimised:\n" << dfa;

    return 0;
}
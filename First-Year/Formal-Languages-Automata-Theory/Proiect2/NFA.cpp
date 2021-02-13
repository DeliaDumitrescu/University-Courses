#include "NFA.h"
//#include "DFA.h"
#include <bits/stdc++.h>

void NFA::BFS(int stateStart)
{
    int state, i, j, next_state, l;
    std::queue <int> q;
    q.push(stateStart);

    while(!q.empty())
    {
        state = q.front();
        q.pop();
        l = lambdaTransitions[state].size(); ///parcurgem lambda-tranzitiile initiale
        for(i = 0; i < l; i ++)
        {
            next_state = lambdaTransitions[state][i];
            q.push(next_state);
            if(std::find(lambdaTransitions[stateStart].begin(), lambdaTransitions[stateStart].end(), next_state) == lambdaTransitions[stateStart].end()) ///verificam daca lambda-tranzitia e deja formata
                lambdaTransitions[stateStart].push_back(next_state);
        }
    }

 }

 void NFA::addNewTransitions(){

    bool changed = 1, found;
    int state, nextLambdaState, nextState, i, j;
    char letter;

    while(changed)
    {
       changed = 0;

        for(state = 0; state < n; state ++)
        {   for(i = 0; i < lambdaTransitions[state].size(); i ++)
            {
                nextLambdaState = lambdaTransitions[state][i];

                if(qi[state] == 1 && qi[nextLambdaState] == 0)
                    {
                    qi[nextLambdaState] = 1;
                    changed = 1;
                    }
                if(qf[nextLambdaState] == 1 && qf[state] == 0)
                {
                    qf[state] = 1;
                    changed = 1;
                }

                for(j = 0; j < a[nextLambdaState].size(); j ++)
                {
                    nextState = a[nextLambdaState][j].st;
                    letter = a[nextLambdaState][j].c;
                    found = 0;

                    for (std::vector <elem>::const_iterator it = a[state].begin(); it != a[state].end(); ++it) //verificam daca tranzitia exista deja in arrayul de vecini
                        if ( it->st == nextState && it->c == letter)
                            found = 1;

                    if(found == 0)  //adaugam noua starea, daca ea nu exista inainte
                    {   a[state].push_back( {nextState, letter} );
                        changed = 1;
                    }
                }
            }
        }
    }
 }


void NFA::removeLambdaTransitions()
{
    int  i, j, where;
    char how;
    //std::set<int>::iterator it;

    for(i = 0; i < n; i ++)
        BFS(i);
    addNewTransitions();

}

std::istream& operator >> (std::istream &in, NFA& nfa)
{
    int i, q1, q2;
    char c;
    in >> nfa.n >> nfa.m;
    nfa.qf.resize(nfa.n, 0);
    nfa.qi.resize(nfa.n, 0);
    for(i = 0; i < nfa.m; i ++)
    {
        in >> q1 >> q2 >> c;
        if(c == nfa.lambda)
            nfa.lambdaTransitions[q1].push_back(q2);
        else
            nfa.a[q1].push_back({q2,c});
    }

    in >> nfa.q0;      // stare initiala
    nfa.qi[nfa.q0] = 1;
    in >> nfa.f;                // numar stari finale
    for(i = 0; i < nfa.f; i ++)
    {
        in >> q1;
        nfa.qf[q1] = 1;
    }

    return in;
}

std::ostream& operator << (std::ostream &out, const NFA& nfa)
{
    int i,j;
    out << "Transitions:\n";
    for(i = 0; i < nfa.n; i++)
        for (j = 0; j < nfa.a[i].size(); j++)
            out << i << " " << nfa.a[i][j].st << " " << nfa.a[i][j].c << '\n';
    out << "Initial states: ";
    for(i = 0; i < nfa.qi.size(); i++)
        if(nfa.qi[i] == 1)
            out << i << " ";
    out << '\n';
    out << "Final states: ";
    for(i = 0; i < nfa.n; i++)
        if(nfa.qf[i] == 1)
            out << i << " ";

     return out;
}


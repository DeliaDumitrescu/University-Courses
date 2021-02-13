#include "DFA.h"
#include <bits/stdc++.h>

DFA::DFA(NFA& nfa)
{
    int i, j, where;
    char how;
    std::vector <std::map <char, std::set<int> > >  transitions; //in transitions[i]: transitions[0]:['a':{starile in care ajungem cu litera a din starea 0},'b':{starile cu care ajungem cu litera b din starea 0}] -> inainte de transf
    std::queue < std::set<int> > q; //coada de multimi
    transitions.resize(nfa.n, std::map<char, std::set<int>>());

    n = 0;
    q0 = nfa.q0;

    std::set<int> toInsert;
    std::set<int> current;
    toInsert.insert(q0);
    q.push(toInsert);

    std::map< std::set <int>, int > newStates; //vom avea {0,1}:noul nod 0, {1,2}:noul nod 1 etc
    newStates[toInsert] = n++;
    toInsert.clear();

    if(nfa.qf[q0] == 1)
        finalStates.push_back(0); //deoarece {q0} reprez noua stare 0

    for(i = 0; i < nfa.n; i++)
        for (j = 0; j < nfa.a[i].size(); j++)
        {
            where = nfa.a[i][j].st;
            how = nfa.a[i][j].c;
            transitions[i][how].insert(where);
        }

    while(!q.empty())
    {
        current = q.front();
        q.pop();
        for(char l:letters)
        {
            for (const int &from: current)
                if(transitions[from].count(l) != 0)
                {
                    for(const int &to: transitions[from][l])
                        toInsert.insert(to);
                }
            //in toInsert acum avem multimea in care ajungem cu litera l
            if(toInsert.size() != 0)
            {
                if(newStates.count(toInsert) == 0)
                {
                    newStates[toInsert] = n++;
                    q.push(toInsert);

                    for (const int &it: toInsert)
                        if (nfa.qf[it] == 1) //daca o multime contine o fosta stare finala, ea devine automat stare finala
                            finalStates.push_back(newStates[toInsert]);
                }

                a[newStates[current]].push_back({newStates[toInsert], l});
                toInsert.clear();
            }
         }
    }
    /*std::set<int>::iterator it;
    int it = *transitions[0]['a'].begin();
    it++;
    std::cout<<it;*/
}

std::ostream& operator << (std::ostream &out, const DFA& dfa)
{
    int i,j;
    out << "Transitions:\n";
    for(i = 0; i < dfa.n; i++)
        for (j = 0; j < dfa.a[i].size(); j++)
            out << i << " " << dfa.a[i][j].st << " " << dfa.a[i][j].c << '\n';

    out << "Initial states: " << dfa.q0 << '\n';
    out << "Final states: ";
    for(i = 0; i < dfa.finalStates.size(); i++)
        out << dfa.finalStates[i] << " ";

    return out;
}

void DFA::removeUnreachableStates() //starile in care nu ajungem deloc
{
    //BFS din starea initiala si marcam unde nu ajungem deloc, apoi eliminam acele stari
    int state, nextState, i;
    std::queue <int> q;
    std::vector <bool> viz(n, 0);
    q.push(q0);
    viz[q0] = 1;

    while(!q.empty())
    {
        state = q.front();
        q.pop();
        for(i = 0; i < a[state].size(); i++)
        {
            nextState = a[state][i].st;
            if(viz[nextState] == 0)
            {   viz[nextState] = 1;
                q.push(nextState);
            }
        }
    }
    int eliminate = 0;
    for(i = 0; i < n; i++)
        if(viz[i] == 0)
        {
             a[i].clear();
             eliminate++;
        }

    n -= eliminate;

}

void DFA::removeUselessStates()  //starile din care nu ajungem in stari finale
{
    //BFS din starile finale pe muchiile inversate si eliminam starile in care nu ajungem deloc, cat si muchiile legate de aceste stari
    int i, j, state, toClean;
    std::vector <std::vector <int> > inv(n); //in inv[i] vom avea tranzitiile inverse
    std::vector <bool> viz(n, 0);
    std::queue <int> q;

    for(i = 0; i < n; i++)
        for(j = 0; j < a[i].size(); j++)
            inv[a[i][j].st].push_back(i);

    for(i = 0; i < finalStates.size(); i ++)
    {   q.push(finalStates[i]);
        viz[finalStates[i]] = 1;
    }

    while(!q.empty())
    {
        state = q.front();
        q.pop();
        for (auto &it: inv[state])
            if(viz[it] == 0)
            {
                viz[it] = 1;
                q.push(it);
            }
    }

    int eliminate = 0;
    for(i = 0; i < n; i++)
        if(viz[i] == 0)
        {
             a[i].clear();
             eliminate++;
             for(j = 0; j < inv[i].size(); j++)
             {
                toClean = inv[i][j]; //Daca am eliminat starea i, atunci eliminam si toate muchiile care duceau la i, ale caror noduri se gasesc in inv[i]

                  std::vector <elem>::const_iterator it = a[toClean].begin();
                  while (it != a[toClean].end())
                  {
                    if ( it->st == i)
                        a[toClean].erase(it);
                    else
                        ++it;
                 }
            }
        }
    n -= eliminate;
}

int DFA::eqClass(int x, std::vector < std::vector <int> > pi[]) //returneaza pozitia clasei de echivalenta (a cata este)
{
    int i, j;
    for(i = 0; i < pi[0].size(); i++)
        for(j=0; j<pi[0][i].size(); j++)
            if(pi[0][i][j] == x)
                return i;
}

void DFA::minimize()
{
    int i, j, k, x, y, where, madeChanges = 1, inf = 100000;
    char how;
    bool firstPass, inPosition, equiv;
    std::vector < std::vector <int> > pi[2];
    std::vector <int> aux1, aux2;
    std::vector <std::map <char, int > >  newTransitions; //la fel ca transitions[i], dar dupa transformare, cu o litera ajungem intr-o singura stare, nu intr-o multime
    newTransitions.resize(n, std::map<char, int> () );

    removeUnreachableStates();
    removeUselessStates();

    for(i = 0; i < n; i++)
        for (j = 0; j < a[i].size(); j++)
        {   where = a[i][j].st;
            how = a[i][j].c;
            if(where == 0)
                where = inf;
            newTransitions[i][how] = where;     //inlocuim pt moment nodul 0 cu val inf pt a nu incurca starile care merg in nodul 0 cu litera x cu cele care nu exista si au 0 implicit
        }

    for(i = 0; i < n; i++)
        for(char l:letters)
            if(newTransitions[i][l] == 0)
                newTransitions[i][l] = -1;
    for(i = 0; i < n; i++)
        for(char l:letters)
            if(newTransitions[i][l] == inf)
                 newTransitions[i][l] = 0;

    for(i = 0; i < n; i ++)
        if(!std::count(finalStates.begin(), finalStates.end(), i))
            aux1.push_back(i);
    for(i = 0; i < finalStates.size(); i ++)
        aux2.push_back(finalStates[i]);
    pi[0].push_back(aux1);
    pi[0].push_back(aux2);  //la inceput pi[0]=>[[starile nefinale],[starile finale]]

    pi[1] = pi[0];

    while(firstPass == 0 || pi[0] != pi[1]) //ne oprim atunci cand nu mai facem nicio modificare
    {
        firstPass = 1;
        pi[0] = pi[1];                              //Ne uitam in pi[0] si formam in pi[1] noile multimi

        for(i = 0; i < pi[1].size(); i++)
        {    for(j = 1; j < pi[1][i].size(); j++)  //pi[1][i][j]= pt fiecare element din fiecare multime inaf de primul care e reprezentant
            {
                inPosition = 0;
                for(k = 0; k < j; k++)          //verific daca e echivalent cu toate celelalte elem din clasa lui(aflate inaintea sa)
                {
                    equiv = 1;
                    for(char l:letters)           //pt toate tranzitiile, verific daca pi[1][i][j]] si pi[1][i][k]] duc in stari echivalente
                        if(eqClass(newTransitions[pi[1][i][j]][l], pi) != eqClass(newTransitions[pi[1][i][k]][l], pi))
                        {
                            equiv = 0;
                            break;           //e suficient sa gasim o muchie pe care nu s echivalente
                        }
                    if(equiv) //pi[1][i][j] ramane in aceeasi clasa de echivalenta
                    {
                        inPosition = 1;
                        break;
                    }
                }
                if(inPosition) continue; //trecem la urmatorul; acesta e pozitionat bine

                //Daca ajungem aici inseamna ca trebuie sa ii gasim starea de echivalenta
                for(x = pi[0].size(); x < pi[1].size(); x++)
                {   for(y = 0; y < pi[1][x].size(); y++)
                    {
                        equiv = 1;
                        for(char l:letters)
                            if(eqClass(newTransitions[pi[1][i][j]][l], pi) != eqClass(newTransitions[pi[1][x][y]][l], pi))
                            {
                                equiv = 0;
                                break;
                            }

                        if(equiv) //il gasim compatibil in pi[1][x] il adaugam
                        {
                            pi[1][x].push_back(pi[1][i][j]);
                            pi[1][i].erase(pi[1][i].begin() + j);
                            inPosition = 1;
                            break;
                        }
                    }
                    if(inPosition)
                        break; //l-am putut baga intr-o clasa deja formata, diferita de clasa lui initiala
                }
                if(inPosition) continue;
                ///Daca ajungem aici, pi[1][i][j] nu poate fi plasat in nicio clasa deja existenta; cream una noua
                std::vector<int> aux;
                aux.push_back(pi[1][i][j]);
                pi[1].push_back(aux);
                pi[1][i].erase(pi[1][i].begin() + j);       //il stergem din fosta clasa
            }
        }
    }
    pi[0] = pi[1]; //in pi[0] vom avea multimile finale de noduri echivalente

    int ind = 0, elem;
    int minimisedNode[n] = {0}; //minimisedNode[i] = in cine se transforma nodul i DFA-ul minimizat
    std::vector <int> newFinalStates;
    for(i = 0; i < n; i++)
        a[i].clear(); //pt a reactualiza muchiile

    for(i = 0; i < pi[0].size(); i++)
    {
       for(j = 0; j < pi[0][i].size(); j++)
            minimisedNode[pi[0][i][j]] = ind;
        ind++;
    }
    n = ind;

    for(i = 0; i < pi[0].size(); i ++)
    {
        elem = pi[0][i][0]; //primul el din fiec lista
        for(char l:letters)
            if(newTransitions[elem][l] != -1)
                a[minimisedNode[elem]].push_back({eqClass(newTransitions[elem][l], pi), l});
    }

    q0 = minimisedNode[eqClass(q0, pi)];
    for(i = 0; i < pi[0].size(); i++)
        for(j = 0; j < pi[0][i].size(); j ++)
            if( std::count(finalStates.begin(), finalStates.end(), pi[0][i][j]) && !std::count(newFinalStates.begin(), newFinalStates.end(), pi[0][i][j])) //in caz ca 2 foste stari finale raman in ac multime, nu le adaug de 2 ori
                newFinalStates.push_back(minimisedNode[pi[0][i][j]]);
    finalStates = newFinalStates;

}

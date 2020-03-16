#include <bits/stdc++.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

int n, m, q0, t, words_to_test, to_generate;
bool accepted;

char c, cuv[101], s[101];

struct elem
{
    int st;
    char c;

};

struct elem2
{

    int st;
    string seq;

};

vector <int> qf;          // vector in care retinem starile finale
vector <elem> a[101];    // in a[i] avem perechi de forma < stare adiacenta cu i, caracter muchie >
queue <elem2> q;         // in q perechi de forma < stare, secventa_litere_formata_pana_in_starea_respectiva >
unordered_set <string> printed;

/// DFA & NFA

void dfs(char word[], int index_in_word, int state, bool &accepted)
{

    int i, j, letter, next_state;

    for(i = 0; i < a[state].size(); i ++)
    {
        next_state = a[state][i].st;
        letter = a[state][i].c;

        if(letter == word[index_in_word])

            if(index_in_word == strlen(word) - 1)
            {
                for(j = 0; j < t; j ++)          //verificam daca ultima stare in care ajungem e stare finala
                    if(next_state == qf[j])
                        accepted = 1;
            }
            else

                dfs(word, index_in_word + 1, next_state, accepted);
    }

}

/// FIRST ... WORDS GENERATED

bool depth[101][1001];

void bfs(int to_generate)
{

    int i, j, nr = 0, next_state;
    char letter;
    elem2 node;
    string current_word, new_word;

    q.push({q0,""});

    while(!q.empty() && nr < to_generate)
    {
        node = q.front();
        current_word = node.seq;
        q.pop();

        for(i = 0; i < a[node.st].size(); i ++)
        {
            next_state = a[node.st][i].st;
            letter = a[node.st][i].c;
            new_word = current_word + letter;

            q.push({ next_state, new_word });

            for(j = 0; j < t; j ++)          //verificam daca ultima stare in care ajungem e stare finala
                if(next_state == qf[j])
                {

                    if( printed.find(new_word) == printed.end())    //verificam daca am afisat deja cuvantul format trecand prin alte stari
                    {
                        printed.insert(new_word);
                        fout << nr + 1 << " -> " << new_word << '\n';
                        nr += 1;
                    }

                }

        }
    }
}


int main()
{
    int i, q1, q2, x;

    fin >> n >> m;                 // n stari, m tranzitii

    for(i = 1; i <= m; i ++)
    {
        fin >> q1 >> q2 >> c;
        a[q1].push_back({q2,c});
    }


    fin >> q0;      // stare initiala

    fin >> t;                // numar stari finale

    for(i = 0; i < t; i++)   // stari finale
    {
        fin >> x;
        qf.push_back(x);
    }

    fin >> words_to_test;

    for(i = 0; i < words_to_test; i++)
    {
        fin >> s;
        accepted = 0;

        dfs(s, 0, q0, accepted);

        if(accepted == 1)
            fout << s << "  " << "Cuvantul poate fi procesat." << '\n';
        else
            fout << s << "  " << "Cuvantul nu poate fi procesat." << '\n';

    }

    fin >> to_generate;    //numar cuvinte de generat

    fout << '\n' << "Primele " << to_generate << " de stari generate sunt: \n";
    bfs(to_generate);

    return 0;
}

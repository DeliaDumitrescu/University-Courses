#include <bits/stdc++.h>
#include "NFA.h"
#include "DFA.h"

//std::ifstream fin("date.in");
std::ofstream fout("date.out");

int main()
{

    NFA reg;
    reg.RegularGrammarToNFA();
    fout << "Reg into NFA:\n" << reg;


    return 0;
}
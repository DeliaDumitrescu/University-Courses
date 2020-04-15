#include <bits/stdc++.h>
#include "FibonacciHeap.h"

std::ifstream fin("date.in");
std::ofstream fout("date.out");

int main()
{
    int n, i, x, y;
    FibonacciHeap h;
    fin >> n;
    for(i = 0; i < n; i++)
    {
        fin >> x;
        if(x == 1)
        {
            fin >> y;
            h.insert(y);
        }
        if(x == 2)
        {
            fin >> y;
            h.deleteNode(y);
        }
        if(x == 3)
            fout << h.findMin() << '\n';
        if(x == 4)
            h.extractMin();
    }

    return 0;
}

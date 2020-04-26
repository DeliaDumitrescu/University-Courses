#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H
#include <bits/stdc++.h>

struct node{
    int val, degree;
    node* parent;
    node* left;
    node* right;
    node* child;
    bool marked;
};

class FibonacciHeap{

public:
    node* mini;
    int  nrNodes;
    std::map< int, node* > nodes; // map in care retinem pointer catre noduri si valoarea lor pt a le putea sterge fara sa cautam valoarea de fiecare data prin toata structura. multa memorie :(.
public:

    FibonacciHeap(); // = operatia de build empty heap
    friend std::ostream& operator << (std::ostream&, const FibonacciHeap&);
    node* createNode(int);
    void insert(int);
    node* link(node*, node*);
    void consolidate();
    void merge(FibonacciHeap&);
    void deleteNode(int val);
    void deleteTop(node*); //functie de stergere pentru o radacina
    void extractMin();
    int findMin();
};


#endif // FIBONACCI_HEAP_H

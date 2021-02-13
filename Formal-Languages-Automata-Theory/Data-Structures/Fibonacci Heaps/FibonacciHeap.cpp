#include "FibonacciHeap.h"
#include <bits/stdc++.h>

FibonacciHeap::FibonacciHeap()
{
    mini = nullptr;
    nrNodes = 0;
}

std::ostream& operator << (std::ostream& out, const FibonacciHeap& H)
{
    node* aux = H.mini;
    if(aux == nullptr)
        out << "Empty heap!";
    else{
        do
        {
            out << aux->val << " ";
            aux = aux->right;
        }while(aux != H.mini);
    }
    out << '\n';
    return out;

}

node* FibonacciHeap::createNode(int value)
{
    node* x = new node;
    x->val = value;
    x->degree = 0;
    x->parent = nullptr;
    x->left = x;
    x->right = x;
    x->child = nullptr;
    x->marked = 0;
    return x;
}

void FibonacciHeap::insert(int value)
{
    nrNodes += 1;
    node* aux = this->createNode(value);
    nodes.insert({value, aux});

    if(mini == nullptr)       //daca heapul este gol
        mini = aux;
    else
    {                         //altfel adaugam nod in stg lui mini
        (mini->left)->right = aux;
        aux->right = mini;
        aux->left = mini->left;
        mini->left = aux;
        if(aux->val < mini->val)
            mini = aux;
    }

}

node* FibonacciHeap::link(node* n1, node* n2)
{
    node* aux;
    //legam arborele 2 la arborele 1
    if(n1->val > n2->val)
    {
        aux = n1;
        n1 = n2;
        n2 = aux;
    }
    //decupam arbore 2
    (n2->right)->left = n2->left;
    (n2->left)->right = n2->right;
    //ii atasam parinte pe n1
    n2->parent = n1;
    //il adaugam pe n2 la copiii lui n1
    if(n1->child == nullptr)
    {
        n1->child = n2;
        n2->left = n2;
        n2->right = n2;
    }
    else //daca are deja copii; il adaugam in dreapta copilului "principal"
    {
        aux = n1->child;
        n2->right = aux->right;
        (aux->right)->left = n2;
        n2->left = aux;
        aux->right = n2;
    }

    n1->degree ++;
    return n1;
}

void FibonacciHeap::consolidate()
{
    int i;
    int degr = (log(nrNodes)) / (log(2));
    node* current;
    node* aux;
    node* d[degr + 1]; //vector de pointeri pt heapurile de diferite grade
    for(i = 0; i <= degr; i++)
        d[i] = nullptr;
    d[mini->degree] = mini;

    aux = mini->right;
    while(aux != mini)
    {
        current = aux;
        aux = aux->right;
        while(d[current->degree] != nullptr)
        {
            current = link(current, d[current->degree]);
            //dupa ce linkuim 2 heapuri de aceeasi lungime, se elibereaza d[lungimea celor unite]
            d[current->degree - 1] = nullptr;
        }
        d[current->degree] = current;
    }
}

void FibonacciHeap::merge(FibonacciHeap& H2)
{
    if(mini == nullptr)
        {
            if(H2.mini != nullptr)
            {   mini = H2.mini;
                nrNodes = H2.nrNodes;
                std::cout<<mini->val;
            }
        }
    else if(H2.mini != nullptr)
    {
        (mini->left)->right = H2.mini;
        (H2.mini->left)->right = mini;
        node* aux = mini->left;
        mini->left = H2.mini->left;
        H2.mini->left = aux;

        nrNodes += H2.nrNodes;
        if(mini->val > H2.mini->val)
            mini = H2.mini;

        H2.mini = nullptr; //dupa ce unim, nu mai avem nevoie de al doilea heap
        H2.nrNodes = 0;
    }

}

void FibonacciHeap::deleteNode(int val) //lazy delete
{
    (nodes[val])->marked = true;
}

void FibonacciHeap::deleteTop(node* toDelete)
{
    node *aux, *newMini, *leftaux, *root1, *root2;

    if(toDelete->right == toDelete)     //o singura radacina
    {   if(toDelete->child == nullptr)  //daca nu are copii, heap ul are 1 singur nod, il sterg direct
        {
            delete toDelete;
            mini = nullptr;
            nrNodes = 0;
            return;
        }
        else
            newMini = toDelete->child; //daca are o singura radacina dar si copii, vom cauta minimul printre copiii ei
    }


    else                            //mai multe radacini; cautam mini si printre radacini si printre copiii lui toDelete
    {   aux = toDelete->right;
        newMini = aux;
        while(aux != toDelete)     //cautam mini printre radacini
        {   if(aux->val < newMini->val)
                newMini = aux;
            aux = aux->right;
        }
    }

    if(toDelete->child == nullptr) //nu are copii: stergem direct toDelete si assign mini
    {
        mini = newMini;
        (toDelete->left)->right = toDelete->right;
        (toDelete->right)->left = toDelete->left;
        delete toDelete;
        nrNodes --;
        return;
    }

    else      //are copii:le stergem parintele; cautam mini si printre ei
    {
        if((toDelete->child)->val < newMini->val)
            newMini = toDelete->child;
        aux = (toDelete->child)->right;

        while(aux != toDelete->child)
        {
            if(aux->val < newMini->val)
                newMini = aux;
            aux = aux->right;
            aux->parent = nullptr;
        }

        mini = newMini;
        (toDelete->child)->parent = nullptr;

        if (toDelete -> right == toDelete)     //daca era doar o radacina cu mai multi copii, am gasit deja mini deci putem elimina direct
        {
            delete toDelete;
            nrNodes--;
            return;
        }

        else              //altfel, trebuie updatate relatiile
        {
            (toDelete->left)->right = toDelete->right; //delete toDelete
            (toDelete->right)->left = toDelete->left;

            aux = toDelete->child; //adaugam copiii la lista de radacini
            leftaux = aux->left;
            root1 = toDelete->right;
            root2 = (toDelete->right)->right;

            root1->right = aux;
            leftaux->right = root2;
            root2->left = leftaux;
            aux->left = root1;

            delete toDelete;
            nrNodes--;
        }
    }
}

void FibonacciHeap::extractMin()
{
    if(mini != nullptr)
    {
        while(mini != nullptr && mini->marked == true)
            deleteTop(mini);

        deleteTop(mini);
        if(mini != nullptr)
            consolidate();
    }
}

int FibonacciHeap::findMin()
{
    if(mini == NULL)
    {
         std::cout << "No min! Empty heap.";
         return -1;
    }
    else
    {
        while(mini != nullptr && mini->marked == true)
            deleteTop(mini);

        if(mini == NULL)
        {
            std::cout << "No min! Empty heap.";
            return -1;
        }

        return mini->val;
    }
}







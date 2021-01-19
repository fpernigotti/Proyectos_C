// practica PILA. Dado un conjunto de Productos (Codp y PU) que finalizan con un Codp nulo,
//armar una pila con dichos valores e imprimirla
//

#include <iostream>
#include <stdio.h>
using namespace std;


struct tProd {
    int codp;
    int pu;

};
struct NodoProd{
    tProd INFO;
    NodoProd* sgte;
};


void Meter(NodoProd*& pila, tProd RProd)
{
   
    NodoProd* ptrnue = new NodoProd();
    ptrnue->INFO = RProd;
    ptrnue->sgte = pila;
    pila = ptrnue;
}

void Sacar(NodoProd*& pila, tProd& RProd)
{
    NodoProd* ptr;
    ptr = pila;
    pila = pila->sgte;
    RProd = ptr->INFO;
    delete ptr;
}
   

int main()
{
    tProd RProd;
    NodoProd* pila = NULL;

    cout << "ingrese codp" << endl;
    cin >> RProd.codp;

    while (RProd.codp != 0)
    {
        cout << "ingrese pu" << endl;
        cin >> RProd.pu;

        Meter(pila, RProd);

        cout << "ingrese codp" << endl;
        cin >> RProd.codp ;

    }

    while (pila != NULL)
    {

        Sacar(pila, RProd);
        cout << RProd.codp << "   ";

        cout << RProd.pu << endl;

    }

}


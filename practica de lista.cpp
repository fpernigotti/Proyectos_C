#include <iostream>
using namespace std;

struct tProd {
   int CodP;
   float PU;
};

struct Nodo {
   tProd Info;
   Nodo* sig;
};

Nodo* ptrnue;

void InsertaNodo(Nodo*& lista, tProd rProd, Nodo* &ptrnue)  //en ptrnue devuelve puntero al nodo insertado
{
   ptrnue = new Nodo();
   ptrnue->Info = rProd;
   Nodo* aux1 = lista;
   Nodo* aux2 = NULL;

   while ((aux1 != NULL) && (aux1->Info.CodP < rProd.CodP)) // cuando queremos insertar elementos en el MEDIO O FIN DE LA LISTA
   {
      aux2 = aux1;                  // Si va en el MEDIO O FINAL pasa esto y esto (*)
      aux1 = aux1->sig;

   }

   //para saber si el nodo va a l principio de la lista, al medio o al final
   if (lista == aux1) // Con esto ya sabemos que si se cumple, el elemento que debemos insertar es menor al elemento que ya tenemos,
   {                 //por lo cual se insertaria en el PRINCIPIO DE LA LISTA.
      lista = ptrnue;  //si va al principio pasa ESTO y esto (**)
   }
   else
   {
      aux2->sig = ptrnue; //(*)
   }
   ptrnue->sig = aux1; //(*) y ()
}

void ElminaPrimero(Nodo* &lista, tProd &RInfo){
   Nodo *ptr = lista;
   RInfo = ptr -> Info;
   lista = lista -> sig;
   delete ptr;
}

int main() {
   tProd rProd;
   Nodo *lista = NULL;

   cout << "Ingrese un Codigo de producto" << endl;
   cin >> rProd.CodP;
   while(rProd.CodP != 0){
      cout << "Ingrese un precio unitario" << endl;
      cin >> rProd.PU;
      InsertaNodo(lista, rProd, ptrnue);
      cout << "Ingrese un Codigo de producto" << endl;
      cin >> rProd.CodP;
   }

   cout << "CodP  PU"<< endl;
   while (lista!=NULL) {
      ElminaPrimero(lista, rProd);
      cout << " " << rProd.CodP << " - " << rProd.PU << endl;
   }
   return 0;
}


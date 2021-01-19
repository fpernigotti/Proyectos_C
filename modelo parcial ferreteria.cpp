/*Ferretería de comercialización al por menor

Temas evaluados: Resolución de problemas, abstracción, estructuras de datos, accesos

Contexto
Usted trabaja en un equipo de desarrollo de sistemas que es convocado para realizar mejoras a un sistema de facturación de una ferretería.


Problema
Una ferretería que comercializa sus productos al por mayor desea actualizar su sistema de control de comercialización de productos, para lo cual necesita desarrollar módulos de facturación de los mismos y control de productos más comercializados, a partir de una serie de pedidos a procesar.


Recursos disponibles para utilizar

- Lista de productos (Lista) sin orden que contiene por cada Nodo de producto:
Info con      CodP (Cód de producto – 4díg)  PU (Precio unitario - decimal)  TotF (Total Facturado - decimal, inicialmente en 0)    TUV   (total de unidades vendidas, entero inicialmente en 0)
Sig

- Archivo de ventas VTAS.DAT que contiene por cada registro de venta:
CodP (Cód de producto – 4díg)  CantV (Cantidad vendida - entero)

- void  InsertaOrdenado (Nodo* & Lista, tInfo Info)   (no necesita desarrollar, inserta nodo ord por total fact)
- void  EliminaPrimerNodo (Nodo* & Lista, tInfo & Info)   (no necesita desarrollar)


Se pide:

a. 1,5pts) Defina en C/C++ la estructura de datos que representa el nodo de productos.

b.1pt)  Escriba en C/C++ la cabecera de un módulo AcumularFactProd que recibe la lista de productos, un cód de producto y la cantidad vendida de una venta, y actualiza la lista de productos.

c. 4.5 pts) Diseñe el algoritmo de dicho módulo, que busca dicho producto en la lista (si no existe solicita ingreso de precio unitario e incorpora el nodo al final de la lista) y actualiza los TotF y TUV del nodo a partir de los datos de la venta.  

d. 3pts) Reordenamiento - Desarrolle la parte del programa principal que al final imprime los CodP y TUV en orden creciente por Total de Unidades Vendidas.
*/












struct tInfo {
    int CodP;
    float PU;
    float TotF;
    int TUV;
    
};

struct nodo{
    tInfo Info;
    nodo* sig;
};


Void AcumularFactProd(nodo* &Lista, int CodP, int CantV){
    
    nodo* puntero = Lista;
    nodo* Puntero_anterior = NULL;
    
    while((puntero != NULL)&&(puntero -> Info.CodP != CodP)){
        Puntero_anterior=puntero;
        puntero = puntero -> sig;
    }
    
    if(puntero != NULL){
        puntero -> Info.TUV =  puntero -> Info.TUV + CantV;
        puntero -> Info.TotF = puntero -> Info.TotF + (puntero -> Info.PU * CantV);
    }
    else{
        
        nodo* nuevo_nodo = new nodo();
        
        nuevo_nodo ->Info.CodP = CodP;
        nuevo_nodo ->Info.TUV = CantV;
        nuevo_nodo ->sig = NULL;
        
        cout<<"ingrese el precio unitario:"<<endl;
        cin>> nuevo_nodo ->Info.PU;
        
        nuevo_nodo ->Info.TotF = ( nuevo_nodo ->Info.PU*CantV);
        
        
        if(Lista == NULL){
            Lista = nuevo_nodo;
        }
        else{
            Puntero_anterior ->sig = nuevo_nodo;
        }
    }
}



while (Lista != NULL){
    EliminaPrimerNodo (Lista,Info);
    InsertaOrdenado (Lista_ordenada, Info); //ordena por unidades vendidas en orden creciente   
}

cout<<"Codigo               Unidades vendidas"<<endl;

while(Lista_ordenada != NULL){
   
    EliminaPrimerNodo (Lista_ordenada,Info);
    cout<<Info.CodP<<"              "<<Info.TUV<<endl;
    
}



#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


struct tProd{
    int CodP;
    char Desc[20];
    float PU;
 };
tProd rProd;

struct tVta{
    int CodP;
    int CantV;
};
tVta rVta;

struct tInfo{
    int CodP;
    char Desc[20];
    float PU;
    float TotF;
};
tInfo rInfo;

 
struct Nodo{
    tInfo Info;
    Nodo* sig;
};
Nodo* Lista = NULL;




void GenerarArchivodeProd (tProd rProd) {
  
   FILE *ap = fopen("PRODS.dat", "w+b");
   
   cout << "Ingrese codigo de producto (0 para cortar)" << endl;
   cin >> rProd.CodP;
   
   
   while (rProd.CodP!=0){
     cout<<"Ingrese la descripcion del producto"<<endl;
     cin>>rProd.Desc; //CUANDO IMPRIMO SALEN TODOS LAS DESC IGUAL A LA ULTIMA!!
     cout<<"Ingrese el precio unitario"<<endl;
     cin>>rProd.PU;
 
     fwrite (&rProd, sizeof (rProd), 1, ap);
     
     cout << "Ingrese codigo de producto (0 para cortar)" << endl;
     cin >> rProd.CodP;
   };
   
    fclose (ap);
    
    //impresion para probar la carga(error no se porque en el string de desc)
   
   FILE* ap_lectura = fopen("PRODS.dat", "r");
   
   fread(&rProd, sizeof (rProd), 1, ap_lectura);
    cout<<" codigo      Desc        precio"<<endl;
   while(!feof(ap_lectura)){
       cout<<rProd.CodP<<"      "<<rProd.Desc<<"        "<<rProd.PU<<endl;
       fread(&rProd, sizeof (rProd), 1, ap_lectura);
   }
   
   fclose (ap_lectura);
   
   
};


void GenerarArchivodeVtas (tVta rVta, int &tope_ventas) {
   int i =0;
  
   FILE *av = fopen("VTAS.dat", "w+b");
    
   cout << "Ingrese codigo de producto (0 para cortar)" << endl;
   cin >> rVta.CodP;
   while (rVta.CodP!=0){
     cout<<"Ingrese la cantidad vendida"<<endl;
     cin>>rVta.CantV;
    
     fwrite (&rVta, sizeof (rVta), 1, av);
     i++;
     
     cout << "Ingrese codigo de producto (0 para cortar)" << endl;
     cin >> rVta.CodP;
   };
   fclose (av);
   
   tope_ventas = i-1;
   
   FILE* av_lectura = fopen ("VTAS.dat", "rb");
   cout<<"codigo        cantidad"<<endl;
  
  //probar si carga bien al archivo de ventas(carga ok)
  fread(&rVta, sizeof (rVta), 1, av_lectura);
  
   while(!feof(av_lectura)){
     
       cout<<rVta.CodP<<"       "<<rVta.CantV<<endl;
       fread(&rVta, sizeof (rVta), 1, av_lectura);
   }
   
   fclose(av_lectura);
   
   
};






void Insertar_a_Lista(Nodo* &Lista, tProd rProd){
    
    Nodo* nodonuevo = new Nodo();
    
    nodonuevo ->Info.CodP = rProd.CodP;
    strcpy(nodonuevo ->Info.Desc , rProd.Desc);
    nodonuevo ->Info.PU = rProd.PU;
    nodonuevo ->Info.TotF = 0;
    
    
    
    Nodo* puntero = Lista;
    Nodo* anterior = NULL;

    while((puntero != NULL)&&(puntero -> Info.CodP < nodonuevo -> Info.CodP)){
        
        anterior = puntero;
        puntero = puntero -> sig;
        
    }
    
    if (Lista == puntero){
        
        Lista = nodonuevo;
        
    }
    else{
        anterior -> sig  = nodonuevo;
    }
    
    nodonuevo ->sig = puntero;
    
    
}

void leer_y_cargar(Nodo* &Lista,tProd rProd){
    
    FILE *ap = fopen ("PRODS.dat", "r");
           
            fread (&rProd, sizeof (rProd), 1, ap);
            
           while(!feof(ap)){
               Insertar_a_Lista(Lista,rProd);
               fread (&rProd, sizeof (rProd), 1, ap);
           }
           
           fclose(ap);
    
}

void sumar_ventas(Nodo* &Lista, int tope_ventas){
    
    tVta vector_ventas[tope_ventas];
    
    Nodo* puntero = Lista;
    
    int i=0;
    
    
    FILE* av = fopen("VTAS.dat","r");
    
    fread(&rVta, sizeof(rVta),1,av);
    
    while(!feof(av)){
        if(i<=tope_ventas){
            vector_ventas[i] = rVta;
            i++;
        }
        
        fread(&rVta, sizeof(rVta),1,av);
    
    }
    
    fclose(av);
    
    for(int j=0;j<=tope_ventas;j++){
        
        while(puntero -> Info.CodP != vector_ventas[j].CodP){
            puntero = puntero -> sig;
        }
        
        puntero->Info.TotF = puntero->Info.TotF + (puntero->Info.PU*vector_ventas[j].CantV);
        
        puntero = Lista;
        
    }
    
    
}





void elimina_nodo(Nodo* &Lista, tInfo &rInfo){
    Nodo* puntero;
    
    puntero = Lista;
    Lista = Lista -> sig;
    
    rInfo = puntero ->Info;
    delete puntero;
    
    
}





int main () {
    
    int tope_ventas=0;
   int opc = -1;
   do {
      cout<<"Ingrese la opción deseada"<<endl;
      cout<<"1) Generar archivo de productos"<<endl;
      cout<<"2) Generar archivo de ventas"<<endl;
      cout<<"3) Corre ej "<<endl;
      cout<<"0) Salir"<<endl;
      cin >> opc;

      switch (opc) {
         case 0:
            cout<<"Muchas gracias por utilizar el programa"<<endl;
            break;
         case 1:
            GenerarArchivodeProd(rProd);
            break;
         case 2:
            GenerarArchivodeVtas(rVta, tope_ventas);
            break;
         case 3:
            {
           leer_y_cargar(Lista,rProd);
           
           sumar_ventas(Lista,tope_ventas);
              
             /*
             
             esto lo use para probar los modulos de cargar y borrar las listas, aca no pincho
               cout<<"cod"<<endl;
                cin>>rProd.CodP;
               while(rProd.CodP != 0){
                
                 cout<<"desc"<<endl;
                cin>>rProd.Desc;
                 cout<<"pu"<<endl;
                cin>>rProd.PU;
                
                Insertar_a_Lista(Lista,rProd);
                
                cout<<"cod"<<endl;
                cin>>rProd.CodP;
                
               }
                
                */
                
                cout<< "CodP    desc    precio      total"<<endl;
                while(Lista != NULL){
                    
                    elimina_nodo(Lista,rInfo);
                    
                    cout<<rInfo.CodP<<"     "<<rInfo.Desc;
                    cout<<"     "<<rInfo.PU<<"      "<<rInfo.TotF<<endl;
                    
                }
                
            }
                
            break;
         
         default:
            cout <<"ERROR! La opcion seleccionada es invalida"<<endl;
            break;
      }
   }
   while (opc != 0);
   return 0;
}










#include <iostream>
#include <stdio.h>
using namespace std;

//Tipo de dato necesario para trabajar con el archivo y vector de Productos
struct tProd{
       int Codp;
       float PU;
       int Stk;
};

//Genera un archivo de Productos a partir de ingresos de usuario
void GenerarArchivoProds () {
   FILE *aProds= fopen("Productos.dat", "wb");
   tProd RProd;
   cout << "Ingrese el Cód Producto (0 para cortar)" << endl;
   cin >> RProd.Codp;
   while (RProd.Codp!= 0){
     cout << "Ingrese Precio unitario" << endl;
     cin >> RProd.PU;
     cout << "Ingrese stock del producto" << endl;
     cin >> RProd.Stk;
     fwrite (&RProd, sizeof (RProd), 1, aProds);   // write(RProd,aProds)
     cout << "Ingrese el Cód Producto (0 para cortar)" << endl;
     cin >> RProd.Codp;
   };
   fclose (aProds);
};

//Imprime el archivo de Destinos
void LeerArchivoProds () {
   tProd RProd;
   FILE *aProds = fopen ("Productos.dat", "rb");
   if (aProds == NULL) {
      cout << "ERROR! No existe el archivo" << endl;
      return;
   }
   cout << "CodP   P.Unit   Stock" << endl;
   fread(&RProd, sizeof (RProd), 1, aProds);   // read(RProd,aProds)
   while (!feof (aProds)){
      cout << RProd.Codp << "       ";
      cout << RProd.PU << "        ";
      cout << RProd.Stk << endl;
      fread(&RProd, sizeof (RProd), 1, aProds);   // read(RProd,aProds)
      };
   fclose (aProds);
};



void ActualizarProds(tProd VP[], int & topep) {
   int i;
   FILE *aProds= fopen("Productos.dat", "wb");

   for (i=0;i<=topep;i++) {
      fwrite (&VP[i], sizeof (VP[i]), 1, aProds);   // write(VP[i],aProds)
   };
   fclose (aProds);
}

void Cargaenvector(tProd VP[], int &topevec){
   int i = 0;
   tProd RProd;
    FILE* AP = fopen ("Productos.dat", "rb");
            
            fread(&RProd, sizeof (RProd), 1, AP);
            
            while(!feof(AP)){
                VP[i]=RProd;
                i++;
                fread(&RProd, sizeof (RProd), 1, AP);
            };
            
            topevec= i-1;
    fclose(AP);
    
}


void BuscarenVec(tProd VP[], int topevec, int dato, int &pos ){
    pos = 0;
    
    while((pos<=topevec)&&(VP[pos].Codp != dato)){
        pos++;
    };
    if(pos>topevec){
        pos = -1;
    };
}

int main () {
   cout<<"Ej 78 Ventas de Productos"<< endl;
   int Codp,Cants;
   int topep=0;
   tProd VP[30];
   int topevec=0;
   int opc = -1;
   int i=0;
   
   
   do {
      cout<<"Ingrese la opción deseada"<<endl;
      cout<<"1) Generar y mostrar archivo de productos"<<endl;
      cout<<"2) Correr Ej 78"<<endl;
      cout<<"0) Salir"<<endl;
      cin >> opc;

      switch (opc) {
         case 0:
            cout<<"Muchas gracias por utilizar el programa"<<endl;
            break;
         case 1:
            // Para poder generar y controlar el archivo desde acá cuando haga falta
            GenerarArchivoProds();
            LeerArchivoProds();
            break;
         case 2:  // Corre el ej 78
            // Carga los Productos a un vector de productos
          
            Cargaenvector(VP, topevec);
            
           
            // Ingresa los pedidos hasta Codp = 0 y por cada uno busca el destino
            cout << "Ingrese el Cód Producto (0 para cortar)" << endl;
            cin >> Codp;
            while (Codp!= 0){
               cout << "Ingrese Cantidad solicitada" << endl;
               cin >> Cants;

               // Busca el producto ingresado en el vector de productos

              int pos;
              BuscarenVec(VP,  topevec,  Codp, pos );
              
              if(pos!= -1){
                              if((VP[pos].Stk - Cants)>=0){
                                                      if((Cants*VP[pos].PU)<=9999.99){
                                                          VP[pos].Stk = VP[pos].Stk - Cants;
                                                          
                                                          cout<<"SON "<<Cants*VP[pos].PU<<" PESOS"<<endl;
                                                      }
                                                      else{
                                                          cout<<"EL PRECIO ES EXCESIVO"<<endl;
                                                      }
                                                    
                                
                                  
                              }
                              else{
                                  cout<<"STOCK INSUFICIENTE"<<endl;
                              }
              }
              else{
                  cout<<"NO EXISTE EL CODIGO"<<endl;
              }
              


               cout << "Ingrese el Cód Producto (0 para cortar)" << endl;
               cin >> Codp;
            }

            // Actualizar el archivo de Productos a partir del vector de productos
            ActualizarProds(VP, topevec);
            // Imprimo archivo actualizado para control
            cout << "Los productos quedaron así " << endl<< endl;
            LeerArchivoProds();
            break;
         default:
            cout <<"ERROR! La opcion seleccionada es invalida"<<endl;
            break;
      }
   }
   while (opc != 0);
   return 0;
}
    
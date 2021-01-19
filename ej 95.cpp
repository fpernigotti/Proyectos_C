
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


struct tVta{
    int codP;
    char Desc[21];
    int cantV;
    float TotFact;
};

struct lProd{
    int codP;
    char Desc[21];
    float precioU;
};

void GenerarArchivodeProd () {
   tVta RVta;
   FILE *av = fopen("Ventas.dat", "w+b");
   int n =0; 
   cout << "Ingrese codigo de producto de 3 digitos (000 para cortar)" << endl;
   cin >> RVta.codP;
   while (RVta.codP!= 000 && n <= 4999){
     cout<<"Ingrese la descripcion del producto"<<endl;
     cin>>RVta.Desc;
     cout<<"Ingrese la cantidad vendida"<<endl;
     cin>>RVta.cantV;
     cout<<"Ingrese el total facturado"<<endl;
     cin>>RVta.TotFact;
     fwrite (&RVta, sizeof (RVta), 1, av);
     n++;
     cout << "Ingrese codigo de producto (0 para cortar)" << endl;
     cin >> RVta.codP;
   };
   fclose (av);
};


void LeerArchivo () {
   FILE *av = fopen ("Ventas.dat", "r+b");
   tVta RVta;
   if (av == NULL) {
      cout << "ERROR! No existe el archivo" << endl;
      return;
   }
      fread (&RVta, sizeof (RVta), 1, av);
      while (!feof (av)){   // feof se da cuenta que llegó al final del archivo sólo cuando intenta leer y la operacion falla
         cout << "Codigo de producto: " << RVta.codP<<endl;
         cout << "Descripcion del producto: "<< RVta.Desc<<endl;
         cout << "Cantidad Vendida: " << RVta.cantV << endl;
         cout << "Total facturado; " << RVta.TotFact << endl;
         fread (&RVta, sizeof (RVta), 1, av);
};
   fclose (av);
};


void OrdenarListado(lProd listProd[], int tope){
    int codPAux=0;
    lProd varAux;
    
    for (int i=0; i<tope; i++){
        for (int j=0 ; j<tope - 1; j++){
            if (listProd[j].codP > listProd[j+1].codP){
                   varAux = listProd[j];
                   listProd[j] = listProd[j+1];
                   listProd[j+1] = varAux;   
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Cod.Producto          Desc.               Pu"<<endl;
    for(int i=0;i<tope;i++){
    cout<<listProd[i].codP<<"                      "<<listProd[i].Desc<<"                   "<<listProd[i].precioU<<endl;    
    }

}

int main () {
   int opc = -1;
   do {
      cout<<"Ingrese la opción deseada"<<endl;
      cout<<"1) Generar archivo de productos"<<endl;
      cout<<"2) Leer archivo"<<endl;
      cout<<"3) Corre ej 95"<<endl;
      cout<<"0) Salir"<<endl;
      cin >> opc;

      switch (opc) {
         case 0:
            cout<<"Muchas gracias por utilizar el programa"<<endl;
            break;
         case 1:
            GenerarArchivodeProd();
            break;
         case 2:
            LeerArchivo();
            break;
         case 3:
            {
                int anterior = 0;
                char descAnterior[21];
                float PromQ = 0;
                int totFacturado=0;
                int VentI=0;
                int Qvent=0;
                int vent3000=0;
                int prod5000=0;
                int tope=0;
                lProd listProd[5000];
                
                FILE *av = fopen ("Ventas.dat", "r+b");
                tVta RVta;
                fread(&RVta, sizeof (RVta), 1, av);
                
              
                while(!feof(av)){
                    anterior = RVta.codP;
                    strcpy(descAnterior,RVta.Desc);
                    VentI=0;
                    PromQ = 0;
                    Qvent=0;
                    totFacturado=0;
                    vent3000=0;
                    
                    while((!feof(av)) && (RVta.codP==anterior)){
                        Qvent = Qvent +RVta.cantV;
                        totFacturado=totFacturado+RVta.TotFact;
                        if(RVta.TotFact>3000){
                          vent3000++;  
                        }
                        VentI++;
                        fread(&RVta, sizeof (RVta), 1, av);
                    };
                    
                    if((totFacturado/(Qvent*1.0))>1000){
                       listProd[tope].codP=anterior;
                       strcpy(listProd[tope].Desc,descAnterior);
                       listProd[tope].precioU=(totFacturado/(Qvent*1.0));
                       tope++;
                    }
                    
                    PromQ = Qvent/VentI;
                    cout<< "El promedio de ventas de "<<anterior<<" es "<< PromQ<<endl;
                    cout<< "El total facturado de "<<anterior<<" es "<<totFacturado<<endl;
                    if(vent3000!=0){
                        cout<< "Las ventas de más de 3000 de "<<anterior<<" fueron "<<vent3000<<endl;
                    }else{
                        cout<<"No hubo ventas de más de 3000"<<endl;
                    }
                    
                    if(totFacturado>5000){
                        prod5000++;
                    }
                    /*Por cada producto:
                        Promedio de cantidades vendidas de las ventas individual
                        Total facturado del producto
                        Cantidad de ventas de más de $3.000*/
                };
                
                if(prod5000!=0){
                    cout<<"Los productos que facturaron más de 5000 son "<<prod5000<<endl;
                }else{
                    cout<<"Ningun producto facturo más de 5000"<<endl;
                }
                
                OrdenarListado(listProd, tope);
                
                /*Del total de productos:
                Cantidad de productos que facturaron en total más de $5.000.

                    Listado de Productos que cuestan más de $1.000, ordenados por Cód Producto, con el siguiente formato
                      Cód Producto          Desc               Pu
                            999                    XX..XX         99.999,99
                            999                    XX..XX         99.999,99
                                     ..                         ..                     ..
                */
                
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


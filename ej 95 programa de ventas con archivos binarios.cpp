
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


struct tProd{
    int CodP;
    char Desc[30];
    float PU;
    float FacTot;
};

struct tVta{
    int CodP;
    int CantV;
};


void GenerarArchivodeProd () {
   tProd rProd;
   FILE* ap = fopen("PRODS.dat", "w+b");
   int n =0; 
   cout << "Ingrese codigo de producto de 3 digitos (0 para cortar)" << endl;
   cin >> rProd.CodP;
   while (rProd.CodP!=0 && n <= 499){
     cout<<"Ingrese la descripcion del producto"<<endl;
     cin>>rProd.Desc;
     cout<<"Ingrese el precio unitario"<<endl;
     cin>>rProd.PU;
 
     fwrite (&rProd, sizeof (rProd), 1, ap);
     n++;
     cout << "Ingrese codigo de producto (0 para cortar)" << endl;
     cin >> rProd.CodP;
   };
   fclose (ap);
};


void GenerarArchivodeVtas () {
   tVta rVta;
  
   FILE *av = fopen("VTAS.dat", "w+b");
    
   cout << "Ingrese codigo de producto (0 para cortar)" << endl;
   cin >> rVta.CodP;
   while (rVta.CodP!=0){
     cout<<"Ingrese la cantidad vendida"<<endl;
     cin>>rVta.CantV;
    
     fwrite (&rVta, sizeof (rVta), 1, av);
     
     cout << "Ingrese codigo de producto (0 para cortar)" << endl;
     cin >> rVta.CodP;
   };
   fclose (av);
};


void LeerArchivo () {
   FILE *ap = fopen ("PRODS.dat", "r+b");
   tProd rProd;
   if (ap == NULL) {
      cout << "ERROR! No existe el archivo" << endl;
      return;
   }
      fread (&rProd, sizeof (rProd), 1, ap);
      while (!feof (ap)){   // feof se da cuenta que llegó al final del archivo sólo cuando intenta leer y la operacion falla
         cout << "Codigo de producto: " << rProd.CodP<<endl;
         cout << "Descripcion del producto: "<< rProd.Desc<<endl;
         cout << "Precio unitario: " << rProd.PU << endl;
     
         fread (&rProd, sizeof (rProd), 1, ap);
};
   fclose (ap);
};

int BuscaProdenVec(tProd vProd[], int topeprod, int cod){ // devuelve la pos dentro del vector
   int i = 0; 
    while((vProd[i].CodP!=cod)&&(i<=topeprod)){
        i++;
    }
    return i;
};



void  CargaProdsaVec(tProd vProd[], int &topeprod){
    FILE*ap = fopen("PRODS.dat","r");
    tProd rProd;
    int i=0,j,k;
    fread(&rProd, sizeof (rProd), 1, ap);
    while(!feof(ap)){
        vProd[i] = rProd;
        i++;
        fread(&rProd, sizeof (rProd), 1, ap);
    }
    
    fclose(ap);
    topeprod = i-1;
    
    for (j=0;j<=topeprod;j++){
        vProd[j].FacTot =0;
    }
    
    FILE* av= fopen("VTAS.dat","r");
    tVta rVta;
    
    fread(&rVta, sizeof(rVta),1,av);
    while(!feof(av)){
        k = BuscaProdenVec(vProd,topeprod,rVta.CodP);
        
        vProd[k].FacTot=vProd[k].FacTot+(rVta.CantV*vProd[k].PU);
        
        fread(&rVta, sizeof(rVta),1,av);
    }
        fclose(av);
}



void  ImprimeVec(tProd vProd[], int topeprod){
    int i=0;
    cout<<"Cod"<<"               "<<"Descripcion"<<"               "<<"total facturado"<<endl;
   
    for(i=0 ;i<=topeprod;i++){
        cout<<vProd[i].CodP<<"               "<<vProd[i].Desc<<"                         "<<(vProd[i].FacTot)<<endl; 
    }
}

int main () {
   int opc = -1;
   do {
      cout<<"Ingrese la opción deseada"<<endl;
      cout<<"1) Generar archivo de productos"<<endl;
      cout<<"2) Generar archivo de ventas"<<endl;
      cout<<"3) Leer archivo"<<endl;
      cout<<"4) Corre ej 95"<<endl;
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
            GenerarArchivodeVtas();
            break;
         case 3:
            LeerArchivo();
            break;
         case 4:
            {
                tProd vProd[500];
                int topeprod =0;
                CargaProdsaVec(vProd,topeprod);
                ImprimeVec(vProd,topeprod);
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






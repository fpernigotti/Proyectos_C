/*
Una agencia de viajes desea llevar estadísticas de los destinos turísticos más consultados.

Para ello cuenta con un vector de Destinos VDest ya cargado con n destinos (máx 50) y con la siguiente estructura:

struct tDest {

   int CodDest;

   int Categ;

   int CC;   (Cant de Consultas realizadas)

};

tDest VDest[50];

 Se pide:

Desarrolle un módulo void BuscAgrDestino que recibe

   el vector VDest,

   la cantidad de destinos cargados n  y

   un cod de Destino a buscar DestABuscar.

Agregue los parámetros que considere necesarios.

 

Debe buscar dicho Destino en el vector.

   Si lo encuentra, debe incrementar en uno la Cantidad de Consultas realizadas.  

   Si no lo encuentra, debe agregar dicho destino al vector (en Categoría como no la tiene, se la debe solicitar al usuario).

Debe devolver por referencia, la Categoría correspondiente al destino buscado sea que lo agregó o lo encontró.

 

Dispone del módulo estándar  (que puede aplicar sin desarrollar)

int buscar(tvec vec[], int n, int datoabuscar)

que busca secuencialmente un elemento en un vector retornando el índice donde lo encuentra, si el dato buscado está o el valor -1 si lo buscado no está en el vector. Ya busca por el campo que hace falta, no hace falta indicar nada más que el datoabuscar.

 */






void BuscAgrDestino(tDest VDest[], int &n, int DestABuscar, int &categoria_buscada){
  
  int pos;  
  
  pos = buscar(VDest[],n, DestABuscar);
  
  if(pos==-1){
      
      if(n<49){
          VDest[n].CodDest = DestABuscar;
          cout<<"ingrese la categoria"<<endl;
          cin>>VDest[n].Categ;
          VDest[n].CC = 1; //porque aunque no estaba esta seria su primera consulta(podria ser 0 tambien no especifica).
          
          categoria_buscada = VDest[n].Categ 
          
          n++;
      }
      else{
          cout<<"excede el limite del vector en cantidad de destinos";
      }
      
      
  }
  else{
       VDest[pos].CC = VDest[pos].CC +1;
       categoria_buscada = VDest[pos].Categ;
      
      
  }
    
    
    
}
/*Una compañía eléctrica de una ciudad cuenta con un vector de zonas ya cargado con n zonas (máx 100) con la estructura detallada abajo, y listas de clientes por cada zona ya cargadas, con la estructura detallada abajo:

struct tZona {

   int Zona;

   float FactTot;  (facturación total de la zona)

   nodo * LCli (Lista de Clientes de la zona)

};

tZona VZonas[100];

struct Nodo {

   int DNI;

   Nodo* sig;

};


e pide desarrollar UNO de los dos algoritmos siguientes  (puede elegir el que prefiera,

aunque la opción b llega a valer a lo sumo 2 de los 3 puntos):

 

a) un módulo void AsignarCliente que recibe los siguientes parámetros: 

el vector VZonas, la cantidad de elementos cargados n, una Zona de tipo entero a buscar ZonaABuscar, un nro de documento DNI y facturación Fact de un cliente.

Debe buscar dicha Zona en el vector (está seguro), acumula la facturación total de la Zona e inserta ordenado dicho cliente en la lista correspondiente.

(la solución es muy corta)

 

Dispone de los módulos estándar  (que puede aplicar sin desarrollar)

int buscar(tvec vec[], int n, int datoabuscar)

que busca secuencialmente un elemento en un vector retornando el índice donde lo encuentra, si el dato buscado está o el valor -1 si lo buscado no está en el vector

Nodo* insertarOrdenado(Nodo & Lista, int infodelnodo)

inserta creciente en una lista según el criterio de ordenamiento requerido

 

b) el módulo void ListadoClientes, que recibe los siguientes parámetros: 

el vector VZonas y la cantidad de elementos cargados n, e imprime el siguiente listado sin liberar los nodos:*/







void ListadoClientes(tZona VZonas[], int n, )

int i;
nodo* auxiliar;

for(i=0;i<=n;i++){
    cout<<"zona:"<<VZonas[i].Zona<<" FactTot: "<<VZonas[i].FactTot<<endl;
    
    cout<<"DNI"<<endl;
    
    auxiliar = VZonas[i].LCli;
    
    while(auxiliar!= NULL){
        cout<< auxiliar-> DNI<<endl;
        auxiliar = auxiliar -> sig;
    }

}








void AsignarCliente(tZona VZonas[], int n, int ZonaABuscar, int DNI, float Fact){
    
    int posicion=-1;
    
    posicion = buscar(VZonas[], n, ZonaABuscar);
    
    if(posicion != -1){
        VZonas[posicion].FactTot = VZonas[posicion].FactTot + Fact;
        
        insertarOrdenado(VZonas[posicion].LCli, DNI);
        
    }

    
}
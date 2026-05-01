#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarea{ 
int TareaID;//Numérico autoincremental comenzando en 1000 
char *Descripcion;  //       
int Duracion; // entre 10 – 100  
} tarea;  

typedef struct nodo{ 
tarea T;  
struct nodo *Siguiente;  
} nodo;

nodo *crearTarea(int id);
void insertarTarea(nodo **cabecera, nodo *nuevo);
nodo *extraerTarea(nodo **cabecera, int id);
void liberarLista(nodo *cabecera);
void mostrarListas(nodo *cabecera)

int main(){
    nodo *tareasPendientes = NULL;
    nodo *tareasRealizadas = NULL;
    int idContador = 1000;
    int hecha;
    char agregarTarea;

    do{
        insertarTarea(&tareasPendientes,crearTarea(idContador + 1));
        printf("¿Cuantas tareas se van a realizar?:\n");
        scanf("%c",&agregarTarea);
        while(getchar()!='\n');
    }while(agregarTarea == 's');
    
    nodo *actual = tareasPendientes;
    while(actual != NULL){
        printf("Realizo la tarea %s?(1: SI - 0: NO)\n");
        scanf("%d", &hecha);
        while(getchar()!='\n');
        nodo *auxSiguiente = actual->Siguiente;

        if(hecha == 1){
            nodo *tareaEncontrada = extraerTarea(&tareasPendientes, actual->T.TareaID);
            insertarTarea(&tareasRealizadas, tareaEncontrada);
        }
        actual = auxSiguiente;
    }
    printf("\nTAREAS PENDIENTES\n");
    mostrarListas(&tareasPendientes);
    printf("\nTAREAS REALIZADAS\n");
    mostrarListas(&tareasRealizadas);

    liberarLista(tareasPendientes);
    liberarLista(tareasRealizadas);
    return 0;


}
nodo *crearTarea(int id)
{
    char buff[100];
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->T.TareaID = id;

    printf("Descripcion de la tarea:\n");
    gets(buff);
    nuevoNodo->T.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion,buff);

    printf("Duracion(10-100):\n");
    scanf("%d",&nuevoNodo->T.Duracion);
    while(getchar()!='\n');

    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void insertarTarea(nodo **cabecera, nodo *nuevo)
{
    nuevo->Siguiente = *cabecera;//el nuevo nodo apunta al que antes era el primero
    *cabecera = nuevo;//el nuevo nodo ahora es el primer nodo de la lista
}

nodo *extraerTarea(nodo **cabecera, int id)
{
    nodo *actual = *cabecera;//el primer nodo de la lista
    nodo *anterior = NULL;//necesitamos este puntero para luego volver a "unir" la lista

    while(actual != NULL && actual->T.TareaID != id)//mientras no lleguesmos al final y no lleguemos al id que estamos buscando
    {
        anterior = actual;//el que ahora es actual en el siguiente paso sera el anterior
        actual = actual->Siguiente;//pasamos al siguiente nodo de la lista
    }
    if(actual != NULL){//si no existe el anterior significa que el nodo que queremos sacar es el primero
        if(anterior == NULL){
            *cabecera = actual->Siguiente;//el primer nodo de la lista ahora es el que antes era el segundo
        }else{
        //el nodo de atras se une al que estaba despues del que nosotros sacamos
        //asi dejamos afuera de la lista el nodo que queriamos sacar
        anterior->Siguiente = actual->Siguiente;
        }
        actual->Siguiente = NULL;//limpiamos para que el gancho del nodo que sacamos no apunte a nada viejo
    }
    return actual;//devolvemos la direccion de memoria del nodo que sacamos
}

void liberarLista(nodo *cabecera) {
    nodo *aux; // Usamos un auxiliar para no perder la referencia

    while (cabecera != NULL) { // Mientras haya vagones en el tren...
        aux = cabecera;        // 1. Me guardo el vagón actual
        cabecera = cabecera->Siguiente; // 2. Avanzo la cabecera al próximo
        
        free(aux->T.Descripcion); // 3. Libero el texto de adentro
        free(aux);               // 4. Libero el vagón completo
    }
}

void mostrarListas(nodo *cabecera)
{
    nodo *actual = cabecera;
    if(actual == NULL){
        return 0;
    }else{
        while (actual != NULL)
        {
            printf("id tarea %d\n",actual->T.TareaID);
            printf("\ndescripcion: %s\n",actual->T.Descripcion);
            printf("duracion: %d\n",actual->T.Duracion);
        }
        actual = actual->Siguiente;
    }
}
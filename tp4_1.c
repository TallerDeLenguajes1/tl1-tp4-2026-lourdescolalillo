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
void mostrarListas(nodo *cabecera);
void buscarTarea(nodo *pendientes, nodo *realizadas);

int main(){
    nodo *tareasPendientes = NULL;
    nodo *tareasRealizadas = NULL;
    int idContador = 1000;
    int hecha;
    char agregarTarea;

    do{
        insertarTarea(&tareasPendientes,crearTarea(idContador++));
        printf("\n");
        printf("Desea ingresar otra tarea?(s/n)\n");
        scanf("%c",&agregarTarea);
        while(getchar()!='\n');
    }while(agregarTarea == 's');
    
    nodo *actual = tareasPendientes;
    while(actual != NULL){
        printf("Realizo la tarea:  %s?(1: SI - 0: NO)\n", actual->T.Descripcion);
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
    mostrarListas(tareasPendientes);
    printf("\nTAREAS REALIZADAS\n");
    mostrarListas(tareasRealizadas);

    buscarTarea(tareasPendientes,tareasRealizadas);

    liberarLista(tareasPendientes);
    liberarLista(tareasRealizadas);
    return 0;


}
nodo*crearTarea(int id)
{
    char buff[100];
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->T.TareaID = id;

    printf("Descripcion de la tarea: ");
    gets(buff);
    nuevoNodo->T.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion,buff);

    printf("Duracion(10-100): ");
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
        printf("lista de tareas vacia.\n");
    }else{
        while (actual != NULL)
        {
            printf("id tarea: %d || descripcion: %s || duracion: %d\n",actual->T.TareaID,actual->T.Descripcion,actual->T.Duracion);
            actual = actual->Siguiente;
        }
    }
}

void buscarTarea(nodo *pendientes, nodo *realizadas)
{
    int i,opcion, idBucado;
    char clave [50];
    int tareaEncontrada = 0;
    nodo *auxiliar;
    printf("\nBUSCADOR DE TAREAS\n");
    printf("\n1. Buscar por ID\n2. Buscar por palabra clave\n");
    scanf("%d", &opcion);
    while(getchar()!='\n');

    if(opcion == 1)
    {
        printf("Ingrese el id a buscar:");
        scanf("%d", &idBucado);
        auxiliar = pendientes;
        while(auxiliar != NULL){
            if(auxiliar->T.TareaID == idBucado){
                printf("\n[TAREA ENCONTRADA]");
                printf("\nEstado: PENDIENTE");
                printf("\nID: %d | Descripcion: %s\n", auxiliar->T.TareaID, auxiliar->T.Descripcion);
                tareaEncontrada = 1;
            }
            auxiliar = auxiliar->Siguiente;
        }

        auxiliar = realizadas;
        while(auxiliar != NULL){
            if(auxiliar->T.TareaID == idBucado){
                printf("\n[TAREA ENCONTRADA]");
                printf("\nEstado: REALIZADA");
                printf("\nID: %d | Descripcion: %s\n", auxiliar->T.TareaID, auxiliar->T.Descripcion);
                tareaEncontrada = 1;
            }
            auxiliar = auxiliar->Siguiente;
        }
    }else if (opcion == 2)
    {
        printf("Ingrese la palabra clave:");
        gets(clave);
        auxiliar = pendientes;
        while(auxiliar != NULL){
            if(strstr(auxiliar->T.Descripcion,clave) != NULL){
                printf("\n[TAREA ENCONTRADA]");
                printf("\nEstado: PENDIENTE");
                printf("\nID: %d | Descripcion: %s\n", auxiliar->T.TareaID, auxiliar->T.Descripcion);
                tareaEncontrada = 1;
            }
            auxiliar = auxiliar->Siguiente;
        }

        auxiliar = realizadas;
        while(auxiliar != NULL){
            if(strstr(auxiliar->T.Descripcion,clave) != NULL){
                printf("\n[TAREA ENCONTRADA]");
                printf("\nEstado: REALIZADA");
                printf("\nID: %d | Descripcion: %s | Duracion\n", auxiliar->T.TareaID, auxiliar->T.Descripcion, auxiliar->T.Duracion);
                tareaEncontrada = 1;
            }
            auxiliar = auxiliar->Siguiente;
        }
    }
    if(tareaEncontrada == 0){
        printf("\nNo se encontro ninguna tarea");
    }
}
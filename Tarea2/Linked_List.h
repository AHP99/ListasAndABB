#include <stdlib.h>
#include <stdio.h>
#define INVALID -100

typedef int tElemLista;

typedef struct nodo{ //Definición de un nodo

    tElemLista inByte; //Este campo indica el byte inicial del nodo (del bloque)
    tElemLista endByte; //Este campo indica el byte de término del nodo (del bloque)

    struct nodo *sig;
}tNodo;

typedef struct //Definición de una lista enlazada
{
    tNodo *head; //* Apunta al primer elemento de la lista
    tNodo *tail; //* Apunta al ultimo elemento de la lista
    tNodo *curr; //* Apunta a un nodo anterior al nodo actual en el que estamos en la lista
    int listSize; //* tamaño de la lista
    int pos; //* Indica la posición de determinado nodo (actual) en la lista. Comienza desde la posición 0.
} tLinkedList;


/********************
 * void InitList()
 *******************
 * Resumen Función: 
   Inicializa una lista enlazada vacia.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L que queremos inicializar, donde cada nodo
   representa un bloque de memoria.
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void initList(tLinkedList *L)
{
    //* Se asigna el espacio necesario para que podamos incluir un puntero de tipo tNodo, en cada uno de los elementos del struct
    L->head = L->tail = L->curr = (tNodo*)malloc(sizeof(tNodo));     
    L->listSize = L->pos = 0; //* Ambos se inicializan en 0 porque no tiene elementos aun, y si es que fueramos a agregar algo, se agregaria en la posicion 0
} 

/********************
 * void clear()
 *******************
 * Resumen Función: 
   Vacia una lista, dejandola inicializada, pero vacia.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L que queremos vaciar, donde cada nodo
   representa un bloque de memoria.
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void clear(tLinkedList *L)
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
    next = L->curr->sig; //* Aqui decimos que el puntero tipo tNodo next almacenara el siguiente elemento de la lista, al que estamos revisando en este momento
    free(L->curr);
    L->curr = next;
    }
    L->head = L->tail = L->curr = (tNodo *)malloc(sizeof(tNodo));
    L->listSize = 0;
    L->pos = 0;
}

/********************
 * int insert()
 *******************
 * Resumen Función: 
   Inserta un elemento en la poscion actual, y retorna la poscion en la que el elemento quedo.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L en la cual vamos a insertar el nuevo nodo.

   tElemLista in: Es el byte inicial del nodo que queremos insertar.

   tElemLista end: Es el bute final del nodo que queremos insertar.
 ********************
 * Returns:
   Retorna int L->pos: La posición de la lista en donde se insertó el nodo.
 ********************/
int insert(tLinkedList *L, tElemLista in, tElemLista end)
{
    tNodo *aux = L->curr->sig;
    L->curr->sig = (tNodo *)malloc(sizeof(tNodo)); //* En caso de crear un nuevo nodo en la lisa, hay que asignarle memoria suficiente para guardar la cantidad de datos que se le dara
    L->curr->sig->inByte = in;
    L->curr->sig->endByte = end;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail)
        L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}

/********************
 * int erase()
 *******************
 * Resumen Función: 
   Elimina el elemento (nodo) que está en la posicion actual en la lista.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L en la cual vamos a borrar el nuevo nodo.
 ********************
 * Returns:
   Retorna int 0: si la eliminación del nodo fue exitosa.
 ********************/
int erase(tLinkedList *L)
{
    tNodo *aux; //* Puntero a nodo, auxiliar
    aux=L->curr->sig; //*
    L->curr->sig = L->curr->sig->sig;
    free(aux);//* Queremos liberar la memoria de aquello a lo que apunta aux
    L->listSize--;
    return 0;
}

/********************
 * int erase()
 *******************
 * Resumen Función: 
   Elimina el elemento (nodo) que está en la posicion actual en la lista.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L en la cual vamos a borrar el nuevo nodo.
 ********************
 * Returns:
   Retorna int 0: si la eliminación del nodo fue exitosa.
 ********************/
int ListSize(tLinkedList *L)
{
    return L->listSize;
}

/********************
 * void deleteList()
 *******************
 * Resumen Función: 
   Elimina todos los elementos de la lista, borrando incluso la inicializacion de la lista
 ********************
 * input:
   tLinkedList* L: Lista enlazada L la cual vamos a utilizar
 ********************
 * Returns:
   Nada; de tipo void.
 ********************/
void deleteList(tLinkedList *L)
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
        next = L->curr->sig;
        free(L->curr);
        L->curr = next;
    }
}

/*********
* void moveToStart()
******
* Resumen función:
Mueve el cursor de la lista al primer elemento (Hace que el curr que en la primera posicion)
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* No retorna ya que es tipo void
*****/

void moveToStart(tLinkedList *L)
{
    L->curr = L->head;
    L->pos = 0;
}

/*********
* void moveToEnd()
******
* Resumen función:
*  Mueve el cursor de la lista al ultimo elemento (Hace que el curr que en la ultima posicion)
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* No retorna ya que es tipo void
*****/
void moveToEnd(tLinkedList *L)//? Mueve el cursor de la lista al ultimo elemento (Hace que el curr que en la ultima posicion)
{
    L->curr = L->tail;
    L->pos = L->listSize;
}

/********
* void prev()
******
* Resumen función:
* Mueve sel cursor al elemento anterior de la lista
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* No retorna ya que es tipo void
*****/
void prev(tLinkedList *L)  
{
    if (L->curr == L->head)
        return; //* Si es que estabamos en el primer elemento, no hay nada mas que hacer a si que retornamos
    tNodo *temp = L->head; //* Colocamos un cursor auxiliar, para recorrer hata la posicion buscada desde el inicio
    while (temp->sig != L->curr){
        temp = temp->sig;}
    L->curr = temp; //* Ahora que ya alcanzamos con el cursor auxiliar la poscion anterior, cambiamos el curr a la posicion del cursor auxiliar
    L->pos--;//* Al retroceder un espacio, el numero del cursor disminuye en 1
}

/*****
* void next()
******
* Resumen función:
* Mueve el cursor a la posicion siguiente, si es que el actual es el tail, no hace nada
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* No retorna ya que es tipo void
*****/
int next(tLinkedList *L) 
{
    if (L->curr != L->tail)
    {
        L->curr = L->curr->sig;
        L->pos++;
    }
    return L->pos;
}

/*****
* void moveToPos()
******
* Resumen de la función:
* Mueve el cursor a una posicion, mientras que esta exista en la lista
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*
* int posicion: Posicion a la cual quiero mover mi curr
*******
* Returns:
* No retorna ya que es tipo void
*****/
void moveToPos(tLinkedList *L, int posicion)
{
    if (posicion > L->listSize)
        return; //* Si es que se entrega una posicion negativa, o mas grande que la lista, no es valido
    
    if (posicion == L->pos){//* CAMBIO PERSONAL: Si es que es igual, retorna, ya que no hay nada que hacer
        return;}

    if (posicion > L->pos){ //* CAMBIO PERSONAL: Si es que es mayor que la posicion actual, avanza hasta llegar a la posicion
        while (posicion > L->pos)
            next(L);}

    else{//* Si es que es menor, comienza a buscar desde el principio
        int i;
        L->curr = L->head;
        L->pos = 0;
        for (i = 0; i < posicion; i++){
            next(L);
        }
    }
}

/************
* void printList()
******
* Resumen función:
* Para printear una lista
******
* Input:
* tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* No retorna ya que es tipo void
*****/
void printList(tLinkedList *L) //? 
{
    moveToStart(L);
    printf("[");
    int n = L->listSize;
    n--;
    for (int i = 0; i < n; i++)
    {
        printf("%d - %d, ", L->curr->inByte, L->curr->endByte);
        L->pos++;
        L->curr = L->curr->sig;
    }
    printf("%d - %d]\n ", L->curr->inByte, L->curr->endByte);
    moveToEnd(L);
}

/***********
* int getInValue()
******
* Resumen función:
* Esta funcion retorna el comienzo del bloque de memoria
******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    int pos: posicion en la cual se encuentra el nodo que utilizaremos
*******
* Returns:
* Retorna el valor de la primera casilla de nodo ( ejemplificacion->ÓOO)
*****/

int getInValue(tLinkedList *L, int pos){//?
    moveToPos(L, pos);
    return L->curr->sig->inByte;
}

/***********
* int getEndValue()
******
* Resumen función:
* Esta funcion retorna el fin del bloque de memoria
******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    int pos: posicion en la cual se encuentra el nodo que utilizaremos
*******
* Returns:
* Retorna el valor de la primera casilla de nodo ( ejemplificacion->OOÓ)
*****/

int getEndValue(tLinkedList *L, int pos){//? Esta funcion retorna el fin del bloque de memoria
    moveToPos(L, pos);
    return L->curr->sig->endByte;
}

/***********
* int getTamBlock()
******
* Resumen función:
*  Esta función retorna el tamaño de un bloque en bytes dado un nodo determinado restando su nodo final con el inicial
(ejemplo nodoInicial=3 y nodoFinal=8 ; nodoFinal-nodoInicial= 8-3 =5)

******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    int pos: posicion en la cual se encuentra el nodo que utilizaremos
*******
* Returns:
* Retorna el tamaño de la casilla de nodo 
*****/

int getTamBlock(tLinkedList *L, int pos){
    int tam;
    int fin = (int)getEndValue(L, pos);
    int inicio = (int)getInValue(L, pos);
    tam = (fin - inicio)+1;
    return tam;
}

/***********
* int CambiarFinal()
******
* Resumen función:
*  Esta función cambia el valor final de un nodo en una posicion ya ubicada

******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    tElemLista valorFinal: Valor numerico que tomara el nodo en su casilla final
*******
* Returns:
* Retorna 0 si es que el cambio fue exitoso
*****/

int CambiarFinal(tLinkedList *L, tElemLista valorFinal ){
    L->curr->sig->endByte = valorFinal;
    return 0;
}

/***********
* int CambiarInicio()
******
* Resumen función:
*  Esta función cambia el valor inicial de un nodo en una posicion ya ubicada

******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    tElemLista valorInicial:  Valor numerico que toma el nodo en su casilla inicial
*******
* Returns:
* Retorna 0 si es que el cambio fue exitoso
*****/

int CambiarInicio(tLinkedList *L, tElemLista valorInicial){
    L->curr->sig->inByte = valorInicial;
    return 0; 
}

/***********
* int getPosCurr()
******
* Resumen función:
*  Muestra la ubicacion del cursor en una lista dada
******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
* Esta función retorna la posicion en la que se encuentra el cursor
*****/

int getPosCurr(tLinkedList *L){
    return L->pos;
}

/***********
* int getPos()
******
* Resumen función:
*  Muestra la ubicacion del inbyte que estamos buscando, colocando el cursor en su inicio y recorriendo los nodos
por medio de un while que compara la posicion en la que esta con el tamaño de la lista
******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    tElemLista inbyte: Inbyte que buscaremos en la lista
*******
* Returns:
    Esta función retorna la posicion en la que se encuentra el inbyte buscado, y en el caso de no encontrarlo 
    retorna INVALID
*****/

int getPos(tLinkedList *L, tElemLista inbyte)
{
    moveToStart(L);
    int size = ListSize(L);
    while (L->pos != size){
        if (L->curr->sig->inByte == inbyte){
            return L->pos;
        }
        else{
            next(L);
        }
    }
    return INVALID;
}

/***********
* tElemLista buscar_nodo_erase()
******
* Resumen función:
*  Muestra la ubicacion del nodo que queremos eliminar utilizando, los valores iniciales de cada nodo (inbyte) y 
utilizando un for que nos recorra los nodos de alguna lista señalada

******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    tElemLista in: Inbyte que buscaremos en la lista para eliminar
*******
* Returns:
    Esta función retorna la posicion en la que se encuentra el inbyte buscado, y en el caso de no encontrarlo 
    retorna INVALID
*****/

tElemLista buscar_nodo_erase(tLinkedList *L, tElemLista in){

    moveToStart(L);
    int size = L->listSize;
    for (int i = 0; i < size ; i++)
    {
        if (L->curr->sig->inByte == in) {
            tElemLista B = getEndValue(L, i);
            erase(L);
            return B;
        }
        else
            next(L);
    }
    return INVALID;
}

/**************
* int bytes_asignados()
******
* Resumen función:
*  Va contando la cantidad de nytes que posee cada nodo de una lista señalada para poder retonar la cantidad total
    de bytes que tiene asignada dicha lista
******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
*******
* Returns:
    Esta función retorna la cantidad de bytes asignados a la lista señalada
*****/

int bytes_asignados(tLinkedList *L){
    moveToStart(L);
     int size = L->listSize;
     int contador = 0;
    for (int i = 0; i < size ; i++)
    {
        int end = (int)L->curr->sig->endByte;
        int in = ((int)L->curr->sig->inByte)-1; //Al byte inicial se le resta 1 para que, al hacer la resta, se considere dicho byte, obteniendo por ejemplo [1][2][3][4]; (4-(1-1)) = (4-0) bytes
        contador += (end-in);
        next(L);

    }
    return contador;
}

/***********
* void buscar_pos_insert()
******
* Resumen función:
*  En esta funcion realizaremos 2 sub-funciones (buscar donde insertar dicho nodo e insertarlo) para poder insertar
de manera correcta nuestro nodo ya que tenemos 3 casos principales de insercion, los cuales son insercion al inicio, 
medio y final. Para realizar un correcto funcionamiento de la insercion necesitamos comparar los valores de los 
extremos del nodo que insertaremos con los valores, ya sea inicial o final, del lugar en el cual se insertara el nodo
(Ejemplo: Queremos realizar una insercion de un nodo que comienza con in2=5 y finaliza con un valor de end2=35, y 
lo queremos incertar entre un nodo que finaliza con un endByte=2 y otro nodo que parte con un inByte=36, como el valor 
final del nodo que quemos insertar es end2=35 se diferencia en uno de la parte incial del nodo inByte=36 de la lista
en la que incertaremos el nodo, lo que hacemos es tomar el in2=5 y lo copiamos en el inByte ya que acabamos de señalar 
que son consecutivos (solo con un nodo, ya que si fuera otro caso aplicamos otra metodologia), por lo tanto como ya 
insertamos el nodo que partia en in2=5 y finalizaba en end2=35, porcedemos a eliminar el nodo que ya incertamos en la 
lista señalada terminando el proceso de buscar_pos_insert()


******
* Input:
    tLinkedList* L: Lista enlazada L la cual vamos a utilizar
    in2= Es el inicio del nodo que queremos insertar en L1
    end2= Es el final del nodo que queremos inserterar en L1
*******
* Returns:
    Esta función no retorna valor alguno ya que es void
*****/

//Esta función toma un elemento de inicio y de final de un nodo, y busca en una lista L la posición correcta de inserción.
//La posición de inserción correcta es donde el inByte de el nodo actual sea menor que in2 y el inByte del siguiente del actual sea mayor que in2.
void buscar_pos_insert(tLinkedList *L, tElemLista in2, tElemLista end2){ 

    moveToStart(L);

    int size = ListSize(L);

    //Iteramos en la lista mientras que la posición no sea igual al size, pues pos = {0,1,2...} y size = {1,2,3...} con pos = (size-1)
    while( L->pos < size){

        //*********************
        //***** CASO COLA *****
        //*********************

        if (L->curr->sig == L->tail){ 
            //Tenemos que revisar 4 casos, debido a que la lista puede tener 1 elemento y ese unico elemento sería tail
            //*CASOS DE FUSIÓN CON EL NODO TAIL
            //Si el nodo actual es consecutivo con el in2:
            if (L->curr->sig->endByte == (in2 - 1) ){ //Caso de fusión del nodo a insertar con el tail, a la derecha
                CambiarFinal(L, end2);
                return;
            }
            //Si el nodo actual es consecutivo con el end2:
            else if (L->curr->sig->inByte == (end2 + 1) ){//Caso de fusión del nodo a insertar con el tail, a la izquierda
                CambiarInicio(L, in2);
                return;
            }
            //*-----------------------------------------------------

            //*CASOS DE INSERCIÓN 
            else{
                if (in2 > L->curr->sig->endByte){ //*Caso de inserción a la derecha del tail
                    next(L);
                    insert(L, in2, end2);
                    return;
                }
                if (L->curr->sig->inByte > end2){ //*Caso de inserción a la izquierda del tail
                    insert(L, in2, end2);
                    return;
                }
            }
            //*-----------------------------------------------------    
        }
        
        //**************************
        //**** CASO INTERMEDIO  ****
        //**************************


        if((in2 > L->curr->sig->endByte) && (end2 < L->curr->sig->sig->inByte)){

            //Si no esta ni al inicio, ni al final, hay que encontrar entre que nodos está

            //*FUSÓN 3 NODOS (ANTERIOR, ACTUAL A INSERTAR, SIGUIENTE)
            if((L->curr->sig->endByte == (in2 - 1)) && (L->curr->sig->sig->inByte == (end2 + 1))){
                CambiarFinal(L, L->curr->sig->sig->endByte);
                next(L);
                erase(L);
                return;
            }
            //*-----------------------------------------------------

            //*FUSIÓN NODO CON ANTERIOR
            else if(L->curr->sig->endByte == (in2 - 1)){
                CambiarFinal(L, end2);
                return;
            }
            //*-----------------------------------------------------
 

            //*FUSIÓN CON NODO SIGUIENTE
            else if(L->curr->sig->sig->inByte == (end2 + 1)){
                next(L);
                CambiarInicio(L, in2);
                return;
            }
            //*-----------------------------------------------------

            //*INSERCIÓN EN POSICIÓN INTERMEDIA
            else{
                insert(L, in2, end2);
                return;
            }
        }

        
        //*********************
        //**** CASO INICIO ****
        //*********************


        if (L->curr->sig->inByte > end2){

            //*CASO DE FUSIÓN
            if(L->curr->sig->inByte == (end2 + 1) ){ //*Si es que el inByte del primer elemento, es sucesor del end2 que queremos insertar
                CambiarInicio(L, in2);
                return;
            }
            //*-----------------------------------------------------

            //*CASO DE INSERCIÓN AL INICIO
            else { //* Si no es consecutivo, simplemente se hace una insercion, quedando al inicio
                insert(L, in2, end2);
                return;
            }
            //*-----------------------------------------------------
        }
    next(L);
    }
}

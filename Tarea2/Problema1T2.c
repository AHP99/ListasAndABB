#include <stdio.h>
#include <string.h>
#include "Linked_List.h"


/********************
 * int FirstFit()
 *******************
 * Resumen Función: 
   Busca en la lista L un nodo que corresponda a un bluque de memoria
   que contenga bytes suficientes para almacenar información de tam bytes.
   Encuentra el primer calce de tamaño tam bytes.
 ********************
 * input:
   tLinkedList* L: Lista enlazada L, donde cada nodo representa un bloque
   de memoria. Generalmente esta variable será lo que más adelante se
   define como "L1"; la lista que contiene los bloques de memoria disponibles.

   int tam: tamaño en bytes del bloque de memoria que necesitamos calzar en
   la lista L.
 ********************
 * Returns:
   int i : La función retorna la posición i del nodo que cumple con el mínimo
   tamaño tam, en la lista L. Se asume que no se entregarán valores de tam que
   no sea posible calzar en L (por enunciado). Retorna int INVALID (definido en
   el TDA) en el caso de que no encontrara un bloque que satisfaga la petición
   de memoria.
 ********************/
int FirstFit(tLinkedList* L, int tam){

    int size = ListSize(L);
    int i;
    for (i=0 ; i < size ; i++)
    {
        int block = getTamBlock(L, i);
        if (tam <= block){
        return i;
        }        
    }
    return INVALID;
}


/********************
 * int Main()
 *******************
 * Resumen Función: 
   Esta función abre y lee un archivo (input1.dat, de tipo txt) y realiza las
   operaciones de pedido y de liberado de memoria indicado en cada linea,
   utilizando listas que contengan los bloques de memoria tanto pedidos como
   disponibles, y operando con las funciones definidas en el TDA Linked_List.h
 ********************
 * Input: --
   Nada; El archivo input1.dat debe estar guardado en el mismo directorio que
   el programa.
 ********************
 * Returns:
   retorna int 0: si el programa corrió de manera exitosa.
   Además el programa crea un archivo txt llamado output1.dat, el cual indica en
   cada linea que  las operaciones de pedido y liberado de memoria fueron hechas
   según lo pedido, y especifíca desde qué byte fue asignada o liberada la memoria.
   Al final de output1.dat se indica en una linea la cantidad de bloques sin
   liberar y los bytes totales a los que corresponde esa memoria asignada.
 ********************/
int main(){

    FILE *input = fopen("input1.dat.txt", "r");
     //comprobacion de apertura exitosa del archivo
    if (input == NULL)
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;}
    //comprobacion de apertura exitosa del archivo
    FILE *output = fopen("output1.dat.txt","w" );
    if (output == NULL) 
    {
        printf("Problema de apertura de archivo para output, finalizacion anticipada del programa");
        return 2;
    }
    //Hacemos rewind para asegurarnos de que el cursor esta al inicio del archivo
    rewind(input);
    int M, N;
    // M: total de memoria inicial disponible en un solo bloque contiguo
    fscanf(input, "%d", &M);
    // N: cantidad de operaciones de petición o liberación de memoria a realizar
    fscanf(input, "%d", &N);

    //Se crea una variable L1: lista de bloques disponibles
    tLinkedList L1;
    //Se crea variable L2: Lista de bloques asignados
    tLinkedList L2;
    //Se inicializa la lista vecía usando el TDA Linked_List.h
    initList(&L1);
    //Se inicializa la lista L2 vacía usando el TDA Linked_List.h
    initList(&L2);

    //La lista L1 se inicia con un nodo que indica un bloque de memoria contigua desde el byte 1 hasta M
    insert(&L1, 1, M);
    
    char m[]="malloc";
    char f[]="free";
    int tamblock; //Tamaño del bloque de memoria a asignar en bytes
    int bytefree; //Byte inicial del bloque de memoria a liberar
    for (int i = 0; i < N; i++) //Se itera hasta completar N lecturas (correspondiente a N opercaciones)
    {
        char* id=(char*)malloc(sizeof(char)*8); //string identificador (toma los valores "malloc" o "free")
        
        //Se lee la primera palabra de la operación actual (iteración i), se almacena en espacio perido para string id.
        fscanf(input, "%s", id);
        
        //*********************
        //**** CASO MALLOC ****
        //*********************

        if ((strcmp(id, m) == 0))
        {
            fscanf(input, "%d", &tamblock); // Aqui leemos cuanta memoria tenemos que asignar

            // Encontramos el primer bloque de memoria que cumple con el espacio suficiente para satisfacer la memoria solicitada
            int NodoLibre = FirstFit(&L1, tamblock); // NodoLibre es la posición del nodo (bloque de memoria) que satisface la petición, en L1
            
            //Caso en que no hay ningun bloque de memoria que cumpla con el espacio solicitado
            if ((NodoLibre == INVALID)){
                fprintf(output, "%s %d %s", "Bloque de ", tamblock, " bytes NO puede ser asignado\n"); 
            }
            //Caso de que sí exista un nodo que satisfaga la petición
            else {
                moveToPos(&L1, NodoLibre);
                
                //Se inserta en L2 el Nodo correspondiente al bloque de memoria asignado
                insert(&L2, getInValue(&L1, getPosCurr(&L1)), (getInValue(&L1, getPosCurr(&L1)) + tamblock-1));

                //Si el nodo que satisface a la petición (en L1) es del tamaño justo, se elimina el nodo completo de L1
                if (tamblock == getTamBlock(&L1 ,NodoLibre)){
                    erase(&L1);
                }
                else { //Si el bloque en L1 que satisface la petición es > que la memoria pedida:
                    int nuevo_in_L1 = (getInValue(&L1, getPosCurr(&L1)) + tamblock); //Calculamos el nuevo comienzo del bloque de L1
                    CambiarInicio(&L1, nuevo_in_L1); // Quitamos de este bloque de memoria, el espacio necesario para tamblock (Re-definiendo el comienzo del bloque )
                }
                   
                fprintf(output, "%s %d %s %d %s", "Bloque de ", tamblock, " bytes asignado a partir del byte ",  getInValue(&L2, getPosCurr(&L2)), "\n");
                moveToEnd(&L2); //Luego de insertar, dejamos el current al final de L2 para que la siguiente inserción (ciclo for) se haga al final.   
            }
            //Liberamos la memoria pedida para el string identificador (free o malloc), la cual se volverá a asignar en cada iteración
            free(id);
        }
        
        //*******************
        //**** CASO FREE ****
        //*******************

        else if ((strcmp(id,f) == 0))
        {
            fscanf(input, "%d" , &bytefree); //Recordar que byetfree es el byte de inico del bloque a liberar

            tElemLista ByteFree = (tElemLista)bytefree; //(Cast a bytefree, obtenido como entero, transformado a tipo lista para usarlo en una función del TDA)
            //Ahora, buscamos en L2 el nodo que comience con el byte indicado (ByteFree)
            tElemLista endfree = buscar_nodo_erase(&L2, ByteFree); //OBS: buscar_nodo_erase, encuentra el nodo y lo elimina de la lista
            
            //Luego se busca la posición adecuada para insertar un bloque de memoria libre en L1 (L1 ordenada de manera creciente)
            buscar_pos_insert(&L1, ByteFree, endfree); //OBS: Esta función encuentra la posición y además inserta el nodo considerando casos de fusión entre nodos consecutivos de memoria libre

            //Indicamos la memoria liberda en bytes
            int liberados = (int)endfree - bytefree;
            liberados++; //agregamos 1 para que cuente la cantidad de bytes totales
            fprintf(output, "%s %d %s", "Bloque de ", liberados, " bytes liberado\n");

            //Liberamos la memoria pedida para el string identificador (free o malloc), la cual se volverá a asignar en cada iteración
            free(id);
        } 
    }

    fclose(input);
    int BSA = ListSize(&L2); //Cantidad de Bloques Sin Asignar
    int asignados = bytes_asignados(&L2); //Esta función suma los bytes correspondientes a los bloques en L2
    fprintf(output, "%s %d %s %d %s", "Quedaron ", BSA, " bloques sin liberar  (", asignados, " bytes)\n");
    fclose(output); 

    return 0;
}
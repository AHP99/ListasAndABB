#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_ABB.h"

/********************
 * int main()
 *******************
 * Resumen Función: 
   Lee el archivo con instrucciones de inserción y borrado, realizando las operaciones en un arbol binario
   de búsqueda. Además se imprime por pantalla el sucesor de cada elemento pedido en el "input", y los elementos
   del arbol en preorden cada vez que se pide.
 ********************
 * input:
   Nada, el archivo "input" debe estar guardado en el mismo directorio que este programa
 ********************
 * Returns:
   int 0 si es que el programa ha finalizado con éxito.
 ********************/
int main()
{
    FILE *input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Problema de apertura de archivo input1.dat, finalizacion anticipada del programa");
        return 1;
    }

    tABB TREE;       //*Creamos el abrol binario
    initTree(&TREE); //*Se inicializa el arbol

    int u; //* u= Cantidad de operaciones a realizar
    fscanf(input, "%d", &u);

    while (feof(input) == 0)
    {
        int elem;
        char *id = (char *)malloc(sizeof(char) * 9);
        fscanf(input, "%s", id);

        if (strcmp(id, "INSERTAR") == 0) //* Insertar elemento en el ABB
        {
            fscanf(input, "%d", &elem);
            insert(&TREE, elem);
        }
        if (strcmp(id, "BORRAR") == 0) //* Borrar el elemento del ABB
        {
            fscanf(input, "%d", &elem);
            treeNode* Ubicacion= find(&TREE, elem);
            borrar(&TREE, Ubicacion);
        }
        if (strcmp(id, "PREORDEN") == 0) //* Entregar ABB en preorden
        {
            preOrden(&TREE);
        }
        if (strcmp(id, "SUCESOR") == 0) //* Entregar el sucesor del numero en el ABB
        {
            fscanf(input, "%d", &elem);
            sucesor(&TREE, (tipoElem)elem, u);
            printf("%d\n", getValue(sucesor(&TREE, (tipoElem)elem, u)));
        }
        free(id);
    }
    fclose(input);
    return 0;
}
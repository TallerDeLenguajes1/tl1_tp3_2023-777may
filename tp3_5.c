#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reservar(char ***listaNombres, int *cantNombres);
void cargar(char **listaNombres, int cantNombres);
void mostar(char **listaNombres, int cantNombres);
void liberarArreglo(char ***listaNombres, int cantNombres);

///////////////////////////////////
void main()
{
    char **listaNombres;
    int cantNombres;

    reservar(&listaNombres, &cantNombres);
    cargar(listaNombres, cantNombres);
    mostar(listaNombres, cantNombres);
    liberarArreglo(&listaNombres, cantNombres);
}
///////////////////////////////////

void reservar(char ***listaNombres, int *cantNombres)
{//reserva memoria para la lista de nombres
    printf("\nIngrese la cantidad de nombres a listar: ");
    scanf("%d", cantNombres);
    *listaNombres = malloc(sizeof(char*)*(*cantNombres));
}
void cargar(char **listaNombres, int cantNombres)
{//carga en la lista los nombres que ingresa el usuario
    char *nombreIngresado = malloc(sizeof(char)*100);
    for (int i = 0; i<cantNombres; i++)
    {
        printf("Ingrese el %d nombre: ", i+1);
        scanf("%s", nombreIngresado);
        listaNombres[i] = malloc(sizeof(char)*(strlen(nombreIngresado)+1));
        strcpy(listaNombres[i], nombreIngresado);
    }
    free(nombreIngresado);    
}
void mostar(char **listaNombres, int cantNombres)
{//muestra cada uno de los nombres de la lista
    for (int i = 0; i<cantNombres; i++)
    {
        printf("\nEl %d nombre es: %s", i+1, listaNombres[i]);
    }
}
void liberarArreglo(char ***listaNombres, int cantNombres)
{//libera la memoria
    for (int i = 0; i<cantNombres; i++)
    {
        //lección aprendida: listaNombres[i] != *listaNombres+i 
        // printf("\nLN+i %d \n", *listaNombres+i);   
        // printf("\nLN+i d %d  s %s \n", (*listaNombres)[i], *(*listaNombres+i));
        free((*listaNombres)[i]);
    }
    free(*listaNombres);
}

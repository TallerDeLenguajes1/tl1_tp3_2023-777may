#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    char **nombres; 
    int cant;

    printf("\nIngrese la cantidad de nombres: ");
    scanf("%d", &cant);

    nombres = malloc(sizeof(char*)*cant);

    char *nombre = malloc(sizeof(char)*100);
    
    for (int i = 0; i<cant; i++){
        printf("\nIngrese el %d nombre: ", i+1);
        scanf("%s", nombre);
        nombres[i] = malloc(sizeof(char)*(strlen(nombre)+1));
        strcpy(nombres[i], nombre);
    }
    free(nombre);    
    
    for (int i = 0; i<cant; i++){
        printf("\nEl %d nombre es: %s", i+1, nombres[i]);
    }

    for (int i = 0; i<cant; i++){
        free(nombres[i]);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cargar(char **Nombres5);
void mostar(char **Nombres5);
void liberarArreglo(char **Nombres5);

void main(){
    char * Nombres5[5];
    cargar(Nombres5);
    mostar(Nombres5);
    liberarArreglo(Nombres5);

}

void cargar(char **Nombres5){
    char *nombre = malloc(sizeof(char)*100);
    for (int i = 0; i<5; i++){
        printf("\nIngrese el %d nombre: ", i+1);
        gets(nombre);
        Nombres5[i] = malloc(sizeof(char)*(strlen(nombre)+1));
        strcpy(Nombres5[i], nombre);
    }
    free(nombre);    
}
void mostar(char **Nombres5){
    for (int i = 0; i<5; i++){
        printf("\nEl %d nombre es: %s", i+1, Nombres5[i]);
    }
}

void liberarArreglo(char **Nombres5){
    for (int i = 0; i<5; i++){
        free(Nombres5[i]);
    }
}
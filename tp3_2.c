
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void cargar(int arreglo[][12]);
void mostrar(int arreglo[][12]);
void C(int arreglo[][12]);
void D(int arreglo[][12]);
void main (){
    int anioXmeses[5][12];
    cargar(anioXmeses);
    mostrar(anioXmeses);
    C(anioXmeses);
    D(anioXmeses);

}
void cargar(int arreglo[][12]){
    srand(time(NULL));
    for (int i = 0; i <5; i++){
        for (int j = 0; j <12; j++){
            arreglo[i][j] = 10000 + rand()% (50000-10000+1);//"Si queremos generar números del 0-10 ese número máximo seria “11” (N+1)" según información en internet
        }
    }
}
void mostrar(int arreglo[][12]){
    for (int i = 0; i <5; i++){
        for (int j = 0; j <12; j++){
            printf("%6d ", arreglo[i][j]);
        }
        printf("\n");
    }
}
void C(int arreglo[][12]){
    for (int i = 0; i <5; i++){
        int gananciaAnio = 0;
        for (int j = 0; j <12; j++){
            gananciaAnio += arreglo[i][j];
        }
        printf("La ganancia promedio del anio %d es: %d.\n", i+1, gananciaAnio/12);
        
    }
}
void D(int arreglo[][12]){
    int gananciaMin = arreglo[0][0];
    int gananciaMax = arreglo[0][0];
    int anioMin = 0;
    int mesMin = 0;
    int anioMax = 0;
    int mesMax = 0;
    for (int i = 0; i <5; i++){
        for (int j = 0; j <12; j++){
            if (gananciaMin > arreglo[i][j])
            { 
                gananciaMin = arreglo[i][j];
                anioMin = i;
                mesMin = j;
            }
            else if (gananciaMax < arreglo[i][j])
            {
                gananciaMax = arreglo[i][j];
                anioMax = i;
                mesMax = j;
            }
        }
    }
        printf("La ganancia maxima fue en el mes %d del anio %d.\n", mesMax+1, anioMax+1);
        printf("La ganancia minima fue en el mes %d del anio %d.\n", mesMin+1, anioMin+1);
}


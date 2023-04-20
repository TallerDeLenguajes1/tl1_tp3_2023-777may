#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct{
int ProductoID; //Numerado en el ciclo iterativo
int Cantidad; // entre 1 y 10
char *TipoProducto; // Algún valor del arreglo TiposProductos
float PrecioUnitario; // entre 10 - 100
} typedef Producto;

struct{
int ClienteID; // Numerado en el ciclo iterativo
char *NombreCliente; // Ingresado por usuario
int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
Producto *Productos; //El tamaño de este arreglo depende de la variable "CantidadProductosAPedir"
} typedef Cliente;

//En atender se usa: cargarClientes y mostrarTodo
//En cargarClientes se usa: cargarProductos
//En mostrarTodo se usa: mostrarProductos y totalAPagarCliente
//En mostrarProductos se usa: costoTotalProducto
//En totalAPagarCliente se usa: costoTotalProducto
void atender(char ** TipoProductos);
void cargarClientes(Cliente *clientes, int cant, char **tipoProd);
void cargarProductos(Cliente cliente, char **tipoProd);
void mostrarTodo(Cliente *clientes, int cant);
void mostrarProductos(Cliente cliente);
float costoTotalProducto(Producto producto);
float totalAPagarCliente(Cliente cliente);


void main(){
    char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

    atender(TiposProductos);
}
void atender(char ** TipoProductos)
{
        int cantClientes;
        Cliente *ListaClientes;
        printf("\nIngrese la cantidad de clientes a atender: ");
        scanf("%d", &cantClientes);
        ListaClientes = malloc(sizeof(Cliente)*cantClientes);
        cargarClientes(ListaClientes, cantClientes, TipoProductos);
        mostrarTodo(ListaClientes, cantClientes);

}
void cargarClientes(Cliente *clientes, int cant, char **tipoProd)
{
    char *nombre;
    srand(time(NULL));
    for (int i = 0; i < cant; i++)
    {
        nombre = malloc(sizeof(char)*100);
        clientes[i].ClienteID = i;
        printf("Ingrese el nombre del cliente nro %d:\n", i+1);
        // scanf("%s", nombre); por algún motivo no funciona
        fflush(stdin);
        gets(nombre);
        clientes[i].NombreCliente = malloc(sizeof(char)*(strlen(nombre)+1));
        strcpy(clientes[i].NombreCliente, nombre);
        clientes[i].CantidadProductosAPedir = 1+ rand()%5;
        clientes[i].Productos = malloc(sizeof(Producto)*clientes[i].CantidadProductosAPedir);
        cargarProductos(clientes[i], tipoProd);
        free(nombre);
    }
}
void cargarProductos(Cliente cliente, char **tipoProd){
    int numeroTipoProducto;
    for (int j = 0; j < cliente.CantidadProductosAPedir; j++)
    {
        char *nombreProd = malloc(sizeof(char)*100);
        numeroTipoProducto = rand()%5;
        cliente.Productos[j].ProductoID = j;
        cliente.Productos[j].Cantidad = 1+ rand()%10;
        nombreProd = tipoProd[numeroTipoProducto];
        cliente.Productos[j].TipoProducto = malloc(sizeof(char)*(strlen(nombreProd)+1));
        strcpy(cliente.Productos[j].TipoProducto, nombreProd);
        cliente.Productos[j].PrecioUnitario = 10 + rand()% 100-10+1 ;
        free(nombreProd);
    }
}
void mostrarTodo(Cliente *clientes, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        printf("Cliente nro %d:\n", i+1);
        printf("  ID: %d\n",clientes[i].ClienteID);
        printf("  Nombre: %s\n",clientes[i].NombreCliente);
        printf("  Cantidad de productos: %d\n",clientes[i].CantidadProductosAPedir);
        mostrarProductos(clientes[i]);
        printf("El total a pagar por el cliente es: %.2f \n", totalAPagarCliente(clientes[i]));
        printf("\n------------------------------------------------------------\n");
    }
}
void mostrarProductos(Cliente cliente)
{
        printf("  Productos: \n");
        for (int j = 0; j < cliente.CantidadProductosAPedir; j++)
        {
            printf("    ID: %d\n", cliente.Productos[j].ProductoID);
            printf("      Cant: %d\n", cliente.Productos[j].Cantidad);
            printf("      Tipo: %s\n", cliente.Productos[j].TipoProducto);
            printf("      Precio unidad: %.2f\n", cliente.Productos[j].PrecioUnitario);
            printf("      Total producto: %.2f\n", costoTotalProducto(cliente.Productos[j]));
        }
}

float costoTotalProducto(Producto producto)
{
    return producto.Cantidad * producto.PrecioUnitario;
}
float totalAPagarCliente(Cliente cliente)
{
    int suma = 0;
    for (int i = 0; i < cliente.CantidadProductosAPedir; i++)
    {
        suma += costoTotalProducto(cliente.Productos[i]);
    }
    return suma;
}
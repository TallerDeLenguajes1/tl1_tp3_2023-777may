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

void atender(char ** TipoProductos);
void asignarMemoriaListaClientes(Cliente **ListaClientes, int *cantClientes);
int controlCantidadClientes(int cantClientes);
void cargarClientes(Cliente *clientes, int cantClientes, char **tipoProd);
void cargarProductos(Cliente cliente_i, char **tipoProd);
void mostrarTodo(Cliente *clientes, int cantClientes);
void mostrarProductos(Cliente cliente_i);
float costoTotalProducto(Producto producto);
float totalAPagarCliente(Cliente cliente);
void liberarMemoria(Cliente **ListaClientes, int cantClientes);

//////////////////
void main()
{
    char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

    atender(TiposProductos);
}
//////////////////

void atender(char ** TipoProductos)
{//crea el puntero lista de clientes y la cantidad de clientes que usarán todas las funciones y llama a las funciones para todo el proceso: asignar, cargar, mostrar y liberar
    int cantClientes;
    Cliente *ListaClientes;
    asignarMemoriaListaClientes(&ListaClientes, &cantClientes);
    cargarClientes(ListaClientes, cantClientes, TipoProductos);
    mostrarTodo(ListaClientes, cantClientes);
    liberarMemoria(&ListaClientes, cantClientes);
}

void asignarMemoriaListaClientes(Cliente **ListaClientes, int *cantClientes)
{//Solicita la cantidad de clientes, controla el numero  y reserva memoria
    do
    {
        printf("\nIngrese la cantidad de clientes a atender: ");
        scanf("%d", cantClientes);
    } while (!controlCantidadClientes((*cantClientes)));
    *ListaClientes = malloc(sizeof(Cliente)*(*cantClientes));
}

int controlCantidadClientes(int cantClientes)
{//controla que la cantidad tal que 0<= cantidad <= 5
    if (cantClientes > 5)
    {
        printf("Cada preventista solo puede visitar hasta 5 clientes.\n");
    }else if (cantClientes < 0)
    {
        printf("Ingrese una cifra valida de 0 a 5\n");
    }   
    return cantClientes <= 5 && cantClientes >= 0;
}

void cargarClientes(Cliente *clientes, int cantClientes, char **tipoProd)
{//carga cada cliente y solicita la carga de los productos
    char *nombreIngresado = malloc(sizeof(char)*100);
    srand(time(NULL));
    for (int i = 0; i < cantClientes; i++)
    {
        clientes[i].ClienteID = i;
        printf("\nIngrese el nombre del cliente nro %d:\n", i+1);
        fflush(stdin);
        scanf("%s", nombreIngresado); 
        clientes[i].NombreCliente = malloc(sizeof(char)*(strlen(nombreIngresado)+1));
        strcpy(clientes[i].NombreCliente, nombreIngresado);
        clientes[i].CantidadProductosAPedir = 1+ rand()%5;
        clientes[i].Productos = malloc(sizeof(Producto)*clientes[i].CantidadProductosAPedir);
        cargarProductos(clientes[i], tipoProd);
    }
    free(nombreIngresado);
}

void cargarProductos(Cliente cliente_i, char **tipoProd)
{//carga los productos del cliente brindado y selecciona los nombres de producto del arreglo 
    int tipoProductoAlAzar;
    char *nombreProd = malloc(sizeof(char)*100);
    for (int j = 0; j < cliente_i.CantidadProductosAPedir; j++)
    {
        tipoProductoAlAzar = rand()%5;
        cliente_i.Productos[j].ProductoID = j;
        cliente_i.Productos[j].Cantidad = 1+ rand()%10;
        nombreProd = tipoProd[tipoProductoAlAzar];
        cliente_i.Productos[j].TipoProducto = malloc(sizeof(char)*(strlen(nombreProd)+1));
        strcpy(cliente_i.Productos[j].TipoProducto, nombreProd);
        cliente_i.Productos[j].PrecioUnitario = 10 + rand()% 100-10+1 ;
    }
    free(nombreProd);
}

void mostrarTodo(Cliente *clientes, int cantClientes)
{//muetra cada cliente, solicita que se muestren los productos y solicita el total a pagar del cliente y lo muestra
    for (int i = 0; i < cantClientes; i++)
    {
        printf("\nCliente nro %d:\n", i+1);
        printf("  ID: %d\n",clientes[i].ClienteID);
        printf("  Nombre: %s\n",clientes[i].NombreCliente);
        printf("  Cantidad de productos: %d\n",clientes[i].CantidadProductosAPedir);
        mostrarProductos(clientes[i]);
        printf("El total a pagar por el cliente es: %.2f \n", totalAPagarCliente(clientes[i]));
        printf("\n------------------------------------------------------------\n");
    }
}

void mostrarProductos(Cliente cliente_i)
{//muestra los productos del cliente dado y solicita el costo total del producto para mostrar
        printf("  Productos: \n");
        for (int j = 0; j < cliente_i.CantidadProductosAPedir; j++)
        { 
            printf("    ID: %d\n", cliente_i.Productos[j].ProductoID);
            printf("      Cant: %d\n", cliente_i.Productos[j].Cantidad);
            printf("      Tipo: %s\n", cliente_i.Productos[j].TipoProducto);
            printf("      Precio unidad: %.2f\n", cliente_i.Productos[j].PrecioUnitario);
            printf("      Total producto: %.2f\n", costoTotalProducto(cliente_i.Productos[j]));
        }
}
float costoTotalProducto(Producto producto)
{//calcula el precio total del producto dado 
    return producto.Cantidad * producto.PrecioUnitario;
}

float totalAPagarCliente(Cliente cliente)
{//por cada producto del cliente solicita el costo total del producto y lo suma hasta tener el total de la suma de los costos
    int suma = 0;
    for (int i = 0; i < cliente.CantidadProductosAPedir; i++)
    {
        suma += costoTotalProducto(cliente.Productos[i]);
    }
    return suma;
}

void liberarMemoria(Cliente **ListaClientes, int cantClientes)
{//libera la memoria del nombre de cada producto de la lista de cada cliente, libera la memoria del nombre y lista de producto de cada cliente y al final libera la memoria de la lista de clientes
    for (int i = 0; i < cantClientes; i++)
    {
        for (int j = 0; j < ListaClientes[i]->CantidadProductosAPedir; j++){
            free(ListaClientes[i]->Productos[j].TipoProducto);
        }
        free(ListaClientes[i]->Productos);
        free(ListaClientes[i]->NombreCliente);
    }
    free(*ListaClientes);
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50

void mostrarProductos();
int buscarProducto(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_PRODUCTOS][MAX_NOMBRE], int numProductos);
void mostrarMenu();
void mandarProducto(int numeroProducto, char nombre[MAX_NOMBRE], float precio, int cantidad);
void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos);
void leerProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos);
void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos);
void venderProductos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos);

void mostrarProductos() {
    FILE *archivo = fopen("baseDatos.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    printf("\n*** Lista de productos ***\n");

    char nombre[MAX_NOMBRE];
    float precio;
    int cantidad;

    while (fscanf(archivo, "%*d %s %f %d", nombre, &precio, &cantidad) == 3) {
        printf("%s - Precio: %.2f - Cantidad: %d\n", nombre, precio, cantidad);
    }

    fclose(archivo);
}

int buscarProducto(const char nombreBuscar[MAX_NOMBRE], char nombres[MAX_PRODUCTOS][MAX_NOMBRE], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            return i;
        }
    }
    return -1;
}

void mostrarMenu() {
    printf("\n*** Micromercado Vaquita - Sistema de Inventario ***\n");
    printf("1. Agregar producto\n");
    printf("2. Mostrar productos\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Vender productos\n");
    printf("6. Salir\n");
}

void mandarProducto(int numeroProducto, char nombre[MAX_NOMBRE], float precio, int cantidad) {
    FILE *archivo = fopen("baseDatos.txt", "a+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
    } else {
        fprintf(archivo, "%d %s %.2f %d\n", numeroProducto, nombre, precio, cantidad);
    }

    fclose(archivo);
}

void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos) {
    printf("\n*** Editar producto***\n");
    if (numProductos == 0) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    mostrarProductos();

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea editar: ");
    scanf("%s", nombreBuscar);

    int indiceProducto = buscarProducto(nombreBuscar, nombres, numProductos);

    if (indiceProducto != -1) {
        printf("Ingrese el nuevo nombre del producto: ");
        scanf("%s", nombres[indiceProducto]);
        printf("Ingrese el nuevo precio del producto: ");
        scanf("%f", &precios[indiceProducto]);
        printf("Ingrese la nueva cantidad en inventario: ");
        scanf("%d", &cantidades[indiceProducto]);

        printf("Producto \"%s\" editado con éxito.\n", nombreBuscar);

        FILE *archivo = fopen("baseDatos.txt", "w");
        for (int j = 0; j < numProductos; j++) {
            fprintf(archivo, "%d %s %.2f %d\n", j + 1, nombres[j], precios[j], cantidades[j]);
        }
        fclose(archivo);
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void leerProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos) {
    int rep, ooo = 0;

    printf("Cuantos productos quiere agregar?");
    scanf("%d", &rep);

    do {
        if (*numProductos < MAX_PRODUCTOS) {
            int numeroProducto = *numProductos + 1; // Asignar un número único al producto

            printf("\nIngrese el nombre del producto: ");
            scanf("%s", nombres[*numProductos]);

            printf("Ingrese el precio del producto: ");
            scanf("%f", &precios[*numProductos]);

            printf("Ingrese la cantidad en inventario del producto: ");
            scanf("%d", &cantidades[*numProductos]);

            mandarProducto(numeroProducto, nombres[*numProductos], precios[*numProductos], cantidades[*numProductos]);

            (*numProductos)++;

            printf("Producto %d agregado con éxito.\n", numeroProducto);
        } else {
            printf("El inventario está lleno. No se puede agregar más productos.\n");
        }

        ooo++;

    } while (ooo < rep);
}

void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int *numProductos) {
    printf("\n*** Eliminar producto ***\n");
    if (*numProductos == 0) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    mostrarProductos();

    char nombreBuscar[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%s", nombreBuscar);

    int indiceProducto = buscarProducto(nombreBuscar, nombres, *numProductos);

    if (indiceProducto != -1) {
        for (int i = indiceProducto; i < *numProductos - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            precios[i] = precios[i + 1];
            cantidades[i] = cantidades[i + 1];
        }
        (*numProductos)--;

        printf("Producto \"%s\" eliminado con éxito.\n", nombreBuscar);

        FILE *archivo = fopen("baseDatos.txt", "w");
        for (int j = 0; j < *numProductos; j++) {
            fprintf(archivo, "%d %s %.2f %d\n", j + 1, nombres[j], precios[j], cantidades[j]);
        }
        fclose(archivo);
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreBuscar);
    }
}

void venderProductos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float precios[MAX_PRODUCTOS], int cantidades[MAX_PRODUCTOS], int numProductos) {
    printf("\n*** Vender productos ***\n");
    if (numProductos == 0) {
        printf("No hay productos en el inventario.\n");
        return;
    }

    mostrarProductos(nombres, precios, cantidades, numProductos);

    char nombreVender[MAX_NOMBRE];
    printf("Ingrese el nombre del producto que desea vender: ");
    scanf("%s", nombreVender);

    int indiceProducto = buscarProducto(nombreVender, nombres, numProductos);

    if (indiceProducto != -1) {
        int cantidadVender;
        printf("Ingrese la cantidad que desea vender: ");
        scanf("%d", &cantidadVender);

        if (cantidadVender > 0 && cantidadVender <= cantidades[indiceProducto]) {
            cantidades[indiceProducto] -= cantidadVender;
            printf("Venta realizada con éxito. Total a pagar: %.2f\n", precios[indiceProducto] * cantidadVender);

            FILE *archivo = fopen("baseDatos.txt", "w");
            for (int j = 0; j < numProductos; j++) {
                fprintf(archivo, "%d %s %.2f %d\n", j + 1, nombres[j], precios[j], cantidades[j]);
            }
            fclose(archivo);
        } else {
            printf("Cantidad no válida.\n");
        }
    } else {
        printf("Producto \"%s\" no encontrado.\n", nombreVender);
    }
}

int main() {
    int opcion;
    int numProductos = 0;

    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float precios[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS];

    do {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                leerProducto(nombres, precios, cantidades, &numProductos);
                break;

            case 2:
                mostrarProductos(nombres, precios, cantidades, numProductos);
                break;

            case 3:
                editarProducto(nombres, precios, cantidades, numProductos);
                break;

            case 4:
                eliminarProducto(nombres, precios, cantidades, &numProductos);
                break;

            case 5:
                venderProductos(nombres, precios, cantidades, numProductos);
                break;

            case 6:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opción no válida\n");
        }

    } while (opcion != 6);

    return 0;
}

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_DATOS 20
#define NUM_PREFIJOS 9

// Escalas y sus multiplicadores
char *prefijos[NUM_PREFIJOS] = {"Pico", "Nano", "Micro", "Mili", "Unidad", "Kilo", "Mega", "Giga", "Tera"};
double multiplicadores[NUM_PREFIJOS] = {1e-12, 1e-9, 1e-6, 1e-3, 1, 1e3, 1e6, 1e9, 1e12};

// Funcion para mostrar menu principal
void mostrarMenu() {
    printf("\n --- MENU PRINCIPAL --- \n");
    printf("1. Ingresar valores\n");
    printf("2. Tabla de valores ingresados\n");
    printf("3. Tabla de conversiones\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

// Funcion para mostrar prefijos disponibles
void mostrarPrefijos() {
    printf("\nPrefijos disponibles:\n");
    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("%d. %s\n", i + 1, prefijos[i]);
    }
}

// Funcion para imprimir la tabla de valores ingresados
void mostrarValoresIngresados(double valores[], int prefijosDatos[], int cantidad) {
    if (cantidad == 0) {
        printf("\nNo hay valores ingresados.\n");
        return;
    }

    printf("\n --- TABLA DE VALORES INGRESADOS ---\n");
    printf("%-10s%-15s%-15s\n", "Indice", "Prefijo", "Valor");
    for (int i = 0; i < cantidad; i++) {
        printf("%-10d%-10s%10.3lf\n", i + 1, prefijos[prefijosDatos[i]], valores[i]);
    }
}

// Funcion para imprimir tabla de conversiones
void mostrarTablaConversiones(double valores[], int prefijosDatos[], int cantidad) {
    if (cantidad == 0) {
        printf("\nPrimero debes ingresar al menos un valor.\n");
        return;
    }

    printf("\n --- TABLA DE CONVERSIONES ---\n");
    printf("%-10s", "Prefijo    ");
    for (int i = 0; i < cantidad; i++) {
        printf("Dato #%d       ", i + 1);
    }
    printf("\n");

    // Mostrar valores por cada prefijo (de pico a tera)
    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("%-10s", prefijos[i]);
        for (int j = 0; j < cantidad; j++) {
            double base = valores[j] * multiplicadores[prefijosDatos[j]];
            double convertido = base / multiplicadores[i];
            printf("%10.3e\t", convertido);
        }
        printf("\n");
    }
}

int main() {
    int opcion;
    double valores[MAX_DATOS];
    int prefijosDatos[MAX_DATOS];
    int cantidad = 0;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                printf("\nCuantos valores deseas ingresar (maximo %d): ", MAX_DATOS);
                scanf("%d", &cantidad);

                if (cantidad < 1 || cantidad > MAX_DATOS) {
                    printf("Cantidad no valida.\n");
                    cantidad = 0;
                    break;
                }

                for (int i = 0; i < cantidad; i++) {
                    printf("\n--- Valor #%d ---\n", i + 1);
                    mostrarPrefijos();
                    int indicePrefijo;
                    printf("Seleccione el numero del prefijo: ");
                    scanf("%d", &indicePrefijo);

                    if (indicePrefijo < 1 || indicePrefijo > NUM_PREFIJOS) {
                        printf("Prefijo no valido. Reintente este valor.\n");
                        i--;
                        continue;
                    }

                    double valor;
                    printf("Ingrese el valor numerico: ");
                    scanf("%lf", &valor);

                    valores[i] = valor;
                    prefijosDatos[i] = indicePrefijo - 1;
                }
                printf("\nValores ingresados correctamente.\n");
                break;
            }
            case 2:
                mostrarValoresIngresados(valores, prefijosDatos, cantidad);
                break;
            case 3:
                mostrarTablaConversiones(valores, prefijosDatos, cantidad);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }

    } while (opcion != 4);

    return 0;
}

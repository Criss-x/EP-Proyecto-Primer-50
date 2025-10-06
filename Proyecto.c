#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_DATOS 7 //Mayor a 7 se desborda el texto en la consola
#define NUM_PREFIJOS 9
#define ANCHO_GRAFICA 100
#define ALTO_GRAFICA 20

// Escalas y sus multiplicadores correspondientes
char *prefijos[NUM_PREFIJOS] = {"Pico", "Nano", "Micro", "Mili", "Unidad", "Kilo", "Mega", "Giga", "Tera"};
double multiplicadores[NUM_PREFIJOS] = {1e-12, 1e-9, 1e-6, 1e-3, 1, 1e3, 1e6, 1e9, 1e12};

// Menu de conversion unidades
void mostrarMenuConversion() {
    printf("\n --- MENU DE CONVERSION DE UNIDADES --- \n");
    printf("1. Ingresar valores\n");
    printf("2. Tabla de valores ingresados\n");
    printf("3. Tabla de conversiones\n");
    printf("4. Volver al menu principal\n");
    printf("Seleccione una opcion: ");
}

void mostrarPrefijos() {
    printf("\nPrefijos disponibles:\n");
    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("%d. %s\n", i + 1, prefijos[i]);
    }
}

void mostrarValoresIngresados(double valores[], int prefijosDatos[], int cantidad) {
    if (cantidad == 0) {
        printf("\nNo has ingresado valores.\n");
        return;
    }

    printf("\n --- TABLA DE VALORES INGRESADOS ---\n");
    printf("%-10s%-15s%-15s\n", "Indice", "Prefijo", "Valor");
    for (int i = 0; i < cantidad; i++) {
        printf("%-10d%-10s%10.3lf\n", i + 1, prefijos[prefijosDatos[i]], valores[i]);
    }
}

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

    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("%-10s", prefijos[i]);
        for (int j = 0; j < cantidad; j++) {
            double base = valores[j] * multiplicadores[prefijosDatos[j]];
            double numConvertido = base / multiplicadores[i];
            printf("%10.3e\t", numConvertido);
        }
        printf("\n");
    }
}

// ---------------------- FUNCIONES PARA GRAFICAR ONDAS ----------------------
void graficarOndaSinusoidal(double frecuencia) {
    printf("\n--- Onda Sinusoidal ---\n");
    for (int j = ALTO_GRAFICA / 2; j >= -ALTO_GRAFICA / 2; j--) {
        for (int i = 0; i < ANCHO_GRAFICA; i++) {
            double valor = sin(2 * M_PI * frecuencia * i / ANCHO_GRAFICA);
            int pos = (int)(valor * (ALTO_GRAFICA / 2));
            if (pos == j)
                printf("*");
            else if (j == 0)
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }
}

// Grafico onda cuadrada
void graficarOndaCuadrada(double frecuencia) {
    printf("\n--- Onda Cuadrada ---\n");

    int alturaGrafica[ANCHO_GRAFICA];
    for (int x = 0; x < ANCHO_GRAFICA; x++) {
        double valor = sin(2 * M_PI * frecuencia * x / ANCHO_GRAFICA);
        alturaGrafica[x] = valor >= 0 ? 1 : -1;
    }

    for (int j = ALTO_GRAFICA / 2; j >= -ALTO_GRAFICA / 2; j--) {
        for (int i = 0; i < ANCHO_GRAFICA; i++) {
            int posActual = alturaGrafica[i] * (ALTO_GRAFICA / 2);

            // Si este punto está en la línea superior o inferior
            if (posActual == j) {
                printf("*");
            }
            // Dibuja la "columna" entre transiciones de alto a bajo
            else if (i > 0 && alturaGrafica[i] != alturaGrafica[i - 1]) {
                int alto = (ALTO_GRAFICA / 2);
                int bajo = -(ALTO_GRAFICA / 2);
                if (j < alto && j > bajo)
                    printf("*");
                else
                    printf(" ");
            }
            else if (j == 0)
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void graficarOndaTriangular(double frecuencia) {
    printf("\n--- Onda Triangular ---\n");
    for (int j = ALTO_GRAFICA / 2; j >= -ALTO_GRAFICA / 2; j--) {
        for (int i = 0; i < ANCHO_GRAFICA; i++) {
            double posicionActual = fmod(frecuencia * i / ANCHO_GRAFICA, 1.0);
            double valor = posicionActual < 0.5 ? (4 * posicionActual - 1) : (-4 * posicionActual + 3);
            int pos = (int)(valor * (ALTO_GRAFICA / 2));
            if (pos == j)
                printf("*");
            else if (j == 0)
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }
}

// Grafica onda en sierra
void graficarOndaSierra(double frecuencia) {
    printf("\n--- Onda en Sierra ---\n");

    // Detecta las posiciones de discontinuidad o saltos
    int discontinuidad[ANCHO_GRAFICA] = {0};
    double posicionInicial = fmod(frecuencia * 0.0 / ANCHO_GRAFICA, 1.0); // fmod
    for (int i = 1; i < ANCHO_GRAFICA; i++) {
        double posicionActual = fmod(frecuencia * i / ANCHO_GRAFICA, 1.0);
        if (posicionActual < posicionInicial) {
            discontinuidad[i] = 1;
        }
        posicionInicial = posicionActual;
    }

    for (int j = ALTO_GRAFICA / 2; j >= -ALTO_GRAFICA / 2; j--) {
        for (int i = 0; i < ANCHO_GRAFICA; i++) {
            double posicionActual = fmod(frecuencia * i / ANCHO_GRAFICA, 1.0);
            double valor = 2 * posicionActual - 1;
            int pos = (int)(valor * (ALTO_GRAFICA / 2));

            if (pos == j) {
                printf("*");
            }
            //Imprime * en la discontinuidad
            else if (discontinuidad[i]) {
                printf("*");
            }
            else if (j == 0) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Menu graficas
void menuGraficas() {
    int opcion;
    double frecuencia;

    do {
        printf("\n--- MENU DE GRAFICAS ---\n");
        printf("1. Onda sinusoidal\n");
        printf("2. Onda cuadrada\n");
        printf("3. Onda triangular\n");
        printf("4. Onda en sierra\n");
        printf("5. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        if (opcion >= 1 && opcion <= 4) {
            printf("Ingrese la frecuencia (recomendada entre 0.5 y 5): ");
            scanf("%lf", &frecuencia);
        }

        switch (opcion) {
            case 1:
                graficarOndaSinusoidal(frecuencia); break;
            case 2:
                graficarOndaCuadrada(frecuencia); break;
            case 3:
                graficarOndaTriangular(frecuencia); break;
            case 4:
                graficarOndaSierra(frecuencia); break;
            case 5:
                printf("Volviendo al menu principal...\n"); break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 5);
}


int main() {
    int opcionPrincipal;
    double valores[MAX_DATOS];
    int prefijosDatos[MAX_DATOS];
    int cantidad = 0;

    do {
        printf("\n  ---   MENU PRINCIPAL  ---  \n");
        printf("1. Conversion de unidades\n");
        printf("2. Graficar ondas\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionPrincipal);

        switch (opcionPrincipal) {
            case 1: {
                int opcionConversion;
                do {
                    mostrarMenuConversion();
                    scanf("%d", &opcionConversion);

                    switch (opcionConversion) {
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
                                    printf("Prefijo no valido. Ingrese nuevamente el valor.\n");
                                    i--;
                                    continue;
                                }

                                double valor;
                                printf("Ingrese el valor: ");
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
                            printf("Volviendo al menu principal...\n");
                            break;
                        default:
                            printf("Opcion no valida. Intente nuevamente.\n");
                    }
                } while (opcionConversion != 4);
                break;
            }
            case 2:
                menuGraficas();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }

    } while (opcionPrincipal != 3);

    return 0;
}

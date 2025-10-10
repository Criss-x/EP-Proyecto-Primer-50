#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 1000
#define PI 3.14149265359
float signal[MAX];
float time[MAX];
int nmuestras;
#define MAX_DATOS 4 // Mayor a 7 se desborda el texto en la consola.
#define NUM_PREFIJOS 9
#define ANCHO_GRAFICA 100
#define ALTO_GRAFICA 20
//-------------------------------------GRAFICADOR DE ONDAS----------------------------------------------------
// Escalas y sus multiplicadores correspondientes
char *prefijos[NUM_PREFIJOS] = {"Pico", "Nano", "Micro", "Mili", "Unidad", "Kilo", "Mega", "Giga", "Tera"};
double multiplicadores[NUM_PREFIJOS] = {1e-12, 1e-9, 1e-6, 1e-3, 1, 1e3, 1e6, 1e9, 1e12};

// ---------------------- FUNCIONES PARA CONVERSION DE UNIDADES ----------------------------------------------

// Menu de conversion unidades
void mostrarMenuConversion() {
    system("cls");
    printf("\n \t\t\t--- MENU DE CONVERSION DE UNIDADES --- \n");
    printf("\t\t\t1. Ingresar valores\n");
    printf("\t\t\t2. Tabla de valores ingresados\n");
    printf("\t\t\t3. Tabla de conversiones\n");
    printf("\t\t\t4. Volver al menu principal\n");
    printf("\t\t\tSeleccione una opcion: ");
}

void mostrarPrefijos() {
    printf("\n\t\t\tPrefijos disponibles:\n");
    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("\t\t\t%d. %s\n", i + 1, prefijos[i]);
    }
}

void mostrarValoresIngresados(double valores[], int prefijosDatos[], int cantidad) {
    
    if (cantidad == 0) {
        printf("\n\t\t\tNo has ingresado valores.\n");
        return;
    }
   

    printf("\n \t\t\t--- TABLA DE VALORES INGRESADOS ---\n");
    printf("\t\t\t%-10s%-15s%-15s\n", "Indice", "Prefijo", "Valor");
    for (int i = 0; i < cantidad; i++) {
        printf("\t\t\t%-10d%-10s%10.5lf\n", i + 1, prefijos[prefijosDatos[i]], valores[i]);
    }
     system("pause");
}

void mostrarTablaConversiones(double valores[], int prefijosDatos[], int cantidad) {
    
    if (cantidad == 0) {
        printf("\n\t\t\tPrimero debes ingresar al menos un valor.\n");
        return;
    }

    printf("\n                   --- TABLA DE CONVERSIONES ---\n\n");
    printf("%-10s", "Prefijo    ");
    for (int i = 0; i < cantidad; i++) {
        printf("%15s%d\t", "Dato #",  i + 1);
    }
    printf("\n");

    for (int i = 0; i < NUM_PREFIJOS; i++) {
        printf("%-10s", prefijos[i]);
        for (int j = 0; j < cantidad; j++) {
            double base =  multiplicadores[prefijosDatos[j]];
            double numConvertido = base / multiplicadores[i];
            //printf("base: %lf\n", base);
            //printf("Num convertido: %lf\n", numConvertido);
            char expo[32];
            sprintf(expo, "%15.5e", numConvertido); //Guarda un numero como un string
            char *exponente = strchr(expo, 'e');
            printf("%12.5f", valores[j]);
            if (exponente != NULL)
                printf("%s\t", exponente);  // imprime solo "e-03"
            else
                printf("");

        }
        printf("\n");
    }
   system("pause");
}

// ---------------------- FUNCIONES PARA GRAFICAR ONDAS ----------------------
void graficarOndaSinusoidal(double frecuencia) {
    printf("\n\t\t\t--- Onda Sinusoidal ---\n");
    for (int j = ALTO_GRAFICA / 2; j >= -ALTO_GRAFICA / 2; j--) {
        for (int i = 0; i < ANCHO_GRAFICA; i++) {
            double valor = sin(2 * PI * frecuencia * i / ANCHO_GRAFICA);
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
    system("pause");
}

// Grafico onda cuadrada
void graficarOndaCuadrada(double frecuencia) {
    printf("\n\t\t\t--- Onda Cuadrada ---\n");

    int alturaGrafica[ANCHO_GRAFICA];
    for (int x = 0; x < ANCHO_GRAFICA; x++) {
        double valor = sin(2 * PI * frecuencia * x / ANCHO_GRAFICA);
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
    system("pause");
}

void graficarOndaTriangular(double frecuencia) {
    printf("\n\t\t\t--- Onda Triangular ---\n");
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
    system("pause");
}
// Grafica onda en sierra
void graficarOndaSierra(double frecuencia) {
    printf("\n\t\t\t--- Onda en Sierra ---\n");

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
    system("pause");
}

// Menu graficas
void menuGraficas() {
   
    int opcion;
    double frecuencia;

    do {
         system("cls");
        printf("\n\t\t\t--- MENU DE GRAFICAS ---\n");
        printf("\t\t\t1. Onda sinusoidal\n");
        printf("\t\t\t2. Onda cuadrada\n");
        printf("\t\t\t3. Onda triangular\n");
        printf("\t\t\t4. Onda en sierra\n");
        printf("\t\t\t5. Volver al menu principal\n");
        printf("\t\t\tSeleccione una opcion: ");
        scanf("%d", &opcion);

         if (opcion >= 1 && opcion <= 4) {
            do{
                printf("\t\t\tIngrese la frecuencia (entre 0.5 y 5): ");
                scanf("%lf", &frecuencia);
                if( frecuencia < 0.5 || frecuencia > 5.0){
                    printf("\t\t\tValor invalido\n");
                }
            } while ( frecuencia < 0.5 || frecuencia > 5.0);
            
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
                printf("\t\t\tVolviendo al menu principal...\n"); break;
            default:
                printf("\t\t\tOpcion no valida.\n");
        }

    } while (opcion != 5);
}
void Principalfuntion(){
    int opcionPrincipal;
    double valores[MAX_DATOS];
    int prefijosDatos[MAX_DATOS];
    int cantidad = 0;

    do {
        system("cls");
        printf("\n\t\t\t  ---   GRAFICADOR DE ONDAS  ---  \n");
        printf("\t\t\t1. Conversion de unidades\n");
        printf("\t\t\t2. Graficar ondas\n");
        printf("\t\t\t3. Salir\n");
        printf("\t\t\tSeleccione una opcion: ");
        scanf("%d", &opcionPrincipal);

        switch (opcionPrincipal) {
            case 1: {
                int opcionConversion;
                do {
                    mostrarMenuConversion();
                    scanf("%d", &opcionConversion);

                    switch (opcionConversion) {
                        case 1: {
                            printf("\n\t\t\tCuantos valores deseas ingresar (maximo %d): ", MAX_DATOS);
                            scanf("%d", &cantidad);

                            if (cantidad < 1 || cantidad > MAX_DATOS) {
                                printf("\t\t\tCantidad no valida.\n");
                                cantidad = 0;
                                break;
                            }

                            for (int i = 0; i < cantidad; i++) {
                                system("cls");
                                printf("\n\t\t\t--- Valor #%d ---\n", i + 1);
                                mostrarPrefijos();
                                int indicePrefijo;
                                printf("\t\t\tSeleccione el numero del prefijo: ");
                                scanf("%d", &indicePrefijo);

                                if (indicePrefijo < 1 || indicePrefijo > NUM_PREFIJOS) {
                                    printf("\t\t\tPrefijo no valido. Ingrese nuevamente el valor.\n");
                                    i--;
                                    continue;
                                }

                                double valor;
                                printf("\t\t\tIngrese el valor: ");
                                scanf("%lf", &valor);
                                valores[i] = valor;
                                prefijosDatos[i] = indicePrefijo - 1;

                                do {
                                    if ( valores[i] >= 1000 && prefijosDatos[i] >= 8 ) {
                                        printf("*_* Superaste el limite superior de valores *_*\nIngresa un valor un poco menos grande\n\n");
                                        printf("\t\t\tIngrese el valor: ");
                                        scanf("%lf", &valor);
                                        valores[i] = valor;
                                        prefijosDatos[i] = indicePrefijo - 1;
                                    }
                                } while (valores[i] >= 1000 && prefijosDatos[i] >= 8);

                                do {
                                    if ( valores[i] < 1 && prefijosDatos[i] <= 0 ) {
                                        printf("*_* Superaste el limite inferior de valores *_*\nIngresa un valor un poco mas grande\n\n");
                                        printf("\t\t\tIngrese el valor: ");
                                        scanf("%lf", &valor);
                                        valores[i] = valor;
                                        prefijosDatos[i] = indicePrefijo - 1;
                                    }
                                } while ( valores[i] < 1 && prefijosDatos[i] <= 0 );

                                do {
                                    if ( valores[i] < 1) {
                                        indicePrefijo--;
                                        valores[i] = valores[i] * 1000;
                                        prefijosDatos[i] = indicePrefijo-1;
                                    }

                                } while (valores[i] < 1);
                                do {
                                    if ( valores[i] >= 1000) {
                                        valores[i] = valores[i] / 1000;
                                        prefijosDatos[i] = indicePrefijo;
                                    }
                                    indicePrefijo++;
                                } while (valores[i] >= 1000);

                            }
                            printf("\n\t\t\tValores ingresados correctamente.\n");
                            break;
                        }
                        case 2:
                            mostrarValoresIngresados(valores, prefijosDatos, cantidad);
                            break;
                        case 3:
                            mostrarTablaConversiones(valores, prefijosDatos, cantidad);
                            break;
                        case 4:
                            printf("\t\t\tVolviendo al menu principal...\n");
                            break;
                        default:
                            printf("\t\t\tOpcion no valida. Intente nuevamente.\n");
                    }
                } while (opcionConversion != 4);
                break;
            }
            case 2:
                menuGraficas();
                break;
            case 3:
                printf("\t\t\tSaliendo del programa...\n");
                break;
            default:
                printf("\t\t\tOpcion no valida. Intente nuevamente.\n");
        }

    } while (opcionPrincipal != 3);

}
//-------------------------------------GENERADOR DE ONDAS ELECTRICAS------------------------------------------
//------------------------------------------------------------------------------------------------------------
//Funciones para filtrar datos
void MenuFiltrado(){
    system("cls");
    printf("\t\t\t\t<<< FILTRAR DATOS >>>\n\n");
    printf("\t\t\t<1> Muestras dentro de un rango\n");
    printf("\t\t\t<2> Filtrar muestra\n");
    printf("\t\t\t<3> Muestras positivas\n");
    printf("\t\t\t<4> Muestras negativas\n");
    printf("\t\t\t<5> Volver\n\n");
    printf("\t\t\tDigite un opcion: ");
}
void MostrarMuestrasFiltradas(float filtro[],int max, int min){
   int j=0;
   float t;
   printf("\t\t\t   ============================================\n");
   printf("\t\t\t     TABLA DE MUESTRAS DE LA ONDA ENTRE %d y %d\n",min,max);
   printf("\t\t\t   --------------------------------------------\n");
   printf("\t\t\t   | N Muestra  |  Tiempo (s) |   Voltaje (V) |\n");
    for(int contador=min;contador<=max;contador++){
    t=time[contador];
    printf("\t\t\t   | %6d     |   %0.6f  |  %8.4f     |\n",contador,t,filtro[j]);
    j++;
   }
   printf("\t\t\t   --------------------------------------------\n\n");

}
void filtrarMuestras(int opc){
    float filtro[MAX];
    if(opc==1){
        int minimo,maximo;
        printf("\t\t\t\tDigite el rango minimo: ");
        scanf("%d",&minimo);
        printf("\t\t\t\tDigite el rango maximo: ");
        scanf("%d",&maximo);
        printf("\t\t\t\n");
        int j=0;
        if(minimo>=1 && maximo<=nmuestras && minimo<maximo){
            for(int contador=minimo;contador<=maximo;contador++){
              filtro[j]=signal[contador-1];
              j++;
       }
       MostrarMuestrasFiltradas(filtro,maximo, minimo);
        }else{
           if(maximo<minimo){
             printf("\t\t\tEl rango maximo debe ser mayor que el rango minimo\n");
           }
           if(maximo>nmuestras){
            printf("\t\t\tError...: El rango debe ocilar entre 1 y el numero de muestras generadas\n");
           }
           printf("\t\t\tSugerencia: Digite un valor entre 1 y %d (cantidad de muestras generadas)\n\n",nmuestras); 

        }
    }else{
        if(opc==2){
            int posicion;
            float muestra_1,t;
            printf("\t\t\tDigite la posicion de la muestra: ");
            scanf("%d",&posicion);
            if(posicion>=1 && posicion<=nmuestras){
                for(int contador=0;contador<posicion;contador++){
                muestra_1=signal[contador];
                t=time[contador];
            }
            printf("\t\t\tLa muestra numero %d en t igual a %f segundos es igual a %f\n\n",posicion,t,muestra_1);

            }else{
                printf("\t\t\tError...: La posicion debe ser un numero entre 1 y %d\n\n",nmuestras);
            }
        }else{
            if(opc==3){
                float nmuestras_2[MAX];
                int j=0;
                printf("\t\t\t   ============================================\n");
                printf("\t\t\t\t  TABLA DE MUESTRAS DE MUESTRAS POSITIVAS\n");
                printf("\t\t\t   --------------------------------------------\n");
                printf("\t\t\t   | N Muestra  |  Tiempo (s) |   Voltaje (V) |\n");
                for(int contador=0;contador<nmuestras;contador++){
                    if(signal[contador]>0){
                        float t = time[contador];
                        nmuestras_2[j]=signal[contador];
                        printf("\t\t\t   | %6d     |   %0.6f  |  %8.4f     |\n",contador+1,t,nmuestras_2[j]);
                        j++;  
                    }
                }
                printf("\t\t\t   --------------------------------------------\n\n"); 
            }else{
                if(opc==4){
                    float nmuestras_2[MAX];
                    int j=0;
                    printf("\t\t\t   ============================================\n");
                    printf("\t\t\t\t  TABLA DE MUESTRAS NEGATIVAS\n");
                    printf("\t\t\t   --------------------------------------------\n");
                    printf("\t\t\t   | N Muestra  |  Tiempo (s) |   Voltaje (V) |\n");
                    for(int contador=0;contador<nmuestras;contador++){
                       if(signal[contador]<0){
                         float t = time[contador];
                         nmuestras_2[j]=signal[contador];
                         printf("\t\t\t   | %6d     |   %0.6f  |  %8.4f     |\n",contador+1,t,nmuestras_2[j]);
                         j++;  
                       }
                    } 
                    printf("\t\t\t   --------------------------------------------\n\n");
                }
            }
        }
    }
}
void manejoDeOpciones3(){
    int opc=0;
    while(opc!=5){
        MenuFiltrado();
        scanf("%d",&opc);
        switch (opc){
        case 1:system("cls");
        filtrarMuestras(opc);
        break;
        case 2:system("cls");
        filtrarMuestras(opc);
        break;
        case 3:system("cls");
        filtrarMuestras(opc);
        break;
        case 4:system("cls");
        filtrarMuestras(opc);
        break;
        case 5:
        opc=5;
        break;
        default:
        printf("\t\t\tError, opcion invalida\n\n");
        break;
        }

    system("pause");
    }
}
//-------------------------------------------------------------------------------------------------------------
//Funcion o metodo ValorRms, calcula el Voltage y la corriente rms mediante la informacion de la onda generada.
float ValorRms(int nmuestras){
    float rms,suma=0;
    for(int cont=0;cont<nmuestras;cont++){
        suma=pow(signal[cont],2)+suma;
    }
    rms=sqrt(((float)1/nmuestras)*suma);
    return rms;
}
//---------------------------------------------------------------------------------------------------------------
float PotenciaPromedio(int r){
    float potencia=pow(ValorRms(nmuestras),2)/r;
     return potencia;
}
//-------------------------------------------------------------------------------------------------------------
float valorPromedio(int nmuestras){
    float suma=0;
    float promedio;
    for(int contador=0;contador<nmuestras;contador++){
        suma=suma+signal[contador];
    }
    promedio=fabsf(suma/nmuestras);
    return promedio;

}
//---------------------------------------------------------------------------------------------------------------
float valorMinimo(int nmuestras){
    float min=signal[0];
    for(int contador=1;contador<nmuestras;contador++){
        if(signal[contador]<min){
            min=signal[contador];
        }
    }
    return min;

}
//---------------------------------------------------------------------------------------------------------------
float valorMaximo(int nmuestras){
    float max=signal[0];
    for(int contador=1;contador<nmuestras;contador++){
        if(signal[contador]>max){
              max=signal[contador];
        }
    }
    return max;

}
//---------------------------------------------------------------------------------------------------------------
void MostrarTabla(int n){
   float muestra=0;
   float t;
   printf("\t\t\t   ============================================\n");
   printf("\t\t\t\t  TABLA DE MUESTRAS DE LA ONDA\n");
   printf("\t\t\t   --------------------------------------------\n");
   printf("\t\t\t   | N Muestra  |  Tiempo (s) |   Voltaje (V) |\n");
   for(int contador=0;contador<n;contador++){
    muestra=signal[contador];
    t=time[contador];
    printf("\t\t\t   | %6d     |   %0.6f  |  %8.4f     |\n",contador+1,t,signal[contador]);
   }
    printf("\t\t\t   --------------------------------------------\n\n");


}
//---------------------------------------------------------------------------------------------------------------
//Permite generar el tipo de señal 
float GeneradorSignal(int n, int opc,float vp,float f){
    if(f>0 && vp!=0){
         if(opc==1){
        for(int contador=0;contador<n;contador++){
            time[contador]=(float)contador/(f*n);
            signal[contador]=vp*sin(2*PI*f*time[contador]);
        }
    }else{
        if(opc==2){
            for(int contador=0;contador<n;contador++){
                time[contador]=(float)contador/(f*n);
                signal[contador]=(sin(2*PI*f*time[contador])>=0) ? vp : -vp;

            }

        }else{
            if(opc==3){
                double p=1/f;
                for(int cont=0;cont<n;cont++){
                
                time[cont]=cont*(p)/n;
                double t_mod=fmod(time[cont],p);
                signal[cont]=(4*vp/p)*fabs(t_mod-p/2)-vp;

                }
            }
        }
    }
    }
}
//---------------------------------------------------------------------------------------------------------------
void Menu1(){
    printf("\t\t\t        <<<ANALIZADOR DE ONDA>>>\n\n");
    printf("\t\t\t<1> Mostrar muestras de la onda\n");
    printf("\t\t\t<2> Calcular el valor maximo y el minimo\n");
    printf("\t\t\t<3> Calcular valor promedio\n");
    printf("\t\t\t<4> Calcular valor RMS\n");
    printf("\t\t\t<5> Calcular potencia promedio (requiere R)\n");
    printf("\t\t\t<6> Filtrar datos\n");
    printf("\t\t\t<7> Salir\n\n");
    printf("\t\t\tDigite un opcion: ");
}
//---------------------------------------------------------------------------------------------------------------
void MenuDesignal(){
    system("cls");
    printf("\t\t\tONDAS DISPONIBLES\n\n");
    printf("\t\t\t<1> Senoidal\n");
    printf("\t\t\t<2> Cuadrada\n");
    printf("\t\t\t<3> Triangular\n\n");
    printf("\t\t\tDigite un opcion: ");
}
//---------------------------------------------------------------------------------------------------------------
//Funcion o metodo ManejoDeOpciones1 que nos permite navegar por un menu para analizar la señal.
void ManejoDeOpciones1(){
    system("cls");
    int opc;
    while(opc!=7){
        system("cls");
        Menu1();
        scanf("%d",&opc);
        switch(opc){
        case 1:system("cls");
        MostrarTabla(nmuestras);
        system("pause"); 
        break;
        case 2:system("cls");
        float maximo=valorMaximo(nmuestras);
        float minimo=valorMinimo(nmuestras);
        printf("\t\t\tEl valor maximo de la onda con %d muestras es: %f\n",nmuestras,maximo);
        printf("\t\t\tEl valor minimo de la onda con %d muestras es: %f\n\n",nmuestras,minimo);
        system("pause"); 
        break;
        case 3:system("cls");
        printf("\t\t\tEl valor promedio de la onda con la %d muestras es: %f\n\n",nmuestras,valorPromedio(nmuestras));
         printf("\t\t\tNota: El valor promedio de una onda tiende a cero entre mas muestras se generen.\n\n");
        system("pause");
        break;
        case 4:system("cls");
        printf("\t\t\tEl volage RMS de la onda con %d muestras es: %f\n\n",nmuestras,ValorRms(nmuestras));
        system("pause");
        break;
        case 5:system("cls");
        int r;
        printf("\t\t\tDigite el valor de una resistencia en ohms: ");
        scanf("%d",&r);
        printf("\t\t\tLa potencia promedio de la onda es: %f\n",PotenciaPromedio(r));
        system("pause");
        break;
        case 6:
        manejoDeOpciones3();
        break;
        case 7:
        printf("\t\t\tSaliendo...\n");
        opc=7;
        break;
        default:system("cls");
        printf("\t\t\tOpcion invalida\n");
         system("pause"); 
        break;
        }
    }
    
}
//---------------------------------------------------------------------------------------------------------------
// Funcion o metodo ManejoDeOpciones2 que nos permite navegar por un menu de opciones.
void ManejoDeOpciones2(){
    int opc=0;
    float frecuencia;
    int opc2=0;
    float valorpico;
    printf("\t\t\tGENERAR UNA ONDA A PARTIR DE SU FRECUENCIA Y AMPLITUD \n\n");
    printf("\t\t\tDigite el numero de muestras a generar: ");
    scanf("%d",&nmuestras);
    printf("\t\t\tIngrese la frecuencia de la onda en Hz: ");
    scanf("%f",&frecuencia);
    printf("\t\t\tIngrese el valor pico en Voltios: ");
    scanf("%f",&valorpico);
    if(nmuestras < MAX && nmuestras > 0 && frecuencia > 0){
        MenuDesignal();
        scanf("%d",&opc);
        switch(opc){
        case 1:system("cls");
        GeneradorSignal(nmuestras,opc,valorpico,frecuencia);
        printf("\t\t\tMuestras generadas exitosamente\n\n");
        ManejoDeOpciones1();
        break;
        case 2:system("cls");
        GeneradorSignal(nmuestras,opc,valorpico,frecuencia);
        printf("\t\t\tMuestras generadas exitosamente\n\n");
        ManejoDeOpciones1();
        break;
        case 3:system("cls");
        GeneradorSignal(nmuestras,opc,valorpico,frecuencia);
        printf("\t\t\tMuestras generadas exitosamente\n\n");
        ManejoDeOpciones1();
        break;
        default:
        printf("\t\t\tError, opcion invalida\n\n");
        break;
    }
        }else{
        printf("\t\t\tError, exede el numero maximo de muestras que se pueden generar (1000 muestras maximo)\n\n");
        }
}
//---------------------------------------------------------------------------------------------------------------
void MenuPrincipal(){
    system("cls");
    printf("\t\t\t<< MENU PRINCIPAL >>\n\n");
    printf("\t\t\t<1> Generador de ondas electricas\n");
    printf("\t\t\t<2> Graficador de ondas\n");
    printf("\t\t\t<3> Finalizar\n\n");
    printf("\t\t\tDigite un opcion: ");
}
//---------------------------------------------------------------------------------------------------------------
//Funcion que controla todo el programa.
void manejoDeOpciones(){
    int opc=0;
    while(opc!=3){
        MenuPrincipal();
        scanf("%d",&opc);
        switch (opc){
        case 1:system("cls");
        ManejoDeOpciones2();
        break;
        case 2:system("cls");
        Principalfuntion();
        break;
        case 3:system("cls");
        opc=3;
        break;
        default:
        printf("\t\t\tError, opcion invalida\n\n");
        break;
        }

    system("pause");
    }
}
int main(){
    manejoDeOpciones();
    return 0;
}


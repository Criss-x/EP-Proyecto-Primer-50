#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Nombre Propio
void NombrePropio(char *nombrePropio) {
    if (strlen(nombrePropio) > 1) {
        nombrePropio[0] = toupper(nombrePropio[0]);
    }
    for (int i = 0; i < strlen(nombrePropio); i++) {
        if (nombrePropio[i] == ' ' ) {
            nombrePropio[(i+1)] = toupper(nombrePropio[(i+1)]);
        }
        printf("%c", nombrePropio[i]);
    }
}

//Contar caracteres
void contarCaracteres(char *cadCaracteres, char caracter) {
    int contador = 0;
    for (int i = 0; i < strlen(cadCaracteres); i++) {
        if ( tolower(cadCaracteres[i]) == caracter ) {
            contador++;
            }
    }
    printf("El caracter %c se encuentra %i veces en la cadena de texto", caracter, contador);
}

//Contar palabras
int contarPalabras(char *texto, char *palabra) {
    int contador = 0;
    char textoAlmacenado[100];
    int j = 0;

    for (int i = 0; i <= strlen(texto); i++) {
        if (texto[i] == ' ' || texto[i] == '\0') {
            textoAlmacenado[j] = '\0';
            if (strcmp(textoAlmacenado, palabra) == 0) {
                contador++;
            }
            j = 0;
        } else {
            textoAlmacenado[j] = texto[i];
            j++;
        }
    }
    return contador;
}

//SUBSTRING
typedef char* (*subCadena)(char[], int);
typedef char* (*SubCadena)(char[], int, int);

char* subCadenaInicio(char texto[], int inicio) {
    static char resultado[200];
    int longitud = strlen(texto);

    if (inicio < 0) {
        inicio = 0;
    }
    if (inicio >= longitud) {
        return "";
    }
    strcpy(resultado, texto + inicio);
    return resultado;
}
char* subCadenaFin(char texto[], int inicio, int fin) {
    static char resultado[200];
    int longitud = strlen(texto);

    if (inicio < 0) inicio = 0;
    if (fin > longitud) fin = longitud;

    int i = 0;
    if (inicio <= fin) {
        for (int j = inicio; j < fin && j < longitud; j++) {
            resultado[i++] = texto[j];
        }
    } else {
        for (int j = inicio; j > fin && j >= 0; j--) {
            resultado[i++] = texto[j];
        }
    }
    resultado[i] = '\0';
    return resultado;
}

//Bases Numéricas
char *convertirBase(char *numeroDecimal, int base) {
    static char resultado[100];
    int num = 0;

    //Verificamos que todos los valores ingresados son numeros usando !isdigit
    for (int i = 0; i < strlen(numeroDecimal); i++) {
        if (!isdigit(numeroDecimal[i])) {
            return NULL;
        }
    }

    // Atoi convierte la cadena de caracteres a un  numero entero
    num = atoi(numeroDecimal);

    //Verifica que se haya escogido una base valida
    if (base < 2 || base > 16) {
        return NULL;
    }

    //Caracteres validos para representar en bases 2...16
    char digitos[] = "0123456789ABCDEF";
    int i = 0;

    if (num == 0) {
        strcpy(resultado, "0");
        return resultado;
    }

    while (num > 0) {
        resultado[i++] = digitos[num % base];
        num /= base;
    }
    resultado[i] = '\0';

    // Invierte el resultado
    for (int j = 0; j < i / 2; j++) {
        char temp = resultado[j];
        resultado[j] = resultado[i - j - 1];
        resultado[i - j - 1] = temp;
    }

    return resultado;
}

//Palindromo
int Palindromo(char palabra[]) {
    int i = 0;
    int j = strlen(palabra) - 1;

    while (i < j) {
        if (tolower(palabra[i]) != tolower(palabra[j])) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

int main(){

    //Nombre Propio
    char nombrePropio[100];
    printf("Ingrese un texto: ");
    fgets(nombrePropio, sizeof(nombrePropio), stdin);
    nombrePropio[strcspn(nombrePropio, "\n")] = 0; //No guarda el salto de linea
    printf("Reescrito como nombre propio: ");
    NombrePropio(nombrePropio);

    //Contar caracteres
    char caracter;
    char cadCaracteres[100];
    printf("\nIngresa un texto: ");
    fgets(cadCaracteres, sizeof(cadCaracteres), stdin);
    cadCaracteres[strcspn(cadCaracteres, "\n")] = 0;
    printf("Ingresa el caracter que deseas encontrar: \n");
    scanf("%c", &caracter);
    contarCaracteres(cadCaracteres, caracter);

    //Contar palabras
    getchar();
    char texto[200];
    char palabra[50];
    printf("\nIngrese un texto: \n");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0;

    printf("Ingrese la palabra que desea buscar: \n");
    fgets(palabra, sizeof(palabra), stdin);
    palabra[strcspn(palabra, "\n")] = 0;

    int nVeces = contarPalabras(texto, palabra);
    printf("La palabra '%s' aparece %d veces en el texto.\n", palabra, nVeces );


    //SUBSTRING
    int inicio;
    int fin;
    int opcion;
    char cadenaDeTexto[100];
    //char cadenaDeTexto[] = "Sogamoso ciudad del Sol y del Acero"; //EJEMPLO
    printf("1. Obtener subcadena desde un indice\n");
    printf("2. Obtener subcadena entre inicio y fin\n");
    printf("Elige una opcion: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1) {
        printf("Ingrese una cadena de texto: ");
        fgets(cadenaDeTexto, sizeof(cadenaDeTexto), stdin);
        cadenaDeTexto[strcspn(cadenaDeTexto, "\n")] = 0;
        printf("Ingrese el indice de inicio: ");
        scanf("%d", &inicio);
        printf("\nResultado: %s\n", subCadenaInicio(cadenaDeTexto, inicio));
    }
    else if (opcion == 2) {
        printf("Ingrese una cadena de texto: ");
        fgets(cadenaDeTexto, sizeof(cadenaDeTexto), stdin);
        cadenaDeTexto[strcspn(cadenaDeTexto, "\n")] = 0;
        printf("Ingrese el indice de inicio: ");
        scanf("%d", &inicio);
        printf("Ingrese el indice de fin: ");
        scanf("%d", &fin);
        printf("Resultado: %s\n", subCadenaFin(cadenaDeTexto, inicio, fin));
    }
    else {
        printf("Opcion no valida.\n");
    }


    //Bases Numéricas
    char numeroDecimal[100];
    int base;
    printf("Ingresa un numero decimal: \n");
    scanf("%s", &numeroDecimal);
    printf("Ingresa la base a la cual convertir ( 2...16 ): ");
    scanf("%d", &base);
    convertirBase(numeroDecimal, base);
    printf("El numero %s en base %i es: %s\n", numeroDecimal, base, convertirBase(numeroDecimal, base));

    //Palindromo
    char palabra_palindromo[100];

    printf("Ingrese una palabra: ");
    scanf("%s", palabra_palindromo);

    if (Palindromo(palabra_palindromo)) {
        printf("La palabra '%s' es palindromo\n", palabra_palindromo);
    } else {
        printf("La palabra '%s' no es palindromo\n", palabra_palindromo);
    }
    return 0;
}
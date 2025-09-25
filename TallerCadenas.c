#include <stdio.h>
#include <string.h>
#include <ctype.h>

void NombrePropio(char *nombrePropio) {
    if (strlen(nombrePropio) > 2) {
        nombrePropio[0] = toupper(nombrePropio[0]);
    }
    for (int i = 0; i < strlen(nombrePropio); i++) {
        if (nombrePropio[i] == ' ' ) {
            nombrePropio[(i+1)] = toupper(nombrePropio[(i+1)]);
        }
        printf("%c ", nombrePropio[i]);
    }
}

void contarCaracteres(char *cadCaracteres, char caracter) {
    int contador = 0;
    for (int i = 0; i < strlen(cadCaracteres); i++) {
        if ( tolower(cadCaracteres[i]) == caracter ) {
            contador++;
            }
    }
    printf("El caracter %c se encuentra %i veces en la cadena de texto", caracter, contador);
}

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
    char nombrePropio[100];
    printf("Ingrese un texto: ");
    fgets(nombrePropio, sizeof(nombrePropio), stdin);
    nombrePropio[strcspn(nombrePropio, "\n")] = 0; //No guarda el salto de linea
    printf("Reescrito como nombre propio: ");
    NombrePropio(nombrePropio);

    char caracter;
    char cadCaracteres[100];
    printf("\nIngresa un texto: ");
    fgets(cadCaracteres, sizeof(cadCaracteres), stdin);
    cadCaracteres[strcspn(cadCaracteres, "\n")] = 0;
    printf("Ingresa el caracter que deseas encontrar: ");
    scanf("%c", &caracter);
    contarCaracteres(cadCaracteres, caracter);

    getchar();
    char texto[200];
    char palabra[50];
    printf("\nIngrese un texto: \n");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0;

    getchar();
    printf("\nIngrese la palabra que desea buscar: \n");
    fgets(palabra, sizeof(palabra), stdin);
    palabra[strcspn(palabra, "\n")] = 0;

    int nVeces = contarPalabras(texto, palabra);
    printf("La palabra '%s' aparece %d veces en el texto.\n", palabra, nVeces );


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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void NombrePropio(char *nombrePropio) {
    // strlen() > 2 ya que la cadena almacena un un valor de mas que corresponde al salto de linea
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

void contarCaracteres(char *nombrePropio, char caracter) {
    int contador = 0;
    for (int i = 0; i < strlen(nombrePropio); i++) {
        if ( tolower(nombrePropio[i]) == caracter ) {
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

int main(){
    char nombrePropio[100];
    printf("Ingrese su nombre: ");
    fgets(nombrePropio, sizeof(nombrePropio), stdin);
    NombrePropio(nombrePropio);

    char caracter;
    printf("\nIngresa el caracter que deseas encontrar: ");
    scanf("%c", &caracter);
    contarCaracteres(nombrePropio, caracter);

    getchar();
    char texto[200];
    char palabra[50];
    printf("\nIngrese un texto: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0;

    getchar();
    printf("\nIngrese la palabra que desea buscar: ");
    fgets(palabra, sizeof(palabra), stdin);
    palabra[strcspn(palabra, "\n")] = 0;

    int nVeces = contarPalabras(texto, palabra);
    printf("La palabra '%s' aparece %d veces en el texto.\n", palabra, nVeces );

}

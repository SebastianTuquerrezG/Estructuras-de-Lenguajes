#include <stdio.h>
#include <ctype.h>

// Función para cifrar un carácter usando el cifrado César
char cifrarCesar(char letra, int desplazamiento) {
    // Verificar si la letra es una letra del alfabeto
    if (isalpha(letra)) {
        // Obtener el rango de valores ASCII para mayúsculas o minúsculas
        int rango = isupper(letra) ? 'A' : 'a';
        // Aplicar el desplazamiento y asegurarse de que la letra resultante esté dentro del rango de letras
        return (char)(((letra - rango + desplazamiento - 1) % 26) + rango);
    } else {
        // Si no es una letra del alfabeto, mantener el carácter tal como está
        return letra;
    }
}

// Función para cifrar una cadena usando el cifrado César
void cifrarCesarCadena(char cadena[], int desplazamiento) {
    int i = 0;
    // Iterar sobre cada carácter de la cadena
    while (cadena[i] != '\0') {
        // Cifrar el carácter y reemplazarlo en la cadena
        cadena[i] = cifrarCesar(cadena[i], desplazamiento);
        i++;
    }
}

int main() {
    char mensaje[100];
    int desplazamiento;

    // Solicitar al usuario que ingrese el mensaje y el desplazamiento
    printf("Ingrese el mensaje a cifrar: ");
    fgets(mensaje, sizeof(mensaje), stdin);
    printf("Ingrese el desplazamiento (número entero positivo): ");
    scanf("%d", &desplazamiento);

    // Cifrar el mensaje
    cifrarCesarCadena(mensaje, desplazamiento);

    // Mostrar el mensaje cifrado
    printf("Mensaje cifrado: %s\n", mensaje);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Función para convertir un string a minúsculas
void toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

void stringMatching(char *texto, char *patron) {
    int n = strlen(texto);
    int m = strlen(patron);

    toLowerCase(texto);
    toLowerCase(patron);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (texto[i + j] != patron[j]) {
                break; // Si encuentra un carácter diferente, salimos del bucle
            }
        }
        if (j == m) {
            printf("Patron encontrado en el indice %d\n", i);
        }
    }
}

int main() {
    char texto[] = "Este es un ejemplo de Texto para buscar todas las ocurrencias de una palabra en un texto mas largo.";
    char patron[] = "texto";

    printf("Texto: %s\n", texto);
    printf("Patron: %s\n", patron);

    printf("Resultados:\n");
    stringMatching(texto, patron);

    return 0;
}

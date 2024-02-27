#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

char document[MAX_LINES][MAX_LENGTH];
int lines = 0;

void addLine() {
    if (lines < MAX_LINES) {
        printf("Ingresa el texto de la nueva linea:\n");
        fgets(document[lines], MAX_LENGTH, stdin);
        lines++;
    } else {
        printf("Documento lleno, no se puede agregar una nueva linea.\n");
    }
}

void deleteLine(int lineNum) {
    if (lineNum >= 0 && lineNum < lines) {
        for (int i = lineNum; i < lines - 1; i++) {
            strcpy(document[i], document[i + 1]);
        }
        lines--;
    } else {
        printf("Numero de linea invalido.\n");
    }
}

void createDocument() {
    lines = 0;
    printf("Documento creado.\n");
}

void deleteDocument() {
    lines = 0;
    printf("Documento eliminado.\n");
}

void modifyLine(int lineNum) {
    if (lineNum >= 0 && lineNum < lines) {
        printf("Ingresa el nuevo texto de la linea %d:\n", lineNum + 1);
        fgets(document[lineNum], MAX_LENGTH, stdin);
    } else {
        printf("Numero de linea invalido.\n");
    }
}

void displayDocument() {
    printf("Documento:\n");
    for (int i = 0; i < lines; i++) {
        printf("%d. %s", i + 1, document[i]);
    }
}

int main() {
    int choice;
    int lineNum;

    while (1) {
        printf("\n Menu de Opciones:\n");
        printf("1. Añadir linea\n");
        printf("2. Eliminar linea\n");
        printf("3. Crear documento\n");
        printf("4. Eliminar documento\n");
        printf("5. Modificar linea\n");
        printf("6. Mostrar documento\n");
        printf("7. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                addLine();
                break;
            case 2:
                printf("Ingrese el numero de linea a eliminar: ");
                scanf("%d", &lineNum);
                deleteLine(lineNum - 1);
                break;
            case 3:
                createDocument();
                break;
            case 4:
                deleteDocument();
                break;
            case 5:
                printf("Ingrese el numero de linea a modificar: ");
                scanf("%d", &lineNum);
                modifyLine(lineNum - 1);
                break;
            case 6:
                displayDocument();
                break;
            case 7:
                exit(0);
            default:
                printf("Opcion invalida.\n");
        }
    }
}
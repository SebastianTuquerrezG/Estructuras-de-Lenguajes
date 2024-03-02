#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 300
#define MAX_LENGTH 30

typedef struct historiaLaboral{
    char empresa[20];
    char cargo[15];
    char fechaInicio[10];
    char fechaFin[10];
    struct historiaLaboral* next;
} historiaLaboral;

typedef struct pregrado{
    char titulo[20];
    struct pregrado* next;
} pregrado;

typedef struct posgrado{
    char titulo[20];
    char especializacion[15];
    struct posgrado* next;
} posgrado;

typedef struct persona{
    char cedula[12];
    char nombre[15];
    char apellido[15];
    char edad[3];
    char direccion[15];
    char telefono[10];
    char email[20];
    pregrado *pregrados;
    posgrado *posgrados;
    historiaLaboral *historiasLaborales;
    struct persona* next;
} persona;

persona *head = NULL;

int lines = 0;

void addLine() {
    persona *new_person = malloc(sizeof(persona));
    if (new_person == NULL) {
        printf("Error al reservar memoria.\n");
        return;
    }

    printf("Ingresa los datos de la nueva persona:\n");
    printf("Cedula: ");
    fgets(new_person->cedula, MAX_LENGTH, stdin);
    printf("Nombre: ");
    fgets(new_person->nombre, MAX_LENGTH, stdin);
    printf("Apellido: ");
    fgets(new_person->apellido, MAX_LENGTH, stdin);
    printf("Edad: ");
    fgets(new_person->edad, MAX_LENGTH, stdin);
    printf("Direccion: ");
    fgets(new_person->direccion, MAX_LENGTH, stdin);
    printf("Telefono: ");
    fgets(new_person->telefono, MAX_LENGTH, stdin);
    printf("Email: ");
    fgets(new_person->email, MAX_LENGTH, stdin);

    // Agregar pregrados
    new_person->pregrados = NULL;
    pregrado *pregrado_temp = NULL;
    do {
        pregrado_temp = malloc(sizeof(pregrado));
        if (pregrado_temp == NULL) {
            printf("Error al reservar memoria.\n");
            return;
        }
        printf("Ingresa un pregrado (o '0' para dejar de ingresar): ");
        fgets(pregrado_temp->titulo, MAX_LENGTH, stdin);
        pregrado_temp->next = NULL;

        if (strcmp(pregrado_temp->titulo, "0\n") != 0) {
            pregrado_temp->next = new_person->pregrados;
            new_person->pregrados = pregrado_temp;
        } else {
            free(pregrado_temp);
            break;
        }
    } while (1);

    // Agregar posgrados
    new_person->posgrados = NULL;
    posgrado *posgrado_temp = NULL;
    int posgrados_index;
    printf("Cuantos posgrados tiene:\n");
    scanf("%d", &posgrados_index);
    getchar();
    for (int i = 0; i < posgrados_index; i++) {
        posgrado_temp = malloc(sizeof(posgrado));
        if (posgrado_temp == NULL) {
            printf("Error al reservar memoria.\n");
            return;
        }
        printf("Titulo del posgrado: ");
        fgets(posgrado_temp->titulo, MAX_LENGTH, stdin);
        printf("Especializacion: ");
        fgets(posgrado_temp->especializacion, MAX_LENGTH, stdin);
        posgrado_temp->next = new_person->posgrados;
        new_person->posgrados = posgrado_temp;
    }

    // Agregar historias laborales
    new_person->historiasLaborales = NULL;
    historiaLaboral *historia_temp = NULL;
    int historias_index;
    printf("Cuantas historias laborales tiene:\n");
    scanf("%d", &historias_index);
    getchar();
    for (int i = 0; i < historias_index; i++) {
        historia_temp = malloc(sizeof(historiaLaboral));
        if (historia_temp == NULL) {
            printf("Error al reservar memoria.\n");
            return;
        }
        printf("Empresa: ");
        fgets(historia_temp->empresa, MAX_LENGTH, stdin);
        printf("Cargo: ");
        fgets(historia_temp->cargo, MAX_LENGTH, stdin);
        printf("Fecha de inicio: ");
        fgets(historia_temp->fechaInicio, MAX_LENGTH, stdin);
        printf("Fecha de fin: ");
        fgets(historia_temp->fechaFin, MAX_LENGTH, stdin);
        historia_temp->next = new_person->historiasLaborales;
        new_person->historiasLaborales = historia_temp;
    }

    new_person->next = head;
    head = new_person;
}

void deleteLine(int lineNum) {
    if (lineNum < 1 || lineNum > lines) {
        printf("Numero de linea invalido.\n");
        return;
    }

    persona *current = head;
    persona *prev = NULL;

    int count = 1;
    while (current != NULL && count < lineNum) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Numero de linea invalido.\n");
        return;
    }

    // Liberar la memoria de los pregrados
    pregrado *pregrado_temp = current->pregrados;
    while (pregrado_temp != NULL) {
        pregrado *temp = pregrado_temp;
        pregrado_temp = pregrado_temp->next;
        free(temp);
    }

    // Liberar la memoria de los posgrados
    posgrado *posgrado_temp = current->posgrados;
    while (posgrado_temp != NULL) {
        posgrado *temp = posgrado_temp;
        posgrado_temp = posgrado_temp->next;
        free(temp);
    }

    // Liberar la memoria de las historias laborales
    historiaLaboral *historia_temp = current->historiasLaborales;
    while (historia_temp != NULL) {
        historiaLaboral *temp = historia_temp;
        historia_temp = historia_temp->next;
        free(temp);
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    lines--;
}

void displayDocument() {
    printf("Documento:\n");
    persona *current = head;
    int count = 1;

    while (current != NULL) {
        printf("%d. Cedula: %s\n", count, current->cedula);
        printf("   Nombre: %s\n", current->nombre);
        printf("   Apellido: %s\n", current->apellido);
        printf("   Edad: %s\n", current->edad);
        printf("   Direccion: %s\n", current->direccion);
        printf("   Telefono: %s\n", current->telefono);
        printf("   Email: %s\n", current->email);
        printf("   Pregrados:\n");

        pregrado *pregrado_temp = current->pregrados;
        while (pregrado_temp != NULL) {
            printf("       - %s\n", pregrado_temp->titulo);
            pregrado_temp = pregrado_temp->next;
        }

        printf("   Posgrados:\n");

        posgrado *posgrado_temp = current->posgrados;
        while (posgrado_temp != NULL) {
            printf("       - %s\n", posgrado_temp->titulo);
            printf("       - %s\n", posgrado_temp->especializacion);
            posgrado_temp = posgrado_temp->next;
        }

        printf("   Historias Laborales:\n");

        historiaLaboral *historia_temp = current->historiasLaborales;
        while (historia_temp != NULL) {
            printf("       - Empresa: %s\n", historia_temp->empresa);
            printf("         Cargo: %s\n", historia_temp->cargo);
            printf("         Fecha de inicio: %s\n", historia_temp->fechaInicio);
            printf("         Fecha de fin: %s\n", historia_temp->fechaFin);
            historia_temp = historia_temp->next;
        }

        current = current->next;
        count++;
    }
}

void sortRecordsByCedula() {
    if (head == NULL || head->next == NULL) {
        printf("No hay registros para ordenar.\n");
        return;
    }

    persona *current, *nextNode;
    char tempCedula[MAX_LENGTH];
    char tempNombre[MAX_LENGTH];
    char tempApellido[MAX_LENGTH];
    char tempEdad[MAX_LENGTH];
    char tempDireccion[MAX_LENGTH];
    char tempTelefono[MAX_LENGTH];
    char tempEmail[MAX_LENGTH];
    pregrado *tempPregrado;
    posgrado *tempPosgrado;
    historiaLaboral *tempHistoria;

    int swapped;
    do {
        swapped = 0;
        current = head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (strcmp(current->cedula, nextNode->cedula) > 0) {
                // Swap cedula
                strcpy(tempCedula, current->cedula);
                strcpy(current->cedula, nextNode->cedula);
                strcpy(nextNode->cedula, tempCedula);
                // Swap nombre
                strcpy(tempNombre, current->nombre);
                strcpy(current->nombre, nextNode->nombre);
                strcpy(nextNode->nombre, tempNombre);
                // Swap apellido
                strcpy(tempApellido, current->apellido);
                strcpy(current->apellido, nextNode->apellido);
                strcpy(nextNode->apellido, tempApellido);
                // Swap edad
                strcpy(tempEdad, current->edad);
                strcpy(current->edad, nextNode->edad);
                strcpy(nextNode->edad, tempEdad);
                // Swap direccion
                strcpy(tempDireccion, current->direccion);
                strcpy(current->direccion, nextNode->direccion);
                strcpy(nextNode->direccion, tempDireccion);
                // Swap telefono
                strcpy(tempTelefono, current->telefono);
                strcpy(current->telefono, nextNode->telefono);
                strcpy(nextNode->telefono, tempTelefono);
                // Swap email
                strcpy(tempEmail, current->email);
                strcpy(current->email, nextNode->email);
                strcpy(nextNode->email, tempEmail);
                // Swap pregrados
                tempPregrado = current->pregrados;
                current->pregrados = nextNode->pregrados;
                nextNode->pregrados = tempPregrado;
                // Swap posgrados
                tempPosgrado = current->posgrados;
                current->posgrados = nextNode->posgrados;
                nextNode->posgrados = tempPosgrado;
                // Swap historias laborales
                tempHistoria = current->historiasLaborales;
                current->historiasLaborales = nextNode->historiasLaborales;
                nextNode->historiasLaborales = tempHistoria;

                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
    printf("Registros ordenados por cedula de forma ascendente.\n");
}

void saveDocument() {
    FILE *file = fopen("./personas.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    }

    persona *current = head;
    while (current != NULL) {
        fprintf(file, "Cedula: %s", current->cedula);
        fprintf(file, "Nombre: %s", current->nombre);
        fprintf(file, "Apellido: %s", current->apellido);
        fprintf(file, "Edad: %s", current->edad);
        fprintf(file, "Direccion: %s", current->direccion);
        fprintf(file, "Telefono: %s", current->telefono);
        fprintf(file, "Email: %s", current->email);

        // Escribir pregrados
        pregrado *pregrado_temp = current->pregrados;
        while (pregrado_temp != NULL) {
            fprintf(file, "Pregrado: %s", pregrado_temp->titulo);
            pregrado_temp = pregrado_temp->next;
        }

        // Escribir posgrados
        posgrado *posgrado_temp = current->posgrados;
        while (posgrado_temp != NULL) {
            fprintf(file, "Posgrado: %s", posgrado_temp->titulo);
            fprintf(file, "Especializacion: %s", posgrado_temp->especializacion);
            posgrado_temp = posgrado_temp->next;
        }

        // Escribir historias laborales
        historiaLaboral *historia_temp = current->historiasLaborales;
        while (historia_temp != NULL) {
            fprintf(file, "Empresa: %s", historia_temp->empresa);
            fprintf(file, "Cargo: %s", historia_temp->cargo);
            fprintf(file, "Fecha de inicio: %s", historia_temp->fechaInicio);
            fprintf(file, "Fecha de fin: %s", historia_temp->fechaFin);
            historia_temp = historia_temp->next;
        }

        fprintf(file, "\n"); // Separador entre personas
        current = current->next;
    }

    fclose(file);
    if (file != NULL) {
        printf("La información se ha guardado correctamente en el archivo personas.txt.\n");
    } else {
        printf("Error al guardar la información en el archivo personas.txt.\n");
    }
}

void loadDocument() {
    FILE *file = fopen("./personas.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo para leer.\n");
        return;
    }

    char line[MAX_LENGTH];
    persona *current = NULL;

    while (fgets(line, MAX_LENGTH, file) != NULL) {
        if (strstr(line, "Cedula:") != NULL) {
            persona *new_person = malloc(sizeof(persona));
            if (new_person == NULL) {
                printf("Error al reservar memoria.\n");
                fclose(file);
                return;
            }
            sscanf(line, "Cedula: %[^\n]", new_person->cedula);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Nombre: %[^\n]", new_person->nombre);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Apellido: %[^\n]", new_person->apellido);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Edad: %[^\n]", new_person->edad);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Direccion: %[^\n]", new_person->direccion);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Telefono: %[^\n]", new_person->telefono);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Email: %[^\n]", new_person->email);

            // Initialize other fields to NULL
            new_person->pregrados = NULL;
            new_person->posgrados = NULL;
            new_person->historiasLaborales = NULL;

            // Link the new person to the list
            new_person->next = NULL;
            if (head == NULL) {
                head = new_person;
            } else {
                current->next = new_person;
            }
            current = new_person;
        } else if (strstr(line, "Pregrado:") != NULL) {
            pregrado *new_pregrado = malloc(sizeof(pregrado));
            if (new_pregrado == NULL) {
                printf("Error al reservar memoria.\n");
                fclose(file);
                return;
            }
            sscanf(line, "Pregrado: %[^\n]", new_pregrado->titulo);
            // Link the new pregrado to the current person's list
            new_pregrado->next = current->pregrados;
            current->pregrados = new_pregrado;
        } else if (strstr(line, "Posgrado:") != NULL) {
            posgrado *new_posgrado = malloc(sizeof(posgrado));
            if (new_posgrado == NULL) {
                printf("Error al reservar memoria.\n");
                fclose(file);
                return;
            }
            sscanf(line, "Posgrado: %[^\n]", new_posgrado->titulo);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Especializacion: %[^\n]", new_posgrado->especializacion);
            // Link the new posgrado to the current person's list
            new_posgrado->next = current->posgrados;
            current->posgrados = new_posgrado;
        } else if (strstr(line, "Empresa:") != NULL) {
            historiaLaboral *new_historia = malloc(sizeof(historiaLaboral));
            if (new_historia == NULL) {
                printf("Error al reservar memoria.\n");
                fclose(file);
                return;
            }
            sscanf(line, "Empresa: %[^\n]", new_historia->empresa);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Cargo: %[^\n]", new_historia->cargo);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Fecha de inicio: %[^\n]", new_historia->fechaInicio);
            fgets(line, MAX_LENGTH, file); // Read the next line
            sscanf(line, "Fecha de fin: %[^\n]", new_historia->fechaFin);
            // Link the new historia to the current person's list
            new_historia->next = current->historiasLaborales;
            current->historiasLaborales = new_historia;
        }
    }

    fclose(file);
    printf("La información se ha cargado correctamente desde el archivo personas.txt.\n");
}


int main() {
    int choice;
    int lineNum;

    while (1) {
        printf("\n Menu de Opciones:\n");
        printf("1. Agregar Persona\n");
        printf("2. Eliminar Persona\n");
        printf("3. Ordenar Datos\n");
        printf("4. Hacer Consultas\n");
        printf("5. Guardar Archivo\n");
        printf("6. Cargar Archivo\n");
        printf("7. Mostrar Informacion en memoria\n");
        printf("8. Salir\n");
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
                sortRecordsByCedula();
                break;
            case 4:
                //TODO
                break;
            case 5:
                saveDocument();
                break;
            case 6:
                loadDocument();
                break;
            case 7:
                displayDocument();
                break;
            case 8:
                exit(0);
            default:
                printf("Opcion invalida.\n");
        }
    }
}
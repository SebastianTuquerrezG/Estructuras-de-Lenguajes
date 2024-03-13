#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 800

/**
 * @brief Estructura para almacenar las historias laborales de una persona.
 */
typedef struct historiaLaboral{
    char empresa[MAX_LENGTH];
    char cargo[MAX_LENGTH];
    char fechaInicio[MAX_LENGTH];
    char fechaFin[MAX_LENGTH];
    struct historiaLaboral* next;
} historiaLaboral;

/**
 * @brief Estructura para almacenar los títulos de pregrado de una persona.
 */
typedef struct pregrado{
    char titulo[MAX_LENGTH];
    struct pregrado* next;
} pregrado;

/**
 * @brief Estructura para almacenar los título y la especialización de los posgrado de una persona.
 */
typedef struct posgrado{
    char titulo[MAX_LENGTH];
    char especializacion[MAX_LENGTH];
    struct posgrado* next;
} posgrado;

/**
 * @brief Estructura para almacenar la información personal y académica de una persona.
 */
typedef struct persona{
    char cedula[MAX_LENGTH];
    char nombre[MAX_LENGTH];
    char apellido[MAX_LENGTH];
    char edad[MAX_LENGTH];
    char direccion[MAX_LENGTH];
    char telefono[MAX_LENGTH];
    char email[MAX_LENGTH];
    pregrado *pregrados;
    posgrado *posgrados;
    historiaLaboral *historiasLaborales;
    struct persona* next;
} persona;

persona *head = NULL; ///< Puntero al primer elemento de la lista de personas

int lines = 0;

/**
 * @brief Agrega una nueva persona al documento.
 */
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

    ///<Agregar pregrados
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

    ///<Agregar posgrados
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

    ///<Agregar historias laborales
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

/**
 * @brief Elimina una persona del documento.
 * @param lineNum Número de línea correspondiente a la persona a eliminar.
 */
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

    ///< Liberar la memoria de los pregrados
    pregrado *pregrado_temp = current->pregrados;
    while (pregrado_temp != NULL) {
        pregrado *temp = pregrado_temp;
        pregrado_temp = pregrado_temp->next;
        free(temp);
    }

    ///<Liberar la memoria de los posgrados
    posgrado *posgrado_temp = current->posgrados;
    while (posgrado_temp != NULL) {
        posgrado *temp = posgrado_temp;
        posgrado_temp = posgrado_temp->next;
        free(temp);
    }

    ///<Liberar la memoria de las historias laborales
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

/**
 * @brief Muestra el contenido completo del documento en memoria.
 */
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

/**
 * @brief Ordena las personas en el documento por número de cédula usando BubbleSort.
 */
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
                ///<Swap cedula
                strcpy(tempCedula, current->cedula);
                strcpy(current->cedula, nextNode->cedula);
                strcpy(nextNode->cedula, tempCedula);
                ///< nombre
                strcpy(tempNombre, current->nombre);
                strcpy(current->nombre, nextNode->nombre);
                strcpy(nextNode->nombre, tempNombre);
                ///<Swap apellido
                strcpy(tempApellido, current->apellido);
                strcpy(current->apellido, nextNode->apellido);
                strcpy(nextNode->apellido, tempApellido);
                // Swap edad
                strcpy(tempEdad, current->edad);
                strcpy(current->edad, nextNode->edad);
                strcpy(nextNode->edad, tempEdad);
                ///< Swap direccion
                strcpy(tempDireccion, current->direccion);
                strcpy(current->direccion, nextNode->direccion);
                strcpy(nextNode->direccion, tempDireccion);
                ///< Swap telefono
                strcpy(tempTelefono, current->telefono);
                strcpy(current->telefono, nextNode->telefono);
                strcpy(nextNode->telefono, tempTelefono);
                ///< Swap email
                strcpy(tempEmail, current->email);
                strcpy(current->email, nextNode->email);
                strcpy(nextNode->email, tempEmail);
                ///<Swap pregrados
                tempPregrado = current->pregrados;
                current->pregrados = nextNode->pregrados;
                nextNode->pregrados = tempPregrado;
                ///< Swap posgrados
                tempPosgrado = current->posgrados;
                current->posgrados = nextNode->posgrados;
                nextNode->posgrados = tempPosgrado;
                ///< Swap historias laborales
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

/**
 * @brief Guarda el contenido del documento en un archivo de texto.
 */
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

        ///< Escribir pregrados
        pregrado *pregrado_temp = current->pregrados;
        while (pregrado_temp != NULL) {
            fprintf(file, "Pregrado: %s", pregrado_temp->titulo);
            pregrado_temp = pregrado_temp->next;
        }

        ///<  Escribir posgrados
        posgrado *posgrado_temp = current->posgrados;
        while (posgrado_temp != NULL) {
            fprintf(file, "Posgrado: %s", posgrado_temp->titulo);
            fprintf(file, "Especializacion: %s", posgrado_temp->especializacion);
            posgrado_temp = posgrado_temp->next;
        }

        ///<  Escribir historias laborales
        historiaLaboral *historia_temp = current->historiasLaborales;
        while (historia_temp != NULL) {
            fprintf(file, "Empresa: %s", historia_temp->empresa);
            fprintf(file, "Cargo: %s", historia_temp->cargo);
            fprintf(file, "Fecha de inicio: %s", historia_temp->fechaInicio);
            fprintf(file, "Fecha de fin: %s", historia_temp->fechaFin);
            historia_temp = historia_temp->next;
        }

        fprintf(file, "\n"); ///< Separador entre personas
        current = current->next;
    }

    fclose(file);
    if (file != NULL) {
        printf("La información se ha guardado correctamente en el archivo personas.txt.\n");
    } else {
        printf("Error al guardar la información en el archivo personas.txt.\n");
    }
}

/**
 * @brief Carga el contenido de un archivo de texto en el documento.
 */
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

            ///< Inicializar los punteros de pregrados, posgrados y historias laborales
            new_person->pregrados = NULL;
            new_person->posgrados = NULL;
            new_person->historiasLaborales = NULL;

            ///< Agregar la nueva persona a la cabecera
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
            ///< Agregar el nuevo pregrado a la lista de pregrados de la persona actual
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
            ///< Agregar el nuevo posgrado a la lista de posgrados de la persona actual
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
            fgets(line, MAX_LENGTH, file);
            sscanf(line, "Cargo: %[^\n]", new_historia->cargo);
            fgets(line, MAX_LENGTH, file);
            sscanf(line, "Fecha de inicio: %[^\n]", new_historia->fechaInicio);
            fgets(line, MAX_LENGTH, file);
            sscanf(line, "Fecha de fin: %[^\n]", new_historia->fechaFin);
            ///< Agregar la nueva historia laboral a la lista de historias laborales de la persona actual
            new_historia->next = current->historiasLaborales;
            current->historiasLaborales = new_historia;
        }
    }

    fclose(file);
    printf("La información se ha cargado correctamente desde el archivo personas.txt.\n");
}

/**
 * @brief Muestra todas las personas que tienen una profesión determinada.
 * @param profesion La profesión a buscar.
 */
void mostrarPersonasPorProfesion(char *profesion) {
    ///< Eliminar el carácter de nueva línea del string profesion
    profesion[strcspn(profesion, "\n")] = '\0';

    persona *current = head;
    int encontradas = 0;

    while (current != NULL) {
        historiaLaboral *historia_temp = current->historiasLaborales;
        while (historia_temp != NULL) {
            if (strcmp(historia_temp->cargo, profesion) == 0) {
                encontradas++;
                printf("Cedula: %s\n", current->cedula);
                printf("Nombre: %s\n", current->nombre);
                printf("Apellido: %s\n", current->apellido);
                printf("Empresa: %s\n", historia_temp->empresa);
                printf("Cargo: %s\n", historia_temp->cargo);
                printf("\n");
                break; ///< No es necesario seguir buscando en las demás historias laborales
            }
            historia_temp = historia_temp->next;
        }
        current = current->next;
    }

    if (encontradas == 0) {
        printf("No se encontraron personas con la profesion '%s'.\n", profesion);
    }
}

/**
 * @brief Muestra todas las personas con más de 25 años.
 */
void mostrarPersonasMas25() {
    persona *current = head;
    int encontradas = 0;

    while (current != NULL) {
        int edad = atoi(current->edad);
        if (edad > 25) {
            encontradas++;
            printf("Cedula: %s\n", current->cedula);
            printf("Nombre: %s\n", current->nombre);
            printf("Apellido: %s\n", current->apellido);
            printf("Edad: %s\n", current->edad);
            printf("\n");
        }
        current = current->next;
    }

    if (encontradas == 0) {
        printf("No se encontraron personas con más de 25 años.\n");
    }
}

/**
 * @brief Muestra todas las personas que trabajan en una empresa específica.
 * @param empresa El nombre de la empresa a buscar.
 */
void mostrarPersonasPorEmpresa(char *empresa) {
    ///< / Eliminar el carácter de nueva línea del string empresa
    empresa[strcspn(empresa, "\n")] = '\0';

    persona *current = head;
    int encontradas = 0;

    while (current != NULL) {
        historiaLaboral *historia_temp = current->historiasLaborales;
        while (historia_temp != NULL) {
            if (strcmp(historia_temp->empresa, empresa) == 0) {
                encontradas++;
                printf("Cedula: %s\n", current->cedula);
                printf("Nombre: %s\n", current->nombre);
                printf("Apellido: %s\n", current->apellido);
                printf("Empresa: %s\n", historia_temp->empresa);
                printf("Cargo: %s\n", historia_temp->cargo);
                printf("\n");
                break; ///<  No es necesario seguir buscando en las demás historias laborales
            }
            historia_temp = historia_temp->next;
        }
        current = current->next;
    }

    if (encontradas == 0) {
        printf("No se encontraron personas que trabajen en la empresa '%s'.\n", empresa);
    }
}

/**
 * @brief Cuenta cuántas personas tienen especialización, maestría y doctorado.
 */
void contarNivelesDeEducacion() {
    persona *current = head;
    int especializacion = 0, maestria = 0, doctorado = 0;

    while (current != NULL) {
        ///< Contar los niveles de educación de cada persona
        posgrado *posgrado_temp = current->posgrados;
        while (posgrado_temp != NULL) {
            if (strstr(posgrado_temp->especializacion, "Especializac") != NULL) {
                especializacion++;
            } else if (strstr(posgrado_temp->especializacion, "Maestria") != NULL) {
                maestria++;
            } else if (strstr(posgrado_temp->especializacion, "Doctorado") != NULL) {
                doctorado++;
            }
            posgrado_temp = posgrado_temp->next;
        }

        current = current->next;
    }

    printf("Cantidad de personas con especializacion: %d\n", especializacion);
    printf("Cantidad de personas con maestria: %d\n", maestria);
    printf("Cantidad de personas con doctorado: %d\n", doctorado);
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
        getchar(); ///< Limpiar el buffer de entrada

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
                printf("\nConsultas:\n");
                printf("1. Mostrar todas las personas con una profesion determinada\n");
                printf("2. Mostrar todas las personas con mas de 25 anos\n");
                printf("3. Mostrar todas las personas que trabajan en una empresa\n");
                printf("4. Mostrar cuantas personas tienen especializacion, maestria y doctorado\n");
                printf("Elija una consulta: ");
                int consulta;
                scanf("%d", &consulta);
                getchar(); ///< Limpiar el buffer de entrada

                switch (consulta) {
                    case 1:
                        ///< Consulta 1: Mostrar todas las personas con una profesión determinada
                        printf("Ingrese la profesion: ");
                        char profesion[MAX_LENGTH];
                        fgets(profesion, MAX_LENGTH, stdin);
                        mostrarPersonasPorProfesion(profesion);
                        break;
                    case 2:
                        ///<Consulta 2: Mostrar todas las personas con más de 25 años
                        mostrarPersonasMas25();
                        break;
                    case 3:
                        ///< Consulta 3: Mostrar todas las personas que trabajan en una empresa
                        printf("Ingrese el nombre de la empresa: ");
                        char empresa[MAX_LENGTH];
                        fgets(empresa, MAX_LENGTH, stdin);
                        mostrarPersonasPorEmpresa(empresa);
                        break;
                    case 4:
                        ///< Consulta 4: Mostrar cuantas personas tienen especializacion, maestria y doctorado
                        contarNivelesDeEducacion();
                        break;
                    default:
                        printf("Consulta invalida.\n");
                }
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
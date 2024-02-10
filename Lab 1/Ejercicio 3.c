#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANO_MUNDO 10
#define PORCENTAJE_MOVIMIENTO 0.1

// Función para inicializar el mundo con células vivas aleatorias
void inicializarMundo(int mundo[][TAMANO_MUNDO]) {
    srand(time(NULL));
    for (int i = 0; i < TAMANO_MUNDO; i++) {
        for (int j = 0; j < TAMANO_MUNDO; j++) {
            mundo[i][j] = rand() % 2; // 0 para muerto, 1 para vivo
        }
    }
}

// Función para imprimir el mundo en la consola
void imprimirMundo(int mundo[][TAMANO_MUNDO]) {
    for (int i = 0; i < TAMANO_MUNDO; i++) {
        for (int j = 0; j < TAMANO_MUNDO; j++) {
            printf("%c ", mundo[i][j] ? 'O' : '-'); // 'O' para célula viva, '-' para célula muerta
        }
        printf("\n");
    }
}

// Función para contar el número de células vecinas vivas
int contarVecinos(int mundo[][TAMANO_MUNDO], int fila, int columna) {
    int contador = 0;
    for (int i = fila - 1; i <= fila + 1; i++) {
        for (int j = columna - 1; j <= columna + 1; j++) {
            if (i >= 0 && i < TAMANO_MUNDO && j >= 0 && j < TAMANO_MUNDO && (i != fila || j != columna)) {
                contador += mundo[i][j];
            }
        }
    }
    return contador;
}

// Función para aplicar una iteración del juego de la vida
void aplicarIteracion(int mundo[][TAMANO_MUNDO]) {
    int nuevoMundo[TAMANO_MUNDO][TAMANO_MUNDO];
    for (int i = 0; i < TAMANO_MUNDO; i++) {
        for (int j = 0; j < TAMANO_MUNDO; j++) {
            int vecinos = contarVecinos(mundo, i, j);
            if (mundo[i][j]) { // célula viva
                nuevoMundo[i][j] = (vecinos == 2 || vecinos == 3) ? 1 : 0; // supervivencia o muerte
            } else { // célula muerta
                nuevoMundo[i][j] = (vecinos == 3) ? 1 : 0; // nacimiento
            }
        }
    }
    // Actualizar el mundo con el nuevo estado
    for (int i = 0; i < TAMANO_MUNDO; i++) {
        for (int j = 0; j < TAMANO_MUNDO; j++) {
            mundo[i][j] = nuevoMundo[i][j];
        }
    }
}

// Función para realizar el movimiento de células
void moverCelulas(int mundo[][TAMANO_MUNDO]) {
    srand(time(NULL));
    int celulasAMover = (int)(TAMANO_MUNDO * TAMANO_MUNDO * PORCENTAJE_MOVIMIENTO);
    for (int k = 0; k < celulasAMover; k++) {
        int filaOrigen = rand() % TAMANO_MUNDO;
        int columnaOrigen = rand() % TAMANO_MUNDO;
        if (mundo[filaOrigen][columnaOrigen]) { // Si la célula está viva
            int filaDestino = rand() % TAMANO_MUNDO;
            int columnaDestino = rand() % TAMANO_MUNDO;
            mundo[filaDestino][columnaDestino] = 1;
            mundo[filaOrigen][columnaOrigen] = 0;
        }
    }
}

int main() {
    int mundo[TAMANO_MUNDO][TAMANO_MUNDO];

    // Inicializar el mundo con células vivas aleatorias
    inicializarMundo(mundo);

    // Mostrar el mundo inicial
    printf("Mundo inicial:\n");
    imprimirMundo(mundo);

    // Iterar para cada generación del juego
    for (int generacion = 1; generacion <= 10; generacion++) {
        // Aplicar movimiento de células
        moverCelulas(mundo);
        // Aplicar una iteración del juego de la vida
        aplicarIteracion(mundo);
        // Mostrar el mundo actual después de la iteración
        printf("Generacion %d:\n", generacion);
        imprimirMundo(mundo);
        printf("\n");
    }

    return 0;
}

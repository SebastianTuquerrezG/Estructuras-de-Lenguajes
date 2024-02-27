#include <stdio.h>
#include <stdlib.h>

// Definición de una estructura para representar una actividad
typedef struct {
    int inicio;
    int fin;
} Actividad;

// Función para comparar dos actividades según sus tiempos de inicio y finalización
int comparar(const void *a, const void *b) {
    Actividad *act1 = (Actividad *)a;
    Actividad *act2 = (Actividad *)b;

    // Si los tiempos de finalización son diferentes, ordenar por tiempo de finalización
    if (act1->fin != act2->fin) {
        return act1->fin - act2->fin;
    }

    // Si los tiempos de finalización son iguales, ordenar por tiempo de inicio
    return act1->inicio - act2->inicio;
}

// Función para imprimir las actividades seleccionadas
void imprimirActividades(Actividad actividades[], int n) {
    printf("Actividades seleccionadas:\n");
    printf("Inicio\tFin\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", actividades[i].inicio, actividades[i].fin);
    }
}

// Función para programar actividades sin superposición
void programarActividades(Actividad actividades[], int n) {
    // Ordenar las actividades por tiempo de finalización
    qsort(actividades, n, sizeof(Actividad), comparar);

    // La primera actividad siempre se selecciona
    int seleccionadas = 1;
    int ultimaSeleccionada = 0;

    // Iterar sobre las actividades restantes
    for (int i = 1; i < n; i++) {
        // Si la actividad actual no se superpone con la última seleccionada
        if (actividades[i].inicio >= actividades[ultimaSeleccionada].fin) {
            seleccionadas++;
            ultimaSeleccionada = i;
        }
    }

    // Imprimir las actividades seleccionadas
    imprimirActividades(actividades, seleccionadas);
}

int main() {
    // Definir el conjunto de actividades
    Actividad actividades[] = {{1, 2}, {0, 5}, {2, 3}, {3, 4}, {4, 6}, {5, 7}, {6, 8}, {7, 9}};
    int n = sizeof(actividades) / sizeof(actividades[0]);

    printf("Arreglo antes de ordenar:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", actividades[i].inicio, actividades[i].fin);
    }

    // Programar las actividades
    programarActividades(actividades, n);

    return 0;
}

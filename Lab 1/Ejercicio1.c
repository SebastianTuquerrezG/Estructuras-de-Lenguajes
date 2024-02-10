#include <stdio.h>

// Función para verificar si un número es primo
int esPrimo(int n) {
    if (n <= 1) return 0; // 0 y 1 no son primos
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Si n es divisible por i, entonces no es primo
    }
    return 1; // Si no hay ningún divisor encontrado, n es primo
}

// Función para contar el número de representaciones
int contarRepresentaciones(int n) {
    int contador = 0;
    for (int inicio = 2; inicio <= n; inicio++) {
        int suma = 0;
        for (int i = inicio; i <= n; i++) {
            if (esPrimo(i)) {
                suma += i;
                if (suma == n) {
                    contador++;
                    break;
                } else if (suma > n) {
                    break;
                }
            }
        }
    }
    return contador;
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        printf("%d\n", contarRepresentaciones(n));
    }
    return 0;
}

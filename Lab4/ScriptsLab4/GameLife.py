import os
import random
import time

def limpiar_consola():
    os.system('cls' if os.name == 'nt' else 'clear')

def inicializar_mundo(filas, columnas):
    mundo = [[random.choice([0, 1]) for _ in range(columnas)] for _ in range(filas)]
    return mundo

def imprimir_mundo(mundo):
    for fila in mundo:
        print(' '.join(['*' if celula else '.' for celula in fila]))
    print()

def contar_vecinos(mundo, fila, columna):
    vecinos = 0
    filas, columnas = len(mundo), len(mundo[0])
    for i in range(-1, 2):
        for j in range(-1, 2):
            vecino_fila = (fila + i) % filas
            vecino_columna = (columna + j) % columnas
            vecinos += mundo[vecino_fila][vecino_columna]
    vecinos -= mundo[fila][columna]
    return vecinos

def evolucionar(mundo):
    nueva_generacion = [[0] * len(mundo[0]) for _ in range(len(mundo))]
    for i in range(len(mundo)):
        for j in range(len(mundo[0])):
            vecinos = contar_vecinos(mundo, i, j)
            if mundo[i][j] == 1: # Célula viva
                if vecinos == 2 or vecinos == 3:
                    nueva_generacion[i][j] = 1
                else:
                    nueva_generacion[i][j] = 0
            else: # Célula muerta
                if vecinos == 3:
                    nueva_generacion[i][j] = 1
                else:
                    nueva_generacion[i][j] = 0
    return nueva_generacion

def juego_de_la_vida(filas, columnas):
    mundo = inicializar_mundo(filas, columnas)
    while True:
        imprimir_mundo(mundo)
        mundo = evolucionar(mundo)
        time.sleep(1)  # Pausa de 1 segundo

# Ejemplo de uso
filas = 10
columnas = 10
juego_de_la_vida(filas, columnas)

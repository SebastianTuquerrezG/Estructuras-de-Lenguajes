def es_primo(n):
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def contar_representaciones(numero):
    if numero <= 1:
        return 0

    cantidad_representaciones = 0
    suma = 0
    primos = []

    # Generar una lista de números primos menores o iguales al número dado
    for i in range(2, numero + 1):
        if es_primo(i):
            primos.append(i)

    # Calcular las representaciones de la suma de números primos consecutivos
    for i in range(len(primos)):
        suma = 0
        for j in range(i, len(primos)):
            suma += primos[j]
            if suma == numero:
                cantidad_representaciones += 1
                break
            elif suma > numero:
                break

    return cantidad_representaciones


# Leer la secuencia de enteros positivos
while True:
    numero = int(input())
    if numero == 0:
        break
    print(contar_representaciones(numero))

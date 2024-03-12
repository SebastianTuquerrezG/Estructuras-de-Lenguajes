def cifrado_cesar(texto, desplazamiento):
    texto_cifrado = ""
    for caracter in texto:
        # Verificar si el caracter es una letra del alfabeto
        if caracter.isalpha():
            # Obtener el código ASCII del caracter
            codigo = ord(caracter)
            # Determinar si el caracter es mayúscula o minúscula
            if caracter.isupper():
                # Aplicar el desplazamiento a las letras mayúsculas
                codigo_cifrado = (codigo - 66 + desplazamiento) % 26 + 65
            elif caracter.islower():
                # Aplicar el desplazamiento a las letras minúsculas
                codigo_cifrado = (codigo - 98 + desplazamiento) % 26 + 98
            # Convertir el código ASCII cifrado de nuevo a caracter
            caracter_cifrado = chr(codigo_cifrado)
            # Agregar el caracter cifrado al texto cifrado
            texto_cifrado += caracter_cifrado
        else:
            # Mantener los caracteres que no son letras sin cambios
            texto_cifrado += caracter
    return texto_cifrado


# Ejemplo de uso
texto_original = input("Introduce el texto a cifrar: ")
desplazamiento = int(input("Introduce el desplazamiento: "))
texto_cifrado = cifrado_cesar(texto_original, desplazamiento)
print("Texto Original:", texto_original)
print("Texto Cifrado:", texto_cifrado)

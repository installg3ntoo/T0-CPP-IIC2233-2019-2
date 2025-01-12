
# Dejaremos en claro los puntos claves de este código
# Cuando se trata de trabajar con coordenadas en éste código, se tratan por las variables i que
# representa la variables de las filas y la variable j, que representa la variable de las columnas
# normalmente van siempre acompañadas en una lista [i, j]
# la variable L SIEMPRE representa la cantidad de legos de un tablero

import math
import os
import random
from parametros import PROB_LEGO, POND_PUNT
from tablero import print_tablero

# Crearemos una clase Tablero, que tendrá en su interior una lista de listas que será el Tablero
# en cuestión, ademas de contener la variable que indica la cantidad de filas del tablero, y la
# variable que indica la cantidad de columnas del mismo
class Tablero:

    def __init__(self, filas, columnas):

        self.filas = int(filas)
        self.columnas = int(columnas)
        self.tablero = []

# funcion que crea un tablero con casillas con ' '
    def creacion_tablero(self):

        for x in range(self.filas):
            columna = [" "] * self.columnas
            self.tablero.append(columna)

# función que crea un tablero con casillas con '0'
    def creacion_tablero_cero(self):

        for x in range(self.filas):
            columna = [0] * self.columnas
            self.tablero.append(columna)

# función que agrega legos a un tablero
    def legos(self):

        L = math.ceil(float(self.filas) * float(self.columnas) * PROB_LEGO)
        legos_puestos = 0

        while (legos_puestos < L):
            for fila in self.tablero:
                for numero_casilla in range(len(fila) - 1):
                    if (legos_puestos < L and aleatorio() and fila[numero_casilla] != "L"):
                        fila[numero_casilla] = "L"
                        legos_puestos += 1
        return L

# función que verifica si hay un lego en la casilla entregada
# retorna 1 (True) si hay un lego y 0 (False) si no hay un lego
# siendo el parámetro lugar una lista de la forma [i, j]
    def lcheck(self, lugar):

        if (self.tablero[lugar[0]][lugar[1]] == "L"):
            return 1
        else:
            return 0
# función que aplica la función poner_numero a todas las casillas alrededor de los legos
    def revisar_legos(self):

        for i in range(len(self.tablero)):
            for j in range(len(self.tablero[i])):

                if (self.lcheck([i, j])):
                    if (i == 0):
                        self.poner_numero([i + 1, j])
                        if(j == 0):
                            self.poner_numero([i, j + 1])
                            self.poner_numero([i + 1, j + 1])
                        elif (j == self.columnas - 1):
                            self.poner_numero([i, j - 1])
                            self.poner_numero([i + 1, j - 1])
                        else:
                            self.poner_numero([i, j + 1])
                            self.poner_numero([i + 1, j + 1])
                            self.poner_numero([i, j - 1])
                            self.poner_numero([i + 1, j - 1])

                    elif (j == 0):
                        self.poner_numero([i, j + 1])
                        if(i == self.filas - 1):
                            self.poner_numero([i - 1, j])
                            self.poner_numero([i - 1, j + 1])
                        else:
                            self.poner_numero([i - 1, j])
                            self.poner_numero([i - 1, j + 1])
                            self.poner_numero([i + 1, j + 1])
                            self.poner_numero([i + 1, j])

                    elif (i == self.filas - 1):
                        self.poner_numero([i, j - 1])
                        self.poner_numero([i - 1, j - 1])
                        self.poner_numero([i - 1, j])

                        if(j != self.columnas - 1):
                            self.poner_numero([i, j + 1])
                            self.poner_numero([i - 1, j + 1])

                    elif(j == self.columnas - 1):
                        self.poner_numero([i + 1, j])
                        self.poner_numero([i + 1, j - 1])
                        self.poner_numero([i, j - 1])
                        self.poner_numero([i - 1, j])
                        self.poner_numero([i - 1, j - 1])

                    else:
                        self.poner_numero([i, j + 1])
                        self.poner_numero([i, j - 1])
                        self.poner_numero([i + 1, j])
                        self.poner_numero([i + 1, j - 1])
                        self.poner_numero([i + 1, j + 1])
                        self.poner_numero([i - 1, j])
                        self.poner_numero([i - 1, j - 1])
                        self.poner_numero([i - 1, j + 1])

# función que chequea si la casilla entregada es " " o no
# siendo el parámetro lugar una lista de la forma [i, j]
    def check(self, lugar):
        if (self.tablero[lugar[0]][lugar[1]] == " "):
            return 1
        else:
            return 0

# función que aumenta en 1 el valor de la casilla entregada
# en caso de que la casilla sea un lego, la función no hace nada
# siendo el parámetro lugar una lista de la forma [i, j]
    def poner_numero(self, lugar):
        if(self.tablero[lugar[0]][lugar[1]] != "L"):
            self.tablero[lugar[0]][lugar[1]] += 1

###################################################################################################
#           FIN DE LA CLASE
###################################################################################################

# función que tiene un 20% de probabilidad de entregar 1 (True)
# y un 80% de probabilidad de entregar 0 (False)
def aleatorio():
    lista = [0, 1, 0, 0, 0]
    return random.choice(lista)

# función que funciona como el menú de inicio del juego
def MenuInicio():
    entrada = ""
    bool = False
    print ("\u001b[33mBienvenido A Lego Sweeper!\n\n\u001b[34mPorfavor escoja una opción\n")

    while (entrada != "1" and entrada != "2" and entrada != "3" and entrada != "4"):
        if (bool):
            os.system("cls")
            print("\u001b[31mCarácter incorrecto, porfavor escriba el número de la opción deseada")
            print("\n")
        else:
            bool = True
        print("\u001b[32m1)Comenzar una nueva partida")
        if(True):
            print("\u001b[33m2)Cargar partida existente")
        print("\u001b[35m3)Ver el ranking de puntajes\n\u001b[36;1m4)Salir\u001b[0m")
        entrada = input()
    return int(entrada)

# funcion que guarda una partida, recibe como parametro un string del nombre
# ambos Tablero T1 y T2, un entero que representa las filas, un entero
# que representa las columnas, un entero que representa las celdas que ha descubierto
# y un entero que representa la cantidad de legos del tablero
def Guardar(nombre, T1, T2, filas, columnas, celdas_descubiertas, L):
    if(not os.path.isdir("partidas")):
        os.mkdir("partidas")
    fp = open("./partidas/" + nombre + ".txt", "w")
    fp.write(nombre + "\n")
    fp.write(str(filas) + "\n")
    fp.write(str(columnas) + "\n")
    fp.write(str(celdas_descubiertas) + "\n")
    fp.write(str(L) + "\n")
    for i in range(len(T1.tablero)):
        for j in range(len(T1.tablero[i])):
            fp.write(str(T1.tablero[i][j]) + "-")
        fp.write("\n")
    fp.write("\n")
    for i in range(len(T2.tablero)):
        for j in range(len(T2.tablero[i])):
            fp.write(str(T2.tablero[i][j]) + "-")
        fp.write("\n")
    fp.close()
    return 0
# funcion que recibe como parametros un modo de abrir un archivo
# un nombre y un puntaje, y después agrega dichos datos al archivo
# puntajes, si no recibe esos parametros, imprime los 10 mejores
# puntajes de dicho archivo
def puntajes(modo = "r", nombre = "", puntaje = 0):
    fp = open("puntajes.txt", modo)
    if(modo == "a"):
        fp.write(nombre + "\t" + str(puntaje) + "\n")
    else:
        print("\033[32mLugar\t\033[36mPuntaje\t\033[35mNombre\033[0m\n")
        lista = []
        for fila in fp:
            lista.append((int(fila.strip().split("\t")[1]),fila.strip().split("\t")[0]))
        lista.sort()
        lista.reverse()
        contador = 0

        while(contador <= 10 and contador < len(lista)):
# Esta linea no pudo ser más corta que 104 caracteres
            print("#" + str(contador + 1) + "\t" +\
             str(lista[contador][0]) + "\t" + lista[contador][1])
            contador += 1
    fp.close()
    return 0

# funcion que ejecuta el juego en sí, si recibe datos, carga estos datos y empieza a jugar
# si no recibe datos empieza una partida nueva
# los datos los recibe en forma de lista
#["NAME", "ROW", "COLUMN", "CELLSDISCOVERED", "LEGOS", "T1", "T2"]
def Opcion1(datos = ""):

# al crear una partida nueva, la función crea 2 tableros con las mismas filas y columnas
# T1 que contiene el tablero visible al jugador y T2, que contiene el tablero "escondido"
# del jugador, donde se encuentran las casillas no reveladas y las casillas de los legos
    if(datos == ""):
        entrada = ""
        while (entrada.strip() == ""):
            print("/////////////////////////////////////////////\n\n            Nueva Partida\n")
            print("/////////////////////////////////////////////\n\n")
            print("Porfavor escriba su nombre")
            entrada = input("Si desea volver al menú principal, escriba 0\n")
            if(entrada.strip() == ""):
                os.system("cls")
                print("\u001b[31mERROR! El nombre no puede ser vacío\u001b[0m\n\n")
            elif(entrada == "0"):
                return 0
        nombre = entrada
        entrada = ""
        print("Bienvenido " + nombre + "!\n\n")
        while (not entrada.isdigit() or int(entrada) < 3 or int(entrada) >15):
            print("Por favor, escriba el número de filas que desea")
            entrada = input("Si desea volver atrás, escriba 0\n\n")
            if(entrada == "0"):
                return 0
            if(not entrada.isdigit()):
                os.system("cls")
                print("\u001b[31mCarácter incorrecto, porfavor escriba sólo números\u001b[0m\n\n")
            elif(int(entrada) < 3 or int(entrada) > 15):
                os.system("cls")
                print("\u001b[31mCarácter incorrecto, porfavor escriba números entre 3 y 15\n")
                print("\u001b[0m\n")

        filas = entrada
        entrada = ""
        os.system("cls")

        while (not entrada.isdigit() or int(entrada) < 3 or int(entrada) >15):
            print("Por favor, escriba el número de columnas que desea")
            entrada = input("Si desea volver atrás, escriba 0\n\n")
            if(entrada == "0"):
                return 0
            if(not entrada.isdigit()):
                os.system("cls")
                print("\u001b[31mCarácter incorrecto, porfavor escriba sólo números\u001b[0m\n\n")
            elif(int(entrada) < 3 or int(entrada) >15):
                os.system("cls")
                print("\u001b[31mCarácter incorrecto, porfavor escriba números entre 3 y 15\n")
                print("\u001b[0m\n")

        os.system("cls")
        columnas = entrada
        celdas_descubiertas = 0
        T1 = Tablero(filas, columnas)
        T1.creacion_tablero()
        T2 = Tablero(filas, columnas)
        T2.creacion_tablero_cero()
        L = T2.legos()
        T2.revisar_legos()

    else:
#["NAME", "ROW", "COLUMN", "CELLSDISCOVERED", "LEGOS", "T1", "T2"]
        print("Bienvenido de vuelta, " +  str(datos[0]) + "!")
        nombre = datos[0]
        filas = datos[1]
        columnas = datos[2]
        celdas_descubiertas = int(datos[3])
        L = int(datos[4])
        T1 = Tablero(filas, columnas)
        T1.tablero = datos[5]
        T2 = Tablero(filas, columnas)
        T2.tablero = datos[6]

    while (celdas_descubiertas < (int(filas) * int(columnas) - L)):
        print_tablero(T1.tablero)
        print("Porfavor, escriba las coordenadas de la casilla que desea descubrir, separadas")
        print("por un espacio.\nSi desea volver al menú principal, escriba MENU")
        entrada = input("Si desea guardar su partida, escriba GUARDAR\n")
# cd de coordenada
        cd = entrada.strip().split()
        if(entrada == "MENU"):
            while(True):
                entrada = input("Desea guardar antes de salir al menú? (Y/N)\n")
                if(entrada == "Y"):
                    Guardar(nombre, T1, T2, filas, columnas, celdas_descubiertas, L)
                    return 0
                elif(entrada == "N"):
                    return 0
                os.system("cls")
                print("\u001b[31mCarácter incorrecto, escriba Y o N\u001b[0m")

        elif(entrada == "GUARDAR"):
            Guardar(nombre, T1, T2, filas, columnas, celdas_descubiertas, L)
            input("Se ha guardado la partida, presione ENTER para continuar\n")
            os.system("cls")
        elif(len(cd) >= 2 and cd[1].isdigit() and 0 <= int(cd[1]) < int(filas) and\
        cd[0].islower() and len(cd[0]) == 1 and 97 <= ord(cd[0]) < 97 + int(columnas)):

            i = int(cd[1])
            j = ord(cd[0]) - 97
            if(T2.lcheck([i, j])):
                T1.tablero[i][j] = T2.tablero[i][j]
                break

            elif(T1.check([i, j])):
                celdas_descubiertas += 1
                T1.tablero[i][j] = T2.tablero[i][j]
                os.system("cls")
            else:
                os.system("cls")


        else:
            os.system("cls")
            print("\u001b[31mCarácter incorrecto, porfavor escriba la letra de las columnas")
            print("seguida del número de las filas en MINÚSCULAS con un espacio, ejemplo:\n")
            print("\u001b[0mLetraColumna NumeroFila\n")
            print("O, si desea salir escriba SALIR\n")

    puntaje = L * celdas_descubiertas * POND_PUNT
    os.system("cls")
    print_tablero(T1.tablero)
    puntajes("a", nombre, puntaje)
    print("Fin del Juego!\n\n" + nombre + "\tPuntaje: " + str(puntaje) + "\n")
    input("Presione ENTER para volver al menú\n")
    return 0

# funcion que carga la partida de un jugador, para cargarla retorna una lista con toda la
# informacion de la partida a cargar
def Opcion2(bool = False):
    if(bool == False):
        return 1
    else:
        print("/////////////////////////////////////////////\n\n            Cargar Partida\n")
        print("/////////////////////////////////////////////\n\n")
        print("Porfavor, escriba el nombre del usuario de la partida que desea cargar")
        entrada = input("Si desea volver atrás, escriba 0\n")
        if(entrada == "0"):
            return 0
        elif(not os.path.isfile("./partidas/" + entrada + ".txt")):
            input("El nombre de usuario no existe, presione ENTER para continuar\n")
            return 0
        fp = open("./partidas/" + entrada + ".txt", "r")
        lista = ["NAME", "ROW", "COLUMN", "CELLSDISCOVERED", "LEGOS", [], []]
        contador = 0
        for fila in fp:
            if (contador <= 4):
                lista[contador] = (fila.strip())
                contador += 1
            else:
                if(not fila == "\n"):
                    lista[contador].append(fila.strip("\n").strip("-").split("-"))
                else:
                    contador += 1

        fp.close()
        return lista

# funcion main que ejecuta todo el juego
def Main():
    opcion = 0
    datos = ""

    while (True):
        os.system("cls")
        if(opcion == 0):
            opcion = MenuInicio()
        elif(opcion == 1):
            if(datos != ""):
                opcion = Opcion1(datos)
            else:
                opcion = Opcion1()
        elif(opcion == 2):
            opcion = Opcion2()
            datos = Opcion2(True)
            if (datos == 0):
                opcion = 0
                datos = ""
        elif(opcion == 3):
            if(os.path.isfile("puntajes.txt")):
                opcion = puntajes()
                input("Presione ENTER para continuar\n")
            else:
                print("No hay puntajes que mostrar!\nPrimero juege un poco antes de revisar\n")
                input("Presione ENTER para continuar\n")
                opcion = 0
            #os.system("cls")
        elif(opcion == 4):
            exit()


Main()

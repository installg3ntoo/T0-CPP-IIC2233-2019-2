#pragma once
#include <string>
#include <vector>
#include <variant>
#include "parametros.h"



/**
 * @class Tablero
 * @brief Representa un tablero
 
 * @tparam `int` n Número de filas del tablero.
 * @tparam `int` m Número de columnas del tablero.
 * @tparam `vector<vector<char>>` tablero Matriz de caracteres que representa el tablero.
 */
class Tablero
{
public:
    int n; 
    int m;
    std::vector<std::vector<std::variant<int, char>>> tablero;

    /**
     * @fn Tablero(int filas, int columnas)
     * @brief Constructor de un tablero.
     * @param filas Número de filas del tablero.
     * @param columnas Número de columnas del tablero.
     */
    Tablero(int filas, int columnas);

};

/**
 * @fn print_tablero_con_utf8(const std::vector<std::vector<std::variant<int, char>>> tablero)
 * @brief Imprime un tablero en la consola.
 * @param tablero Matriz de variantes ints o char que representa el tablero.
 */
void print_tablero_con_utf8(const std::vector<std::vector<std::variant<int, char>>> tablero);
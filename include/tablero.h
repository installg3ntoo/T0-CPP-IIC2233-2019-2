#pragma once
#include <string>
#include <vector>
#include <variant>
#include "parametros.h"



/**
 * @fn print_tablero_con_utf8(const std::vector<std::vector<std::variant<int, char>>> tablero)
 * @brief Imprime un tablero en la consola.
 * @param tablero Matriz de variantes ints o char que representa el tablero.
 */
void print_tablero_con_utf8(const std::vector<std::vector<std::variant<int, char>>> tablero);


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
    int casillasDestapadas;
    int legos;
    std::vector<std::vector<std::variant<int, char>>> tablero;
    std::vector<std::vector<std::variant<int, char>>> tableroVisible;

    enum class EstadoCasilla
    {
        MINA = 1, // La casilla contiene una mina.
        OK = 0,   // La casilla no tiene una mina.
        ERROR_OUT_OF_RANGE = -1 // Las coordenadas proporcionadas están fuera del tablero.
    };

    /**
     * @fn Tablero(int filas, int columnas)
     * @brief Constructor de un tablero.
     * @param filas Número de filas del tablero.
     * @param columnas Número de columnas del tablero.
     */
    Tablero(int filas, int columnas);

    
    void CrearPartida();

    /**
     * @fn DestaparCasilla(int fila, int columna)
     * @brief Destapa una casilla del tablero.
     * @param fila Fila de la casilla a destapar.
     * @param columna Columna de la casilla a destapar.
     * @return MINA si la casilla destapada es una mina, OK sino, OUT_OF_RANGE_ERROR 
     * si las coordenadas están fuera de lo indicado.
     */
    EstadoCasilla DestaparCasilla(int fila, int columna);

    /**
     * @fn DescubrirCasillasVacias(int fila, int columna)
     * @brief Descubre las casillas vacías adyacentes a una casilla. 
     * Funciona de manera recursiva.
     * 
     * @param fila Fila de la casilla a destapar.
     * @param columna Columna de la casilla a destapar.
     */
    void DescubrirCasillasVacias(int fila, int columna);

};


std::string input(const std::string& prompt);

void LimpiarConsola();

void IniciarJuego();
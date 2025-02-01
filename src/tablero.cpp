#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <random>
#include <numeric>
#include <sstream>
#include <cctype>

using namespace std;


void print_tablero_con_utf8(const vector<vector<variant<int, char>>> tablero)
{
    int n = tablero.size();
    int m = tablero[0].size();

    string columnas {5, ' '};
    columnas.reserve(m + 5);

    for (char c = 'A'; c < 'A' + m; c++) {
       columnas += string(1, c) + " ";
    }

    vector<string> texto(n, string{});

    for (int indice = 0; indice < n; indice++){
        texto[indice].reserve(6 + 2 * m + 6);
        if (indice < 10){
            texto[indice] +=  string("  ") + to_string(indice) + " │ ";
            
        } else {
            texto[indice] += string(" ") + to_string(indice) + " │ ";
        }

        for (int j = 0; j < m; j++){
           // texto[indice] += " " + string(1, get<char>(tablero[indice][j]));
            
            if (holds_alternative<int>(tablero[indice][j])){
                texto[indice] += to_string(get<int>(tablero[indice][j])) + " ";
            }
            else if (holds_alternative<char>(tablero[indice][j]) && get<char>(tablero[indice][j]) == 'L'){
                texto[indice] += string(1, get<char>(tablero[indice][j])) + " ";
            }
            else {
                texto[indice] += "■ ";
            }
        }

        texto[indice] += "│";
    }

    string utf8_char = u8"─";
    string utf8_text;
    utf8_text.reserve(2 * m + 1 * utf8_char.size());

    for (int i = 0; i < 2 * m + 1; ++i) {
        utf8_text += utf8_char;
    }

    cout << "     " << columnas << "\n";
    cout << "    ┌" << utf8_text << "┐" << "\n";
    
    for (int indice = 0; indice < n; indice++){
        cout << texto[indice] << "\n";
    }

    cout << "    └" << utf8_text << "┘" << "\n";
    cout << flush;

};



Tablero::Tablero(int filas, int columnas):
    n{filas}, 
    m{columnas},
    casillasDestapadas{0},
    tablero(filas, vector<variant<int, char>>(columnas, 0)),
    tableroVisible(filas, vector<variant<int, char>>(columnas, ' '))
{
    this->CrearPartida();
};

void Tablero::CrearPartida(){
    // Truncado (redondeado hacia abajo)
    legos = static_cast<int>((n * m) * PROB_LEGO);

    vector<int> posiciones(n * m);
    iota(posiciones.begin(), posiciones.end(), 0);

    random_device rd;
    mt19937 g(rd());
    shuffle(posiciones.begin(), posiciones.end(), g);

    for (int i = 0; i < legos; i++){
        try {
            if (posiciones.size() == 0){
                throw out_of_range("No hay suficientes posiciones para colocar los legos solicitados");
            }
            //int indice = rand() % posiciones.size();

            //int posicion = posiciones.at(indice);
            
            //posiciones.erase(posiciones.begin() + indice);

            int posicion = posiciones.back();
            posiciones.pop_back();
            
            int fila = posicion / m;
            int columna = posicion % m;
            
            tablero[fila][columna] = 'L';

            // Al colocar un lego, sumar 1 a las 9 casillas adyacentes
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j <= 1; j++){
                    if (fila + i >= 0 && fila + i < n && columna + j >= 0 && columna + j < m){
                        if (holds_alternative<int>(tablero[fila + i][columna + j])){
                            tablero[fila + i][columna + j] = get<int>(tablero[fila + i][columna + j]) + 1;
                        }
                        else if (holds_alternative<char>(tablero[fila + i][columna + j]) && get<char>(tablero[fila + i][columna + j]) == ' '){
                            tablero[fila + i][columna + j] = 1;
                        }
                    }
                }
            }

            
            
        } catch (const out_of_range& e) {
            throw out_of_range("No hay suficientes posiciones para colocar los legos solicitados");
        }
    }
}

Tablero::EstadoCasilla Tablero::DestaparCasilla(int fila, int columna){
    if (fila < 0 || fila >= n || columna < 0 || columna >= m){
        return EstadoCasilla::ERROR_OUT_OF_RANGE;
    }

    if (holds_alternative<char>(tablero[fila][columna]) && get<char>(tablero[fila][columna]) == 'L'){
        return EstadoCasilla::MINA;
    }

    //tableroVisible[fila][columna] = tablero[fila][columna];
    //casillasDestapadas++;
    DescubrirCasillasVacias(fila, columna);
    return EstadoCasilla::OK;
}

void Tablero::DescubrirCasillasVacias(int fila, int columna){
    if (fila < 0 || fila >= n || columna < 0 || columna >= m){
        return;
    }

    if (holds_alternative<int>(tablero[fila][columna]) 
        && get<int>(tablero[fila][columna]) > 0
        &&
        // Verificar que la casilla no haya sido destapada
        // evita recursion infinita
        holds_alternative<char>(tableroVisible[fila][columna])
        &&
        get<char>(tableroVisible[fila][columna]) == ' '
        ){
        tableroVisible[fila][columna] = tablero[fila][columna];
        casillasDestapadas++;
    }
    else if (holds_alternative<int>(tablero[fila][columna]) 
            && 
            get<int>(tablero[fila][columna]) == 0
            &&
            // Verificar que la casilla no haya sido destapada
            // evita recursion infinita
            holds_alternative<char>(tableroVisible[fila][columna]) 
            && 
            get<char>(tableroVisible[fila][columna]) == ' '){

        tableroVisible[fila][columna] = tablero[fila][columna];
        casillasDestapadas++;
        DescubrirCasillasVacias(fila - 1, columna);
        DescubrirCasillasVacias(fila + 1, columna);
        DescubrirCasillasVacias(fila, columna - 1);
        DescubrirCasillasVacias(fila, columna + 1);
        DescubrirCasillasVacias(fila - 1, columna - 1);
        DescubrirCasillasVacias(fila - 1, columna + 1);
        DescubrirCasillasVacias(fila + 1, columna - 1);
        DescubrirCasillasVacias(fila + 1, columna + 1);
    }
}



void LimpiarConsola(){

    //cout << "\033[2J\033[1;1H";
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Mac
    #endif
}




std::string input(const std::string& prompt) {
    string inputString;
    cout << prompt;
    getline(cin, inputString); 
    return inputString;
}





void IniciarJuego(){

    /////////////////////////// Lógica pedir filas y columnas ///////////////////////////////// 

    int filas, columnas;

    // Pedir filas
    while (true) {
        try {
            string userInput = input("Por favor, escriba el número de filas que desea: ");
            filas = stoi(userInput);
            if (filas < 3 || filas > 15) {
                throw out_of_range("Número fuera de rango");
            }
            break;
        } catch (const invalid_argument& e) {
            LimpiarConsola();
            cout 
                << u8"\u001b[31mCarácter incorrecto, porfavor escriba sólo números"
                << "\u001b[0m"
                << endl;
        } catch (const out_of_range& e) {
            LimpiarConsola();
            cout 
                << u8"\u001b[31mCarácter incorrecto, porfavor escriba números entre 3 y 15"
                << "\u001b[0m"
                << endl;
        }
    }


    // Pedir columnas
    while (true) {
        try {
            string userInput = input("Por favor, escriba el número de columnas que desea: ");
            columnas = stoi(userInput);
            if (columnas < 3 || columnas > 15) {
                throw out_of_range("Número fuera de rango");
            }
            break;
        } catch (const invalid_argument& e) {
            LimpiarConsola();
            cout 
                << u8"\u001b[31mCarácter incorrecto, porfavor escriba sólo números"
                << "\u001b[0m"
                << endl;
        } catch (const out_of_range& e) {
            LimpiarConsola();
            cout 
                << u8"\u001b[31mCarácter incorrecto, porfavor escriba números entre 3 y 15"
                << "\u001b[0m"
                << endl;
        }
    }

    ////////////////////////// FIN Lógica pedir filas y columnas /////////////////////////////////

    Tablero tablero {filas, columnas};

    

    /////////////////////////////////// LOOP DE JUEGO ////////////////////////////////////////
    while (tablero.casillasDestapadas < (filas * columnas) - tablero.legos){

        print_tablero_con_utf8(tablero.tableroVisible);
        cout 
            << "Porfavor, escriba las coordenadas de la casilla que desea descubrir, \
separadas por un espacio."
            << endl
            << "Si desea volver al menú principal, escriba MENU"
            << endl
            << "Si desea guardar su partida, escriba GUARDAR"
            << endl;
        
        int coord_fila, coord_columna;
        char letra_columna;
       // string string_fila, string_columna;

        istringstream userInput (input(""));

        if (userInput >> letra_columna >> coord_fila) {
            letra_columna = tolower(letra_columna); // Asegurarse de que sea minúscula

            // Verificar que la letra de la columna es válida (una letra entre 'a' y 'z')
            if (!isalpha(letra_columna)) {
                LimpiarConsola();
                cout << "Error: La columna debe ser una letra." << endl;
                continue;
            }
            
            coord_columna = letra_columna - 'a';
            cout << "Fila: " << coord_fila << ", Columna: " << coord_columna << endl;

        } 
        else { // Si no se pudo leer correctamente la entrada
        
            string inputString;
            userInput.clear();
            userInput.seekg(0);
            userInput >> inputString;

            if (inputString == "MENU"){
                cout << "Volviendo al menú principal" << endl;
                break;
            }
            else if (inputString == "GUARDAR"){
                // Guardar partida
                cout << "Partida guardada" << endl;
                break;
            }
            else {
                LimpiarConsola();
                cout 
                    << u8"\u001b[31mCarácter incorrecto, porfavor escriba la letra de las columnas, "
                    << "seguida del número de las filas en MINÚSCULAS con un espacio, ejemplo:"
                    << endl
                    << "\u001b[0mLetraColumna NumeroFila"
                    << endl
                    << "O, si desea salir escriba SALIR"
                    << "\u001b[0m"
                    << endl;
                
                continue;
            }
        }
        
        // LOGICA TABLERO
        Tablero::EstadoCasilla estado = tablero.DestaparCasilla(coord_fila, coord_columna);

        if (estado == Tablero::EstadoCasilla::MINA){
            LimpiarConsola();
            
            cout 
                << u8"\u001b[31m"
                << "¡Perdiste! Has encontrado una mina"
                << "\u001b[0m"
                << endl;
            break;
        }
        else if (estado == Tablero::EstadoCasilla::ERROR_OUT_OF_RANGE){
            LimpiarConsola();
            cout 
                << u8"\u001b[31mCoordenadas fuera de rango, porfavor escriba coordenadas válidas"
                << "\u001b[0m"
                << endl;
            continue;
        }
        else {
            tablero.DescubrirCasillasVacias(coord_fila, coord_columna);
            LimpiarConsola();
        }

    }

    /////////////////////////////////// FIN LOOP DE JUEGO ////////////////////////////////////////
    print_tablero_con_utf8(tablero.tablero);
    cout << "Fin del juego!" << endl;



}
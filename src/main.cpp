#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits> 
#include "tablero.h"


using namespace std;




int main() {

    int opcion {-1};
    int N {7}, M {20};
    cout << N << " " << M << endl;
    
    Tablero tablero {N, M};

    cout <<"hola como estás " <<endl;

    print_tablero_con_utf8(tablero.tablero);

    std::cout << "\u001b[33mBienvenido A Lego Sweeper!\n\n"
              << u8"\u001b[34mPorfavor escoja una opción\n"
              << "\u001b[0m"
              << endl;
    
    while (opcion != 0) {
        cout
            << u8"Seleccione una opción:" << endl
            << "\u001b[32m1)Comenzar una nueva partida" << endl
            << "\u001b[33m2)Cargar partida existente" << endl
            << "\u001b[35m3)Ver el ranking de puntajes" << endl
            << "\u001b[36;1m0)Salir\u001b[0m" << endl;

        cin >> opcion;

        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
        }

        switch (opcion) {
            
            case 1:
                cout << "Jugando..." << endl;
                break;
            case 2:
                cout << "Instrucciones..." << endl;
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                #ifdef _WIN32
                    system("cls");  // Windows
                #else
                    system("clear");  // Linux/Mac
                #endif
                cout << u8"\u001b[31mCarácter incorrecto, porfavor escriba el número de la opción deseada" << endl;
                break;
        }
    }


    //int N {7}, M {20};
    //cout << N << " " << M << endl;

    //Tablero tablero {N, M};

    //cout <<"hola como estás " <<endl;

    //print_tablero_con_utf8(tablero.tablero);

    //vector<vector<char>> tablero (N, vector<char>(M, ' '));
    //cout << tablero.size() << " " << tablero[0].size() << endl;

    return 0;
}
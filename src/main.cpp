#include <iostream>
#include <string>
#include <vector>
#include "tablero.h"


using namespace std;




int main() {

    int opcion {0};

    std::cout << "\u001b[33mBienvenido A Lego Sweeper!\n\n"
              << "\u001b[34mPorfavor escoja una opción\n"
              << "\u001b[0m"
              << endl;
    while (opcion != 3) {
        cout << "1. Jugar" << endl;
        cout << "2. Ver instrucciones" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

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
            default:
                cout << "Opción inválida" << endl;
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
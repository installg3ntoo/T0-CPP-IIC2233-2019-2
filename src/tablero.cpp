#include "tablero.h"
#include <iostream>

using namespace std;

Tablero::Tablero(int filas, int columnas):
    n{filas}, 
    m{columnas}, 
    tablero(filas, vector<variant<int, char>>(columnas, ' ')) 
{};

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
            if (holds_alternative<int>(tablero[indice][j])){
                texto[indice] += " " + to_string(get<int>(tablero[indice][j]));
            } else {
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

    cout << "     " << columnas << endl;
    cout << "    ┌" << utf8_text << "┐" << endl;
    
    for (int indice = 0; indice < n; indice++){
        cout << texto[indice] << endl;
    }

    cout << "    └" << utf8_text << "┘" << endl;
}
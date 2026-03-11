#include <iostream>

using namespace std;

unsigned char* crearTablero(int ancho, int alto, int &bytesPorFila) {

    if (ancho < 8 || alto < 8 || ancho % 8 != 0) {
        cout << "Dimensiones invalidas" << endl;
        return NULL;
    }

    bytesPorFila = ancho / 8;

    unsigned char* tablero = new unsigned char[alto * bytesPorFila];

    return tablero;
}

void inicializarTablero(unsigned char* tablero, int alto, int bytesPorFila) {

    for (int i = 0; i < alto * bytesPorFila; i++) {
        tablero[i] = 0;
    }

}

void imprimirTablero(unsigned char* tablero, int ancho, int alto, int bytesPorFila) {

    for (int y = 0; y < alto; y++) {

        for (int x = 0; x < ancho; x++) {

            int indice = y * bytesPorFila + (x / 8);

            int bit = 7 - (x % 8);

            if ((tablero[indice] >> bit) & 1)
                cout << "#";
            else
                cout << ".";
        }

        cout << endl;
    }

}

int main() {

    int ancho;
    int alto;

    cout << "Ingrese el ancho (multiplo de 8): ";
    cin >> ancho;

    cout << "Ingrese el alto: ";
    cin >> alto;

    int bytesPorFila;

    unsigned char* tablero = crearTablero(ancho, alto, bytesPorFila);

    if (tablero == NULL)
        return 0;

    inicializarTablero(tablero, alto, bytesPorFila);

    cout << endl << "Tablero creado:" << endl;

    imprimirTablero(tablero, ancho, alto, bytesPorFila);

    delete[] tablero;

    return 0;
}

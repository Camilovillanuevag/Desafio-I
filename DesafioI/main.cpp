<<<<<<< HEAD
=======
#include <iostream>

using namespace std;

unsigned char* crearTablero(int ancho, int alto, int &bytesPorFila)
{
    bytesPorFila = ancho / 8;

    unsigned char* tablero = new unsigned char[alto * bytesPorFila];

    return tablero;
}

void inicializarTablero(unsigned char* tablero, int alto, int bytesPorFila)
{
    for(int i = 0; i < alto * bytesPorFila; i++)
        tablero[i] = 0;
}

void imprimirTablero(unsigned char* tablero, int ancho, int alto, int bytesPorFila)
{
    for(int y = 0; y < alto; y++)
    {
        for(int x = 0; x < ancho; x++)
        {
            int indice = y * bytesPorFila + (x / 8);
            int bit = 7 - (x % 8);

            if((tablero[indice] >> bit) & 1)
                cout << "#";
            else
                cout << ".";
        }

        cout << endl;
    }
}

void crearPieza(unsigned char pieza[4], int tipo)
{
    for(int i = 0; i < 4; i++)
        pieza[i] = 0;

    switch(tipo)
    {
    case 0: // I
        pieza[0] = 0b11110000;
        break;

    case 1: // O
        pieza[0] = 0b11000000;
        pieza[1] = 0b11000000;
        break;

    case 2: // T
        pieza[0] = 0b11100000;
        pieza[1] = 0b01000000;
        break;

    case 3: // S
        pieza[0] = 0b01100000;
        pieza[1] = 0b11000000;
        break;

    case 4: // Z
        pieza[0] = 0b11000000;
        pieza[1] = 0b01100000;
        break;

    case 5: // J
        pieza[0] = 0b10000000;
        pieza[1] = 0b11100000;
        break;

    case 6: // L
        pieza[0] = 0b00100000;
        pieza[1] = 0b11100000;
        break;
    }
}

int obtenerAnchoPieza(int tipo)
{
    switch(tipo)
    {
    case 0: return 4; // I
    case 1: return 2; // O
    case 2: return 3; // T
    case 3: return 4; // S
    case 4: return 4; // Z
    case 5: return 3; // J
    case 6: return 3; // L
    default: return 4;
    }
}

void imprimirPieza(unsigned char pieza[4])
{
    for(int y = 0; y < 4; y++)
    {
        for(int bit = 7; bit >= 0; bit--)
        {
            if((pieza[y] >> bit) & 1)
                cout << "#";
            else
                cout << ".";
        }

        cout << endl;
    }
}

int generarPieza()
{
    static int pieza = 0;

    pieza++;

    if(pieza == 7)
        pieza = 0;

    return pieza;
}

void colocarPieza(unsigned char* tablero, unsigned char pieza[4],
                  int x, int y, int bytesPorFila, int alto)
{
    for(int fila = 0; fila < 4; fila++)
    {
        if (y + fila >= alto) break;

        int baseIndice = (y + fila) * bytesPorFila;
        int byteIndex = x / 8;
        int bitOffset = x % 8;

        if (byteIndex >= bytesPorFila) continue;

        unsigned char parteIzquierda = pieza[fila] >> bitOffset;
        unsigned char parteDerecha = pieza[fila] << (8 - bitOffset);

        tablero[baseIndice + byteIndex] |= parteIzquierda;

        if (byteIndex + 1 < bytesPorFila)
        {
            tablero[baseIndice + byteIndex + 1] |= parteDerecha;
        }
    }
}

int main()
{
    int ancho;
    int alto;

    do
    {
        cout << "Ingrese el ancho (multiplo de 8): ";
        cin >> ancho;

        cout << "Ingrese el alto: ";
        cin >> alto;

        if(ancho < 8 || alto < 8 || ancho % 8 != 0)
            cout << "Dimensiones invalidas\n";

    } while(ancho < 8 || alto < 8 || ancho % 8 != 0);

    int bytesPorFila;

    unsigned char* tablero = crearTablero(ancho, alto, bytesPorFila);

    inicializarTablero(tablero, alto, bytesPorFila);

    unsigned char pieza[4];

    int tipo = generarPieza();

    crearPieza(pieza, tipo);

    int anchoPieza = obtenerAnchoPieza(tipo);
    int x = (ancho - anchoPieza) / 2;
    int y = 0;

    colocarPieza(tablero, pieza, x, y, bytesPorFila, alto);

    cout << "\nTablero:\n";

    imprimirTablero(tablero, ancho, alto, bytesPorFila);

    delete[] tablero;

    return 0;
}
>>>>>>> cfca585ab76af81f9f39615d3611c0d011d1453b

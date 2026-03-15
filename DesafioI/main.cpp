<<<<<<< HEAD
=======
#include <iostream>
#include <random>

using namespace std;

unsigned char* crearTablero(int ancho, int alto, int &bytesPorFila)
{
    bytesPorFila = ancho / 8;
    unsigned char* tablero = new unsigned char[alto * bytesPorFila];
    return tablero;
}

void inicializarTablero(unsigned char* tablero, int alto, int bytesPorFila)
{
    for(int pos = 0; pos < alto * bytesPorFila; pos++)
        tablero[pos] = 0;
}

void imprimirTablero(unsigned char* tablero, int ancho, int alto, int bytesPorFila)
{
    for(int fila = 0; fila < alto; fila++)
    {
        for(int columna = 0; columna < ancho; columna++)
        {
            int indice = fila * bytesPorFila + (columna / 8);
            int bit = 7 - (columna % 8);

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
    for(int pos = 0; pos < 4; pos++)
        pieza[pos] = 0;

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
    case 0: return 4;
    case 1: return 2;
    case 2: return 3;
    case 3: return 3;
    case 4: return 3;
    case 5: return 3;
    case 6: return 3;
    default: return 4;
    }
}

void imprimirPieza(unsigned char pieza[4])
{
    for(int fila = 0; fila < 4; fila++)
    {
        for(int bit = 7; bit >= 0; bit--)
        {
            if((pieza[fila] >> bit) & 1)
                cout << "#";
            else
                cout << ".";
        }

        cout << endl;
    }
}

int generarPieza()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(0,6);

    return dist(gen);
}



bool hayColision(unsigned char* tablero, unsigned char pieza[4],
                 int x, int y, int bytesPorFila, int alto)
{
    for(int fila = 0; fila < 4; fila++)
    {
        if(pieza[fila] == 0)
            continue;

        if(y + fila >= alto)
            return true;

        int baseIndice = (y + fila) * bytesPorFila;
        int byteIndex = x / 8;
        int bitOffset = x % 8;

        unsigned char izquierda = pieza[fila] >> bitOffset;

        if(tablero[baseIndice + byteIndex] & izquierda)
            return true;

        if(bitOffset != 0 && byteIndex + 1 < bytesPorFila)
        {
            unsigned char derecha = pieza[fila] << (8 - bitOffset);

            if(tablero[baseIndice + byteIndex + 1] & derecha)
                return true;
        }
    }

    return false;
}


void colocarPieza(unsigned char* tablero, unsigned char pieza[4],
                  int x, int y, int bytesPorFila, int alto)
{
    for(int fila = 0; fila < 4; fila++)
    {
        if(y + fila >= alto)
            break;

        int baseIndice = (y + fila) * bytesPorFila;
        int byteIndex = x / 8;
        int bitOffset = x % 8;

        if(byteIndex >= bytesPorFila)
            continue;

        unsigned char parteIzquierda = pieza[fila] >> bitOffset;

        tablero[baseIndice + byteIndex] |= parteIzquierda;

        if(bitOffset != 0 && byteIndex + 1 < bytesPorFila)
        {
            unsigned char parteDerecha = pieza[fila] << (8 - bitOffset);
            tablero[baseIndice + byteIndex + 1] |= parteDerecha;
        }
    }
}

bool columnaLlena(unsigned char* tablero, int ancho, int alto, int bytesPorFila)
{
    for(int col = 0; col < ancho; col++)
    {
        bool llena = true;

        for(int fila = 0; fila < alto; fila++)
        {
            int indice = fila * bytesPorFila + (col / 8);
            int bit = 7 - (col % 8);

            if(((tablero[indice] >> bit) & 1) == 0)
            {
                llena = false;
                break;
            }
        }

        if(llena)
            return true;
    }

    return false;
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

    while(!columnaLlena(tablero, ancho, alto, bytesPorFila))
    {
        unsigned char pieza[4];

        int tipo = generarPieza();

        crearPieza(pieza, tipo);

        int anchoPieza = obtenerAnchoPieza(tipo);

        int x = (ancho - anchoPieza) / 2;
        int y = 0;

        if(hayColision(tablero, pieza, x, y, bytesPorFila, alto))
        {
            cout << "Game Over\n";
            delete[] tablero;
            return 0;
        }

        while(!hayColision(tablero, pieza, x, y + 1, bytesPorFila, alto))
        {
            y++;

            unsigned char* tableroTemp = new unsigned char[alto * bytesPorFila];

            for(int pos = 0; pos < alto * bytesPorFila; pos++)
                tableroTemp[pos] = tablero[pos];

            colocarPieza(tableroTemp, pieza, x, y, bytesPorFila, alto);

            cout << "\n";
            imprimirTablero(tableroTemp, ancho, alto, bytesPorFila);

            delete[] tableroTemp;
        }

        colocarPieza(tablero, pieza, x, y, bytesPorFila, alto);

        if(columnaLlena(tablero, ancho, alto, bytesPorFila))
        {
            cout << "\nJuego terminado: una columna se lleno\n";
            imprimirTablero(tablero, ancho, alto, bytesPorFila);

            delete[] tablero;
            return 0;
        }

        cout << "\nTablero actualizado:\n";
        imprimirTablero(tablero, ancho, alto, bytesPorFila);
    }


    return 0;
}
>>>>>>> cfca585ab76af81f9f39615d3611c0d011d1453b

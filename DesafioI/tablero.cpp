#include <iostream>
using namespace std;

#include "tablero.h"

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
    for(int fila = 0; fila < alto; fila++)
    {
        for(int col = 0; col < ancho; col++)
        {
            int byteIndex = fila * bytesPorFila + col / 8;
            int bitIndex = 7 - (col % 8);

            if((tablero[byteIndex] >> bitIndex) & 1)
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}

bool filaLlena(unsigned char* tablero, int fila, int bytesPorFila)
{
    for(int i = 0; i < bytesPorFila; i++)
    {
        if(tablero[fila * bytesPorFila + i] != 255)
            return false;
    }
    return true;
}

void eliminarFila(unsigned char* tablero, int fila, int bytesPorFila)
{
    for(int f = fila; f > 0; f--)
    {
        for(int i = 0; i < bytesPorFila; i++)
            tablero[f * bytesPorFila + i] = tablero[(f - 1) * bytesPorFila + i];
    }

    for(int i = 0; i < bytesPorFila; i++)
        tablero[i] = 0;
}

void limpiarFilasCompletas(unsigned char* tablero, int alto, int bytesPorFila)
{
    for(int fila = 0; fila < alto; fila++)
    {
        if(filaLlena(tablero, fila, bytesPorFila))
        {
            eliminarFila(tablero, fila, bytesPorFila);
            fila--;
        }
    }
}
#include <iostream>
#include <random>
using namespace std;

#include "pieza.h"

void crearPieza(unsigned char pieza[4], int tipo)
{
    for(int i = 0; i < 4; i++)
        pieza[i] = 0;

    if(tipo == 0) // I
    {
        pieza[0] = 0b11110000;
    }
    else if(tipo == 1) // O
    {
        pieza[0] = 0b11000000;
        pieza[1] = 0b11000000;
    }
    else if(tipo == 2) // J
    {
        pieza[0] = 0b11100000;
        pieza[1] = 0b00100000;
    }
    else if(tipo == 3) // L
    {
        pieza[0] = 0b11100000;
        pieza[1] = 0b10000000;
    }
    else if(tipo == 4) // S
    {
        pieza[0] = 0b01100000;
        pieza[1] = 0b11000000;
    }
    else if(tipo == 5) // T
    {
        pieza[0] = 0b11100000;
        pieza[1] = 0b01000000;
    }
    else if(tipo == 6) // Z
    {
        pieza[0] = 0b11000000;
        pieza[1] = 0b01100000;
    }
}

int obtenerAnchoPieza(int tipo)
{
    if(tipo == 0)
        return 4;
    if(tipo == 1)
        return 2;
    if(tipo == 2)
        return 3;
    if(tipo == 3)
        return 2;
    if(tipo == 4)
        return 2;
    if(tipo == 5)
        return 3;
    return 3;
}

void imprimirPieza(unsigned char pieza[4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if((pieza[i] >> (7 - j)) & 1)
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}

int generarPieza()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 6);
    return dis(gen);
}

int obtenerAnchoReal(unsigned char pieza[4])
{
    int maxCol = -1;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if((pieza[i] >> (7 - j)) & 1)
            {
                if(j > maxCol)
                    maxCol = j;
            }
        }
    }

    return maxCol + 1;
}

bool obtenerCelda(unsigned char pieza[4], int fila, int col)
{
    return (pieza[fila] >> (7 - col)) & 1;
}

void ponerCelda(unsigned char pieza[4], int fila, int col)
{
    pieza[fila] |= (1 << (7 - col));
}

void normalizarPieza(unsigned char pieza[4])
{
    while(pieza[0] == 0 && (pieza[1] != 0 || pieza[2] != 0 || pieza[3] != 0))
    {
        pieza[0] = pieza[1];
        pieza[1] = pieza[2];
        pieza[2] = pieza[3];
        pieza[3] = 0;
    }

    bool vaciaIzq = true;

    for(int i = 0; i < 4; i++)
    {
        if((pieza[i] >> 7) & 1)
        {
            vaciaIzq = false;
            break;
        }
    }

    while(vaciaIzq)
    {
        for(int i = 0; i < 4; i++)
            pieza[i] <<= 1;

        vaciaIzq = true;
        for(int i = 0; i < 4; i++)
        {
            if((pieza[i] >> 7) & 1)
            {
                vaciaIzq = false;
                break;
            }
        }
    }
}

void rotarPieza(unsigned char pieza[4])
{
    unsigned char temp[4];
    for(int i = 0; i < 4; i++)
        temp[i] = 0;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(obtenerCelda(pieza, i, j))
                ponerCelda(temp, j, 3 - i);
        }
    }

    for(int i = 0; i < 4; i++)
        pieza[i] = temp[i];

    normalizarPieza(pieza);
}
#include <iostream>
using namespace std;

#include "tablero.h"
#include "pieza.h"
#include "juego.h"

bool hayColision(unsigned char* tablero, unsigned char pieza[4],
                 int x, int y, int bytesPorFila, int alto, int ancho)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if((pieza[i] >> (7 - j)) & 1)
            {
                int tableroX = x + j;
                int tableroY = y + i;

                if(tableroX < 0 || tableroX >= ancho || tableroY >= alto)
                    return true;

                if(tableroY >= 0)
                {
                    int byteIndex = tableroY * bytesPorFila + tableroX / 8;
                    int bitIndex = 7 - (tableroX % 8);

                    if((tablero[byteIndex] >> bitIndex) & 1)
                        return true;
                }
            }
        }
    }
    return false;
}

void colocarPieza(unsigned char* tablero, unsigned char pieza[4],
                  int x, int y, int bytesPorFila, int alto)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if((pieza[i] >> (7 - j)) & 1)
            {
                int tableroX = x + j;
                int tableroY = y + i;

                if(tableroY >= 0 && tableroY < alto)
                {
                    int byteIndex = tableroY * bytesPorFila + tableroX / 8;
                    int bitIndex = 7 - (tableroX % 8);
                    tablero[byteIndex] |= (1 << bitIndex);
                }
            }
        }
    }
}

void imprimirTableroConPieza(unsigned char* tablero, unsigned char pieza[4],
                             int x, int y, int ancho, int alto, int bytesPorFila)
{
    for(int fila = 0; fila < alto; fila++)
    {
        for(int col = 0; col < ancho; col++)
        {
            bool ocupado = false;

            int byteIndex = fila * bytesPorFila + col / 8;
            int bitIndex = 7 - (col % 8);

            if((tablero[byteIndex] >> bitIndex) & 1)
                ocupado = true;

            int filaPieza = fila - y;
            int colPieza = col - x;

            if(filaPieza >= 0 && filaPieza < 4 && colPieza >= 0 && colPieza < 4)
            {
                if((pieza[filaPieza] >> (7 - colPieza)) & 1)
                    ocupado = true;
            }

            if(ocupado)
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}

void jugar()
{
    int ancho, alto;

    cout << "========================" << endl;
    cout << "       BIT TETRIS       " << endl;
    cout << "========================" << endl;
    cout << "a / A: izquierda" << endl;
    cout << "d / D: derecha" << endl;
    cout << "s / S: bajar" << endl;
    cout << "r / R: rotar" << endl;
    cout << "q / Q: salir" << endl;
    cout << endl;

    while(true)
    {
        while(true)
        {
            cout << "Ancho del tablero (multiplo de 8): ";
            cin >> ancho;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida. Debes poner un numero entero." << endl;
                cout << endl;
                continue;
            }

            cout << "Alto del tablero: ";
            cin >> alto;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida. Debes poner un numero entero." << endl;
                cout << endl;
                continue;
            }

            if(ancho <= 0 || alto <= 0)
            {
                cout << "Error. El ancho y el alto deben ser mayores que 0." << endl;
                cout << endl;
                continue;
            }

            if(ancho % 8 != 0)
            {
                cout << "Error. El ancho debe ser multiplo de 8." << endl;
                cout << endl;
                continue;
            }

            break;
        }

        int bytesPorFila;
        unsigned char* tablero = crearTablero(ancho, alto, bytesPorFila);
        inicializarTablero(tablero, alto, bytesPorFila);

        bool gameOver = false;

        while(!gameOver)
        {
            int tipo = generarPieza();
            unsigned char pieza[4];
            crearPieza(pieza, tipo);

            int anchoPieza = obtenerAnchoReal(pieza);
            int x = (ancho - anchoPieza) / 2;
            int y = 0;

            if(hayColision(tablero, pieza, x, y, bytesPorFila, alto, ancho))
            {
                break;
            }

            bool fija = false;

            while(!fija)
            {
                cout << endl;
                imprimirTableroConPieza(tablero, pieza, x, y, ancho, alto, bytesPorFila);
                cout << "Accion [a/d/s/r/q]: ";

                char op;
                cin >> op;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada invalida." << endl;
                    continue;
                }

                if(op == 'q' || op == 'Q')
                {
                    cout << "Saliendo del juego..." << endl;
                    delete[] tablero;
                    return;
                }
                else if(op == 'a' || op == 'A')
                {
                    if(!hayColision(tablero, pieza, x - 1, y, bytesPorFila, alto, ancho))
                        x--;
                }
                else if(op == 'd' || op == 'D')
                {
                    if(!hayColision(tablero, pieza, x + 1, y, bytesPorFila, alto, ancho))
                        x++;
                }
                else if(op == 'r' || op == 'R')
                {
                    unsigned char copia[4];
                    for(int i = 0; i < 4; i++)
                        copia[i] = pieza[i];

                    rotarPieza(copia);

                    if(!hayColision(tablero, copia, x, y, bytesPorFila, alto, ancho))
                    {
                        for(int i = 0; i < 4; i++)
                            pieza[i] = copia[i];
                    }
                }
                else if(op == 's' || op == 'S')
                {
                    if(!hayColision(tablero, pieza, x, y + 1, bytesPorFila, alto, ancho))
                        y++;
                    else
                    {
                        colocarPieza(tablero, pieza, x, y, bytesPorFila, alto);
                        limpiarFilasCompletas(tablero, alto, bytesPorFila);
                        fija = true;
                        continue;
                    }
                }
                else if(op >= '0' && op <= '9')
                {
                    cout << "Entrada invalida. No debes ingresar numeros." << endl;
                    cout << "Usa solo: a, d, s, r o q." << endl;
                    continue;
                }
                else if((op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z'))
                {
                    cout << "Letra no valida: " << op << endl;
                    cout << "Usa solo: a, d, s, r o q." << endl;
                    continue;
                }
                else
                {
                    cout << "Caracter no valido: " << op << endl;
                    cout << "Usa solo: a, d, s, r o q." << endl;
                    continue;
                }

                if(hayColision(tablero, pieza, x, y + 1, bytesPorFila, alto, ancho))
                {
                    colocarPieza(tablero, pieza, x, y, bytesPorFila, alto);
                    limpiarFilasCompletas(tablero, alto, bytesPorFila);
                    fija = true;
                }
            }
        }

        cout << endl;
        cout << "===== GAME OVER =====" << endl;
        cout << "r / R: reiniciar" << endl;
        cout << "q / Q: salir" << endl;

        char opcionFinal;

        while(true)
        {
            cout << "Opcion: ";
            cin >> opcionFinal;

            if(opcionFinal == 'r' || opcionFinal == 'R')
            {
                delete[] tablero;
                cout << endl;
                break;
            }
            else if(opcionFinal == 'q' || opcionFinal == 'Q')
            {
                delete[] tablero;
                cout << "Saliendo del juego..." << endl;
                return;
            }
            else if(opcionFinal >= '0' && opcionFinal <= '9')
            {
                cout << "No debes ingresar numeros." << endl;
            }
            else if((opcionFinal >= 'a' && opcionFinal <= 'z') || (opcionFinal >= 'A' && opcionFinal <= 'Z'))
            {
                cout << "Letra no valida. Usa solo r o q." << endl;
            }
            else
            {
                cout << "Caracter no valido. Usa solo r o q." << endl;
            }
        }
    }
}
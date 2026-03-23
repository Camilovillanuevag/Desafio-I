#ifndef JUEGO_H
#define JUEGO_H

bool hayColision(unsigned char* tablero, unsigned char pieza[4],
                 int x, int y, int bytesPorFila, int alto, int ancho);

void colocarPieza(unsigned char* tablero, unsigned char pieza[4],
                  int x, int y, int bytesPorFila, int alto);

void jugar();

#endif
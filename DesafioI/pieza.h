#ifndef PIEZA_H
#define PIEZA_H

void crearPieza(unsigned char pieza[4], int tipo);
int obtenerAnchoPieza(int tipo);
void imprimirPieza(unsigned char pieza[4]);
int generarPieza();

int obtenerAnchoReal(unsigned char pieza[4]);
bool obtenerCelda(unsigned char pieza[4], int fila, int col);
void ponerCelda(unsigned char pieza[4], int fila, int col);
void normalizarPieza(unsigned char pieza[4]);
void rotarPieza(unsigned char pieza[4]);

#endif
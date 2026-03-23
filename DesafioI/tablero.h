#ifndef TABLERO_H
#define TABLERO_H

unsigned char* crearTablero(int ancho, int alto, int &bytesPorFila);
void inicializarTablero(unsigned char* tablero, int alto, int bytesPorFila);
void imprimirTablero(unsigned char* tablero, int ancho, int alto, int bytesPorFila);

bool filaLlena(unsigned char* tablero, int fila, int bytesPorFila);
void eliminarFila(unsigned char* tablero, int fila, int alto, int bytesPorFila);
void limpiarFilasCompletas(unsigned char* tablero, int alto, int bytesPorFila);

#endif

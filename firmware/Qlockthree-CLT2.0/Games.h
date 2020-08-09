
/*
    Definition für die zusätzlich implementierten Games

*/

#ifndef GAMES_H
#define GAMES_H

// Für 4 gewinnt / connect 4
#define N_ROWS 6 // Anzahl der Zeilen des Spielfelds
#define N_COLS 7 // Anzahl der Spalten des Spielfelds
#define NUM_COLORS 2 // Anzahl an Farben die im Game Mode "Connect 4" übertragen werden
/**  Anzahl an bytes die im Game Mode "Connect 4" übertragen werden
 *      Farben jeweils als 3 Bytes RGB
 *      Spielfeld: Farbindex
 *      Ecken: Farbindex     */
#define NUM_BYTES_BT_CON4 (NUM_COLORS*3 + N_ROWS*N_COLS + 1) 

#endif
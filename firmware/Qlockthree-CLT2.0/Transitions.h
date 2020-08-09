/**
 * Transitions.h
 * Transitionen bei Wechsel Zeitmatrix
 *
 * @mc       Arduino/UNO
 * @autor    Manuel Bracher / manuel.bracher@gmail.com
 * @version  1.0
 * @created  19.05.15
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 */

#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "Arduino.h"

class Transitions {
  public:
    static boolean nextSlideStep (uint16_t matrixNew[16], uint16_t matrix[16]);
    static void resetTransition();
    static boolean nextMatrixStep(uint16_t matrixOld[16], uint16_t matrixNew[16], uint16_t matrixOverlay[16], uint16_t matrix[16]);

  private:
    static void shiftColumnDown(uint16_t matrix[16], uint8_t column);
    static void shiftColumnUp (uint16_t matrixNew[16], uint16_t matrix[16], uint8_t column);
    static void shiftDownMatrixErease(uint16_t matrixMatrix[16], uint16_t matrixWeak[16]);
    static void shiftDownMatrixWrite(uint16_t matrixMatrix[16], uint16_t matrixWeak[16]);
    static uint8_t _counter;
    static uint16_t _usedColumns;
    static uint8_t _remainingCoulumnCount;
    static boolean _ereasingDone;
    static boolean _writingDone;
};


#endif

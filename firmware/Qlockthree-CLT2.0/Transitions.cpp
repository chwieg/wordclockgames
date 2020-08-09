/**
 * Transitions.cpp
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

#include "Transitions.h"

uint8_t Transitions::_counter;
uint16_t Transitions::_usedColumns;
uint8_t Transitions::_remainingCoulumnCount;
boolean Transitions::_ereasingDone;
boolean Transitions::_writingDone;

void Transitions::resetTransition () {
  _counter = 0;
  _usedColumns = 0;
  _remainingCoulumnCount = 12;
  _ereasingDone = false;
  _writingDone = false;
}

boolean Transitions::nextSlideStep (uint16_t matrixNew[16], uint16_t matrix[16]) {
  _counter++;
  if (_counter < 22) {
    for (uint8_t i = 0; i < min( _counter, 12); i++) {
      shiftColumnDown(matrixNew, i);
    }
  }
  else {
    for (uint8_t i = max(_counter - 22 - 9, 0); i < min( _counter - 21, 12); i++) {
      shiftColumnUp(matrixNew, matrix, i);
    }
  }
  return (_counter > 41);
}

void Transitions::shiftColumnDown (uint16_t matrix[16], uint8_t column) {
  uint16_t tempMatrix = (0x01 << (15 - column));
  for (uint8_t i = 10; i > 0; i--) {
    matrix[i] &= ~tempMatrix;
    matrix[i] |= (matrix[i - 1] & tempMatrix);
  }
  matrix[0] &= ~tempMatrix;
}

void Transitions::shiftColumnUp (uint16_t matrixNew[16], uint16_t matrix[16], uint8_t column) {
  uint16_t tempMatrix = (0x01 << (15 - column));
  uint8_t tempIdx;
  for (uint8_t i = 0; i < 10; i++) {
    matrixNew[i] &= ~tempMatrix;
    tempIdx = i - (9 + column - (_counter - 22));
    if (tempIdx < 12) {
      matrixNew[i] |= (matrix[tempIdx] & tempMatrix);
    }
  }
  matrix[10] &= ~tempMatrix;
}

boolean Transitions::nextMatrixStep(uint16_t matrixWeak[16], uint16_t matrixTime[16], uint16_t matrixMatrix[16], uint16_t matrix[16]) {
  uint8_t loopCount = random(0, 5);
  uint8_t column;

  if (!_ereasingDone) {
    shiftDownMatrixErease(matrixMatrix, matrixWeak);
    if (random(0, 3) > 0)
    {
      if ( (_remainingCoulumnCount < 3) && (_remainingCoulumnCount > 0))
      {
        matrixMatrix[0] |= ~_usedColumns;
        _usedColumns |= matrixMatrix[0];
        _remainingCoulumnCount = 0;
      }
      else
      {
        for ( uint8_t i = 0; i < loopCount; i++) {
          column = random(4, 16);
          if (!(_usedColumns & (0x01 << column))) {
            _usedColumns |= (0x01 << column);
            _remainingCoulumnCount--;
          }
          matrixMatrix[0] |= 0x01 << column;
        }
      }
    }
  }
  else {
    shiftDownMatrixWrite(matrixMatrix, matrixWeak);
    if ( (random(0, 3) > 0) && (_remainingCoulumnCount > 0) )
    {
      if ( _remainingCoulumnCount < 3 )
      {
        matrixMatrix[0] |= ~_usedColumns;
        _usedColumns |= matrixMatrix[0];
        _remainingCoulumnCount = 0;
      }
      else
      {
        for ( uint8_t i = 0; i < loopCount; i++) {
          column = random(4, 16);
          if (!(_usedColumns & (0x01 << column))) {
            _usedColumns |= (0x01 << column);
            _remainingCoulumnCount--;
            matrixMatrix[0] |= 0x01 << column;
          }
        }
      }
    }
  }

  if (!_remainingCoulumnCount) {
    _counter++;
    if (_counter > 11) {
      if (!_ereasingDone) {
        for (uint8_t i = 0; i < 11; i++) {
          matrixTime[i] = matrix[i];
        }
        _usedColumns = 0;
        _remainingCoulumnCount = 12;
        _counter = 0;
        _ereasingDone = true;
      }
      else {
        _writingDone = true;
      }
    }
  }

  return (_writingDone);
}

void Transitions::shiftDownMatrixErease(uint16_t matrixMatrix[16], uint16_t matrixWeak[16]) {
  for (uint8_t i = 10; i > 0; i--) {
    matrixMatrix[i] = matrixMatrix[i - 1];
    matrixWeak[i] |= matrixWeak[i - 1];
  }
  matrixWeak[0] = (matrixMatrix[1] | matrixWeak[1]) ;
  matrixMatrix[0] = 0;
}

void Transitions::shiftDownMatrixWrite(uint16_t matrixMatrix[16], uint16_t matrixWeak[16]) {
  for (uint8_t i = 10; i > 0; i--) {
    matrixMatrix[i] = matrixMatrix[i - 1];
    matrixWeak[i] = matrixWeak[i - 1];
  }
  matrixWeak[0] = (~matrixMatrix[1] & matrixWeak[1]) ;
  matrixMatrix[0] = 0;
}




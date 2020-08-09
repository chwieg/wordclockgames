/**
 * LedDriverDefault
 * Implementierung auf der Basis 74HC595 und UDN2981A.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.4
 * @created  18.1.2013
 * @updated  18.1.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - printSignature() eingefuehrt.
 *         - Benennung verbessert.
 * V 1.2:  - Anpassung Helligkeit 0-100%
 * V 1.3:  - Getter fuer Helligkeit nachgezogen.
 * V 1.4:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 */
#ifndef LED_DRIVER_DEFAULT_H
#define LED_DRIVER_DEFAULT_H

#include "Arduino.h"
#include "ShiftRegister.h"
#include "LedDriver.h"

class LedDriverDefault : public LedDriver {
  public:
    LedDriverDefault(uint8_t data, uint8_t clock, uint8_t latch, uint8_t outputEnable, uint8_t linesToWrite);

    void init();

    void printSignature();

    void writeScreenBufferToMatrix(uint16_t matrix[16], boolean onChange, eColors a_color = color_none);

    void setBrightness(uint8_t brightnessInPercent);
    uint8_t getBrightness();

    void setLinesToWrite(uint8_t linesToWrite);

    void shutDown();
    void wakeUp();

    void clearData();

  private:
    uint8_t _brightnessInPercent;

    uint8_t _linesToWrite;

    uint8_t _outputEnablePin;

    ShiftRegister *_shiftRegister;
    unsigned int _delayOldMatrix;
    unsigned int _delayNewMatrix;
};

#endif

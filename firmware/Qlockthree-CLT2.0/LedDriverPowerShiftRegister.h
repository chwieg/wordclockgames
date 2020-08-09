/**
 * LedDriverPowerShiftRegister
 * Implementierung auf der Basis von TPICB595N.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.3
 * @created  13.8.2013
 * @updated  16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - Anpassung auf Helligkeit 0-100%
 * V 1.2:  - Getter fuer Helligkeit nachgezogen.
 * V 1.3:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 */
#ifndef LED_DRIVER_POWER_SHIFT_REGISTER_H
#define LED_DRIVER_POWER_SHIFT_REGISTER_H

#include "Arduino.h"
#include "LedDriver.h"
#include "ShiftRegister.h"

class LedDriverPowerShiftRegister : public LedDriver {
  public:
    LedDriverPowerShiftRegister(uint8_t data, uint8_t clock, uint8_t latch, uint8_t outputEnable);

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

    uint8_t _outputEnable;

    ShiftRegister *_shiftRegister;
};

#endif

/**
 * LedDriverDotStar
 * Implementierung auf der Basis von APA102-Streifen wie sie die Adafruit-Dot-Stars verwenden.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  9.2.2015
 * @updated  16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 *
 * Verkabelung: Einspeisung oben links, dann schlangenfoermig runter,
 * dann Ecke unten links, oben links, oben rechts, unten rechts.
 *
 */
#ifndef LED_DRIVER_DOTSTAR_H
#define LED_DRIVER_DOTSTAR_H

#include "Arduino.h"
#include "LedDriver.h"
#include <Adafruit_DotStar.h>

class LedDriverDotStar : public LedDriver {
  public:
    LedDriverDotStar(uint8_t dataPin, uint8_t clockPin);

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

    boolean _dirty;

    void _setPixel(uint8_t x, uint8_t y, uint32_t c);
    void _setPixel(uint8_t num, uint32_t c);

    uint32_t _wheel(uint8_t brightness, uint8_t wheelPos);

    void _clear();

    uint8_t _brightnessScaleColor(uint8_t brightness, uint8_t colorPart);

    Adafruit_DotStar *_strip;
};

#endif

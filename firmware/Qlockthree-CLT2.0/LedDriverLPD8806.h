/**
 * LedDriverLPD8806
 * Implementierung auf der Basis von LPD8806-Streifen.
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
 * Achtung! LPD8806-Streifen koennen nur in Vielfachen von 2 getrennt werden! Daher bleiben am Rand LEDs uebrig (und dunkel)!
 *
 */
#ifndef LED_DRIVER_LPD8806_H
#define LED_DRIVER_LPD8806_H

#include "Arduino.h"
#include "LedDriver.h"

#ifdef MATRIX_XXL
  #ifdef RGBW_LEDS
    #include <LPD8806RGBW_DBL.h>
  #else 
    #include <LPD8806DBL.h>
  #endif
#else
  #ifdef RGBW_LEDS
    #include <LPD8806RGBW.h>
  #else
    #include <LPD8806.h>
  #endif
#endif

#include "Games.h"


class LedDriverLPD8806 : public LedDriver {
  public:
    LedDriverLPD8806(uint8_t dataPin, uint8_t clockPin);

    void init();

    void printSignature();

    void writeScreenBufferToMatrix(uint16_t matrix[16], boolean onChange, eColors a_color);
    void writeBoardToMatrix(uint8_t colorDef[NUM_COLORS][3], uint8_t board[N_ROWS][N_COLS], uint8_t corners); 
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

    unsigned int _lastLEDsOn;

#ifdef MATRIX_XXL
  #ifdef RGBW_LEDS
    LPD8806RGBW_DBL *_strip;
  #else 
    LPD8806DBL *_strip;
  #endif
#else
  #ifdef RGBW_LEDS
    LPD8806RGBW *_strip;
  #else
    LPD8806 *_strip;
  #endif
#endif

};

#endif

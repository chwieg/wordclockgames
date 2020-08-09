/**
 * LedDriver
 * Abstrakte Klasse fuer einen LED-Treiber. Hiervon koennen andere Implementierungen
 * erben (75HC595, MAX7219, AS1130 etc.)
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.5
 * @created  18.1.2013
 * @updated  16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - printSignature() eingefuehrt.
 * V 1.2:  - Setzen und lesen von Pixel eingefuehrt.
 * V 1.3:  - Anpassung auf Helligkeit in Prozent.
 * V 1.4:  - Getter fuer Helligkeit eingefuehrt.
 * V 1.5:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 */
#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "Arduino.h"

#include "Settings.h"
#include "MyRTC.h"
#include "Transitions.h"
#include "Modes.h"
#include "Configuration.h"
#include "Colors.h"

extern volatile uint8_t helperSeconds;
extern Mode mode;
extern Settings settings;
extern MyRTC rtc;
extern bool evtActive;

/* Treiberkonfiguration */
#if defined(LED_DRIVER_LPD8806)
#define FADINGCOUNTERLOAD 25
#define SLIDINGCOUNTERLOAD 350
#define MATRIXCOUNTERLOAD 950
#elif defined(LED_DRIVER_NEOPIXEL)
#define FADINGCOUNTERLOAD 100
#define SLIDINGCOUNTERLOAD 525
#define MATRIXCOUNTERLOAD 1400
#elif defined(LED_DRIVER_DOTSTAR)
#define FADINGCOUNTERLOAD 70
#define SLIDINGCOUNTERLOAD 350
#define MATRIXCOUNTERLOAD 1100
#else
#define FADINGCOUNTERLOAD 70
#define SLIDINGCOUNTERLOAD 7
#define MATRIXCOUNTERLOAD 1100
#endif

#define FADINGDURATION 5

#define NORMALCOUNTERLOAD 1000

class LedDriver {
  public:
    virtual void init();

    virtual void printSignature();

    virtual void writeScreenBufferToMatrix(uint16_t matrix[16], boolean onChange, eColors a_color);

    virtual void setBrightness(uint8_t brightnessInPercent);
    virtual uint8_t getBrightness();

    virtual void setLinesToWrite(uint8_t linesToWrite);

    virtual void shutDown();
    virtual void wakeUp();

    virtual void clearData();

    void setPixelInScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[16]);
    boolean getPixelFromScreenBuffer(uint8_t x, uint8_t y, uint16_t matrix[16]);
    void resetWheelPos(void);
    
    void demoTransition();

  protected:
    uint16_t _matrixOld[11];
    uint16_t _matrixNew[11];
    uint16_t _matrixOverlay[11];
    uint8_t _wheelPos;
    unsigned long _lastColorUpdate;
    boolean _transitionCompleted;
    uint16_t _transitionCounter;
    boolean _demoTransition;
};

#endif

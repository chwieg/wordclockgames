/**
   Settings
   Die vom Benutzer getaetigten Einstellungen werden hier verwaltet
   und im EEPROM persistiert.

   @mc       Arduino/RBBB
   @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
   @version  1.3
   @created  23.1.2013
   @updated  16.2.2015

   Versionshistorie:
   V 1.0:  - Erstellt.
   V 1.1:  - LDR-Modus aufgenommen.
   V 1.2:  - Brightness aufgenommen.
           - EnableAlarm aufgenommen.
           - DcfSignalIsInverted aufgenommen.
           - TimeShift aufgenommen.
   V 1.3:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
*/
#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"
#include "Colors.h"
#include "TimeStamp.h"

class Settings {
  public:
    enum eTransitions : uint8_t {
      TRANSITION_MODE_NORMAL,
      TRANSITION_MODE_FADE,
      TRANSITION_MODE_MATRIX,
      TRANSITION_MODE_SLIDE,

      TRANSITION_MODE_MAX
    };

    Settings();

    uint8_t getLanguage();
    void setLanguage(uint8_t language);

    uint8_t getEvent();
    void setEvent(uint8_t event);

    boolean getRenderCornersCw();
    void setRenderCornersCw(boolean cw);

    boolean getUseLdr();
    void setUseLdr(boolean useLdr);

    uint8_t getBrightness();
    void setBrightness(uint8_t brightness);

    void setColor(eColors color);
    eColors getColor();

    boolean getEnableAlarm();
    void setEnableAlarm(boolean enableAlarm);

    uint8_t getTransitionMode();
    void setTransitionMode(uint8_t transitionMode);

    boolean getDcfSignalIsInverted();
    void setDcfSignalIsInverted(boolean dcfSignalIsInverted);

    char getTimeShift();
    void setTimeShift(char timeShift);

    uint8_t getJumpToNormalTimeout();
    void setJumpToNormalTimeout(uint8_t jumpToNormalTimeout);

    uint8_t getColorChangeRate();
    void setColorChangeRate(uint8_t rate);

    void loadFromEEPROM();
    void saveToEEPROM();

    void resetToDefault();

    TimeStamp* getNightModeTime(bool onTime);

  private:
    uint8_t _language;
    boolean _renderCornersCw;
    boolean _use_ldr;
    uint8_t _brightness;
    boolean _enableAlarm;
    boolean _dcfSignalIsInverted;
    char _timeShift;
    eColors _color;
    uint8_t _transitionMode;
    uint8_t _event;
    TimeStamp* _nightModeTime[2];

    uint8_t _jumpToNormalTimeout;
    uint8_t _colorChangeRate;
};

#endif


/**
 * Alarm
 * Klasse fuer die Weckfunktion.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @created  22.1.2013
 * @update   16.2.2015
 *
 * Versionshistorie:
 * V 1.0:  - Erstellt.
 * V 1.1:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 */
#ifndef ALARM_H
#define ALARM_H

#include "Arduino.h"
#include "TimeStamp.h"

class Alarm : public TimeStamp {
  public:
    Alarm(uint8_t speakerPin);

    void activate();
    void deactivate();
    void buzz(boolean on);

    uint8_t getShowAlarmTimeTimer();
    void setShowAlarmTimeTimer(uint8_t seconds);
    void decShowAlarmTimeTimer();

    boolean isActive();

  private:
    boolean _isActive;
    uint8_t _showAlarmTimeTimer;
    uint8_t _speakerPin;
};

#endif

/**
 * TimeStamp
 * Klasse fuer die Kapselung eines Zeitstempels. Dadurch lassen sich
 * Zeiten aus der Echtzeituhr und von dem DCF77-Empfaenger
 * leichter verarbeiten und vergleichen.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.7a
 * @created  2.3.2011
 * @updated  29.03.2016 (ergänzt durch A. Mueller)
 *
 * Versionshistorie:
 * V 1.1:  - Fehler in toString() behoben.
 * V 1.2:  - Kompatibilitaet zu Arduino-IDE 1.0 hergestellt.
 * V 1.3:  - neuer Konstruktor, neue Methoden.
 * V 1.4:  - getMinutesOf12HoursDay eingefuehrt.
 * V 1.5:  - Optimierung hinsichtlich Speicherbedarf.
 * V 1.6:  - Verbessertes Debugging & leeren Konstruktor entfernt.
 * V 1.7:  - Unterstuetzung fuer die alte Arduino-IDE (bis 1.0.6) entfernt.
 * V 1.7a: - Funktion getMinutesOfCentury() hinzugefügt
 */
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "Arduino.h"

class TimeStamp {
public:
    TimeStamp(uint8_t minutes, uint8_t hours, uint8_t date, uint8_t dayOfWeek, uint8_t month, uint8_t year);

    void incMinutes();
    void decMinutes();
    void incFiveMinutes();
    void incHours();
    void decHours();
    void incDate(uint8_t addDate = 1);
    void incMonth(uint8_t addMonth = 1);
    void incYear(uint8_t addYear = 1);

    uint8_t getMinutes();
    int getMinutesOfDay();
    int getMinutesOf12HoursDay(int minutesDiff);
    uint8_t getHours();

    uint8_t getDate();
    uint8_t getDayOfWeek();
    uint8_t getMonth();
    uint8_t getYear();
    unsigned long getMinutesOfCentury();

    void setMinutes(uint8_t minutes);
    void setHours(uint8_t hours);
    void setDate(uint8_t date);
    void setDayOfWeek(uint8_t dayOfWeek);
    void setMonth(uint8_t month);
    void setYear(uint8_t year);

    void set(uint8_t minutes, uint8_t hours, uint8_t date, uint8_t dayOfWeek, uint8_t month, uint8_t year);
    void set(TimeStamp* timeStamp);

    char* asString();

protected:
    uint8_t getDaysOfMonth(uint8_t month, uint8_t year);
    void CalculateAndSetDayOfWeek();
    void CheckDateValidity();

    uint8_t _minutes;
    uint8_t _hours;

    uint8_t _date;
    uint8_t _dayOfWeek;
    uint8_t _month;
    uint8_t _year;

    char _cDateTime[17];
};

#endif

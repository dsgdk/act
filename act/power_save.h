#ifndef POWER_SAVE_H
#define POWER_SAVE_H

#include <Arduino.h>
#include <avr/power.h>

void disableADC    (); // -- Вимикаємо ADC
void disableSPI    (); // -- Вимикаємо SPI
void disableI2C    (); // -- Вимикаємо I2C
void disableSerial (); // -- Вимикаємо Serial

class pSave {
  public:
    pSave();
    // -- Методи очікування
    void sleepMilliseconds(unsigned long milliseconds);
    void sleepSeconds     (unsigned long seconds);
    void sleepMinutes     (unsigned long minutes);
    void sleepHours       (unsigned long hours);
    void sleepDays        (unsigned long days);
    void sleepWeeks       (unsigned long weeks);
  
  private:
    void sleep            (unsigned long milliseconds);
};

#endif

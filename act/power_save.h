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
    void waitMilliseconds(unsigned long milliseconds);
    void waitSeconds     (unsigned long seconds);
    void waitMinutes     (unsigned long minutes);
    void waitHours       (unsigned long hours);
    void waitDays        (unsigned long days);
    void waitWeeks       (unsigned long weeks);
  
  private:
    void wait            (unsigned long milliseconds);
};

#endif

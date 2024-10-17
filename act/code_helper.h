#ifndef CODE_HELPER_H
#define CODE_HELPER_H

/* -- Бібліотеки -- */
#include <Arduino.h>

#include <SoftwareSerial.h>
#include <EEPROM.h>

#include <avr/wdt.h>
/* -- Функції -- */
int  ee_read          ();                           // -- Оголошення функції для читання  EEPROM
void ee_reset         ();                           // -- Оголошення функції для скидання EEPROM
void ee_add           (uint8_t data);               // -- Оголошення функції для запису в EEPROM

uint8_t a_reboot      ();                           // -- Оголошення функції для програмного перезавантаження

void delayMilliseconds(unsigned long milliseconds); // -- Оголошення функції для затримки в мілісекундах
void delaySeconds     (unsigned long seconds);      // -- Оголошення функції для затримки в секундах
void delayMinutes     (unsigned long minutes);      // -- Оголошення функції для затримки в хвилинах
void delayHours       (unsigned long hours);        // -- Оголошення функції для затримки в годинах
void delayDays        (unsigned long days);         // -- Оголошення функції для затримки в днях
void delayWeeks       (unsigned long weeks);        // -- Оголошення функції для затримки в тижнях

#endif

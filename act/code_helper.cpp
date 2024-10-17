#include "code_helper.h"

/* -- EEPROM -- */
void ee_reset()                                    {  // -- Функція для скидання  EEPROM
  EEPROM.write(0, 0);
}
void ee_add  (uint8_t data)                        {  // -- Функція для запису  в EEPROM
  EEPROM.write(0, data);
}
int  ee_read ()                                    {  // -- Функція для читання з EEPROM
  return EEPROM.read(0);
}

/* -- Reboot -- */
uint8_t a_reboot()                                 {  // -- Функція для програмного перезавантаження
  wdt_enable(WDTO_30MS);
}

/* -- Delay -- */
void delayMilliseconds(unsigned long milliseconds) {  // -- Функція для затримки в мілісекундах
    unsigned long endTime = millis() + milliseconds;
    while (millis() < endTime);
}
void delaySeconds     (unsigned long seconds)      {  // -- Функція для затримки в секундах
    unsigned long endTime = millis() + seconds * 1000;
    while (millis() < endTime);
}
void delayMinutes     (unsigned long minutes)      {  // -- Функція для затримки в хвилинах
    unsigned long endTime = millis() + minutes * 60000; 
    while (millis() < endTime);
}
void delayHours       (unsigned long hours)        {  // -- Функція для затримки в годинах
    unsigned long endTime = millis() + hours * 3600000; 
    while (millis() < endTime);
}
void delayDays        (unsigned long days)         {  // -- Функція для затримки в днях
    unsigned long endTime = millis() + days * 86400000; 
    while (millis() < endTime);
}
void delayWeeks       (unsigned long weeks)        {  // -- Функція для затримки в тижнях
    unsigned long endTime = millis() + weeks * 604800000; 
    while (millis() < endTime);
}

#include "power_save.h"
#include "config.h"
#include <Wire.h>

// -- Реалізація функцій для вимкнення периферії
void disableADC   ()           {
    power_adc_disable();
}
void disableSPI   ()           {
    power_spi_disable();
}
void disableI2C   ()           {
    power_twi_disable();
}
void disableSerial(bool debug) {
    if (debug == 0) power_usart0_disable();
}

// -- Реалізація конструктора pSave
pSave::pSave() {
    // Вимкнення периферії при створенні об'єкта
    disableADC();
    disableSPI();
    disableI2C();
    disableSerial(DEBUG);
}

// -- Різні варіанти методів очікування
void pSave::sleep             (unsigned long milliseconds) {
    unsigned long endTime = millis() + milliseconds;
    while ((long)(millis() - endTime) < 0);
}
void pSave::sleepMilliseconds (unsigned long milliseconds) {
    sleep(milliseconds);
}
void pSave::sleepSeconds      (unsigned long seconds     ) {
    sleep(seconds * 1000);
}
void pSave::sleepMinutes      (unsigned long minutes     ) {
    sleep(minutes * 60000);
}
void pSave::sleepHours        (unsigned long hours       ) {
    sleep(hours * 3600000);
}
void pSave::sleepDays         (unsigned long days        ) {
    sleep(days * 86400000);
}
void pSave::sleepWeeks        (unsigned long weeks       ) {
    sleep(weeks * 604800000);
}

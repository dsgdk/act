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
void pSave::wait             (unsigned long milliseconds) {
    unsigned long endTime = millis() + milliseconds;
    while ((long)(millis() - endTime) < 0);
}
void pSave::waitMilliseconds (unsigned long milliseconds) {
    wait(milliseconds);
}
void pSave::waitSeconds      (unsigned long seconds     ) {
    wait(seconds * 1000);
}
void pSave::waitMinutes      (unsigned long minutes     ) {
    wait(minutes * 60000);
}
void pSave::waitHours        (unsigned long hours       ) {
    wait(hours * 3600000);
}
void pSave::waitDays         (unsigned long days        ) {
    wait(days * 86400000);
}
void pSave::waitWeeks        (unsigned long weeks       ) {
    wait(weeks * 604800000);
}

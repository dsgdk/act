#include "config.h"
#include "code_helper.h"
#include "power_save.h"

SoftwareSerial SIM800L(3, 2);
pSave pSave;

void sim_init () {                      // -- Ініціалізація SIM800L
  SIM800L.println("AT");                // -- Перевірка зв'язку з модулем
  delayMilliseconds(100);               // -- Чекаємо 100 мс
  if (SIM800L.available()) {
    if (DEBUG == 1) Serial.println(SIM800L.readString());
    SIM800L.readString();
  }
  SIM800L.print("AT+CPIN=\"");
  SIM800L.print(PIN_CODE_SIM);
  SIM800L.println("\"");
  delayMilliseconds(100);               // -- Чекаємо 100 мс
  if (SIM800L.available()) {
    if (DEBUG == 1) Serial.println(SIM800L.readString());
    SIM800L.readString();
  }
  /* ------------------------------------------------------------ */
  uint8_t flag = 0;
  while (flag != NUMB_OF_CONNECT) {
    SIM800L.println("AT+CREG?");              // -- Перевірка реєстрації в мережі
    delayMilliseconds(100);                   // -- Чекаємо 100 мс
    if (SIM800L.available()) {
      String response = SIM800L.readString(); // -- Читаємо відповідь
      if (response.indexOf("+CREG: 0,1") != -1 || response.indexOf("+CREG: 0,5") != -1) {
        if (DEBUG == 1) Serial.println("OK"); // -- Зареєстровано в мережі
        break;
      } else {                                // -- Якщо не зареєстровано
        Serial.println("ERROR");
        delayMinutes(DELAY_TIME);             // -- Чекаємо 15 хв
        flag++;
      }
    } else {                                  // -- Якщо немає відповіді
      Serial.println("ERROR");
      delayMinutes(DELAY_TIME);               // -- Чекаємо 15 хв
      flag++;
    }
  }
  /* ------------------------------------------------------------ */
  SIM800L.println("AT+CMGF=1");         // -- Встановлення текстового режиму для SMS
  delayMilliseconds(100);               // -- Чекаємо 100 мс
  if (SIM800L.available()) {
    if (DEBUG == 1) Serial.println(SIM800L.readString());
    SIM800L.readString();
  }
  SIM800L.println("AT+CNMI=1,2,0,0,0"); // -- Налаштування на автоматичне отримання повідомлень
  delayMilliseconds(100);               // -- Чекаємо 100 мс
  if (SIM800L.available()) {
    if (DEBUG == 1) Serial.println(SIM800L.readString());
    SIM800L.readString();
  }
}

void send_sms (String number, String msg) { // -- 
  SIM800L.print("AT+CMGS=\"");          // -- Відправка SMS-повідомлення
  SIM800L.print(number);                // -- Вставляємо номер телефону
  SIM800L.println("\"");

  // -- Чекаємо підтвердження від модуля (символ '>'), що можна вводити повідомлення
  delaySeconds(1);                      // -- Чекаємо 1 c
  String response = SIM800L.readString();
  if (response.indexOf('>') != -1) {
    // Тепер можна надсилати текст повідомлення
    SIM800L.print(msg);                 // -- Надсилаємо повідомлення
    delayMilliseconds(100);             // -- Чекаємо 100 мс
    SIM800L.write(26);                  // -- Надсилаємо "Ctrl+Z" для завершення повідомлення
    delaySeconds(5);                    // -- Чекаємо 5 с, щоб дочекатися завершення
  } else {
    // -- Якщо немає символа '>', значить щось пішло не так
    if (DEBUG == 1) Serial.println("Помилка: немає підтвердження від модуля для надсилання повідомлення");
  }

}

void start_listen() {
  pSave.sleepMinutes(1); // -- Спимо
  sim_init();            // -- Відправляємо СМС, що прокинулись

}

void setup () {
  Serial.begin  (9600);  // -- Юарт для нас
  SIM800L.begin (9600);  // -- Юарт для SIM800L
  if (DEBUG == 1) Serial.println("Start");
  sim_init();
}

void loop () {

}

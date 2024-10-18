#include "config.h"
#include "code_helper.h"
#include "power_save.h"

SoftwareSerial SIM800L(3, 2);
pSave pSave;

/* --------------------------- */
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
/* --------------------------- */
String extractSenderNumber(String line) {        // -- Функція для пошуку номера відправника
  int startIdx = line.indexOf("\"") + 1;      // -- Перший індекс після лапок
  int endIdx = line.indexOf("\"", startIdx);  // -- Знаходимо кінець номера
  return line.substring(startIdx, endIdx);    // -- Витягуємо номер телефону
}
bool message_verification() {                    // -- Функція повертає true, якщо повідомлення отримано
  if (SIM800L.available()) {                     // -- Перевіряємо, чи є дані з модуля SIM800L
    String line = SIM800L.readStringUntil('\n'); // -- Читаємо вхідну лінію від SIM800L
    line.trim();                                 // -- Видаляємо зайві пробіли
    if (line.startsWith("+CMT:")) {              // -- Перевіряємо, чи це повідомлення
      String senderNumber = extractSenderNumber(line);
      if (senderNumber == IN_NUMBER) {
        if (SIM800L.available()) {
          String message = SIM800L.readStringUntil('\n'); // -- Читаємо саме повідомлення
          message.trim();                                 // -- Видаляємо зайві пробіли
          if (message == LAUNCH_CODE) {                   // -- Перевіряємо зміст повідомлення
            return true;                                  // -- Якщо отримали правильне повідомлення
          }
        }
      }
    }
  }
  return false; // -- Якщо повідомлення не отримано або воно не відповідає умовам
}

void start_listen() {
  pSave.sleepMinutes(1);                       // -- Спимо
  sim_init();                                  // --
  send_sms(OUT_NUMBER, MESSAGE);               // -- Відправляємо СМС, що прокинулись

  String waiting_units = WAITING_UNITS;        // -- Створюємо змінну на основі макроса
  unsigned long endTime = 0;

  if (waiting_units == "milsec") {             // -- Обробка для мілісекунд
    if (DEBUG == 1) Serial.println ("milsec"); // -- Виводимо milsec, для дебага
    endTime = millis() + WAITING_TIME;
  }
  else if (waiting_units == "sec") {           // -- Обробка для секунд
    if (DEBUG == 1) Serial.println ("sec");    // -- Виводимо sec, для дебага
    endTime = millis() + WAITING_TIME * 1000;
  }
  else if (waiting_units == "min") {           // -- Обробка для хвилин
    if (DEBUG == 1) Serial.println ("min");    // -- Виводимо min, для дебага
    endTime = millis() + WAITING_TIME * 60000;
  }
  else if (waiting_units == "hours") {         // -- Обробка для годин
    if (DEBUG == 1) Serial.println ("hours");  // -- Виводимо hours, для дебага
    endTime = millis() + WAITING_TIME * 3600000;
  }
  else if (waiting_units == "days") {          // -- Обробка для днів
    if (DEBUG == 1) Serial.println ("days");   // -- Виводимо days, для дебага
    endTime = millis() + WAITING_TIME * 86400000;
  }

  bool messageReceived = false;                // -- Прапорець для перевірки отримання повідомлення
  while (millis() < endTime) {                 // -- Виконуємо перевірку повідомлень
    if (message_verification() == true) {      // -- Якщо повідомлення отримано, виходимо з циклу
      if (DEBUG == 1) Serial.println("Повідомлення отримано, вихід з циклу");
      messageReceived = true;                  // -- Помічаємо, що повідомлення отримано
      break;                                   // -- Виходимо з циклу
    }
  }

  if (!messageReceived) {                      // -- Якщо повідомлення не було отримано
    if (DEBUG == 1) Serial.println("Час вийшов, перезавантаження");
    a_reboot();                                // -- Перезавантаження, якщо повідомлення не отримано
    delayMilliseconds(500);
  }
}



void setup () {
  if (DEBUG == 1) Serial.begin   (9600);   // -- Запускаємо юарт для дебага
  if (DEBUG == 1) Serial.println ("Start");// -- Виводимо Start, для дебага

  SIM800L.begin                  (9600);   // -- Юарт для SIM800L
  start_listen();                          // -- Функція перевірки запуска
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);            // -- Вимкнути реле
  if (DEBUG == 1) Serial.println ("Next"); // -- Виводимо Next, для дебага
}

void loop () {
  if (DEBUG == 1) Serial.println ("Loop");       // -- Виводимо Loop, для дебага
  if (SIM800L.available()) {                     // -- Перевіряємо, чи є дані з модуля SIM800L
    String line = SIM800L.readStringUntil('\n'); // -- Читаємо вхідну лінію від SIM800L
    line.trim();                                 // -- Видаляємо зайві пробіли
    if (line.startsWith("+CMT:")) {              // -- Перевіряємо, чи це повідомлення
      String senderNumber = extractSenderNumber(line);
      if (senderNumber == IN_NUMBER) {
        if (SIM800L.available()) {
          String message = SIM800L.readStringUntil('\n'); // -- Читаємо саме повідомлення
          message.trim();                                 // -- Видаляємо зайві пробіли
          if (message == SECRET_CODE) {                   // -- Перевіряємо зміст повідомлення
            digitalWrite(RELE_PIN, LOW);                  // -- Увімкнути реле
            SIM800L.println("AT+CMGD=1");                 // -- Видаляємо повідомлення з пам'яті SIM800L
          }
        }
      }
      delayMilliseconds(100); // -- Чекаємо 100 мс
    }
  }
}

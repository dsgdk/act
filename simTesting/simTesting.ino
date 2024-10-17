#include <SoftwareSerial.h>
SoftwareSerial SIM800L(3, 2);

void setup() {
  Serial.begin(9600);  // -- Ініціалізація серійного порту
  SIM800L.begin(9600); // -- Ініціалізація SIM800L
  checkSIM800L();      // -- Перевіряємо SIM800L
}
void loop() {}

void checkSIM800L() {
  sendCommand("AT",           "Відправка команди: AT");         // -- Перевірка зв'язку з модулем
  sendCommand("AT+CPIN=0000", "Введення PIN-коду: 0000");       // -- Введення PIN-коду
  sendCommand("AT+CPIN?",     "Перевірка статусу PIN-коду");    // -- Перевірка статусу PIN-коду
  sendCommand("AT+CREG?",     "Перевірка реєстрації в мережі"); // -- Перевірка реєстрації в мережі
  sendCommand("AT+COPS?",     "Перевірка оператора");           // -- Перевірка оператора
  sendCommand("AT+CSQ",       "Перевірка рівня сигналу");       // -- Перевірка рівня сигналу
}

void sendCommand(const String &command, const String &message) { // -- Функція для відправки команди та обробки відповіді
  Serial.println(message);
  SIM800L.println(command);
  delay(1000);
  String response = readResponse();
  if (response.indexOf("OK") != -1) {
    Serial.println("ОК");
  } else {
    Serial.println("ERROR");
  }
}

String readResponse() {
  String response;
  while (SIM800L.available()) {
    char c = SIM800L.read();
    response += c;
  }
  // -- Очищення відповіді від зайвих символів
  response.replace("\r", ""); // -- Прибираємо символи переводу рядка
  response.replace("\n", ""); // -- Прибираємо символи нової строки
  response.trim();            // -- Очищуємо пробіли по краях
  return response;
}

# act

The project utilizes the SIM800L module for receiving and processing SMS messages. The system is designed to work on an Arduino board, where the key objective is energy efficiency through extended sleep periods and automatic wake-up to perform tasks.

This project ensures reliable control via mobile communication, which can be useful for remote or autonomous systems.

## Key features

- Sending and receiving SMS: The SIM800L sends messages after waking up and checks incoming SMS for relevant commands.
- Network registration and signal strength check: The project includes checks for module registration in the mobile network and signal strength to ensure reliable connectivity.
- Flexible time configuration: The project allows you to configure the waiting time in different units (seconds, minutes, hours, days). After the waiting period, the device goes to sleep if no command message has been received.
- Energy efficiency: The Arduino sleep mechanism is used, with periodic wake-ups to minimize power consumption.

## Config example
```
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG            0                             // -- Режим дебагу (1 - увімкнено, 0 - вимкнено)
#define RELE_PIN         4                             // -- Пін куди підключене реле

#define IN_NUMBER       "+XXXXXXXXXXXX"                // -- Номер телефону з якого прийде смс
#define OUT_NUMBER      "+XXXXXXXXXXXX"                // -- Номер телефону на який відправлятимуться смс

#define MESSAGE         "I'm ON."                      // -- Текст смс повідомлення

#define LAUNCH_CODE     "1111"                         // -- Код для переходу в активний режим (цифри, або англійські літери)
#define SLEEP_CODE      "2222"                         // -- Код для переходу в сплячий режим  (цифри, або англійські літери)
#define SECRET_CODE     "3333"                         // -- Код активації                     (цифри, або англійські літери)

#define PIN_CODE_SIM    "0000"                         // -- Пін код для сім-карти

#define NUMB_OF_CONNECT 15                             // -- Кількість спроб підключення до мережі
#define DELAY_TIME       5                             // -- Час між спробами підключитися (в хвилинах)

#define WAITING_TIME    30                             // -- Час очікування повідомлення для переходу в активний режим
#define WAITING_UNITS   "sec"                          // -- Одиниці вимірювання (варіанти внизу файлу)

/*
 * milsec 
 * sec    
 * min    
 * hours  
 * days   
 */

#endif

```
## License

This code is proprietary and confidential. Unauthorized copying, distribution, or use of this code in any form is strictly prohibited without prior written consent from the owner.

For permission requests, please contact: Daniil Sahaidak daniilsgk@gmail.com

## Contact

If you have any questions or suggestions regarding this project, please reach out to me at daniilsgk@gmail.com.

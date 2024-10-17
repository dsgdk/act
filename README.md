# act

## Config example
```
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 1

const String IN_NUMBER  = "+380665933013";  // -- The phone number from which the SMS will come
const String OUT_NUMBER = "+380974505458";  // -- Phone number to which SMS will be sent

const String MESSAGE    = "I'm ON, you have 10 minutes.";

#define LAUNCH_CODE "0000"                  // -- Code for switching to active mode (numbers or English letters)
#define SLEEP_CODE  "1111"                  // -- Code for switching to sleep mode  (numbers or English letters)
#define SECRET_CODE "2222"                  // -- Activation code                   (numbers or English letters)

#define NUMB_OF_CONNECT 15                  // -- Number of network connection attempts
#define DELAY_TIME       5                  // -- Time between connection attempts (in minutes)

#define PIN_CODE_SIM 0000                   // -- Pin code for SIM card

#endif

```
## License

This code is proprietary and confidential. Unauthorized copying, distribution, or use of this code in any form is strictly prohibited without prior written consent from the owner.

For permission requests, please contact: Daniil Sahaidak daniilsgk@gmail.com

## Contact

If you have any questions or suggestions regarding this project, please reach out to me at daniilsgk@gmail.com.

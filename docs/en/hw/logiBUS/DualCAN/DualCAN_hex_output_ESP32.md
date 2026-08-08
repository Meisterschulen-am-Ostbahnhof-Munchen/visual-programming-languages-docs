# DualCAN hex output ESP32
## CAN BUS
CAN TX 21
CAN RX 35
## 🔌 OK
### Analogue inputs

| Entrance: | PIN (ESP32) |
|----------------|---------------|
| AnalogInput_I1 | 39 |
| AnalogInput_I2 | 36 |
| AnalogInput_I3 | 34 |
| AnalogInput_I4 | 33 |

```c
ADC1_CHANNEL_0 = 0, /*!< ADC1 channel 0 is GPIO36 */
ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO39 */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO33 */
ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO34 */


Voltage divider is located in the controller:

47/13 --> all other inputs as well as the CAN2 DI inputs

10/10 --> Inputs I1/I2 - Ideal for 5V signals

### Digital Inputs

| Input: | PIN (ESP32) |
|----------|---------------|
| Input_I1 | 39 |
| Input_I2 | 36 |
| Input_I3 | 34 |
| Input_I4 | 33 |

### Digital Inputs (CAN2)

2CAN-I1
2CAN-I2

These inputs have a voltage divider in the controller: 47/13 --> and a Schmitt trigger.

### Digital Outputs

| Output: | PIN (ESP32) |
|------------|---------------|
| Output_Q01 | 22 |
| Output_Q02 | 4 |
| Output_Q03 | 2 |
| Output_Q04 | 15 |
| Output_Q05 | 14 |
| Output_Q06 | 32 |
| Output_Q07 | 27 |

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Loaded & Unloaded Voltage Divider on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/spannungsteiler/)
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)


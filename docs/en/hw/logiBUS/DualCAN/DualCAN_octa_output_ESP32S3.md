# DualCAN octa output ESP32S3
## CAN BUS
CAN TX 4
CAN RX 5
## 🔌 OK
### Analogue inputs

| Entrance: | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I1 |  5 |
| AnalogInput_I2 |  4 |
| AnalogInput_I3 |  6 |

ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO4  */
ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO5  */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */

Voltage divider is located in the controller:

47/13 --> all other inputs as well as the CAN2 DI inputs

10/10 --> Inputs I1/I2 - Ideal for 5V signals

### Digital Inputs

| Input: | PIN (ESP32S3) |
|----------|---------------|
| Input_I1 | 5 |
| Input_I2 | 4 |
| Input_I3 | 6 |
| Input_I4 | 16 |

### Digital Inputs (CAN2)

2CAN-I1
2CAN-I2

These inputs have a voltage divider in the controller: 47/13 --> and a Schmitt trigger.

### Digital Outputs

| Output: | PIN (ESP32S3) |
|------------|---------------|
| Output_Q01 |  2 |
| Output_Q02 | 10 |
| Output_Q03 | 48 |
| Output_Q04 | 47 |
| Output_Q05 | 20 |
| Output_Q06 | 19 |
| Output_Q07 | 15 |
| Output_Q08 |  8 |

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Loaded & Unloaded Voltage Divider on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/spannungsteiler/)
* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

]
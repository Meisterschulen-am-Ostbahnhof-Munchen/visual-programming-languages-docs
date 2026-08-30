# DIN Rail Moped XL

Link to the devkit: <https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/index.html>

## 🔌 I/O

### Analog Inputs

| Input: | PIN (ESP32S3) |
| ---------------- | --------------- |
| AnalogInput_I3 | 9 |
| AnalogInput_I4 | 3 |
| AnalogInput_I7 | 7 |
| AnalogInput_I8 | 6 |

```c
ADC1_CHANNEL_2,     /*!< ADC1 channel 2 is GPIO3  */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */
ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO7  */
ADC1_CHANNEL_8,     /*!< ADC1 channel 8 is GPIO9  */
```

### Digital Inputs

| Input: | PIN (ESP32S3) |
| ---------- | --------------- |
| Input_I1 | 13 |
| Input_I2 | 12 |
| Input_I3 | 9 |
| Input_I4 | 3 |
| Input_I5 | 18 |
| Input_I6 | 17 |
| Input_I7 | 7 |
| Input_I8 | 6 |

### Digital Outputs

| Output: | PIN (ESP32S3) |
| ----------- | --------------- |
| Output_Q1 | 21 |
| Output_Q2 | 47 |
| Output_Q3 | 39 |
| Output_Q4 | 40 |
| Output_Q5 | 41 |
| Output_Q6 | 42 |
| Output_Q7 | 1 |
| Output_Q8 | 2 |

### LED Strip

## More Information

<https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/master/Hutschienenmoped-XL>

contains the DIN Rail Moped-XL, an Open Source ISOBUS ECU.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Loaded & Unloaded Voltage Divider on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/spannungsteiler/)
- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

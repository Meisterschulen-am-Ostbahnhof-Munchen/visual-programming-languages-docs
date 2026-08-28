# DualIO ESP32S3

## CAN-BUS

CAN-TX 42
CAN-RX 7

Kein zweiter CAN-Bus (CAN2) auf diesem Board.

## 🔌 IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I1 |  5            |
| AnalogInput_I2 |  6            |

```c
ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO5  */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */
```

### Digitale Eingänge

| Eingang: | PIN (ESP32S3) |
|----------|---------------|
| Input_I1 |  5            |
| Input_I2 |  6            |

Beide Eingänge sind Combo-Pins: derselbe physische Pin dient wahlweise als
digitaler (`Input_Ix`) oder analoger (`AnalogInput_Ix`) Eingang, aber nicht als
beides gleichzeitig.

### Digitale Ausgänge

| Ausgang:  | PIN (ESP32S3) |
|-----------|---------------|
| Output_Q1 | 21            |
| Output_Q2 | 46            |

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

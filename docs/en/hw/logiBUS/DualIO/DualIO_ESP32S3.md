# DualIO ESP32S3

## CAN BUS

CAN TX 42
CAN RX 7

No second CAN bus (CAN2) on this board.

## 🔌 I/O

### Analog Inputs

| Input:         | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I1 |  5            |
| AnalogInput_I2 |  6            |

```c
ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO5  */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */
```

### Digital Inputs

| Input:   | PIN (ESP32S3) |
|----------|---------------|
| Input_I1 |  5            |
| Input_I2 |  6            |

Both inputs are combo pins: the same physical pin acts either as a digital
(`Input_Ix`) or an analog (`AnalogInput_Ix`) input, but not both at the same time.

### Digital Outputs

| Output:   | PIN (ESP32S3) |
|-----------|---------------|
| Output_Q1 | 21            |
| Output_Q2 | 46            |

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

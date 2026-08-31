# DIN Rail Moped

## 🎧 Podcast

- [DIN Rail Moped XL: ISOBUS ECU Development ](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Hutschienenmoped-XL-ISOBUS-ECU-Entwicklung-e368hdg)

## 🔌 I/O

### Analog Inputs

| Input: | PIN (ESP32) | Wire | Knob |
|----------------|---------------|-------|-------|
| AnalogInput_I2 | 32 | white | Potentiometer |

`ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO32 */`

<https://docs.m5stack.com/en/unit/angle>

The voltage divider is NOT in the controller but in the Angle! Caution: If you connect the input to other analog sources, an external voltage divider must be used.

### Digital Inputs

| Input: | PIN (ESP32) | Wire | Knob |
| ---------- | --------------- | ------- | ------- |
| Input_I1 | 26 | yellow | red |
| Input_I2 | 32 | white | blue |
| Input_I3 | 39 | - | gray |

<https://docs.m5stack.com/en/unit/dual_button>

(Gauer button is directly on the M5)

### Digital Outputs

| Output: | PIN (ESP32) |
| ----------- | --------------- |
| Output_Q1 | 19 |
| Output_Q2 | 23 |
| Output_Q3 | 33 |
| Output_Q4 | 25 |

## Further Information

<https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/master/Hutschienenmoped>

contains the DIN Rail Mount, an Open Source ISOBUS ECU.

See more here:

<https://install-isobus-environment-docs.readthedocs.io/de/latest/HutschienenMoped.html>

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Loaded & Unloaded Voltage Divider on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/spannungsteiler/)
- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

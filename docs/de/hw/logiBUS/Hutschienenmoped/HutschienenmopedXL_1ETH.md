# Hutschienenmoped XL 1ETH

Basis: Hutschienenmoped XL, zusätzlich mit einem W5500-Ethernet-Chip (SPI) bestückt.

Link zum Devkit: <https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/index.html>

## 🔌 IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I3 |  9            |
| AnalogInput_I4 |  3            |
| AnalogInput_I7 |  7            |
| AnalogInput_I8 |  6            |

```c
    ADC1_CHANNEL_2,     /*!< ADC1 channel 2 is GPIO3  */
    ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */
    ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO7  */
    ADC1_CHANNEL_8,     /*!< ADC1 channel 8 is GPIO9  */
```

Spannungsteiler ist im Controller:
47/13

### Digitale Eingänge

| Eingang: | PIN (ESP32S3) |
|----------|---------------|
| Input_I1 | 13            |
| Input_I2 | 12            |
| Input_I3 |  9            |
| Input_I4 |  3            |
| Input_I5 | 18            |
| Input_I6 | 17            |
| Input_I7 |  7            |
| Input_I8 |  6            |

### Digitale Ausgänge

| Ausgang:  | PIN (ESP32S3) |
|-----------|---------------|
| Output_Q1 | 21            |
| Output_Q2 | 47            |
| Output_Q3 | 39            |
| Output_Q4 | 40            |
| Output_Q5 | 41            |
| Output_Q6 | 42            |
| Output_Q7 |  1            |
| Output_Q8 |  2            |

### LED Strip

| Signal:    | PIN (ESP32S3) |
|------------|---------------|
| LEDC_IO_0  | 12            |
| LEDC_IO_1  | 11            |
| RGB        | 38            |

`GPIO_STR_NUM: 1` (ESP32-S3-DevKitC-1 mit ESP32-S3-WROOM-2-N32R8V)

⚠️ Pin-Sharing: `LEDC_IO_0` (GPIO12) liegt auf demselben Pin wie `Input_I2`. Diese
Funktionen können nur abwechselnd genutzt werden, nicht gleichzeitig.

## 🌐 Ethernet

W5500 (SPI) — externer Ethernet-Chip, anders als beim internen EMAC des ESP32-P4
(z. B. APIXON Node-ISO 20).

| Signal:    | PIN (ESP32S3) |
|------------|---------------|
| SCLK       | 10            |
| MOSI       | 11            |
| MISO       | 14            |
| CS         | 46            |
| INT        | 48            |
| PHY Reset  | 16            |

⚠️ **Pin-Konflikt:** `LEDC_IO_1` (GPIO11, siehe LED-Strip-Tabelle oben) liegt auf
demselben Pin wie das SPI-MOSI-Signal des W5500. Wird `LEDC_IO_1` angesteuert,
während Ethernet aktiv ist, stören sich beide Funktionen gegenseitig. Auf dieser
Variante darf `LEDC_IO_1` daher **nicht** genutzt werden.

## Weitere Infos

<https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/master/Hutschienenmoped-XL>

contains the Hutschienenmoped-XL, a Open Source ISOBUS ECU.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Belasteter & Unbelasteter Spannungsteiler auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/spannungsteiler/)
* [🌐 ESP32 & ESP32-S3 DevKit auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

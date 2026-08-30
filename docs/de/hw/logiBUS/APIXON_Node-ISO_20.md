# APIXON Node-ISO 20

Basis: ESP32-P4 (kein WLAN an Bord, siehe unten).

## CAN-BUS

CAN-TX 47
CAN-RX 48

Kein zweiter CAN-Bus (CAN2) auf diesem Board.

## 🔌 IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32P4) |
|----------------|---------------|
| AnalogInput_I1 | 18            |
| AnalogInput_I2 | 17            |
| AnalogInput_I3 | 54            |
| AnalogInput_I4 | 19            |
| AnalogInput_I5 | 16            |
| AnalogInput_I6 | 23            |
| AnalogInput_I7 | 22            |
| AnalogInput_I8 | 21            |

```c
ADC1_CHANNEL_0,     /*!< ADC1 channel 0 is GPIO16 */
ADC1_CHANNEL_1,     /*!< ADC1 channel 1 is GPIO17 */
ADC1_CHANNEL_2,     /*!< ADC1 channel 2 is GPIO18 */
ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO19 */
ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO21 */
ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO22 */
ADC1_CHANNEL_7,     /*!< ADC1 channel 7 is GPIO23 */
ADC2_CHANNEL_5,     /*!< ADC2 channel 5 is GPIO54 */
```

Alle acht analogen Eingänge sind Combo-Pins, die sich den physischen Pin mit dem
gleichnamigen digitalen Eingang teilen (I1↔AnalogInput_I1 usw.) — pro Pin kann nur
eine der beiden Funktionen gleichzeitig genutzt werden.

`AnalogInput_I3` (GPIO54) liegt als einziger auf ADC2 statt ADC1. Das ist hier
unproblematisch, da der ESP32-P4 kein eigenes WLAN-Radio besitzt und der
ADC2/WLAN-Konflikt (der bei ESP32/ESP32-S2/ESP32-S3 mit WLAN besteht) auf diesem Chip
nicht existiert.

### Digitale Eingänge

| Eingang: | PIN (ESP32P4) |
|----------|---------------|
| Input_I1 | 18            |
| Input_I2 | 17            |
| Input_I3 | 54            |
| Input_I4 | 19            |
| Input_I5 | 16            |
| Input_I6 | 23            |
| Input_I7 | 22            |
| Input_I8 | 21            |

### Digitale Ausgänge

| Ausgang:   | PIN (ESP32P4) |
|------------|---------------|
| Output_Q01 |  3            |
| Output_Q02 |  2            |
| Output_Q03 |  8            |
| Output_Q04 |  7            |
| Output_Q05 | 24            |
| Output_Q06 | 25            |
| Output_Q07 |  5            |
| Output_Q08 |  4            |
| Output_Q09 | 46            |
| Output_Q10 | 15            |
| Output_Q11 | 14            |
| Output_Q12 |  6            |

## 🌐 Ethernet

Internes EMAC des ESP32-P4 (kein externer SPI-Ethernet-Chip wie W5500, anders als bei
den ESP32-S3-Boards mit "_1ETH"/"_2ETH").

| Signal:        | PIN (ESP32P4) |
|----------------|---------------|
| MDC            | 31            |
| MDIO           | 52            |
| PHY Reset      | 51            |

PHY-Chip: IP101 (100 MBit, Standard-EMAC-Interface-Konfiguration des ESP-IDF
Ethernet-Treibers, PHY-Adresse automatisch erkannt).

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

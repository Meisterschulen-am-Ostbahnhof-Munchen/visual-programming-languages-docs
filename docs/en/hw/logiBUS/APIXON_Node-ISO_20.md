# APIXON Node-ISO 20

Base chip: ESP32-P4 (no Wi-Fi on board, see below).

## CAN BUS

CAN TX 47
CAN RX 48

No second CAN bus (CAN2) on this board.

## 🔌 I/O

### Analog Inputs

| Input:         | PIN (ESP32P4) |
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

All eight analog inputs are combo pins that share the physical pin with the
digital input of the same number (I1↔AnalogInput_I1 etc.) — only one of the two
functions can be used at a time per pin.

**Raw full-scale value:** `IN` (`logiBUS_AI_ID`/`logiBUS_AI_IDA`) delivers 0-4095
(12 bit) — fixed on the ESP32-P4 in the continuous/DMA ADC mode used here, no
other bit width can be selected (`SOC_ADC_DIGI_MIN_BITWIDTH` =
`SOC_ADC_DIGI_MAX_BITWIDTH` = 12 per the ESP-IDF `soc_caps.h`). Raw-value-to-volt
conversion: `Vout = Dout × Vmax / 4096` (`Vmax` depends on the ADC attenuation
`ADC_ATTEN_DB_12`).

`AnalogInput_I3` (GPIO54) is the only one on ADC2 instead of ADC1. That's fine here
because the ESP32-P4 has no on-chip Wi-Fi radio, so the ADC2/Wi-Fi conflict that
exists on Wi-Fi-capable chips (ESP32/ESP32-S2/ESP32-S3) doesn't apply.

### Digital Inputs

| Input:   | PIN (ESP32P4) |
|----------|---------------|
| Input_I1 | 18            |
| Input_I2 | 17            |
| Input_I3 | 54            |
| Input_I4 | 19            |
| Input_I5 | 16            |
| Input_I6 | 23            |
| Input_I7 | 22            |
| Input_I8 | 21            |

### Digital Outputs

| Output:    | PIN (ESP32P4) |
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

Uses the ESP32-P4's internal EMAC (no external SPI Ethernet chip like the W5500
used on the ESP32-S3 "_1ETH"/"_2ETH" boards).

| Signal:   | PIN (ESP32P4) |
|-----------|---------------|
| MDC       | 31            |
| MDIO      | 52            |
| PHY Reset | 51            |

PHY chip: IP101 (100 Mbit, default EMAC interface configuration of the ESP-IDF
Ethernet driver, PHY address auto-detected).

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

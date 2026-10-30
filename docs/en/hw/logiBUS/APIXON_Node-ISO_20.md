# APIXON Node-ISO 20

Base chip: ESP32-P4 (no Wi-Fi on board, see below).

## CAN BUS

CAN TX 47
CAN RX 48

No second CAN bus (CAN2) on this board.

## 🔌 I/O

### Input Circuit (I1-I8)

All eight inputs have the same input stage (voltage divider with low-pass filter). Only the last capacitor distinguishes the "fast" inputs I1/I2 from the "slow" inputs I3-I8:

```text
I n ──┬────────┬──── 47k ───┬──── 4.7k ───┬──── to the ESP32-P4
      │        │            │             │
    33 nF     47k          22k        100 pF  (I1, I2)
      │        │            │         100 nF  (I3 … I8)
     GND      GND          GND           GND
```

| Inputs | Capacitor after the divider | Time constant | Cut-off frequency (−3 dB) |
|---|---|---|---|
| `I1`, `I2` ("fast") | 100 pF | about 2 µs | about 81 kHz |
| `I3`-`I8` ("slow") | 100 nF | about 2 ms | about 81 Hz |

- **Formula:** f_c = 1 / (2π · R · C) with R = (47 kΩ ‖ 22 kΩ) + 4.7 kΩ ≈ 19.7 kΩ (divider with an ideal source plus the series resistor).
- **Divider ratio:** 22 / (47 + 22) ≈ 0.32 by calculation. The schematic states "2.6 V at 12 V" instead; this difference is not resolved.
- **Assembly:** The bill of materials (JLCPCB export for version v107, 2026-10-30) matches the schematic for all eight input stages: same values, nothing missing.

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

**Limit frequency of the analog input (measurement 2026-10-30):** A square wave is captured exactly up to about 90 Hz; from 100 Hz edges are lost, above that aliasing occurs. The driver delivers at most about 312 averaged values per second (one value every 3.2 ms). For frequency measurements above about 90 Hz, use a pulse input. The measurement series is in the exercise `Uebung_250_AX` (exercises documentation).

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

### Pulse Inputs (Frequency Measurement)

| Input:          | PIN (ESP32P4) |
|-----------------|---------------|
| PulseInput_I1   | 18            |
| PulseInput_I2   | 17            |
| PulseInput_I3   | 54            |
| PulseInput_I4   | 19            |
| PulseInput_I5   | 16            |
| PulseInput_I6   | 23            |
| PulseInput_I7   | 22            |
| PulseInput_I8   | 21            |

The pulse inputs are also combo pins that share the physical pin with the digital
input of the same number (uses the same `EPinDigitalIn` pin table internally, via the
ESP32 PCNT hardware, see `IOHandleESP32PulseIN.cpp`).

**Pulse input measurement (2026-08-30):** square wave 12 V, FNIRSI SG-003A signal generator in Pulse mode (Level, 12.0 V peak), frequency read at the generator and in the 4diac program.

| Inputs | Result |
|---|---|
| `PulseInput_I1`, `_I2` ("fast") | good up to 20 kHz, no longer good at 23 kHz |
| `PulseInput_I3`-`_I8` ("slow") | up to about 2.3 kHz |

Above these frequencies the input loses edges and counts inaccurately; it does not stop and is not damaged. The generator's output impedance and duty cycle are not documented.

**Why the "slow" inputs count up to about 2.3 kHz despite a cut-off frequency of about 81 Hz:** The 81 Hz is the −3 dB frequency of the filter, not the counting limit. The counter does not need half the amplitude, only a signal that still crosses the switching threshold. Behind the divider, the 12 V square wave has about 3.8 V peak. The 100 nF filter leaves a residual ripple of it (calculation for 50 % duty cycle):

| Frequency | Residual ripple `I3`-`I8` (100 nF) | `I1`, `I2` (100 pF) |
|---|---|---|
| 81 Hz | about 3.5 V | about 3.8 V |
| 500 Hz | about 0.95 V | about 3.8 V |
| 2.3 kHz | about 0.21 V | about 3.8 V |
| 5 kHz | about 0.10 V | about 3.8 V |
| 20 kHz | about 0.02 V | about 3.8 V |

At 2.3 kHz about 0.2 V of ripple remains around the mean value; this fits an input hysteresis of about 0.2 V. This is a conclusion from the calculation; the input's threshold and hysteresis are not known. With a different duty cycle the mean value shifts and the limit would be lower. The filter sets no limit for the fast inputs at 20 kHz (full amplitude); there, the 33 nF at the input together with the generator's output impedance, or the firmware, probably limit it. This is not verified either.

**Open observation from live testing (2026-08-30):** Only **4 of 8** pulse inputs work reliably at the same time (similar to the PWM observation, where only 8 of 12 outputs worked simultaneously). Likely a pin/peripheral sharing limit on the ESP32 side, but the exact cause is still open.

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

### Comparison with Common Small Controllers

The competitor values come from the manufacturer manuals ([LOGO! 8 system manual](https://cache.industry.siemens.com/dl/files/041/109741041/att_924627/v1/logo_system_manual_de-DE_de-DE.pdf), [LOGO! product information 05/2024](https://cache.industry.siemens.com/dl/files/848/109971848/att_1286527/v1/Product_Information_for_LOGO_System_Manual_de-DE_de-DE.pdf), [easyE4 manual MN050009](https://es-assets.eaton.com/DOCUMENTATION/AWB_MANUALS/MN050009_EN.pdf)), the APIXON Node-ISO 20 values from the measurements above.

**Analog input (0-10 V)**

| | APIXON Node-ISO 20 | Siemens LOGO! 8 | Eaton easyE4 |
|---|---|---|---|
| Resolution | 12 bit | Base module: not specified (error limit ±1.5 %); AM2: 10 bit, normalized to 0-1000 | 12 bit (0-4095) |
| Update | up to about 312 values/s (every 3.2 ms) | Base module 300 ms, AM2 50 ms | adjustable in easySoft; no fixed figure found |
| Filter | Averaging in the driver (64 samples) | Analog filter and average function blocks | Noise suppression and averaging adjustable, PT1 filter block |
| Square wave measured cleanly up to | about 90 Hz (measurement 2026-10-30) | not specified | not specified |

**Pulse input**

| | Result |
|---|---|
| APIXON Node-ISO 20, `I1`/`I2` ("fast") | good up to 20 kHz, no longer good at 23 kHz (square wave 12 V, 2026-08-30) |
| APIXON Node-ISO 20, `I3`-`I8` ("slow") | up to about 2.3 kHz, deliberately filtered for slower, analog-type signals |
| Siemens LOGO! 8 | max. 5 kHz on `I3`-`I6` (12/24RCE/RCEo and 24CE/24CEo only, directly at the counter) |
| Eaton easyE4 | counter and frequency meter max. 5 kHz |

- The fast pulse input at 20 kHz is about four times the 5 kHz of both small controllers. The "slow" inputs are not meant for fast counting and are not compared with the competitors' fast counter inputs.
- The competitors state the maximum of the counter function. For the APIXON it is the frequency up to which the input still counts cleanly; above it the input loses edges.
- For the analog input, neither manufacturer specifies a usable signal frequency. On the LOGO! 8 the analog value cycle time (300 ms or 50 ms) limits sampling much more strongly.
- The easyE4 data sheets state conversion "each CPU cycle", the manual only an adjustable update rate. One device data sheet gives 10 kHz counting frequency, the manual 5 kHz; this is not resolved.

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

- [🌐 ESP32 & ESP32-S3 DevKit on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

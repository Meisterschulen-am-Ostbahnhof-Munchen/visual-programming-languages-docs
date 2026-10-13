# logiBUS Trainer20

Base: **ESP32-S31-Function-CoreBoard-1** (ESP32-S31-WROOM-3 module, 16 MB flash, 16 MB PSRAM).

!!! warning "Status"
    The ESP32-S31 is still a *preview* target in ESP-IDF 6.1. The Trainer20 target exists and is
    integrated in the build script, but has not been tested on hardware yet.

The name stands for the 20 connections: 8 inputs + 8 outputs + 3 encoder connections
(button, A, B) + 1 DS1820 connection (1-Wire).

## ⚠️ Changes on the CoreBoard

### Remove R83 (CAN RX on GPIO4)

On the CoreBoard, GPIO4 is connected through resistor **R83 (0 Ω)** to the interrupt output
(`ETH_INTN`) of the Ethernet PHY. The Trainer20 uses GPIO4 as **CAN RX**. To keep the PHY from
influencing the CAN line, **remove R83**. This does not affect Ethernet: the ESP-IDF Ethernet driver
does not use the PHY interrupt (link status is polled).

### SD card and Trainer20 functions are mutually exclusive

All six SD card (SDIO) lines of the CoreBoard are used by the Trainer20:

| SD pin | GPIO | Trainer20 function |
|--------|------|--------------------|
| D0     | 20   | Output Q07         |
| D1     | 21   | Output Q08         |
| D2     | 22   | Encoder channel A  |
| D3     | 23   | Encoder channel B  |
| CLK    | 24   | Encoder button     |
| CMD    | 25   | CAN TX             |

Anyone who needs the SD card can cut off the header pins **D0–D3, CLK and CMD** on the
ESP32-S31-Function-CoreBoard-1 and use the SD card. Q07, Q08, the encoder and the CAN bus
will then **no longer work**.

## CAN BUS

| Signal  | PIN (ESP32S31)  |
|---------|-----------------|
| CAN TX  | 25 (SDIO_CMD)   |
| CAN RX  | 4               |

No second CAN bus (CAN2) on this board. Remove R83, see above.

## 🔌 I/O

### Analog inputs

| Input:         | PIN (ESP32S31) | ADC channel |
|----------------|----------------|-------------|
| AnalogInput_I1 | 49             | ADC1_CH7    |
| AnalogInput_I2 | 48             | ADC1_CH6    |
| AnalogInput_I3 | 47             | ADC1_CH5    |
| AnalogInput_I4 | 46             | ADC1_CH4    |
| AnalogInput_I5 | 45             | ADC1_CH3    |
| AnalogInput_I6 | 44             | ADC1_CH2    |
| AnalogInput_I7 | 43             | ADC1_CH1    |
| AnalogInput_I8 | –              | (no analog input, see note below) |

AnalogInput_I1–I7 are combo pins that share the physical pin with the digital input of the
same number (I1↔AnalogInput_I1 etc.) — only one of the two functions can be used per pin at a time.
They are all on ADC1; ADC2 is not routed to the CoreBoard's pin header.

**ESP32-S31 ADC (still to be verified):** The S31 has only *one* attenuation setting
(`SOC_ADC_ATTEN_NUM` = 1, `ADC_ATTEN_DB_0`) and reports the result as the weighted sum of
17 redundant comparator bits (non-uniform weights, according to ESP-IDF), so the maximum code is
**4393** — it is not a 17-bit code. The raw full scale and
the measuring range in volts are still to be checked on hardware; the values documented for the
`logiBUS_AI_*` blocks (0–4095) apply to ESP32-P4/ESP32-S3.

### Digital inputs

| Input:   | PIN (ESP32S31) |
|----------|----------------|
| Input_I1 | 49             |
| Input_I2 | 48             |
| Input_I3 | 47             |
| Input_I4 | 46             |
| Input_I5 | 45             |
| Input_I6 | 44             |
| Input_I7 | 43             |
| Input_I8 | 40             |

### Encoder

| Signal           | Pin on CoreBoard | PIN (ESP32S31) |
|------------------|------------------|----------------|
| Encoder button   | CLK              | 24             |
| Encoder channel A| D2               | 22             |
| Encoder channel B| D3               | 23             |

The pins are reserved for the encoder (assignment see above, the SD card cannot be used at the same time).
A dedicated encoder block is not yet part of the firmware.

### 1-Wire (DS1820)

| Signal   | PIN (ESP32S31) |
|----------|----------------|
| 1-Wire   | 3              |

Connection for a DS1820 temperature sensor (1-Wire bus). A block for it is not yet part of the firmware.

### Digital outputs

All eight outputs are PWM and servo capable.

| Output:    | PIN (ESP32S31) |
|------------|----------------|
| Output_Q01 | 42             |
| Output_Q02 | 39             |
| Output_Q03 | 38             |
| Output_Q04 | 37             |
| Output_Q05 | 36             |
| Output_Q06 | 35             |
| Output_Q07 | 20 (SDIO_D0)   |
| Output_Q08 | 21 (SDIO_D1)   |

Q07 and Q08 share their pins with the SD card slot, see above.

!!! note "Q01 and I8 are crossed on the board"
    On the Trainer20 the terminals of Q01 and I8 are wired crossed: Q01 is on GPIO42, I8 on GPIO40.
    GPIO40 is not an ADC pin, so there is no analog input for I8 (AnalogInput_I8 is not assigned).
    I8 is the joystick button and is only used digitally.

### RGB LED

Addressable RGB LED of the CoreBoard on **GPIO60**.

## 🌐 Ethernet

Internal EMAC of the ESP32-S31 with the Gigabit PHY **YT8531** (RGMII, RJ45) on the CoreBoard.
Driver: `espressif/yt8531`, pulled in through `ethernet_init`.

| Signal           | PIN (ESP32S31) |
|------------------|----------------|
| MDC              | 5              |
| MDIO             | 6              |
| PHY reset        | 7              |
| TXD0–TXD3        | 8, 9, 10, 11   |
| TX_CTL           | 12             |
| TX_CLK           | 13             |
| RX_CLK           | 14             |
| RX_CTL           | 15             |
| RXD3, RXD2, RXD1, RXD0 | 16, 17, 18, 19 |

The PHY address is detected automatically. Wi-Fi is disabled in the first step.

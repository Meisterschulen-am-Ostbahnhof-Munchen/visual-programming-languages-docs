# DualCAN hex-output ESP32

```{index} single: DualCAN hex-output ESP32
```

## CAN-BUS

CAN-TX 21
CAN-RX 35

## IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32)   |
|----------------|---------------|
| AnalogInput_I1 | 39            |
| AnalogInput_I2 | 36            |
| AnalogInput_I3 | 34            |
| AnalogInput_I4 | 33            |

```

    ADC1_CHANNEL_0 = 0, /*!< ADC1 channel 0 is GPIO36 */
    ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO39 */
    ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO33 */
    ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO34 */

```

Spannungsteiler ist im Controller:
47/13 --> alle anderen Eingänge sowie die CAN2 DI Eingänge
10/10 --> Eingänge I1/I2 - Ideal für 5V Singale

### Digitale Eingänge

| Eingang: | PIN (ESP32)   |
|----------|---------------|
| Input_I1 | 39            |
| Input_I2 | 36            |
| Input_I3 | 34            |
| Input_I4 | 33            |

### Digitale Eingänge (CAN2)

2CAN-I1
2CAN-I2

Diese Eingänge haben einen Spannungsteiler im Controller: 47/13 --> und einen Schmitt Trigger.

### Digitale Ausgänge

| Ausgang:   | PIN (ESP32)   |
|------------|---------------|
| Output_Q01 | 22            |
| Output_Q02 |  4            |
| Output_Q03 |  2            |
| Output_Q04 | 15            |
| Output_Q05 | 14            |
| Output_Q06 | 32            |
| Output_Q07 | 27            |
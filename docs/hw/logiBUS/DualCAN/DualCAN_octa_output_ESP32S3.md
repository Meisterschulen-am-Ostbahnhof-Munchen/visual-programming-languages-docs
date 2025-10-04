# DualCAN octa-output ESP32S3



## CAN-BUS

CAN-TX 4
CAN-RX 5



## IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I1 |  5            |
| AnalogInput_I2 |  4            |
| AnalogInput_I3 |  6            |

```

    ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO4  */
    ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO5  */
    ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO6  */

```


Spannungsteiler ist im Controller:
47/13 --> alle anderen Eingänge sowie die CAN2 DI Eingänge
10/10 --> Eingänge I1/I2 - Ideal für 5V Singale




### Digitale Eingänge

| Eingang: | PIN (ESP32S3) |
|----------|---------------|
| Input_I1 |  5            |
| Input_I2 |  4            |
| Input_I3 |  6            |
| Input_I4 | 16            |


### Digitale Eingänge (CAN2)

2CAN-I1
2CAN-I2

Diese Eingänge haben einen Spannungsteiler im Controller: 47/13 --> und einen Schmitt Trigger. 


### Digitale Ausgänge

| Ausgang:   | PIN (ESP32S3) |
|------------|---------------|
| Output_Q01 |  2            |
| Output_Q02 | 10            |
| Output_Q03 | 48            |
| Output_Q04 | 47            |
| Output_Q05 | 20            |
| Output_Q06 | 19            |
| Output_Q07 | 15            |
| Output_Q08 |  8            |



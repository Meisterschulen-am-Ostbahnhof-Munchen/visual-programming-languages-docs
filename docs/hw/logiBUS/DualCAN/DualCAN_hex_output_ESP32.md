# DualCAN hex-output ESP32

```{index} single: DualCAN hex-output ESP32
```



## 🎧 Podcast

* [ISOBUS Output Meter: Dynamische Anzeigen meistern – vom Zeiger bis zur Visualisierung auf dem VT](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Output-Meter-Dynamische-Anzeigen-meistern--vom-Zeiger-bis-zur-Visualisierung-auf-dem-VT-e36t2tp)
* [ISOBUS-Balkendiagramm: Das Output Linear Bar Graph Objekt der ISO 11783-6 entschlüsselt](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Balkendiagramm-Das-Output-Linear-Bar-Graph-Objekt-der-ISO-11783-6-entschlsselt-e36l0v2)
* [ISOBUS-Terminals: Zahlen verstehen – NumberVariable, InputNumber & OutputNumber erklärt](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Terminals-Zahlen-verstehen--NumberVariable--InputNumber--OutputNumber-erklrt-e36aatd)
* [ESP32 als Industrie-SPS: Revolution mit Eclipse 4diac und logiBUS®](https://podcasters.spotify.com/pod/show/logibus/episodes/ESP32-als-Industrie-SPS-Revolution-mit-Eclipse-4diac-und-logiBUS-e375dp6)
* [ESP32 as PLC: Democratizing Industrial Automation with Eclipse 4diac](https://podcasters.spotify.com/pod/show/logibus/episodes/ESP32-as-PLC-Democratizing-Industrial-Automation-with-Eclipse-4diac-e375e13)

## 📺 Video

* [Das ESP32-S3-DevKitC-1](https://www.youtube.com/watch?v=fyQt3THIQEQ)
* [ESP32 in der Landwirtschaft: Revolution durch Software!](https://www.youtube.com/watch?v=9N-hUHq4b1M)
* [ESP32-S3-DevKitC-1 Doku-Analyse: Das Speicher-Monster (32MB Flash/16MB PSRAM) und die Macht der D...](https://www.youtube.com/watch?v=oQPI4NFTt-k)
* [ESP32-S3: Universum im Chip](https://www.youtube.com/watch?v=xXfb8vsVZfs)
* [logiBUS® ESP32 installer   Google Chrome 2022 10 18 17 38 33](https://www.youtube.com/watch?v=pQ53R2zChlc)

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

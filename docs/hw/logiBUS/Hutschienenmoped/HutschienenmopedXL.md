# Hutschienenmoped XL

```{index} single: Hutschienenmoped XL
```


Link zum Devkit: <https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/index.html>




## 🎧 Podcast

* [Hutschienenmoped XL: ISOBUS ECU Entwicklung](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Hutschienenmoped-XL-ISOBUS-ECU-Entwicklung-e368hdg)

## 📺 Video

* [2025 11 15 12 35 11 Montage Hutschienenmoped logiBUS® -- Teil 3 -- Gehäuse](https://www.youtube.com/watch?v=MPm4vLmD5RE)
* [2025 11 15 12 52 26 Montage Hutschienenmoped logiBUS® -- Teil 4 -- Aufbauten](https://www.youtube.com/watch?v=WeowCxZW70Y)
* [2025-11-13 17-50-42 Montage Hutschienenmoped logiBUS® -- Teil 1 -- Einführung und Löten](https://www.youtube.com/watch?v=HWBMBVLMPiw)
* [2025-11-15 12-19-33 Montage Hutschienenmoped logiBUS® -- Teil 2 -- Einführung und Löten](https://www.youtube.com/watch?v=nohE36SZY9M)
* [2025-12-14 20-03-27 Aufspielen Training 1 Übung 1 auf das Hutschienenmoped.](https://www.youtube.com/watch?v=6iog7-DZvW0)

## IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32S3) |
|----------------|---------------|
| AnalogInput_I3 |  9            |
| AnalogInput_I4 |  3            |
| AnalogInput_I7 |  7            |
| AnalogInput_I8 |  6            |

```
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






















## Weitere Infos

<https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/master/Hutschienenmoped-XL>

contains the Hutschienenmoped-XL, a Open Source ISOBUS ECU.

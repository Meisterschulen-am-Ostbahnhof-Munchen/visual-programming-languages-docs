# Hutschienenmoped

```{index} single: Hutschienenmoped
```


Link zum Devkit: <https://docs.m5stack.com/en/atom/atom_display>
Link zum Devkit: <https://docs.m5stack.com/en/core/ATOM%20Lite>

ACHTUNG: logiBUS® ist nicht auf dem Atom-Lite SKU:C008 lauffähig, nur auf dem Atom-PSRAM.

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

| Eingang:       | PIN (ESP32)   | Draht | Knopf |
|----------------|---------------|-------|-------|
| AnalogInput_I2 | 32            | weiß  | Poti  |

`ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO32 */`

<https://docs.m5stack.com/en/unit/angle>

Spannungsteiler ist NICHT im Controller sondern im Angle!!! Achtung wenn man den Eingang an andere Analogquellen anschließt muss ein externer Spannungsteiler vorgeschaltet werden. 



### Digitale Eingänge

| Eingang: | PIN (ESP32)   | Draht | Knopf |
|----------|---------------|-------|-------|
| Input_I1 | 26            | gelb  | Rot   |
| Input_I2 | 32            | weiß  | Blau  |
| Input_I3 | 39            | -     | Grau  |

<https://docs.m5stack.com/en/unit/dual_button>
(Gauer Knopf ist direkt am M5)

### Digitale Ausgänge

| Ausgang:  | PIN (ESP32)   |
|-----------|---------------|
| Output_Q1 | 19            |
| Output_Q2 | 23            |
| Output_Q3 | 33            |
| Output_Q4 | 25            |



### LED Strip






















## Weitere Infos

<https://github.com/Meisterschulen-am-Ostbahnhof-Munchen/ISOBUS_Hardware/tree/master/Hutschienenmoped>

contains the Hutschienenmoped, a Open Source ISOBUS ECU.

see more here: 

<https://install-isobus-environment-docs.readthedocs.io/de/latest/HutschienenMoped.html>
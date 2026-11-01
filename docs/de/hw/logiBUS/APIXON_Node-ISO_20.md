# APIXON Node-ISO 20

Basis: ESP32-P4 (kein WLAN an Bord, siehe unten).

## CAN-BUS

CAN-TX 47
CAN-RX 48

Kein zweiter CAN-Bus (CAN2) auf diesem Board.

## 🔌 IO

### Eingangsbeschaltung (I1–I8)

Alle acht Eingänge haben dieselbe Eingangsstufe (Spannungsteiler mit Tiefpass). Nur der letzte Kondensator unterscheidet die „schnellen“ Eingänge I1/I2 von den „langsamen“ Eingängen I3–I8:

```text
I n ──┬────────┬──── 47k ───┬──── 4,7k ───┬──── zum ESP32-P4
      │        │            │             │
    33 nF     47k          22k        100 pF  (I1, I2)
      │        │            │         100 nF  (I3 … I8)
     GND      GND          GND           GND
```

| Eingänge | Kondensator nach dem Teiler | Zeitkonstante | Grenzfrequenz (−3 dB) |
|---|---|---|---|
| `I1`, `I2` („schnell“) | 100 pF | ca. 2 µs | ca. 81 kHz |
| `I3`–`I8` („langsam“) | 100 nF | ca. 2 ms | ca. 81 Hz |

- **Formel:** f_g = 1 / (2π · R · C) mit R = (47 kΩ ‖ 22 kΩ) + 4,7 kΩ ≈ 19,7 kΩ (Teiler bei idealer Quelle plus Längswiderstand).
- **Teilerverhältnis:** rechnerisch 22 / (47 + 22) ≈ 0,32. Der Schaltplan nennt dagegen „2,6 V bei 12 V“; diese Abweichung ist nicht geklärt.
- **Bestückung:** Die Bestückungsliste (JLCPCB-Export zum Stand v107, 30.10.2026) stimmt für alle acht Eingangsstufen mit dem Schaltplan überein: gleiche Werte, nichts fehlt.

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

**Roh-Vollausschlag:** `IN` (`logiBUS_AI_ID`/`logiBUS_AI_IDA`) liefert 0-4095
(12 bit) — beim ESP32-P4 im hier verwendeten Continuous/DMA-ADC-Modus fix,
keine andere Bit-Breite wählbar (`SOC_ADC_DIGI_MIN_BITWIDTH` =
`SOC_ADC_DIGI_MAX_BITWIDTH` = 12 laut ESP-IDF `soc_caps.h`). Umrechnung
Rohwert → Volt: `Vout = Dout × Vmax / 4096` (`Vmax` abhängig von der
ADC-Dämpfung `ADC_ATTEN_DB_12`).

`AnalogInput_I3` (GPIO54) liegt als einziger auf ADC2 statt ADC1. Das ist hier
unproblematisch, da der ESP32-P4 kein eigenes WLAN-Radio besitzt und der
ADC2/WLAN-Konflikt (der bei ESP32/ESP32-S2/ESP32-S3 mit WLAN besteht) auf diesem Chip
nicht existiert.

**Grenzfrequenz am Analogeingang (Messung 2026-10-30):** Gemessen wurde an `I1` (Rechteck 0–10 V). „Exakt erfasst“ heißt hier: Die aus den AI-Werten gezählte Frequenz stimmt mit dem Hardware-Zähler eines Pulseingangs (`I2`) bis auf 2 Hz überein; die Amplitude wurde nicht bewertet. Das ist die beobachtete Grenze, bis zu der Flanken sauber erkannt werden, keine Filtergrenze: Bis ca. 90 Hz stimmen beide Frequenzen überein, ab 100 Hz gehen Flanken verloren, darüber tritt Aliasing auf. Die Ursache liegt in der Mittelung im Treiber, nicht in der Eingangsbeschaltung. Für `I3`–`I8` wurde nicht gemessen. Dort kommt der Tiefpass mit ca. 81 Hz (−3 dB, siehe „Eingangsbeschaltung“) hinzu: Ein 90-Hz-Signal wird dort bereits gedämpft (Grundschwingung ca. −3,5 dB, Rechteck verschliffen), der Wert von `I1` gilt für diese Eingänge nicht. Der Treiber liefert höchstens ca. 312 gemittelte Werte pro Sekunde (ein Wert alle 3,2 ms). Für Frequenzmessungen über ca. 90 Hz ist ein Puls-Eingang zu verwenden. Aufbau der Messung: Übung [`Uebung_250_AX`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-exercises-docs/de/latest/Uebungen/test_AX/Uebungen_doc/Uebung_250_AX/).

Messreihe (Rechteck 0–10 V auf `I1` als AI und `I2` als PI, Torzeit 1 s; Frequenzen in Hz, `SAMPLES_S` in AI-Werten pro Sekunde, `OK` = Abweichung höchstens 2 Hz):

| f | F_AI | F_PI | SAMPLES_S | OK |
|-------:|-----:|-----:|------------------------:|----|
| 1 | 1 | 1 | 132 | TRUE |
| 10 | 10 | 10 | 196 | TRUE |
| 30 | 30 | 30 | 252 | TRUE |
| 50 | 50 | 50 | 286 | TRUE |
| 60 | 60 | 60 | 287 | TRUE |
| 70 | 70 | 70 | 303 | TRUE |
| 80 | 80 | 80 | 312 | TRUE |
| 90 | 90 | 90 | 313 | TRUE |
| 100 | 87 | 100 | 312 | FALSE |
| 110 | 81 | 110 | 312 | FALSE |

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

### Puls-Eingänge (Frequenzmessung)

| Eingang:        | PIN (ESP32P4) |
|-----------------|---------------|
| PulseInput_I1   | 18            |
| PulseInput_I2   | 17            |
| PulseInput_I3   | 54            |
| PulseInput_I4   | 19            |
| PulseInput_I5   | 16            |
| PulseInput_I6   | 23            |
| PulseInput_I7   | 22            |
| PulseInput_I8   | 21            |

Auch die Puls-Eingänge sind Combo-Pins, die sich den physischen Pin mit dem
gleichnamigen digitalen Eingang teilen (nutzt intern dieselbe `EPinDigitalIn`-Pin-Tabelle
über die ESP32-PCNT-Hardware, siehe `IOHandleESP32PulseIN.cpp`).

**Messung am Puls-Eingang (2026-08-30):** Rechteck 12 V, Signalgenerator FNIRSI SG-003A im Modus Pulse (Level, 12,0 V Spitze), Frequenz am Generator und im 4diac-Programm abgelesen.

**Hinweis zur Eingangsspannung:** Die 12 V sind die Messbedingung, keine Spezifikation. Ein zulässiger Eingangsspannungsbereich und das Schutzverhalten der Eingänge sind hier nicht verifiziert. Rechnerisch liegen hinter dem Teiler bei 12 V ca. 3,8 V an (der Schaltplan nennt 2,6 V, ungeklärt, siehe oben), was über der 3,3-V-Versorgung des ESP32-P4 liegt. Das Messergebnis ist daher nicht als zulässiger Betriebsbereich zu verstehen; die zulässige Eingangsspannung ist beim Hersteller der Platine zu klären.

| Eingänge | Ergebnis |
|---|---|
| `PulseInput_I1`, `_I2` („schnell“) | gut bis 20 kHz, bei 23 kHz nicht mehr gut |
| `PulseInput_I3`–`_I8` („langsam“) | bis ca. 2,3 kHz |

Oberhalb dieser Frequenzen verliert der Eingang Flanken und zählt ungenau; er bricht nicht ab und wird nicht beschädigt. Der Innenwiderstand des Generators und das Tastverhältnis sind nicht dokumentiert.

**Warum die „langsamen“ Eingänge trotz ca. 81 Hz Grenzfrequenz bis ca. 2,3 kHz zählen:** Die 81 Hz sind die −3-dB-Frequenz des Filters, nicht die Zählgrenze. Der Zähler braucht keine halbe Amplitude, sondern nur ein Signal, das die Schaltschwelle noch kreuzt. Hinter dem Teiler hat das Rechteck 12 V rund 3,8 V Spitze. Der 100-nF-Filter lässt davon eine Restwelligkeit übrig (Rechnung für 50 % Tastverhältnis):

| Frequenz | Restwelligkeit `I3`–`I8` (100 nF) | `I1`, `I2` (100 pF) |
|---|---|---|
| 81 Hz | ca. 3,5 V | ca. 3,8 V |
| 500 Hz | ca. 0,95 V | ca. 3,8 V |
| 2,3 kHz | ca. 0,21 V | ca. 3,8 V |
| 5 kHz | ca. 0,10 V | ca. 3,8 V |
| 20 kHz | ca. 0,02 V | ca. 3,8 V |

Bei 2,3 kHz bleiben also noch ca. 0,2 V Welligkeit um den Mittelwert; das passt zu einer Hysterese des Eingangs von etwa 0,2 V. Das ist eine Schlussfolgerung aus der Rechnung, die Schwelle und die Hysterese des Eingangs sind nicht bekannt. Bei anderem Tastverhältnis verschiebt sich der Mittelwert, die Grenze läge dann tiefer. Den schnellen Eingängen setzt der Filter bei 20 kHz keine Grenze (volle Amplitude); dort begrenzen vermutlich die 33 nF am Eingang zusammen mit dem Innenwiderstand des Generators oder die Firmware, auch das ist nicht geprüft.

**Offene Beobachtung aus dem Live-Test (2026-08-30):** Es funktionieren nur **4 von 8** Puls-Eingängen gleichzeitig zuverlässig (analog zur PWM-Beobachtung, bei der nur 8 von 12 Ausgängen gleichzeitig liefen). Vermutlich ein Pin-/Peripherie-Sharing-Limit auf ESP32-Seite, aber die genaue Ursache ist noch offen.

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

### Vergleich mit gängigen Kleinsteuerungen

Die Werte der Wettbewerber stammen aus den Herstellerhandbüchern ([LOGO! 8 Systemhandbuch](https://cache.industry.siemens.com/dl/files/041/109741041/att_924627/v1/logo_system_manual_de-DE_de-DE.pdf), [LOGO! Produktinformation 05/2024](https://cache.industry.siemens.com/dl/files/848/109971848/att_1286527/v1/Product_Information_for_LOGO_System_Manual_de-DE_de-DE.pdf), [easyE4 Handbuch MN050009](https://es-assets.eaton.com/DOCUMENTATION/AWB_MANUALS/MN050009_EN.pdf)), die Werte des APIXON Node-ISO 20 aus den oben genannten Messungen.

**Analogeingang (0–10 V)**

| | APIXON Node-ISO 20 | Siemens LOGO! 8 | Eaton easyE4 |
|---|---|---|---|
| Auflösung | 12 Bit | Basismodul: nicht angegeben (Fehlergrenze ±1,5 %); AM2: 10 Bit, normiert auf 0–1000 | 12 Bit (0–4095) |
| Aktualisierung | bis ca. 312 Werte/s (alle 3,2 ms) | Basismodul 300 ms, AM2 50 ms | in easySoft einstellbar; feste Angabe nicht gefunden |
| Filter | Mittelung im Treiber (64 Samples) | Funktionsblöcke Analogfilter und Mittelwert | Rauschunterdrückung und Mittelung einstellbar, PT1-Filterbaustein |
| Rechteck sauber messbar bis | ca. 90 Hz an `I1` (Messung 2026-10-30; `I3`–`I8` nicht gemessen) | nicht angegeben | nicht angegeben |

**Puls-Eingang**

| | Ergebnis |
|---|---|
| APIXON Node-ISO 20, `I1`/`I2` („schnell“) | gut bis 20 kHz, bei 23 kHz nicht mehr gut (Rechteck 12 V, 2026-08-30) |
| APIXON Node-ISO 20, `I3`–`I8` („langsam“) | bis ca. 2,3 kHz, absichtlich gefiltert für langsamere, analoge Signale |
| Siemens LOGO! 8 | max. 5 kHz an `I3`–`I6` (nur 12/24RCE/RCEo, 24CE/24CEo, direkt am Zähler) |
| Eaton easyE4 | Zähler und Frequenzmesser max. 5 kHz |

- Der schnelle Puls-Eingang liegt mit 20 kHz etwa beim Vierfachen der 5 kHz der beiden Kleinsteuerungen. Die „langsamen“ Eingänge sind nicht für schnelle Zählung gedacht und werden nicht mit den schnellen Zähleingängen der Wettbewerber verglichen.
- Die Wettbewerber geben das Maximum der Zählerfunktion an. Beim APIXON ist es die Frequenz, bis zu der der Eingang noch sauber zählt; darüber verliert er Flanken.
- Beim Analogeingang gibt keiner der beiden Hersteller eine nutzbare Signalfrequenz an. Bei der LOGO! 8 begrenzt die Zykluszeit der Analogwertbildung (300 ms bzw. 50 ms) die Abtastung deutlich stärker.
- Die easyE4-Datenblätter nennen die Wandlung „je CPU-Zyklus“, das Handbuch nur eine einstellbare Update-Rate. Ein Gerätedatenblatt nennt 10 kHz Zählfrequenz, das Handbuch 5 kHz; das ist nicht aufgelöst.

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

- [🌐 ESP32 & ESP32-S3 DevKit auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/esp32/esp32-s3-devkit/)

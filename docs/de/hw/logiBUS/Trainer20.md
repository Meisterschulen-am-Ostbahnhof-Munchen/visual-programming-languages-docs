# logiBUS Trainer20

Basis: **ESP32-S31-Function-CoreBoard-1** (Modul ESP32-S31-WROOM-3, 16 MB Flash, 16 MB PSRAM).

!!! warning "Status"
    Der ESP32-S31 ist in ESP-IDF 6.1 noch ein *Preview*-Target. Das Trainer20-Target ist angelegt und
    im Build-Skript integriert, aber noch nicht auf der Hardware getestet.

Der Name steht für die 20 Anschlüsse: 8 Eingänge + 8 Ausgänge + 3 Encoder-Anschlüsse
(Taster, A, B) + 1 DS1820-Anschluss (1-Wire).

## ⚠️ Änderungen am CoreBoard

### R83 entfernen (CAN RX auf GPIO4)

Auf dem CoreBoard ist GPIO4 über den Widerstand **R83 (0 Ω)** mit dem Interrupt-Ausgang
(`ETH_INTN`) des Ethernet-PHY verbunden. Der Trainer20 nutzt GPIO4 als **CAN-RX**. Damit
der PHY die CAN-Leitung nicht beeinflusst, muss R83 **entfernt** werden. Für Ethernet ist das
unkritisch: der PHY-Interrupt wird vom ESP-IDF-Ethernet-Treiber nicht verwendet (der Link-Status
wird per Polling gelesen).

### SD-Karte und Trainer20-Funktionen schließen sich aus

Alle sechs SD-Karten-Leitungen (SDIO) des CoreBoards sind auf dem Trainer20 belegt:

| SD-Pin | GPIO | Funktion im Trainer20 |
|--------|------|-----------------------|
| D0     | 20   | Ausgang Q07           |
| D1     | 21   | Ausgang Q08           |
| D2     | 22   | Encoder Kanal A       |
| D3     | 23   | Encoder Kanal B       |
| CLK    | 24   | Encoder-Taster        |
| CMD    | 25   | CAN-TX                |

Wer die SD-Karte nutzen möchte, kann die Pins **D0–D3, CLK und CMD** der Stiftleiste am
ESP32-S31-Function-CoreBoard-1 abzwicken und die SD-Karte verwenden. Dann funktionieren aber
Q07, Q08, der Encoder und der CAN-Bus **nicht mehr**.

## CAN-BUS

| Signal  | PIN (ESP32S31)  |
|---------|-----------------|
| CAN-TX  | 25 (SDIO_CMD)   |
| CAN-RX  | 4               |

Kein zweiter CAN-Bus (CAN2) auf diesem Board. R83 entfernen, siehe oben.

## 🔌 IO

### Analoge Eingänge

| Eingang:       | PIN (ESP32S31) | ADC-Kanal |
|----------------|----------------|-----------|
| AnalogInput_I1 | 49             | ADC1_CH7  |
| AnalogInput_I2 | 48             | ADC1_CH6  |
| AnalogInput_I3 | 47             | ADC1_CH5  |
| AnalogInput_I4 | 46             | ADC1_CH4  |
| AnalogInput_I5 | 45             | ADC1_CH3  |
| AnalogInput_I6 | 44             | ADC1_CH2  |
| AnalogInput_I7 | 43             | ADC1_CH1  |
| AnalogInput_I8 | –              | (kein Analogeingang, siehe Hinweis unten) |

AnalogInput_I1–I7 sind Combo-Pins, die sich den physischen Pin mit dem
gleichnamigen digitalen Eingang teilen (I1↔AnalogInput_I1 usw.) — pro Pin kann nur
eine der beiden Funktionen gleichzeitig genutzt werden. Sie liegen alle auf ADC1; ADC2 ist auf der
Stiftleiste des CoreBoards nicht herausgeführt.

**ADC des ESP32-S31 (noch zu verifizieren):** Der S31 kennt nur *eine* Dämpfungsstufe
(`SOC_ADC_ATTEN_NUM` = 1, `ADC_ATTEN_DB_0`) und liefert als Ergebnis die gewichtete Summe von
17 redundanten Komparator-Bits (ungleichmäßige Gewichte, laut ESP-IDF); der maximale Code ist
**4393** — es ist kein 17-Bit-Wert. Der Roh-Vollausschlag und der
Messbereich in Volt werden auf der Hardware noch geprüft; die Angaben bei den
`logiBUS_AI_*`-Bausteinen (0–4095) gelten für ESP32-P4/ESP32-S3.

### Digitale Eingänge

| Eingang: | PIN (ESP32S31) |
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

| Signal           | Pin am CoreBoard | PIN (ESP32S31) |
|------------------|------------------|----------------|
| Encoder-Taster   | CLK              | 24             |
| Encoder Kanal A  | D2               | 22             |
| Encoder Kanal B  | D3               | 23             |

Die Pins sind für den Encoder vorgesehen (Belegung siehe oben, SD-Karte nicht gleichzeitig nutzbar).
Ein eigener Encoder-Baustein ist noch nicht Teil der Firmware.

### 1-Wire (DS1820)

| Signal   | PIN (ESP32S31) |
|----------|----------------|
| 1-Wire   | 3              |

Anschluss für einen DS1820-Temperatursensor (1-Wire-Bus). Ein Baustein dafür ist noch nicht Teil der Firmware.

### Digitale Ausgänge

Alle acht Ausgänge sind PWM- und servofähig.

| Ausgang:   | PIN (ESP32S31) |
|------------|----------------|
| Output_Q01 | 42             |
| Output_Q02 | 39             |
| Output_Q03 | 38             |
| Output_Q04 | 37             |
| Output_Q05 | 36             |
| Output_Q06 | 35             |
| Output_Q07 | 20 (SDIO_D0)   |
| Output_Q08 | 21 (SDIO_D1)   |

Q07 und Q08 teilen sich die Pins mit dem SD-Karten-Slot, siehe oben.

!!! note "Q01 und I8 sind auf der Platine vertauscht"
    Auf dem Trainer20 sind die Anschlüsse von Q01 und I8 gekreuzt verdrahtet: Q01 liegt an GPIO42, I8 an
    GPIO40. GPIO40 ist kein ADC-Pin, deshalb gibt es für I8 keinen Analogeingang (AnalogInput_I8 ist nicht
    belegt). I8 ist der Taster des Joysticks und wird nur digital genutzt.

### RGB-LED

Adressierbare RGB-LED des CoreBoards an **GPIO60**.

## 🌐 Ethernet

Internes EMAC des ESP32-S31 mit dem auf dem CoreBoard verbauten Gigabit-PHY **YT8531** (RGMII, RJ45).
Treiber: `espressif/yt8531`, eingebunden über `ethernet_init`.

| Signal           | PIN (ESP32S31) |
|------------------|----------------|
| MDC              | 5              |
| MDIO             | 6              |
| PHY Reset        | 7              |
| TXD0–TXD3        | 8, 9, 10, 11   |
| TX_CTL           | 12             |
| TX_CLK           | 13             |
| RX_CLK           | 14             |
| RX_CTL           | 15             |
| RXD3, RXD2, RXD1, RXD0 | 16, 17, 18, 19 |

PHY-Adresse wird automatisch erkannt. WLAN ist im ersten Schritt deaktiviert.

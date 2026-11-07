# Leistungsstufen der Ausgänge

Diese Seite beschreibt, welche Leistungstreiber auf den logiBUS-Boards sitzen, welche Frequenzgrenzen für PWM gelten und wie viel Energie beim Abschalten induktiver Lasten (Ventilspulen) im Schalter umgesetzt werden darf.

!!! note "Herkunft der Angaben"
    Die Zuordnung der Boards und die Frequenzgrenzen stammen aus dem Konzept `PWM_KONZEPT.md` (Tabelle „Bestückung je Board“) und von Franz. Die Datenblattwerte hat die Entwicklungssitzung aus den Infineon-Datenblättern gelesen; sie sind hier nicht gegen die Datenblätter geprüft. Die Zuordnung ist nicht gegen die Schaltpläne geprüft. Alle Ausgänge haben laut Franz eine Freilaufdiode.

## Bestückung je Board

| Board | Ausgänge | Leistungsstufe | Seite |
|---|---|---|---|
| APIXON Node-ISO 20 | Q1–Q12 | BTT6030-2ERA | [APIXON Node-ISO 20](APIXON_Node-ISO_20.md) |
| APIXON 15 PWR | Q1 | BTH50030-1LUA | keine eigene Seite |
| APIXON 15 PWR | Q7–Q12 | BTT6030-2ERA | keine eigene Seite |
| Deca Out | alle | BTS7030-2EPA | [DualCAN deca-output](DualCAN/DualCAN_deca_output_ESP32S3.md) |
| Octa Out | alle | BTS7030-2EPA | [DualCAN octa-output](DualCAN/DualCAN_octa_output_ESP32S3.md) |
| Hutschienenmoped 2026 (XL26) | Q1–Q4 | BTS7030-2EPA | [Hutschienenmoped XL26](Hutschienenmoped/HutschienenmopedXL26.md) |
| Hutschienenmoped 2026 (XL26) | Q5–Q8 | zwei BTM9010EP (H-Brücke), PWM auf der Low-Side Q56 und Q78 | [Hutschienenmoped XL26](Hutschienenmoped/HutschienenmopedXL26.md) |
| Dual Out 12-24-48V | alle | BTH6070-2EPV | Seitenzuordnung offen |
| Dual Out 12V | alle | BTS7030-2EPA | Seitenzuordnung offen |
| Hutschienenmoped 12V | alle | BTS7030-2EPA | Seitenzuordnung offen |
| Trainer20 | Q01–Q08 | keine Leistungsstufe | [Trainer20](Trainer20.md) |

Weitere Boards (zum Beispiel M5, lilygo) sind noch nicht erfasst.

## Frequenzgrenzen für PWM

Die Firmware prüft diese Grenzen nicht. Sie stehen als Hinweis im Kommentar von `FREQ` der PWM-Bausteine.

| Leistungsstufe | Grenze |
|---|---|
| BTH50030-1LUA (APIXON 15 PWR Q1) | höchstens 100 Hz (Datenblatt: maximale Eingangsfrequenz `fIN` = 100 Hz) |
| BTS7030-2EPA, BTT6030-2ERA, BTH6070-2EPV | für Ventile 100 bis 200 Hz |
| Trainer20 | ohne Leistungsstufe, jede Frequenz |

## Abschaltenergie induktiver Lasten

Beim Abschalten einer Spule muss die gespeicherte Energie irgendwo bleiben.

- **Mit Freilaufdiode** (alle logiBUS-Ausgänge laut Franz): Die Diode baut die Spulenenergie ab. Bei Ventil-PWM wird die Energie also nicht in der Klemmung des Schalters umgesetzt.
- **Ohne Diode oder bei defekter Diode** (zum Beispiel eine Spule direkt ohne Diode): Der Schalter klemmt die Spannung selbst, und die Energie wird im Schalter umgesetzt. Dafür gelten die Energiegrenzen der Tabelle.

Die Grenzen sind trotzdem hier dokumentiert, weil sie bei einem Diodenausfall oder bei Lasten ohne Diode zählen.

| Schalter | Familie | Klemmspannung | Einzelpuls `EAS` | Wiederholt `EAR` / Hinweis | Datenblatt |
|---|---|---|---|---|---|
| BTS7030-2EPA | PROFET+2 12 V, 2 × 30 mΩ | `VDS(CLAMP)` mindestens 35 V | höchstens 38 mJ bei `IL` = 2 · `IL(NOM)`, `TJ(0)` = 150 °C, `VS` = 28 V | höchstens 18 mJ bei `IL(NOM)`, `TJ(0)` = 85 °C, `VS` = 13,5 V, 1 Mio. Zyklen | 2024-07-29 |
| BTT6030-2ERA | PROFET+2 12/24 V, 2 × 30 mΩ | `VDS(AZ)` 66 bis 75 V | höchstens 85 mJ bei `IL(0)` = 4 A, `TJ(0)` = 150 °C, `VS` = 28 V | Schutzfunktionen nicht für dauernden wiederholten Betrieb ausgelegt | Rev. 2019-03-09 |
| BTH6070-2EPV | PROFET+ 48 V, 2 × 60 mΩ (auf DualOut 48V) | `VDS(CLAMP)` 65 bis 75 V | höchstens 40 mJ bei `IL(NOM)` = 2,17 A, `VS` = 54 V | ebenfalls nicht für wiederholten Betrieb ausgelegt | Rev. 1.00, 2025-11-15 |
| BTH50030-1LUA | Power PROFET+ 24/48 V, 3 mΩ, 25 A | Smart Clamp mit schnellem Abschalten | Grenzkurve `EAS`/`EAR` über `IL` (Datenblatt, Figure 6) | Schaltenergie bei hoher Last etwa 9 bis 12,5 mJ ein und 7 bis 10 mJ aus; `fIN` höchstens 100 Hz | – |
| BTM9010EP (H-Brücke) | Brücke mit eigenen Freilaufdioden | – | – | Durchlassspannung der Diode `Vf` höchstens 0,9 V bei 2 A, 150 °C | – |

Die Klemmenergie beim Abschalten einer Spule `L` mit Widerstand `RL` über die Klemmung gibt das Datenblatt so an:

```text
E = VDS(CLAMP) · L/RL · [ (VS − VDS(CLAMP))/RL · ln(1 − RL·IL/(VS − VDS(CLAMP))) + IL ]
```

Bei PWM ohne Diode fällt diese Energie in jeder Periode an. Die Verlustleistung im Schalter ist dann `E` mal PWM-Frequenz. Beispiel: 18 mJ bei 100 Hz sind 1,8 W allein durch die Klemmung.

## Quellen

- Infineon BTS7030-2EPA (<https://www.infineon.com/part/BTS7030-2EPA>)
- Infineon BTT6030-2ERA (<https://www.infineon.com/part/BTT6030-2ERA>)
- Infineon BTH6070-2EPV (<https://www.infineon.com/part/BTH6070-2EPV>)
- Infineon BTH50030-1LUA (<https://www.infineon.com/part/BTH50030-1LUA>)
- Infineon BTM9010EP (<https://www.infineon.com/part/BTM9010EP>)

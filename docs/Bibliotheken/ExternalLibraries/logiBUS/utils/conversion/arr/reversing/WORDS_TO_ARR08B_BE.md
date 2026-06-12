# WORDS_TO_ARR08B_BE

<br>

![WORDS_TO_ARR08B_BE](./WORDS_TO_ARR08B_BE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **WORDS_TO_ARR08B_BE** fasst vier 16‑Bit‑Wörter (WORD) zu einem 8‑Byte‑Array zusammen. Die Umwandlung erfolgt im **Big‑Endian‑Format** (Network Byte Order), bei dem das höherwertige Byte (High‑Byte) zuerst im Ausgabearray abgelegt wird. Dies entspricht der üblichen Darstellung in Netzwerkprotokollen wie Modbus TCP, Siemens S7‑Kommunikation oder Ethernet‑Headern.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Konvertierung aller vier Eingangswörter. |

### **Ereignis‑Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Wird gesendet, sobald das Ausgabearray vollständig berechnet wurde. |

### **Daten‑Eingänge**
| Name    | Typ   | Kommentar |
|---------|-------|-----------|
| `IN_00` | WORD  | Word 00 (erstes Wort) |
| `IN_01` | WORD  | Word 01 (zweites Wort) |
| `IN_02` | WORD  | Word 02 (drittes Wort) |
| `IN_03` | WORD  | Word 03 (viertes Wort) |

### **Daten‑Ausgänge**
| Name | Typ             | Kommentar |
|------|-----------------|-----------|
| `OUT`| ARRAY[0..7] OF BYTE | 8‑Byte‑Array im Big‑Endian‑Format |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Nach dem Empfangen der Ereignisses `REQ` werden die Werte der vier Eingänge `IN_00` bis `IN_03` ausgelesen. Für jedes Wort wird zuerst das **High‑Byte** (BYTE 1) und dann das **Low‑Byte** (BYTE 0) in das Ausgabearray geschrieben. Die Reihenfolge im Array ist:

- `OUT[0]` = High‑Byte von `IN_00`
- `OUT[1]` = Low‑Byte  von `IN_00`
- `OUT[2]` = High‑Byte von `IN_01`
- `OUT[3]` = Low‑Byte  von `IN_01`
- `OUT[4]` = High‑Byte von `IN_02`
- `OUT[5]` = Low‑Byte  von `IN_02`
- `OUT[6]` = High‑Byte von `IN_03`
- `OUT[7]` = Low‑Byte  von `IN_03`

Anschließend wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- **Big‑Endian‑Format** (Network Byte Order) – die Bytes werden in der Reihenfolge höherwertiges Byte zuerst abgelegt. Dies ist für viele industrielle Kommunikationsprotokolle und Netzwerkstack erforderlich.
- Der Baustein arbeitet **ereignisgesteuert**: Die Konvertierung wird nur bei einem `REQ`‑Ereignis ausgeführt, sodass keine zyklische Berechnung erfolgt.
- Die interne Implementierung erfolgt in **Strukturiertem Text (ST)** mit direkter Bit‑Elementzugriff (`%B1` und `%B0`), was eine effiziente und deterministische Umwandlung gewährleistet.

## Zustandsübersicht
Der Funktionsblock besitzt keinen expliziten internen Zustand (zustandslos). Er führt bei jedem `REQ` sofort die Berechnung durch und signalisiert den Abschluss mit `CNF`. Während der Berechnung sind keine Blockierungen zu erwarten.

## Anwendungsszenarien
- **Netzwerkkommunikation**: Aufbereitung von Daten für Protokolle, die Big‑Endian erwarten, z. B. Modbus TCP, Siemens S7 über Industrial Ethernet oder Raw‑Ethernet‑Frames.
- **Datenvorverarbeitung**: Konvertierung von Sensorwerten oder Steuerbefehlen, die als WORD‑Register vorliegen, in ein Byte‑orientiertes Format.
- **Gateway‑Funktionen**: Umsetzung zwischen Little‑Endian‑Steuerungen und Big‑Endian‑Netzwerken.

## Vergleich mit ähnlichen Bausteinen
| Baustein                    | Besonderheit |
|-----------------------------|--------------|
| WORDS_TO_ARR08B_BE          | Big‑Endian, 4 WORDS → 8 Bytes |
| WORDS_TO_ARR08B_LE          | Little‑Endian (Low‑Byte zuerst) |
| BYTES_TO_WORDS_BE / LE      | Rückwärtskonvertierung |
| WORDS_TO_ARR16B_BE          | Big‑Endian, 8 WORDS → 16 Bytes |
| WORDS_TO_ARR08N             | Ggf. unspezifische Endianness |

Der vorliegende Baustein ist speziell für Big‑Endian‑Anwendungen optimiert und kompakt gehalten.

## Fazit
`WORDS_TO_ARR08B_BE` ist ein präziser, ereignisgesteuerter Funktionsblock zur Big‑Endian‑Konvertierung vierer WORDS in ein 8‑Byte‑Array. Er eignet sich hervorragend für alle Anwendungen, die eine byte‑weise Darstellung im Network Byte Order erfordern, und vereinfacht die Schnittstelle zwischen Steuerungslogik und Kommunikationsprotokollen.
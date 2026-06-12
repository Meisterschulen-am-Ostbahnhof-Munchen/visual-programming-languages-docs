# ARR08B_TO_WORDS_BE


![ARR08B_TO_WORDS_BE](./ARR08B_TO_WORDS_BE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ARR08B_TO_WORDS_BE` extrahiert aus einem 8‑Byte‑Array (Big‑Endian) vier 16‑Bit‑Wörter (WORD). Er wird hauptsächlich zur Konvertierung von binären Datenströmen eingesetzt, die in einem aufsteigenden Byte‑Array vorliegen und als geordnete Wortfolge interpretiert werden sollen. Der Baustein gehört zur Paketgruppe `logiBUS::utils::conversion::arr::forwarding`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|---------|-------------|
| `REQ`   | Startet die Konvertierung: Das anliegende Byte‑Array `IN` wird in die vier Ausgangswörter umgesetzt. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|---------|-------------|
| `CNF`    | Bestätigt die erfolgreiche Umwandlung und signalisiert, dass die Ausgangswerte gültig sind. |

### **Daten-Eingänge**

| Name | Typ | Array-Größe | Beschreibung |
|------|-----|-------------|-------------|
| `IN` | `BYTE` | `0..7` (8 Bytes) | Eingangsarray – die Rohdaten, aus denen die Wörter extrahiert werden. |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| `OUT_00` | `WORD` | Wort aus Byte 0 (High) und Byte 1 (Low) |
| `OUT_01` | `WORD` | Wort aus Byte 2 (High) und Byte 3 (Low) |
| `OUT_02` | `WORD` | Wort aus Byte 4 (High) und Byte 5 (Low) |
| `OUT_03` | `WORD` | Wort aus Byte 6 (High) und Byte 7 (Low) |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Beim Eintreffen eines `REQ`‑Ereignisses werden die acht Bytes des Eingangsarrays `IN` in strenger **Big‑Endian‑Reihenfolge** in vier 16‑Bit‑Wörter verpackt:

- `OUT_00` = `(IN[0] << 8) | IN[1]`
- `OUT_01` = `(IN[2] << 8) | IN[3]`
- `OUT_02` = `(IN[4] << 8) | IN[5]`
- `OUT_03` = `(IN[6] << 8) | IN[7]`

Anschließend wird das Ausgangsereignis `CNF` ausgelöst, das die Gültigkeit aller Ausgabewerte anzeigt. Die Implementierung erfolgt direkt im Structured‑Text‑Teil des Funktionsblocks, ohne internen Zustandsautomaten.

## Technische Besonderheiten

- **Big‑Endian‑Konvention:** Das erste Byte eines Wortes (`IN[0]`, `IN[2]`, …) bildet das höherwertige Byte (`%B1`), das zweite Byte (`IN[1]`, `IN[3]`, …) das niederwertige Byte (`%B0`).  
- **Feste Array‑Größe:** Es werden exakt 8 Bytes erwartet; das Array ist als `ARRAY[0..7] OF BYTE` deklariert.  
- **Keine Nebeneffekte:** Der Baustein ist rein kombinatorisch – er benötigt keinen internen Zustand und arbeitet innerhalb eines einzigen Ereigniszyklus.  
- **Typischer Einsatz:** Konvertierung von Daten aus binären Protokollen (z. B. CAN‑Nachrichten, Modbus‑Registern oder seriellen Streams), die als Byte‑Array vorliegen.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten. Er wird durch das **Ereignis `REQ`** getriggert und gibt nach der Datenverarbeitung **`CNF`** aus. Die Ausführung erfolgt innerhalb eines einzigen Zyklus.

| Zustand | Beschreibung |
|---------|-------------|
| *Idle* | Warten auf `REQ`; Ausgänge behalten den letzten Wert. |
| *Processing* | `REQ` eingetroffen – Daten werden umgesetzt. |
| *Completed* | `CNF` wird gesendet, Ausgänge sind gültig. Baustein kehrt sofort in den Ruhezustand zurück. |

## Anwendungsszenarien

1. **Modbus‑Kommunikation:** Ein 8‑Byte‑Registerblock (z. B. Holding‑Register) wird als Byte‑Array empfangen und muss in vier 16‑Bit‑Werte aufgeteilt werden.  
2. **CAN‑Botschaften:** Ein 8‑Byte‑CAN‑Frame enthält mehrere 16‑Bit‑Sensorwerte, die im Big‑Endian‑Format übertragen werden.  
3. **Serielle Datenanalyse:** Zusammenfassen aufeinanderfolgender Bytes aus einer seriellen Schnittstelle zu nutzbaren WORD‑Größen für die Weiterverarbeitung.  
4. **Gateway‑Funktionen:** Konvertierung von Binär‑ zu Allzweckdaten in Automatisierungsprozessen, die auf IEC 61499 basieren.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|-------------|
| `ARR08B_TO_WORDS_LE` | Verwendet Little‑Endian‑Reihenfolge (Byte[0] = Low‑Byte). |
| `ARR04B_TO_WORD` | Arbeitet mit einem 4‑Byte‑Array und erzeugt nur ein WORD. |
| `BYTE_TO_WORD` | Konvertiert zwei einzelne Bytes in ein WORD; benötigt separate Zusammenstellung. |

`ARR08B_TO_WORDS_BE` fokussiert auf die effiziente, vordefinierte Aufteilung eines 8‑Byte‑Arrays in vier Wörter unter Big‑Endian‑Reihenfolge – ideal für standardisierte Protokolle.

## Fazit

Der Funktionsblock `ARR08B_TO_WORDS_BE` bietet eine einfache und zuverlässige Methode, ein 8‑Byte‑Array in vier Big‑Endian‑Wörter umzuwandeln. Durch die kompakte Schnittstelle (`REQ`/`CNF` + ein Eingang, vier Ausgänge) lässt er sich leicht in bestehende IEC‑61499‑Applikationen integrieren. Dank der direkten ST‑Implementierung entstehen keine Latenzen durch Zustandsautomaten, was ihn besonders für zeitkritische Anwendungen in der Automatisierungstechnik empfiehlt.
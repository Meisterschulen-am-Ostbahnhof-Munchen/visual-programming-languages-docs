# WORDS_TO_ARR08B


![WORDS_TO_ARR08B](./WORDS_TO_ARR08B.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **WORDS_TO_ARR08B** dient dazu, vier 16‑Bit‑Wörter (Typ `WORD`) zu einem Byte‑Array der Länge 8 (Typ `ARRAY[0..7] OF BYTE`) zusammenzufügen. Dabei kommt das Little‑Endian‑Format (Intel‑Standard) zur Anwendung, das die niederwertigen Bytes zuerst ablegt. Der Baustein wird über einen Ereigniseingang gesteuert und eignet sich besonders für PC‑basierte Steuerungen (z. B. Beckhoff, Wago, B&R, Raspberry Pi).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `REQ` | Event | Auslösen der Konvertierung; alle Eingangsvariablen werden dabei gelesen und das Ergebnis berechnet. |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `CNF` | Event | Wird nach erfolgreicher Berechnung gesendet, signalisiert, dass am Ausgang `OUT` gültige Daten anliegen. |

### **Daten-Eingänge**

| Name   | Typ  | Beschreibung                     |
|--------|------|----------------------------------|
| `IN_00` | WORD | Erstes Wort (Byte 0 und 1)      |
| `IN_01` | WORD | Zweites Wort (Byte 2 und 3)     |
| `IN_02` | WORD | Drittes Wort (Byte 4 und 5)     |
| `IN_03` | WORD | Viertes Wort (Byte 6 und 7)     |

### **Daten-Ausgänge**

| Name | Typ                | Beschreibung                                      |
|------|--------------------|---------------------------------------------------|
| `OUT` | ARRAY[0..7] OF BYTE | Ergebnis-Array, enthält die 8 Bytes in Little‑Endian‑Reihenfolge. |

### **Adapter**

Keine Adapter definiert.

## Funktionsweise

Der FB führt bei einer steigenden Flanke am Ereigniseingang `REQ` die folgende Abbildung durch (beschrieben in der Strukturierten Text‑Implementierung):

| Index `OUT` | Quelle          | Bedeutung                           |
|-------------|-----------------|-------------------------------------|
| `OUT[0]`    | `IN_00.%B0`     | Niederwertiges Byte von Wort 0      |
| `OUT[1]`    | `IN_00.%B1`     | Höherwertiges Byte von Wort 0       |
| `OUT[2]`    | `IN_01.%B0`     | Niederwertiges Byte von Wort 1      |
| `OUT[3]`    | `IN_01.%B1`     | Höherwertiges Byte von Wort 1       |
| `OUT[4]`    | `IN_02.%B0`     | Niederwertiges Byte von Wort 2      |
| `OUT[5]`    | `IN_02.%B1`     | Höherwertiges Byte von Wort 2       |
| `OUT[6]    | `IN_03.%B0`     | Niederwertiges Byte von Wort 3      |
| `OUT[7]`    | `IN_03.%B1`     | Höherwertiges Byte von Wort 3       |

Nach Abschluss der Zuweisungen wird der Ausgangsimpuls `CNF` erzeugt.

## Technische Besonderheiten

- **Little‑Endian‑Format**: Die Bytes jedes Wortes werden in aufsteigender Speicheradresse mit niederwertigem Byte zuerst abgelegt. Dies entspricht der Intel‑Byte‑Reihenfolge und ist für viele PC‑basierte Steuerungen und Kommunikationsprotokolle (z. B. Modbus, CANopen, serielle Schnittstellen) üblich.
- **Keine Umkehrung der Gesamtreihenfolge**: Die Wörter selbst werden in der Reihenfolge `IN_00` bis `IN_03` in das Array eingefügt; nur innerhalb jedes Wortes wird die Byte‑Reihenfolge gedreht. Möchte man stattdessen auch die Wortreihenfolge umkehren (z. B. Big‑Endian auf Wortebene), ist eine andere Implementierung notwendig.
- **Sofortige Ausführung**: Der Baustein ist rein kombinatorisch – nach dem Ereignis `REQ` liegt das Ergebnis am nächsten Ausführungszyklus an. Es wird kein interner Zustand gespeichert.

## Zustandsübersicht

Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Das Verhalten ist rein ereignisgesteuert:

1. **Idle**: Warten auf `REQ`.
2. **Processing**: Bei `REQ` werden die Eingangswerte gelesen und die Ausgangsberechnung durchgeführt.
3. **Complete**: `CNF` wird gesendet; der FB kehrt in den Idle‑Zustand zurück.

Die Implementierung ist deterministisch und benötigt nur einen Ausführungsschritt.

## Anwendungsszenarien

- **Kommunikation mit Peripherie**: Ein Mikrocontroller oder IPC sendet 16‑Bit‑Sensordaten (z. B. Analog/Digital‑Wandler, Encoder) über einen seriellen Bus, der Byte‑orientiert ist. Der Baustein packt die Wörter in ein Byte‑Array, das direkt versendet werden kann.
- **Datenlogging**: Zusammenführen mehrerer 16‑Bit‑Messwerte in einen Puffer für die Speicherung oder Übertragung (z. B. CSV, Binärformat).
- **Protokoll‑Konvertierung**: Anpassung von Daten an die Byte‑Anordnung, die von einem bestimmten Protokoll (z. B. OPC UA, MQTT‑Binär‑Payload) gefordert wird.

## Vergleich mit ähnlichen Bausteinen

- **WORDS_TO_ARR08B** erwartet genau vier Wörter und erzeugt ein Array der Länge 8. Für andere Wort‑/Byte‑Anzahlen existieren verwandte Bausteine wie `WORDS_TO_ARR04B`, `WORDS_TO_ARR16B` oder jeweils für Big‑Endian.
- Im Gegensatz zu einem universellen `MERGE`‑Block, der beliebige Datentypen zusammenfügt, ist dieser FB speziell auf die 2‑Byte‑Pro‑Wort‑Konvertierung optimiert und garantiert die korrekte Byte‑Reihenfolge.
- Gegenüber einer einfachen Variablenzuweisung mittels `MOVE` oder einer reinen `WORD_TO_BYTE`‑Funktion vermeidet der Block manuelle Index‑Berechnungen und erhöht die Lesbarkeit.

## Fazit

Der Funktionsblock **WORDS_TO_ARR08B** ist ein kompakter, spezialisierter Baustein für die Umwandlung von vier 16‑Bit‑Wörtern in ein Little‑Endian‑Byte‑Array. Durch die klare ereignisgesteuerte Schnittstelle und die einfache Implementierung eignet er sich ideal für den Einsatz in Steuerungsanwendungen, bei denen Daten auf Byte‑Ebene für die Kommunikation oder Speicherung aufbereitet werden müssen. Er gehört zur Paketfamilie `logiBUS::utils::conversion::arr::reversing` und erweitert die 4diac‑Toolbox um eine nützliche Konvertierungsmöglichkeit.
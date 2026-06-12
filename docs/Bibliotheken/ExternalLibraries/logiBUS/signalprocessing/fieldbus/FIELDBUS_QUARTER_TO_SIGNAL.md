# FIELDBUS_QUARTER_TO_SIGNAL


![FIELDBUS_QUARTER_TO_SIGNAL](./FIELDBUS_QUARTER_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FIELDBUS_QUARTER_TO_SIGNAL` dient als Signalvalidierungs- und Durchleitungsbaustein. Er prüft, ob ein eingehender BYTE-Wert `IN` innerhalb eines gültigen Bereichs liegt, und gibt ihn in diesem Fall unverändert an `OUT` weiter. Zusätzlich wird ein Boolesches Signal `VALID` gesetzt, das den Gültigkeitsstatus des Ausgangs anzeigt. Der Baustein eignet sich zur Filterung von Feldbussignalen, bei denen bestimmte Werte als ungültig oder „don't care“ markiert sind.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Typ   | Kommentar                    | Mit Variablen |
|--------|-------|------------------------------|---------------|
| `REQ`  | Event | Normaler Ausführungsauftrag  | `IN`          |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                   | Mit Variablen     |
|-------|-------|-----------------------------|-------------------|
| `CNF` | Event | Ausführungsbestätigung      | `OUT`, `VALID`    |

### **Daten-Eingänge**

| Name | Typ    | Kommentar          | Initialwert                    |
|------|--------|--------------------|--------------------------------|
| `IN` | `BYTE` | Eingangssignal     | `NOT_AVAILABLE_2bit` (importierte Konstante) |

### **Daten-Ausgänge**

| Name    | Typ    | Kommentar                       | Initialwert |
|---------|--------|---------------------------------|-------------|
| `OUT`   | `BYTE` | Gefiltertes Ausgangssignal      | `16#00`     |
| `VALID` | `BOOL` | `TRUE`, wenn das Signal gültig ist | `FALSE` |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Bei einem Ereignis am Eingang `REQ` wird der Algorithmus `REQ` ausgeführt:
1. Der eingehende Wert `IN` wird mit der importierten Konstanten `DONT_CARE_2bit` verglichen.
2. Ist `IN` kleiner als `DONT_CARE_2bit`, wird der Wert als gültig betrachtet:
   - `OUT` erhält den Wert von `IN`.
   - `VALID` wird auf `TRUE` gesetzt.
3. Andernfalls (wenn `IN` größer oder gleich `DONT_CARE_2bit` ist) wird das Signal als ungültig eingestuft:
   - `OUT` wird auf `BYTE#0` zurückgesetzt.
   - `VALID` wird auf `FALSE` gesetzt.
4. Nach der Verarbeitung wird das Ereignis `CNF` ausgelöst.

Der Vergleich nutzt dabei die Semantik der importierten Konstanten:  
`DONT_CARE_2bit` definiert die Grenze, ab der Werte als „egal“ oder ungültig gelten. Der Initialwert von `IN` ist auf `NOT_AVAILABLE_2bit` gesetzt, der typischerweise oberhalb dieser Grenze liegt, sodass der Baustein beim Start einen definierten ungültigen Zustand ausgibt.

## Technische Besonderheiten

- **Konstantenimport**: Die Werte `DONT_CARE_2bit` und `NOT_AVAILABLE_2bit` werden aus einem übergeordneten Signalverarbeitungs-Paket importiert. Sie müssen im Zielsystem definiert sein und sinnvolle Schwellenwerte repräsentieren (z. B. `16#FC` für don't care).
- **Einfache Zustandslogik**: Der Baustein besitzt nur einen einzigen EC‑Zustand `REQ`. Jedes Ereignis führt sofort zur Berechnung und Ausgabe.
- **Kompatibilität**: Entwickelt gemäß IEC 61499-1, einsetzbar in der 4diac‑IDE und anderen konformen Laufzeitumgebungen.

## Zustandsübersicht

Es existiert nur ein Zustand:

| Zustand | Beschreibung                                      | Ausgabeereignis | Ausgabeaktionen          |
|---------|--------------------------------------------------|----------------|--------------------------|
| `REQ`   | Verarbeitet den Eingang und aktualisiert Ausgänge | `CNF`          | `OUT` und `VALID` setzen |

## Anwendungsszenarien

- **Feldbus-Überwachung**: Ein Sensor liefert auf einem Feldbus (z. B. CANopen, PROFIBUS) 8‑Bit‑Daten, wobei bestimmte Werte als „nicht verfügbar“ oder „Fehler“ codiert sind. Der Baustein extrahiert die gültigen Messwerte und zeigt deren Gültigkeit an.
- **Signalpreprocessing**: Vor der Weiterverarbeitung in einer Steuerung werden ungültige Telegrammteile herausgefiltert, sodass nachfolgende Blöcke nur mit plausiblen Daten arbeiten.
- **Gateway zwischen Bussystemen**: Übersetzung von Don’t‑Care‑Konventionen eines Busses auf ein einheitliches Gültigkeitssignal für das Zielsystem.

## Vergleich mit ähnlichen Bausteinen

- **`FIELDBUS_QUARTER_TO_SIGNAL`** ist spezialisiert auf die Unterscheidung zwischen gültigen und ungültigen Werten mittels eines festen Schwellwerts.  
- Ein allgemeiner **Wertfilter** (z. B. `F_BAND`) könnte dagegen einen unteren und oberen Grenzwert abfragen.  
- Ein **Gültigkeitsprüfer** (z. B. `VALIDITY_CHECK`) setzt oft zusätzlich Quality‑of‑Service‑Flags.  
Der vorliegende Baustein besticht durch seine einfache, auf Feldbustypen zugeschnittene Logik.

## Fazit

`FIELDBUS_QUARTER_TO_SIGNAL` ist ein kompakter, effizienter Funktionsblock zur Validierung von 8‑Bit‑Feldbussignalen. Er trennt zuverlässig gültige Messwerte von als ungültig markierten Werten und stellt die Gültigkeit als separates Boolesches Signal bereit. Dank seiner schlanken Zustandslogik und der Verwendung importierter Konstanten lässt er sich flexibel in unterschiedliche Signalverarbeitungsketten integrieren.
# FIELDBUS_DWORD_TO_SIGNAL_SCALED


![FIELDBUS_DWORD_TO_SIGNAL_SCALED](./FIELDBUS_DWORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_DWORD_TO_SIGNAL_SCALED** dient der Konvertierung eines Feldbus-DWORD-Signals in einen skalierten LREAL-Wert. Er prüft die Gültigkeit des Eingangssignals anhand eines vordefinierten Bereichs und berechnet bei gültigem Signal den Ausgangswert durch Multiplikation mit einem Skalierungsfaktor und Addition eines Offsets. Bei ungültigem Signal wird der Ausgang auf 0 gesetzt und die Gültigkeitsflagge auf FALSE gesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT     | EInit | Initialisierungsanforderung; übergibt Skalierungsparameter |
| REQ      | Event | Normale Ausführungsanforderung zur Verarbeitung des Eingangs |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO    | EInit | Bestätigung der Initialisierung |
| CNF      | Event | Bestätigung der Ausführung; liefert skalierten Ausgang und Gültigkeitsflagge |

### **Daten-Eingänge**

| Name   | Typ   | Initialwert           | Beschreibung |
|--------|-------|-----------------------|--------------|
| IN     | DWORD | NOT_AVAILABLE_DWM     | Eingangswert vom Feldbus |
| SCALE  | LREAL | LREAL#1.0             | Skalierungsfaktor (Multiplikator) |
| OFFSET | DINT  | DINT#0                | Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**

| Name  | Typ   | Initialwert | Beschreibung |
|-------|-------|-------------|--------------|
| OUT   | LREAL | LREAL#0.0   | Skalierter Ausgangswert |
| VALID | BOOL  | FALSE       | TRUE, wenn das Eingangssignal gültig ist |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock besitzt zwei Zustände: **INIT** und **REQ**.

- **INIT-Zustand**: Wird durch das Ereignis INIT ausgelöst. Der zugehörige Algorithmus ist leer, d.h. es werden keine weiteren Aktionen durchgeführt. Der Ausgang INITO bestätigt den Abschluss der Initialisierung.
- **REQ-Zustand**: Wird durch das Ereignis REQ ausgelöst. Der Algorithmus REQ führt folgende Schritte aus:
  1. Prüfung, ob der als UDINT interpretierte Eingangswert IN kleiner oder gleich der Konstanten `VALID_SIGNAL_DW` ist.
  2. Ist diese Bedingung erfüllt, gilt das Signal als gültig:
     - `OUT` wird berechnet als: `UDINT_TO_LREAL(DWORD_TO_UDINT(IN)) * SCALE + DINT_TO_LREAL(OFFSET)`
     - `VALID` wird auf `TRUE` gesetzt.
  3. Andernfalls (Signal ungültig):
     - `OUT` wird auf `0.0` gesetzt.
     - `VALID` wird auf `FALSE` gesetzt.
  4. Anschließend wird das Ereignis CNF ausgelöst, das die Ergebnisse (OUT, VALID) bereitstellt.

Die Konstanten `NOT_AVAILABLE_DWM` und `VALID_SIGNAL_DW` stammen aus importierten Bibliotheken und legen fest, welche DWORD-Werte als „nicht verfügbar“ bzw. als „gültig“ betrachtet werden.

## Technische Besonderheiten
- Der Funktionsblock verwendet eine Bereichsprüfung mittels Vergleich von `DWORD_TO_UDINT(IN)` mit `VALID_SIGNAL_DW`. Dabei wird vorausgesetzt, dass gültige Feldbussignale innerhalb eines bestimmten Zahlenbereichs liegen.
- Die Konvertierung erfolgt ohne Gleitkommafehleranfälligkeit, da zuerst die Umwandlung von DWORD in UDINT und dann in LREAL erfolgt.
- Der Skalierungsfaktor `SCALE` und der Offset `OFFSET` können während der Initialisierung oder Laufzeit gesetzt werden, werden aber nur im REQ-Algorithmus verwendet.
- Der Baustein ist als SimpleFB implementiert und eignet sich für zyklische Verarbeitung.

## Zustandsübersicht

| Zustand | Auslöser | Aktion | Ausgang |
|---------|----------|--------|---------|
| INIT    | INIT-Ereignis | Algorithmus INIT (leer) | INITO |
| REQ     | REQ-Ereignis | Algorithmus REQ (Berechnung und Gültigkeitsprüfung) | CNF |

Der Funktionsblock benötigt keine Zustandsübergänge zwischen INIT und REQ – beide Zustände werden direkt durch ihre jeweiligen Ereignisse gestartet.

## Anwendungsszenarien
- **Landwirtschaftliche Feldbus-Steuerungen**: Umwandlung von rohen DWORD-Sensorwerten (z.B. Drehzahlen, Drücke) in physikalische Einheiten unter Berücksichtigung von Sensorcharakteristiken.
- **Skalierung von analogen Werten**: Wenn ein Feldbusgerät einen 32-Bit-Rohwert liefert, der erst mit einem Faktor und Offset in eine normierte Größe (z.B. 0-100%) umgerechnet werden muss.
- **Signalvalidierung**: Nur gültige Signale (innerhalb eines definierten Bereichs) werden weiterverarbeitet; bei ungültigen Werten wird ein definierter Nullwert ausgegeben.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_DWORD_TO_SIGNAL**: Ein ähnlicher Baustein ohne Skalierungsmöglichkeit, der den Rohwert direkt als LREAL ausgibt.
- **FIELDBUS_DWORD_TO_SIGNAL_SCALED** bietet zusätzlich die Parameter `SCALE` und `OFFSET` für flexible Umrechnung.
- **Ereignisgesteuerte Konverter**: Andere Bausteine nutzen möglicherweise eine andere Validierungslogik (z.B. Bitmasken) oder unterstützen unterschiedliche Feldbustypen.

Der vorliegende Baustein kombiniert Signalvalidierung mit einer einfachen linearen Transformation, was ihn für viele Anwendungen geeignet macht.

## Fazit
Der `FIELDBUS_DWORD_TO_SIGNAL_SCALED` ist ein kompakter und wiederverwendbarer Funktionsblock zur Verarbeitung von Feldbussignalen. Er ermöglicht eine zuverlässige Gültigkeitsprüfung und gleichzeitige Skalierung in einem Schritt. Durch die klare Trennung von Initialisierung und Verarbeitung eignet er sich sowohl für Einmal- als auch für zyklische Aufrufe in Automatisierungssystemen, insbesondere in der Landtechnik.
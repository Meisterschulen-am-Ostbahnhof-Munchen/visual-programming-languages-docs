# FIELDBUS_UDINT_TO_SIGNAL_SCALED


![FIELDBUS_UDINT_TO_SIGNAL_SCALED](./FIELDBUS_UDINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `FIELDBUS_UDINT_TO_SIGNAL_SCALED` dient der Aufbereitung eines über den Feldbus empfangenen UDINT-Wertes. Er spiegelt den Eingang `IN` auf den Ausgang `OUT` wider, jedoch nur dann, wenn das eingehende Signal als gültig erkannt wird. Zusätzlich wird der Wert mit einem Faktor skaliert und einem Offset versehen. Dieser Baustein wird typischerweise in der Signalverarbeitungskette von Feldbusprotokollen eingesetzt, um rohe Integer-Werte in physikalische Größen (z. B. als LREAL) umzurechnen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Mit Parametern | Beschreibung                            |
|----------|-------|----------------|-----------------------------------------|
| `INIT`   | EInit | `SCALE`, `OFFSET` | Initialisierung – setzt Skalierungsfaktor und Offset. |
| `REQ`    | Event | `IN`           | Normales Ausführungsereignis – verarbeitet den aktuellen Eingangswert. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Mit Parametern | Beschreibung                            |
|----------|-------|----------------|-----------------------------------------|
| `INITO`  | EInit | –              | Bestätigung der erfolgreichen Initialisierung. |
| `CNF`    | Event | `OUT`, `VALID` | Bestätigung der Verarbeitung – liefert den skalierten Wert und das Gültigkeitssignal. |

### **Daten-Eingänge**

| Name     | Typ    | Initialwert                              | Beschreibung                          |
|----------|--------|------------------------------------------|---------------------------------------|
| `IN`     | UDINT  | `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)`      | Rohwert aus dem Feldbus.              |
| `SCALE`  | LREAL  | `LREAL#1.0`                              | Multiplikativer Skalierungsfaktor.     |
| `OFFSET` | DINT   | `DINT#0`                                 | Additiver Offset (nach Skalierung).    |

### **Daten-Ausgänge**

| Name    | Typ    | Initialwert | Beschreibung                                  |
|---------|--------|-------------|-----------------------------------------------|
| `OUT`   | LREAL  | `LREAL#0.0` | Skalierter Ausgabewert.                       |
| `VALID` | BOOL   | `FALSE`     | `TRUE`, wenn der Eingangswert als gültig erkannt wurde. |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise

Der Baustein besitzt zwei Zustände: `INIT` und `REQ`.

- **INIT-Zustand**: Bei einem `INIT`-Ereignis wird der leere Algorithmus ausgeführt (keine Aktion) und anschließend `INITO` ausgegeben. Die Parameter `SCALE` und `OFFSET` werden dabei an den Baustein übergeben, aber erst bei der nächsten `REQ`-Verarbeitung verwendet.

- **REQ-Zustand**: Bei einem `REQ`-Ereignis wird folgende Logik ausgeführt:
  1. Der eingehende Wert `IN` wird mit einem vordefinierten Schwellwert `VALID_SIGNAL_DW` (aus dem Import `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL::VALID_SIGNAL_DW`) verglichen.
  2. Wenn `IN <= DWORD_TO_UDINT(VALID_SIGNAL_DW)` gilt, wird der Eingang als gültig betrachtet. Dann wird `OUT` berechnet als:  
     `OUT := UDINT_TO_LREAL(IN) * SCALE + DINT_TO_LREAL(OFFSET)`  
     und `VALID` auf `TRUE` gesetzt.
  3. Andernfalls wird `OUT` auf `0.0` und `VALID` auf `FALSE` gesetzt. Dies signalisiert, dass der übergebene Feldbuswert ungültig ist (z. B. Fehlerwert oder Kommunikationsabbruch).

Der Initialwert von `IN` ist voreingestellt auf `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)`, einer Konstanten aus demselben Import, die einen speziellen „nicht verfügbar“-Wert repräsentiert.

## Technische Besonderheiten

- Die Gültigkeitsprüfung basiert auf zwei importierten Konstanten:
  - `VALID_SIGNAL_DW`: Obergrenze für gültige Werte.
  - `NOT_AVAILABLE_DWM`: Standardwert für nicht verfügbare Signale (wird als Initialwert für `IN` verwendet).
- Die Skalierung erfolgt in LREAL (doppelte Genauigkeit), sodass auch sehr große oder kleine Eingangswerte präzise verarbeitet werden können.
- Der Offset ist als `DINT` definiert, wird aber vor der Addition in `LREAL` konvertiert. Der gesamte Berechnungsbereich wird durch die LREAL-Darstellung abgedeckt.

## Zustandsübersicht

Der Baustein verwendet ein einfaches Zustandsdiagramm mit zwei Zuständen:

- **INIT**: Wird nach dem `INIT`-Ereignis durchlaufen. Der Algorithmus `INIT` ist leer, der Ausgang `INITO` wird getriggert.
- **REQ**: Wird nach dem `REQ`-Ereignis durchlaufen. Hier wird der Algorithmus `REQ` ausgeführt, der die Skalierung und Gültigkeitsprüfung vornimmt, und anschließend `CNF` ausgegeben.

Es gibt keine weiteren Zustände oder Schleifen.

## Anwendungsszenarien

- **Skalierung von Sensorwerten**: Ein Feldbusgerät liefert einen UDINT-Rohwert (z. B. 0 … 65535). Mit `SCALE` wird eine physikalische Größe (z. B. Druck in bar) umgerechnet, der Offset berücksichtigt Nullpunktverschiebungen.
- **Gültigkeitsprüfung**: Typische Feldbusprotokolle definieren bestimmte Bitmuster als „ungültig“. Der Baustein filtert diese Werte automatisch heraus und setzt `VALID = FALSE`.
- **Initialisierung**: Beim Systemstart kann über `INIT` der Skalierungsfaktor gesetzt werden, während der `REQ`-Zyklus regelmäßig die aktuellen Prozesswerte verarbeitet.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Bausteine sind oft allgemeine `SCALE`-Funktionen, die keine Gültigkeitsprüfung enthalten. Dieser Baustein fügt eine explizite Validierung des Feldbussignals hinzu. Andere Implementierungen könnten den Gültigkeitsbereich als Parameter oder über separate Schwellwerte konfigurierbar machen. Der vorliegende Baustein setzt feste, in der Import-Bibliothek definierte Konstanten ein, was die Konfiguration vereinfacht, aber weniger flexibel ist.

## Fazit

Der `FIELDBUS_UDINT_TO_SIGNAL_SCALED`-Funktionsblock bietet eine robuste und einfache Möglichkeit, Rohdaten aus einem Feldbus zu skalieren und gleichzeitig die Signalqualität zu bewerten. Durch die Kombination von Skalierungsfaktor und Offset sowie der integrierten Gültigkeitserkennung eignet er sich besonders für industrielle Automatisierungsanwendungen, bei denen sowohl die Umrechnung als auch die Plausibilitätsprüfung der Messwerte erforderlich ist.
# AUI_UDINT_LE


![AUI_UDINT_LE](./AUI_UDINT_LE.svg)

* * * * * * * * * *
## Einleitung
Der Baustein `AUI_UDINT_LE` führt einen Vergleich "kleiner oder gleich" (less or equal) zwischen zwei Werten vom Typ UDINT durch. Der erste Wert wird über eine unidirektionale Adapter-Schnittstelle (AUI) bereitgestellt, der zweite Wert direkt als Dateneingang. Das Ergebnis des Vergleichs wird über einen unidirektionalen Ausgangsadapter (AX) ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Service Request; löst den Vergleich aus. Der Datenwert `IN2` wird zu diesem Zeitpunkt gelesen. |

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignisausgänge. Die Ergebnisbenachrichtigung erfolgt über den Ereignisausgang des Ausgangsadapters `OUT.E1`.

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN2` | UDINT | Zweiter Eingangswert für den Vergleich. |

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Datenausgänge. Das Vergleichsergebnis wird über den Datenausgang `OUT.D1` des Ausgangsadapters bereitgestellt.

### **Adapter**
| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `IN1` | AUI (adapter::types::unidirectional::AUI) | Socket | Eingangsadapter für den ersten Vergleichswert (UDINT). |
| `OUT` | AX (adapter::types::unidirectional::AX) | Plug | Ausgangsadapter für das Vergleichsergebnis (BOOL). |

## Funktionsweise
Der Baustein realisiert die Funktion `IN1 ≤ IN2`. Interne Verarbeitung:
- Der Ereigniseingang `REQ` oder das eingehende Ereignis `IN1.E1` (über den Socket-Adapter) triggern den internen Funktionsblock `F_LE` (IEC 61131-3 Vergleich `LE`).
- Die Datenwerte `IN1` (über Adapter) und `IN2` (direkt) werden dem internen Baustein zugeführt.
- Das Ergebnis (BOOL) wird über den Ausgangsadapter `OUT` ausgegeben, sobald der interne Baustein seine Berechnung abgeschlossen hat (`F_LE.CNF` → `OUT.E1`).

## Technische Besonderheiten
- **Adapterbasierte Kommunikation**: Der erste Wert (IN1) wird nicht als klassischer Dateneingang, sondern über eine unidirektionale Adapterschnittstelle (AUI) bereitgestellt. Dies ermöglicht eine lose Kopplung in verteilten Systemen.
- **Ergebnisausgabe über Adapter**: Auch das Vergleichsergebnis wird über einen Adapter (AX) ausgegeben, was eine flexible Weiterverarbeitung erlaubt.
- **Standard-Vergleichsfunktion**: Der zugrunde liegende Algorithmus basiert auf dem etablierten IEC 61131-3 Baustein `F_LE` für `Less_or_Equal`.

## Zustandsübersicht
Der Baustein selbst besitzt keine eigenen Zustandsautomaten. Die interne Logik wird durch den Zustand des eingebetteten Bausteins `F_LE` bestimmt, der nach jedem Ereignis eine Berechnung durchführt und das Ergebnis unverzögert ausgibt.

## Anwendungsszenarien
- **Überwachung von Grenzwerten**: Prüfen, ob ein über eine Schnittstelle eingehender Wert (z.B. Sensorwert) einen festgelegten Schwellwert nicht überschreitet.
- **Steuerungslogik**: Einsatz in komplexen Ablaufsteuerungen, bei denen Bedingungen wie `Wert1 ≤ Wert2` Teil einer Entscheidungskette sind.
- **Verteilte Systeme**: Nutzung der Adapter, um Werte aus verschiedenen Komponenten einer Steuerung zu vergleichen, ohne direkte Datenleitungen zu benötigen.

## Vergleich mit ähnlichen Bausteinen
- **`AUI_UDINT_GT`** (greater than): Führt den Vergleich `IN1 > IN2` durch.
- **`AUI_UDINT_EQ`** (equal): Prüft auf Gleichheit.
- **`AUI_UDINT_NE`** (not equal): Prüft auf Ungleichheit.

Diese Bausteine haben eine identische Schnittstellenstruktur und unterscheiden sich lediglich in der Vergleichsfunktion. Der vorliegende Baustein `LE` ist speziell für die Bedingung "kleiner oder gleich" ausgelegt.

## Fazit
Der `AUI_UDINT_LE` Baustein ist ein spezialisierter Vergleichsbaustein für den Datentyp UDINT mit Adapter-Anbindung. Er eignet sich besonders für modulare und verteilte Steuerungssysteme, bei denen Werte über standardisierte Schnittstellen ausgetauscht werden. Die Orientierung an IEC 61131-3 sorgt für Interoperabilität und Wartbarkeit.
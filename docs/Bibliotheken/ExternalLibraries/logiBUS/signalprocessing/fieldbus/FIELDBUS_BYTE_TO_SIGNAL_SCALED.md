# FIELDBUS_BYTE_TO_SIGNAL_SCALED


![FIELDBUS_BYTE_TO_SIGNAL_SCALED](./FIELDBUS_BYTE_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **FIELDBUS_BYTE_TO_SIGNAL_SCALED** dient der Umsetzung eines eingehenden Byte-Werts in einen skalierten Real-Wert. Dabei wird geprüft, ob das eingehende Signal gültig ist. Ist dies der Fall, wird der Eingangswert mit einem Skalierungsfaktor multipliziert und ein Offset addiert. Andernfalls wird der Ausgang auf Null gesetzt und das Gültigkeitssignal zurückgesetzt. Der Block ist für den Einsatz in Feldbussystemen konzipiert, bei denen Sensor- oder Aktordaten als Byte übertragen werden und linearisiert oder normiert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Event | Typ | Beschreibung | Mitgeführte Daten |
|-------|-----|-------------|-------------------|
| `INIT` | EInit | Initialisierungsanforderung; setzt Skalierung und Offset | `SCALE`, `OFFSET` |
| `REQ`  | Event | Normale Verarbeitungsanforderung; wertet den Eingang `IN` aus | `IN` |

### **Ereignis-Ausgänge**
| Event | Typ | Beschreibung | Mitgeführte Daten |
|-------|-----|-------------|-------------------|
| `INITO` | EInit | Bestätigung der Initialisierung | – |
| `CNF`   | Event | Bestätigung der Verarbeitung; liefert skalierten Wert und Gültigkeit | `OUT`, `VALID` |

### **Daten-Eingänge**
| Name    | Datentyp | Initialwert | Beschreibung |
|---------|----------|-------------|--------------|
| `IN`    | BYTE     | `NOT_AVAILABLE_B` | Feldbus-Rohwert (Byte) |
| `SCALE` | REAL     | `1.0`       | Skalierungsfaktor (Multiplikator) |
| `OFFSET`| DINT     | `0`         | Additiver Offset (nach Skalierung) |

### **Daten-Ausgänge**
| Name    | Datentyp | Initialwert | Beschreibung |
|---------|----------|-------------|--------------|
| `OUT`   | REAL     | `0.0`       | Skalierter Ausgangswert |
| `VALID` | BOOL     | `FALSE`     | `TRUE`, wenn der eingehende Byte-Wert als gültig bewertet wurde |

### **Adapter**
Keine.

## Funktionsweise
Der Funktionsblock wird durch zwei Ereignisse gesteuert:

1. **Initialisierung (`INIT`)**  
   Beim Eintreffen von `INIT` werden die Parameter `SCALE` und `OFFSET` übernommen. Der dazugehörige Algorithmus (`INIT`) führt keine weiteren Berechnungen durch. Nach erfolgreicher Initialisierung wird das Ereignis `INITO` gesendet.

2. **Verarbeitung (`REQ`)**  
   Bei `REQ` wird der Wert von `IN` mit einem festen Schwellwert `VALID_SIGNAL_B` verglichen. Dieser Schwellwert wird aus dem importierten Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` bezogen.  
   - **Signal gültig:** Wenn `IN <= VALID_SIGNAL_B`, wird der Ausgangswert nach der Formel  
     `OUT := IN * SCALE + OFFSET`  
     berechnet und `VALID` auf `TRUE` gesetzt.  
   - **Signal ungültig:** Andernfalls wird `OUT` auf `0.0` und `VALID` auf `FALSE` gesetzt.  

   Anschließend wird das Ereignis `CNF` mit den aktuellen Werten von `OUT` und `VALID` gesendet.

Der initiale Wert von `IN` ist `NOT_AVAILABLE_B` – ein weiterer importierter Konstantwert, der ein nicht verfügbares Signal kennzeichnet. Dadurch wird bei erstmaligem Aufruf von `REQ` (ohne vorherige gültige Eingabe) stets eine ungültige Ausgabe erzeugt.

## Technische Besonderheiten
- Die Konstanten `NOT_AVAILABLE_B` und `VALID_SIGNAL_B` werden aus einem separaten Bibliothekspaket importiert und nicht lokal definiert. Dadurch sind sie projektweit einheitlich.
- Die Skalierung erfolgt linear: Multiplikation mit `SCALE` und Addition von `OFFSET`. Der Offset wird vor der Umrechnung in `REAL` vom Typ `DINT` nach `REAL` konvertiert.
- Der Eingang `IN` wird zunächst von `BYTE` nach `USINT` (unsigned short integer) gewandelt, um einen ganzzahligen Wertebereich 0…255 zu erhalten.
- Der Block besitzt einen expliziten Initialisierungsmodus (`INIT`), der es erlaubt, Skalierung und Offset während der Laufzeit neu zu setzen.

## Zustandsübersicht
Der Funktionsblock besitzt zwei einfache Zustände, die jeweils durch das entsprechende Ereignis aktiviert werden:

| Zustand | Auslösendes Event | Ausführbarer Algorithmus | Ausgehende Events |
|---------|-------------------|--------------------------|-------------------|
| `INIT`  | `INIT`            | `INIT` (leer)            | `INITO`           |
| `REQ`   | `REQ`             | `REQ` (Gültigkeitsprüfung + Skalierung) | `CNF` |

Es gibt keine automatischen Zustandsübergänge; jeder Zustand wird ausschließlich durch das zugehörige Ereignis angesprochen.

## Anwendungsszenarien
- **Austausch analoger Sensordaten über Feldbusse:**  
  Ein 8-Bit-Sensorwert (z. B. Temperatur 0…255) soll in physikalische Einheiten (z. B. °C) umgerechnet werden. Über `SCALE` und `OFFSET` wird die Kennlinie angepasst.
- **Fehlererkennung bei der Datenübertragung:**  
  Wenn der Feldbus bestimmte Byte-Werte als ungültig definiert (z. B. `0xFF` für „Sensorfehler“), erkennt der Block diese anhand der Schranke `VALID_SIGNAL_B` und meldet sie über `VALID = FALSE`.
- **Initialisierung von Konfigurationsparametern:**  
  Vor der ersten Verarbeitung kann über `INIT` der gewünschte Skalierungsfaktor und Offset gesetzt werden.

## Vergleich mit ähnlichen Bausteinen
- **`FIELDBUS_BYTE_TO_SIGNAL`** (ohne Skalierung):  
  Dieser Baustein gibt den Byte-Wert direkt als REAL aus, ohne Multiplikation oder Addition. Er eignet sich für Signale, die bereits in der richtigen Einheit vorliegen.
- **`FIELDBUS_BYTE_TO_SIGNAL_SCALED`** (vorliegender Baustein):  
  Bietet zusätzlich die lineare Skalierung und einen Offset. Der Anwender kann die Umrechnung flexibel anpassen, ohne den Algorithmus zu ändern.
- **`FIELDBUS_WORD_TO_SIGNAL_SCALED`**:  
  Analoger Baustein für 16-Bit-Werte (WORD) mit identischer Skalierungslogik, jedoch anderem Eingangsdatentyp.

## Fazit
Der Funktionsblock `FIELDBUS_BYTE_TO_SIGNAL_SCALED` ist ein praktisches Werkzeug für die Verarbeitung von Feldbus-Signalen im Byte-Format. Er kombiniert eine einfache Gültigkeitsprüfung mit einer frei konfigurierbaren linearen Skalierung. Durch die Verwendung importierter Konstanten ist er in einheitliche Signalverarbeitungspipelines integrierbar. Die klare Trennung von Initialisierung und Betrieb sowie die zwei Ereignisschnittstellen machen ihn zu einem robusten und leicht verständlichen Baustein für industrielle Automatisierungslösungen.
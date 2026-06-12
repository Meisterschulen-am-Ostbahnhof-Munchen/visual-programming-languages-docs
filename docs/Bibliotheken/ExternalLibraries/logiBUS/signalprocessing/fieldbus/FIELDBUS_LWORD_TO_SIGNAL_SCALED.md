# FIELDBUS_LWORD_TO_SIGNAL_SCALED


![FIELDBUS_LWORD_TO_SIGNAL_SCALED](./FIELDBUS_LWORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_LWORD_TO_SIGNAL_SCALED** dient der Umwandlung eines als **LWORD** vorliegenden Feldbus-Rohsignals in einen skalierten **LREAL**-Ausgangswert. Er spiegelt das Eingangssignal auf den Ausgang, sofern das Signal gültig ist, und wendet dabei eine lineare Skalierung an. Der Baustein ist für den Einsatz in der industriellen Automatisierung, insbesondere im Kontext von Feldbussystemen, konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Beschreibung | Mitgeführte Daten |
|----------|-----|--------------|-------------------|
| INIT | EInit | Initialisierungsanforderung: Skalierungsfaktor (SCALE) und Offset (OFFSET) setzen | SCALE, OFFSET |
| REQ | Event | Normale Ausführungsanforderung: Verarbeitung des Eingangssignals (IN) | IN |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Beschreibung | Mitgeführte Daten |
|----------|-----|--------------|-------------------|
| INITO | EInit | Bestätigung der Initialisierung | – |
| CNF | Event | Bestätigung der Ausführung | OUT, VALID |

### **Daten-Eingänge**
| Name     | Typ    | Initialwert           | Beschreibung                                  |
|----------|--------|-----------------------|-----------------------------------------------|
| IN       | LWORD  | NOT_AVAILABLE_LWM     | Feldbus-Rohsignal (LWORD)                     |
| SCALE    | LREAL  | LREAL#1.0             | Skalierungsfaktor (Multiplikation)            |
| OFFSET   | DINT   | DINT#0                | Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**
| Name   | Typ   | Initialwert | Beschreibung                                                  |
|--------|-------|-------------|---------------------------------------------------------------|
| OUT    | LREAL | LREAL#0.0   | Skalierter Ausgangswert (LREAL)                               |
| VALID  | BOOL  | FALSE       | Gibt an, ob das Eingangssignal gültig ist (TRUE = gültig)   |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein besitzt zwei Algorithmen, die durch die Ereignisse **INIT** und **REQ** ausgelöst werden.

- **INIT** (bei Ereignis `INIT`): Der Algorithmus ist leer, setzt jedoch den Ausgangs-Ereignis `INITO`. Dies ermöglicht die Initialisierung der Skalierungsparameter (SCALE und OFFSET) über den INIT-Aufruf, ohne dass eine sofortige Verarbeitung stattfindet.
- **REQ** (bei Ereignis `REQ`): Führt die eigentliche Signalverarbeitung durch:
  1. Das Eingangssignal `IN` (LWORD) wird als vorzeichenloser Ganzzahlwert interpretiert (`LWORD_TO_ULINT`).
  2. Dieser Wert wird mit einem intern als gültig definierten Grenzwert **VALID_SIGNAL_LW** (ebenfalls LWORD, importierte Konstante) verglichen. Der Vergleich erfolgt auf ULINT-Ebene.
  3. **Gültigkeit**: Ist `IN` ≤ `VALID_SIGNAL_LW`, so gilt das Signal als gültig:
     - `OUT` = `(ULINT_TO_LREAL(IN)) * SCALE + DINT_TO_LREAL(OFFSET)`
     - `VALID` = `TRUE`
  4. **Ungültigkeit**: Andernfalls wird das Signal als ungültig betrachtet:
     - `OUT` = `0.0`
     - `VALID` = `FALSE`
  5. Nach der Berechnung wird der Ausgangs-Ereignis `CNF` gesendet.

Die Skalierung erfolgt also linear: `OUT = IN_als_LREAL * SCALE + OFFSET`. Der Standardwert von `SCALE` ist 1.0, der von `OFFSET` ist 0, sodass ohne Anpassung eine identische Übertragung stattfindet.

## Technische Besonderheiten
- **Gültigkeitsprüfung**: Der Baustein nutzt zwei importierte Konstanten:
  - `NOT_AVAILABLE_LWM`: Initialwert für den Eingang `IN` (kennzeichnet „nicht verfügbar“).
  - `VALID_SIGNAL_LW`: Grenzwert, bis zu dem ein Signal als gültig gilt (inklusive).
  Der Vergleich erfolgt durch Umwandlung beider LWORD-Werte in ULINT, sodass auch negative Werte (als Bitmuster) korrekt interpretiert werden.
- **Typkonvertierung**: Der Rohwert wird von LWORD über ULINT (64-Bit) in LREAL konvertiert, wobei potenzielle Präzisionsverluste bei sehr großen ULINT-Werten zu beachten sind.
- **Skalierungsparameter**: `SCALE` (LREAL) und `OFFSET` (DINT) werden nur während des INIT-Ereignisses gesetzt, bleiben dann aber für alle folgenden REQ-Aufrufe unverändert.
- **Ereignissteuerung**: Der Baustein hat eine einfache Zustandsmaschine mit zwei Zuständen und erfordert eine explizite Initialisierung vor der ersten Verarbeitung.

## Zustandsübersicht
| Zustand | Ausgelöst durch | Ausgabealgorithmus | Ereignisausgang | Beschreibung |
|---------|----------------|--------------------|-----------------|--------------|
| INIT    | Ereignis INIT  | INIT               | INITO           | Initialisierung: Skalierungsparameter übernehmen |
| REQ     | Ereignis REQ   | REQ                | CNF             | Signalverarbeitung: Skalierung und Gültigkeitsprüfung |

Der Baustein wechselt zwischen diesen beiden Zuständen nur durch die entsprechenden Ereignisse. Es gibt keinen expliziten Übergang nach der Initialisierung in einen Wartezustand; der Baustein bleibt so lange im letzten Zustand, bis ein neues Ereignis eintrifft.

## Anwendungsszenarien
- **Analogwerte aus dem Feldbus**: Ein LWORD-Rohwert von einem analogen Eingangsmodul (z. B. 0…10 V, skaliert als Rohwert) wird mit Hilfe von SCALE und OFFSET in einen physikalischen Wert (z. B. Druck, Temperatur) umgerechnet.
- **Gültigkeitsfilter**: Signale, die außerhalb des zulässigen Bereichs liegen (z. B. Drahtbruch oder Überlauf), werden durch die Gültigkeitsprüfung erkannt und als ungültig markiert, während der Ausgang auf 0 gesetzt wird.
- **Initialisierung von Parametern**: Die Skalierung kann beim Start der Steuerung über das INIT-Ereignis konfiguriert werden, ohne dass die eigentliche Verarbeitung bereits läuft.

## Vergleich mit ähnlichen Bausteinen
- **FIELDBUS_LREAL_TO_SIGNAL_SCALED**: Ein analoger Baustein für LREAL-Eingänge, der eine ähnliche Gültigkeitsprüfung und Skalierung bietet.
- **FIELDBUS_SINT_TO_SIGNAL_SCALED**: Für vorzeichenbehaftete 8-Bit-Werte.
- **Einfache Skalierer ohne Gültigkeitsprüfung**: Bausteine wie `SCALE` oder `MUL_ADD` bieten nur die mathematische Operation, jedoch keine Feldbus-spezifische Gültigkeitserkennung.

Der vorliegende Baustein kombiniert die Gültigkeitsprüfung (über den Grenzwert `VALID_SIGNAL_LW`) mit einer linearen Skalierung und eignet sich daher besonders für Feldbus-Anwendungen, bei denen die Gültigkeit des Signals vor der Weiterverarbeitung sichergestellt werden muss.

## Fazit
**FIELDBUS_LWORD_TO_SIGNAL_SCALED** ist ein kompakter, aber leistungsfähiger Funktionsblock zur Verarbeitung von Feldbus-Signalen im LWORD-Format. Er bietet eine einfache Skalierung, eine integrierte Gültigkeitsprüfung und eine saubere Trennung von Initialisierung und Ausführung. Durch die Verwendung standardisierter Importe (`VALID_SIGNAL_LW`) lässt er sich leicht in bestehende Bibliotheken integrieren und an spezifische Feldbusprotokolle anpassen. Der Baustein ist unter der Eclipse Public License 2.0 verfügbar und eignet sich für den Einsatz in industriellen Steuerungssystemen mit IEC 61499-konformen Laufzeitumgebungen.
# FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE


![FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE](./FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` dient zur Aufbereitung eines 16‑Bit‑Feldbussignals (Typ `UINT`) in einen skalierten Realwert. Dabei wird das eingehende Wort in ein oberes und ein unteres Byte zerlegt, jedes Byte mit einem eigenen Skalierungsfaktor multipliziert und ein Offset addiert. Zusätzlich wird ein Gültigkeitssignal (`VALID`) ausgegeben, das auf einem vorgegebenen Schwellwert basiert. Der FB eignet sich besonders für Protokolle, die zwei Messgrößen (z. B. Temperatur und Druck) in einem einzigen Register kodieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ   | Beschreibung                                           |
|----------|-------|--------------------------------------------------------|
| `INIT`   | EInit | Initialisierungsanforderung (Parameterübernahme)       |
| `REQ`    | Event | Normale Ausführungsanforderung (Verarbeitung von `IN`) |

### **Ereignis-Ausgänge**
| Ereignis | Typ   | Beschreibung                               |
|----------|-------|--------------------------------------------|
| `INITO`  | EInit | Bestätigung der Initialisierung            |
| `CNF`    | Event | Bestätigung der Ausführung (nach `REQ`)    |

### **Daten-Eingänge**
| Variable    | Typ    | Initialwert                | Beschreibung                                           |
|-------------|--------|----------------------------|--------------------------------------------------------|
| `IN`        | UINT   | `WORD_TO_UINT(NOT_AVAILABLE_WM)` | Rohwert vom Feldbus                                    |
| `SCALE_HIGH`| REAL   | `0.256`                    | Skalierungsfaktor für das obere Byte                   |
| `SCALE_LOW` | REAL   | `0.001`                    | Skalierungsfaktor für das untere Byte                  |
| `OFFSET`    | DINT   | `0`                        | Offset, der nach der Skalierung addiert wird (in REAL) |

### **Daten-Ausgänge**
| Variable | Typ    | Initialwert | Beschreibung                                      |
|----------|--------|-------------|---------------------------------------------------|
| `OUT`    | REAL   | `0.0`       | Skalierter Ausgabewert                            |
| `VALID`  | BOOL   | `FALSE`     | `TRUE`, wenn das Eingangssignal als gültig erkannt wurde |

### **Adapter**
Keine.

## Funktionsweise
1. **Initialisierung** (`INIT`):  
   Der Algorithmus `INIT` ist leer, die Parameter `SCALE_HIGH`, `SCALE_LOW` und `OFFSET` werden jedoch über die `With`-Beziehung mit dem Ereignis verknüpft und können so beim Aufruf von `INIT` gesetzt werden.

2. **Normale Verarbeitung** (`REQ`):  
   - Der Eingangswert `IN` wird mit einer Konstanten `VALID_SIGNAL_W` (aus dem importierten Namen `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL::VALID_SIGNAL_W`) verglichen:  
     `IF (IN <= WORD_TO_UINT(VALID_SIGNAL_W)) THEN`  
   - Falls die Bedingung **wahr** ist (Signal gültig):
     - Das obere Byte wird durch Rechts-Shift um 8 Bit und Maskierung mit `0x00FF` extrahiert:  
       `highByte := (IN >> 8) & 0xFF`
     - Das untere Byte wird direkt durch Maskierung gewonnen:  
       `lowByte := IN & 0xFF`
     - Beide Bytes werden in `REAL` gewandelt, mit den jeweiligen Skalierungsfaktoren multipliziert und der Offset addiert:  
       `OUT := highByte * SCALE_HIGH + lowByte * SCALE_LOW + OFFSET`
     - `VALID` wird auf `TRUE` gesetzt.
   - Falls die Bedingung **falsch** ist (ungültiges Signal):
     - `OUT` wird auf `0.0` gesetzt.
     - `VALID` wird auf `FALSE` gesetzt.
   - Anschließend wird das Ereignis `CNF` ausgegeben.

## Technische Besonderheiten
- **Compound‑Skalierung**: Der FB erlaubt getrennte Skalierung für das obere und untere Byte eines 16‑Bit‑Wortes. Dies ist nützlich, wenn zwei unterschiedliche physikalische Größen in einem Register zusammengefasst sind.
- **Gültigkeitsprüfung**: Der Vergleich mit `VALID_SIGNAL_W` definiert einen Schwellwert. Werte oberhalb dieses Schwellwerts werden als ungültig betrachtet – typisch für Feldbus‑Fehlerkodierungen (z. B. „Not Available“).
- **Parametrierung über `INIT`**: Die Skalierungsfaktoren und der Offset können einmalig über das `INIT`-Ereignis gesetzt werden, sodass sie während des Betriebs konstant bleiben.
- **Initialwerte**: Die vorgegebenen Werte (`SCALE_HIGH=0.256`, `SCALE_LOW=0.001`, `OFFSET=0`) sind als Beispielwerte anzusehen; sie sollten an die konkrete Anwendung angepasst werden.

## Zustandsübersicht
Der FB besitzt zwei EC‑Zustände:

- **INIT**: Führt den leeren Algorithmus `INIT` aus und verlässt den Zustand über den Ausgang `INITO`.
- **REQ**: Führt den Algorithmus `REQ` aus, der die gesamte Signalverarbeitung durchführt, und verlässt den Zustand über den Ausgang `CNF`.

Der FB ist als SimpleFB implementiert; es gibt keine weiteren Zustände wie IDLE oder WAIT.

## Anwendungsszenarien
- **Zwei‑in‑eins‑Sensorwerte**: Ein Temperatur‑ und ein Drucksensor liefern ihre Werte als je 8‑Bit‑Zahlen in einem 16‑Bit‑Register. Der FB wandelt diese mit getrennten Skalierungen in physikalische Einheiten um.
- **Fehlererkennung im Feldbus**: Wenn das Feldbusprotokoll für ungültige Messwerte einen bestimmten Bit‑Code (z. B. alle Bits 1) vorsieht, kann über den Schwellwert `VALID_SIGNAL_W` die Gültigkeit erkannt werden.
- **Nachverarbeitung von Logging‑Daten**: Rohdaten aus einem Feldbus‑Logger werden mit den ursprünglichen Skalierungen wieder in die physikalischen Größen zurückgerechnet.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaft | Unterschied |
|----------|-------------|-------------|
| `SCALE` (z. B. nach IEC 61131) | Linearer Faktor und Offset auf den gesamten Wert | Keine Aufteilung in Bytes, keine Gültigkeitsprüfung |
| `LINEAR` (Feldbus‑Standard) | Gleitender Mittelwert oder einfache lineare Transformation | Kein Compound‑Ansatz |
| `UINT_TO_REAL` | Direkte Typumwandlung | Keine Skalierung, keine Fehlererkennung |

Dieser FB kombiniert als einziger die Byte‑trennung mit einer zweifachen Skalierung und einer integrierten Gültigkeitserkennung, was ihn für spezielle Feldbus‑Protokolle mit zusammengesetzten Registern besonders geeignet macht.

## Fazit
Der `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` ist ein leistungsfähiger Funktionsblock zur Aufbereitung von 16‑Bit‑Feldbussignalen, die zwei unabhängige Messwerte in einem Register kodieren. Durch die getrennte Skalierung von High‑ und Low‑Byte sowie die integrierte Gültigkeitsprüfung lassen sich komplexe Sensor‑Register effizient und zuverlässig in physikalische Größen umrechnen. Die Parametrierung über das `INIT`-Ereignis und die klare Trennung von Initialisierung und Betrieb machen den FB wiederverwendbar und anpassbar.
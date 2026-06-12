# ARR_MIN


![ARR_MIN](./ARR_MIN.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ARR_MIN** ermittelt das Minimum aller Elemente eines eindimensionalen Arrays vom Typ `INT`. Der Baustein erwartet ein dynamisches Array (`ARRAY[*]`) als Ein-/Ausgangsparameter und gibt das kleinste gefundene Element über einen separaten Datenausgang aus. Die Berechnung wird durch das Ereignis `REQ` angestoßen; das Ergebnis wird nach Fertigstellung mit dem Ereignis `CNF` quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Mit Daten |
|---------|-----------|
| `REQ`   | `A`       |

### **Ereignis-Ausgänge**
| Ereignis | Mit Daten |
|---------|-----------|
| `CNF`   | `A` (und leerer Datenausgang) |

### **Daten-Eingänge**
| Name | Typ            | Kommentar |
|------|----------------|-----------|
| `A`  | `ARRAY[*] OF INT` | Eingabearray (Ein-/Ausgang) |

### **Daten-Ausgänge**
| Name | Typ  | Kommentar |
|------|------|-----------|
| (unbenannt) | `INT` | Minimalwert des Arrays |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Der Algorithmus initialisiert eine temporäre Variable `currentMin` mit dem Wert des ersten Array-Elements (ermittelt über `LOWER_BOUND(A,1)`).
2. Anschließend wird das Array von Index `LOWER_BOUND(A,1)+1` bis `UPPER_BOUND(A,1)` durchlaufen.
3. In jeder Iteration wird der aktuelle Wert mit `currentMin` verglichen und das Minimum mit der Funktion `MIN()` aktualisiert.
4. Nach Abschluss der Schleife wird der endgültige Minimalwert über den unbenannten Datenausgang ausgegeben und das Ereignis `CNF` gesendet.

Die Berechnung erfolgt rein sequenziell innerhalb eines einzigen Ausführungsschritts, die Laufzeit steigt linear mit der Array-Größe.

## Technische Besonderheiten
- **Dynamisches Array**: Der FB arbeitet mit `ARRAY[*] OF INT`, d.h. die tatsächliche Größe des Arrays wird erst zur Laufzeit über die systemeigenen Funktionen `LOWER_BOUND` und `UPPER_BOUND` bestimmt.
- **Paketzuordnung**: Der Baustein gehört zum Paket `logiBUS::utils::dyn_arr` und ist für den Einsatz in Umgebungen vorgesehen, die dynamische Arrays unterstützen.
- **Ein-/Ausgangsparameter**: Der Parameter `A` ist als `VAR_IN_OUT` deklariert – das Array wird sowohl gelesen als auch (hier nicht verändert) über den Ereignisausgang `CNF` weitergegeben.
- **Keine Zustandsmaschine**: Der Funktionsblock arbeitet rein funktional; es gibt keine internen Zustände oder Verzögerungen.

## Zustandsübersicht
Der FB kennt nur zwei implizite Zustände:
- **Idle**: Warten auf ein `REQ`-Ereignis.
- **Processing**: Nach Eintreffen von `REQ` wird die Berechnung ausgeführt, unmittelbar danach wird `CNF` gesendet und der FB kehrt in den Idle-Zustand zurück.

Es gibt keine mehrfachen Zustände, Warteschleifen oder zeitgesteuerte Abläufe.

## Anwendungsszenarien
- **Sensorfeldanalyse**: Ermittlung der kleinsten Temperatur in einer Reihe von Messwerten.
- **Qualitätskontrolle**: Suche nach dem minimalen Ausschussmaß in einer Produktionscharge.
- **Optimierung**: Bestimmung des günstigsten Preises aus einer Liste von Angeboten.
- **Vergleichsoperationen**: Als Grundbaustein für weitere statistische Auswertungen (z.B. zusammen mit Maximum, Summe).

## Vergleich mit ähnlichen Bausteinen
- **MIN (IEC 61131-3)**: Der klassische MIN-Baustein vergleicht zwei skalare Werte. `ARR_MIN` erweitert dieses Konzept auf ein gesamtes Array und spart so eine iterative Verkettung.
- **ARR_MAX**: Ein logisches Gegenstück für das Maximum; der Algorithmus unterscheidet sich nur in der Vergleichsfunktion (`MIN` vs. `MAX`).
- **Statistische Bausteine**: `ARR_MIN` ist ein Spezialfall allgemeiner Aggregationsfunktionen (z.B. SUM, MEAN). Der Fokus liegt auf dem Minimum, was eine einfache und schnelle Implementierung ermöglicht.

## Fazit
`ARR_MIN` bietet eine kompakte und effiziente Lösung zur Bestimmung des Minimums in dynamischen Integer-Arrays. Dank des einfachen Request/Confirm-Protokolls und der sauberen Paketstruktur lässt er sich leicht in vorhandene 4diac-Industrieanwendungen integrieren. Die Verwendung von `LOWER_BOUND`/`UPPER_BOUND` macht ihn unabhängig von der tatsächlichen Array-Größe und erlaubt flexible Anpassungen zur Laufzeit.
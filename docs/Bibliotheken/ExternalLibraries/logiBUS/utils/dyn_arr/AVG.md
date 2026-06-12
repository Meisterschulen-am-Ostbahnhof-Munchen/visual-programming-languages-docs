# AVG


![AVG](./AVG.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AVG** (Array Average) berechnet den arithmetischen Mittelwert (Durchschnitt) aller Elemente eines Integer-Arrays. Er ist für den Einsatz in der Steuerungstechnik konzipiert und ermöglicht eine schnelle statistische Auswertung von Messwerten oder Prozessdaten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Event | Mit Daten |
|---|---|
| `REQ` | `A` |

### **Ereignis-Ausgänge**
| Event | Mit Daten |
|---|---|
| `CNF` | *(Ergebnis-Ausgang)*, `A` |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Kommentar |
|---|---|---|---|
| `A` | `ARRAY[*] OF INT` | – | Array von Ganzzahlen, dessen Durchschnitt berechnet wird (InOut-Variable) |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Kommentar |
|---|---|---|---|
| *(kein Name)* | `REAL` | – | Ergebnis des Durchschnittswerts |

### **Adapter**
Keine.

## Funktionsweise
1. Der Baustein wird durch das Ereignis `REQ` aktiviert. Dabei wird das Daten-Array `A` übernommen.
2. Intern wird eine Schleife von `LOWER_BOUND(A,1)` bis `UPPER_BOUND(A,1)` durchlaufen, um alle Elemente zu summieren.
3. Die Anzahl der Elemente wird aus `UPPER_BOUND(A,1) - LOWER_BOUND(A,1) + 1` ermittelt.
4. Die Summe wird als `DINT` kumuliert und anschließend durch die Anzahl dividiert. Das Ergebnis wird in einen `REAL`-Wert umgewandelt und am Ausgang bereitgestellt.
5. Nach Abschluss der Berechnung wird das Ereignis `CNF` ausgegeben. Der Ausgangswert steht dann zur Verfügung.

## Technische Besonderheiten
- **Dynamische Array-Größe**: Der Baustein akzeptiert Arrays beliebiger Länge (gekennzeichnet durch `ARRAY[*]`), was eine flexible Anpassung an unterschiedliche Datenmengen erlaubt.
- **Typumwandlungen**: Die Summe wird als `DINT` (Doppelwort) geführt, um Überläufe bei großen Arrays zu vermeiden. Die Division erfolgt nach Umwandlung in `REAL`, sodass ein Gleitkommaergebnis entsteht.
- **Keine Zustandsmaschine**: Der Baustein ist rein funktional aufgebaut – auf einen `REQ` folgt unmittelbar ein `CNF`. Es gibt keine internen Zustände oder Verzögerungen.

## Zustandsübersicht
Da es sich um einen **kombinatorischen Funktionsblock** handelt, existieren keine expliziten Zustände. Der Ablauf ist:

- Initial: Warten auf `REQ`
- Nach `REQ`: Berechnung und sofortige Ausgabe von `CNF`

## Anwendungsszenarien
- **Mittelwertbildung von Sensordaten**: Glättung von Messwerten (z. B. Temperatur, Druck) über einen definierten Messzyklus.
- **Durchschnittsberechnung in Chargenprozessen**: Ermittlung des mittleren Füllstands, Gewichts oder anderer Prozessgrößen.
- **Statistische Auswertung in Qualitätskontrollen**: Beispielsweise Berechnung des Durchmessers mehrerer Prüflinge als Gleitkommawert zur Genauigkeitsanalyse.

## Vergleich mit ähnlichen Bausteinen
| Merkmal | **AVG** | Typischer IEC‑61131-3 AVG-Baustein |
|---|---|---|
| **Parametrierung** | Dynamisch via Array (kein Limit) | Oft statische Array-Größe oder Listen |
| **Ereignisgesteuert** | Ja (REQ/CNF) | Nein (reine Funktion) |
| **Ausgabetyp** | `REAL` | Meist `REAL` oder `LREAL` |
| **Überlaufschutz** | Summe als `DINT` | Abhängig von Implementierung |

Der vorliegende Baustein kombiniert die IEC‑61499 Ereignissteuerung mit der kompakten Logik eines IEC‑61131-3 Durchschnittsbausteins und eignet sich daher besonders für verteilte Automatisierungssysteme.

## Fazit
Der FB **AVG** bietet eine einfache und effiziente Möglichkeit, den Durchschnitt eines ganzzahligen Arrays in Echtzeit zu berechnen. Seine dynamische Array-Unterstützung und die klare Ereignisschnittstelle machen ihn zu einem universellen Werkzeug für Mittelwertbildungen in industriellen Steuerungsanwendungen. Die saubere Integration in die 4diac-IDE und die transparente Berechnungslogik gewährleisten eine hohe Wiederverwendbarkeit und Verständlichkeit.
# FIELDBUS_LWORD_TO_SIGNAL


![FIELDBUS_LWORD_TO_SIGNAL](./FIELDBUS_LWORD_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_LWORD_TO_SIGNAL** dient der Umwandlung eines LWORD-Wertes aus einem Feldbussystem in ein gültiges Signal. Er übernimmt eine Eingangsgröße und gibt diese nur dann unverändert weiter, wenn ihr Wert innerhalb eines definierten gültigen Bereichs liegt. Andernfalls wird ein Nullwert ausgegeben und die Gültigkeit als `FALSE` signalisiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Normale Ausführungsanforderung (mit Daten-Eingang `IN`) |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Ausführungsbestätigung (mit Daten-Ausgängen `OUT` und `VALID`) |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| IN   | LWORD | `NOT_AVAILABLE_LWM` | Eingangswert vom Feldbus |

*Hinweis:* `NOT_AVAILABLE_LWM` ist eine im Projekt definierte Konstante (z. B. `LWORD#16#FFFFFFFFFFFFFFFF`), die einen ungültigen oder nicht verfügbaren Wert repräsentiert.

### **Daten-Ausgänge**
| Name  | Typ    | Initialwert                      | Kommentar |
|-------|--------|----------------------------------|-----------|
| OUT   | LWORD  | `LWORD#16#0000000000000000`      | Gefilterter Ausgangswert (0 bei ungültigem Signal) |
| VALID | BOOL   | `FALSE`                          | Gültigkeitsflag (`TRUE` wenn Signal gültig) |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein wird durch ein Ereignis am Eingang `REQ` aktiviert. Dabei wird der aktuelle Wert von `IN` ausgelesen und gemäß folgender Logik verarbeitet:

1. Der eingehende LWORD-Wert wird in eine vorzeichenlose Ganzzahl (ULINT) konvertiert.
2. Dieser Wert wird mit einer ebenfalls als ULINT interpretierten Konstanten `VALID_SIGNAL_LW` verglichen.  
   - Ist der Eingangswert **kleiner oder gleich** dieser Schwelle, gilt das Signal als gültig:  
     - `OUT` erhält den Wert von `IN`.  
     - `VALID` wird auf `TRUE` gesetzt.  
   - Andernfalls (Wert größer als Schwelle) wird das Signal als ungültig betrachtet:  
     - `OUT` wird auf Null (`LWORD#16#0000000000000000`) gesetzt.  
     - `VALID` wird auf `FALSE` gesetzt.
3. Nach Abschluss der Verarbeitung wird das Ereignis `CNF` ausgegeben, um die Fertigstellung zu bestätigen.

Die Konstante `VALID_SIGNAL_LW` definiert die Obergrenze des gültigen Wertebereichs. Übliche Belegungen sind beispielsweise `LWORD#16#0000FFFFFFFFFFFF` oder ähnliche Bereiche, die vom Feldbusprotokoll vorgegeben werden.

## Technische Besonderheiten
- **Typkonvertierung:** Der Vergleich erfolgt nach Umwandlung beider LWORD-Werte in ULINT mittels `LWORD_TO_ULINT`. Dadurch werden die Werte als vorzeichenlose 64‑Bit‑Ganzzahlen interpretiert, was einen konsistenten Vergleich unabhängig von bitmusterspezifischen Interpretationen ermöglicht.
- **Verwendung projektweiter Konstanten:** Die Werte `NOT_AVAILABLE_LWM` (Initialwert für `IN`) und `VALID_SIGNAL_LW` (Grenzwert) werden über Importe aus einem gemeinsamen Signalverarbeitungs‑Package bezogen. Sie sind nicht im Baustein selbst festgelegt und können somit global angepasst werden.
- **Keine weitere Zustandsmaschine:** Der Baustein besitzt nur einen einzigen Zustand (`REQ`), der nach Ausführung des Algorithmus sofort wieder verlassen wird. Es gibt keine internen Verzögerungen oder Warteschleifen.

## Zustandsübersicht
| Zustand | Beschreibung | Aktion |
|---------|--------------|--------|
| REQ     | Wartet auf ein Ereignis am Eingang `REQ`. | Führt den Algorithmus `REQ` aus (Prüfung und ggf. Filterung) und sendet anschließend das Ereignis `CNF`. |

Der Baustein kehrt nach jeder Ausführung in den Zustand `REQ` zurück, sodass er nach jeder Verarbeitung sofort wieder bereit für einen neuen Auftrag ist.

## Anwendungsszenarien
- **Feldbus‑Signalvalidierung:** Einsatz in Automatisierungssystemen, bei denen analoge oder digitale Signale über einen Feldbus (z. B. PROFIBUS, CANopen) empfangen werden. Der Baustein filtert Werte, die außerhalb des zulässigen Bereichs liegen (z. B. Fehler‑ oder Initialisierungswerte), und gibt stattdessen einen definierten Nullwert aus.
- **Sicherheitsgerichtete Anwendungen:** Wenn das Feldbusprotokoll bestimmte Bitmuster für „Signal nicht verfügbar“ oder „Fehler“ vorsieht, können diese durch die Grenzwertprüfung erkannt und als ungültig markiert werden.
- **Datenvorverarbeitung vor logischen Verknüpfungen:** Der Ausgang `VALID` kann direkt als Freigabe für nachfolgende Funktionsbausteine verwendet werden, sodass diese nur bei gültigen Eingangssignalen aktiviert werden.

## Vergleich mit ähnlichen Bausteinen
- **Einfache Filter (z. B. `FIELDBUS_LWORD_FILTER`):** Diese führen meist eine reine Grenzwertprüfung ohne Gültigkeitsflag durch. Der hier beschriebene Baustein bietet zusätzlich den booleschen Ausgang `VALID`, der die Entscheidungsfindung in der Steuerung erleichtert.
- **Signalumsetzer (z. B. `LWORD_TO_REAL`):** Diese konvertieren den Datentyp, prüfen aber nicht die Gültigkeit des Ursprungswerts. Der Baustein `FIELDBUS_LWORD_TO_SIGNAL` kombiniert Validierung und optionale Konvertierung (hier als 1:1‑Durchleitung bei Gültigkeit).
- **Wächterbausteine (z. B. `WATCHDOG`):** Diese überwachen lediglich die Aktualität des Signals, nicht dessen Wertebereich. Der vorliegende Baustein ergänzt die Wertebereichsprüfung.

## Fazit
Der Funktionsblock `FIELDBUS_LWORD_TO_SIGNAL` ist ein einfaches, aber effektives Werkzeug zur Aufbereitung von Feldbus‑LWORD‑Signalen. Durch die Kombination von Bereichsprüfung und Ausgabe eines Gültigkeitsflags wird eine saubere Trennung von gültigen und ungültigen Werten erreicht. Die Verwendung projektweiter Konstanten sorgt für Flexibilität, während die klare Zustandslogik eine zuverlässige und schnelle Verarbeitung gewährleistet. Er eignet sich besonders für Anwendungen, in denen Fehlersignale oder Initialisierungswerte sicher erkannt und weitergeleitet werden müssen.
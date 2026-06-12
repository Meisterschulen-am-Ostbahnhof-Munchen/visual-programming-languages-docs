# FIELDBUS_WORD_TO_SIGNAL


![FIELDBUS_WORD_TO_SIGNAL](./FIELDBUS_WORD_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock FIELDBUS_WORD_TO_SIGNAL dient der einfachen Signalfilterung in Feldbusanwendungen. Er spiegelt einen eingehenden WORD-Wert am Ausgang wider, sofern das Signal als gültig eingestuft wird. Ein boolescher Ausgang zeigt den Gültigkeitsstatus an. Die Implementierung erfolgt anhand eines Vergleichs mit einer extern definierten Grenzkonstante.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Normaler Ausführungsauftrag; getriggert durch den Eingang IN. |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der Ausführung; wird nach Abschluss der Verarbeitung ausgegeben. |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| IN | WORD | NOT_AVAILABLE_WM | Eingangswert, der auf Gültigkeit geprüft wird. |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| OUT | WORD | 16#0000 | Gefilterter Ausgangswert (nur bei gültigem Signal). |
| VALID | BOOL | FALSE | TRUE, wenn das Eingangssignal als gültig erkannt wurde. |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein arbeitet mit einem einfachen Algorithmus:
1. Beim Eintreffen des Ereignisses **REQ** wird der eingehende Wert **IN** ausgelesen.
2. Der Wert wird mittels `WORD_TO_UINT` in einen vorzeichenlosen Integer konvertiert.
3. Dieser wird mit der externen Konstanten `VALID_SIGNAL_W` verglichen.  
   – Ist der konvertierte Wert **kleiner oder gleich** `VALID_SIGNAL_W`, wird **IN** direkt an **OUT** übernommen und **VALID** auf `TRUE` gesetzt.  
   – Andernfalls wird **OUT** auf `16#0000` zurückgesetzt und **VALID** auf `FALSE`.
4. Anschließend wird das Ereignis **CNF** ausgelöst.

Der Initialwert des Eingangs `IN` ist `NOT_AVAILABLE_WM`, sodass der Baustein im Grundzustand ein ungültiges Signal signalisiert.

## Technische Besonderheiten
- **Externe Konstanten:** Die Vergleichsgrenze `VALID_SIGNAL_W` sowie der Standard‑Unavailable‑Wert `NOT_AVAILABLE_WM` werden aus dem Package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` importiert. Ihre Werte sind außerhalb des Bausteins definiert.
- **Datentypkonvertierung:** Der Vergleich erfolgt nach der Umwandlung von `WORD` nach `UINT` (`WORD_TO_UINT`), um einen vorzeichenlosen numerischen Vergleich zu ermöglichen.
- **Initialwerte:** Der Ausgang `OUT` beginnt mit `16#0000` und `VALID` mit `FALSE`. Der Eingang `IN` startet mit dem als ungültig markierten Wert `NOT_AVAILABLE_WM`.
- **Einfache Zustandsmaschine:** Es existiert nur ein einziger Ausführungszustand (REQ) – der Baustein ist ereignisgesteuert und verweilt nicht in weiteren Zuständen.

## Zustandsübersicht
Der Funktionsblock besitzt genau einen Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| **REQ** | Führt den Algorithmus aus, setzt die Ausgänge entsprechend und sendet das Bestätigungsereignis **CNF**. |

Es gibt keine Schleifen oder Verzweigungen in der Zustandsmaschine; jeder Aufruf von REQ wird einmalig durchlaufen.

## Anwendungsszenarien
- **Feldbus‑Signalfilterung:** Überprüfung, ob ein von einem Feldbus stammender WORD‑Wert innerhalb eines gültigen Bereichs liegt (z. B. Sensorwerte, Steuerbefehle).
- **Plausibilitätsprüfung:** Unterdrücken von Werten, die als „nicht verfügbar“ oder „fehlerhaft“ markiert sind (dargestellt durch `NOT_AVAILABLE_WM`).
- **Datenkonsistenz:** Einsatz als einfaches Tor (Gate) in industriellen Steuerungen, das nur gültige Daten an nachfolgende Logik weitergibt.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Funktionsbausteine wie **FIELDBUS_SIGNAL_FILTER** oder **VALUE_CHECK** führen ebenfalls Vergleiche mit Schwellwerten durch. Der Vorteil von `FIELDBUS_WORD_TO_SIGNAL` liegt in der direkten Integration der Gültigkeitskennung (`VALID`) und der Verwendung von vordefinierten Konstanten aus der Feldbus‑Bibliothek, was eine standardisierte Handhabung von „nicht verfügbar“‑Zuständen ermöglicht. Im Gegensatz zu generischen Mux‑Bausteinen ist die Logik hier auf den spezifischen Einsatz im Feldbuskontext optimiert.

## Fazit
Der Funktionsblock `FIELDBUS_WORD_TO_SIGNAL` bietet eine kompakte und zuverlässige Möglichkeit, Feldbussignale auf Gültigkeit zu prüfen und nur als gültig erkannte Werte weiterzuleiten. Durch die Verwendung von importierten Konstanten wird eine konsistente Definition von Gültigkeitsgrenzen und Unavailable‑Werten über das gesamte Projekt hinweg gewährleistet. Der Baustein eignet sich besonders für sicherheitskritische Anwendungen, in denen ungültige Daten erkannt und unterdrückt werden müssen.
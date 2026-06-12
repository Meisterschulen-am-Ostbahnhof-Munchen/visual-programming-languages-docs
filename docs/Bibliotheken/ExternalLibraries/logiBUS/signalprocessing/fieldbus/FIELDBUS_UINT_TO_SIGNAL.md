# FIELDBUS_UINT_TO_SIGNAL


![FIELDBUS_UINT_TO_SIGNAL](./FIELDBUS_UINT_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein FIELDBUS_UINT_TO_SIGNAL dient der Verarbeitung von Feldbussignalen. Er spiegelt einen eingehenden UINT-Wert auf den Ausgang, sofern dieser als gültig eingestuft wird. Die Gültigkeit wird anhand eines Vergleichs mit einem konfigurierten Schwellwert (VALID_SIGNAL_W) bestimmt. Liegt der Eingangswert über diesem Schwellwert, wird der Ausgang zurückgesetzt und das Signal als ungültig markiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ | Event | Normaler Ausführungsanstoß (verbunden mit IN) |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF | Event | Bestätigung der Ausführung (verbunden mit OUT und VALID) |

### **Daten-Eingänge**
| Name | Datentyp | Initialwert | Kommentar |
|------|----------|-------------|-----------|
| IN | UINT | WORD_TO_UINT(NOT_AVAILABLE_WM) | Eingangswert (rohes Feldbussignal) |

### **Daten-Ausgänge**
| Name | Datentyp | Initialwert | Kommentar |
|------|----------|-------------|-----------|
| OUT | UINT | 16#0000 | Gefilterter Ausgangswert |
| VALID | BOOL | FALSE | TRUE, wenn das Signal als gültig erkannt wurde |

### **Adapter**
Keine.

## Funktionsweise
Bei jedem REQ-Ereignis wird der Algorithmus REQ ausgeführt:
1. Der eingehende Wert IN wird mit der Konstanten `VALID_SIGNAL_W` verglichen.
2. Ist `IN <= WORD_TO_UINT(VALID_SIGNAL_W)`, so gilt das Signal als gültig:
   - `OUT` erhält den Wert von `IN`.
   - `VALID` wird auf TRUE gesetzt.
3. Andernfalls (Signal ungültig):
   - `OUT` wird auf 0 zurückgesetzt.
   - `VALID` wird auf FALSE gesetzt.
4. Anschließend wird das Ereignis CNF ausgelöst.

Die Konstanten `NOT_AVAILABLE_WM` (für den Initialwert von IN) und `VALID_SIGNAL_W` (als Schwellwert) werden aus externen Importen bezogen und definieren den gültigen Bereich des Feldbussignals.

## Technische Besonderheiten
- Verwendung von Typkonvertierungen (`WORD_TO_UINT`) für den Vergleich mit den importierten Konstanten.
- Der Baustein importiert zwei Konstanten aus dem Paket `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`: `NOT_AVAILABLE_WM` und `VALID_SIGNAL_W`. Diese müssen in der Anwendung entsprechend definiert oder bereitgestellt werden.
- Der Funktionsbaustein ist als einfacher FB (Simple FB) realisiert, d. h. er besitzt genau einen Ausführungszustand.

## Zustandsübersicht
Der Baustein besteht aus einem einzigen Zustand **REQ**.  
- **START** → **REQ**: Der Algorithmus wird ausgeführt, sobald das Ereignis REQ eintrifft. Nach Abarbeitung wird CNF ausgegeben und der Zustand bleibt in REQ (zyklische Verarbeitung).

## Anwendungsszenarien
- Verarbeitung von analogen Sensorwerten aus einem Feldbus, bei denen ein bestimmter Wertebereich als gültig definiert ist (z. B. 0–1000 für einen Drucksensor).
- Filterung von Kommunikationsfehlern oder ungültigen Telegrammen, indem Werte außerhalb des gültigen Bereichs auf Null gesetzt und als ungültig markiert werden.
- Vorverarbeitung von Feldbussignalen vor der Weiterleitung an nachfolgende Logikbausteine.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Durchleitbausteinen (z. B. `MOVE`) führt `FIELDBUS_UINT_TO_SIGNAL` eine bewusste Gültigkeitsprüfung durch und unterscheidet zwischen gültigen und ungültigen Werten. Andere Bausteine wie `LIMIT` oder `SCALE` bieten zwar Bereichsbegrenzungen, jedoch keine separate Bool-Ausgabe für die Gültigkeit. Dieser Baustein eignet sich besonders für Anwendungen, die eine explizite Signalzustandsanzeige benötigen.

## Fazit
Der Funktionsbaustein FIELDBUS_UINT_TO_SIGNAL bietet eine einfache und effiziente Möglichkeit, Feldbussignale auf Gültigkeit zu prüfen und entweder durchzureichen oder zu verwerfen. Die klare Schnittstelle und die Verwendung von konfigurierbaren Konstanten machen ihn flexibel einsetzbar in IEC-61499-Anwendungen der Automatisierungstechnik.
# AUDI_TO_AULI


![AUDI_TO_AULI](./AUDI_TO_AULI.svg)

*Bild nicht vorhanden*

* * * * * * * * * *
## Einleitung
Dieser Composite FB konvertiert einen AUDI-Adapter (UDINT) in einen AULI-Adapter (ULINT). Er dient als Schnittstelle zwischen Komponenten, die unterschiedliche Adaptertypen für vorzeichenlose Ganzzahlen verwenden. Der Baustein steht unter der Eclipse Public License 2.0 (EPL 2.0) und wird von der HR Agrartechnik GmbH bereitgestellt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine (Ereignisse werden über den AUDI_IN-Adapter empfangen).

### **Ereignis-Ausgänge**
Keine (Ereignisse werden über den AULI_OUT-Adapter gesendet).

### **Daten-Eingänge**
Keine (Daten werden über den AUDI_IN-Adapter empfangen).

### **Daten-Ausgänge**
Keine (Daten werden über den AULI_OUT-Adapter gesendet).

### **Adapter**
- **AUDI_IN** (Socket): Empfängt einen AUDI-Adapter (Typ: `adapter::types::unidirectional::AUDI`). Enthält einen Ereigniseingang (E1) und einen Dateneingang (D1) vom Typ UDINT.
- **AULI_OUT** (Plug): Sendet einen AULI-Adapter (Typ: `adapter::types::unidirectional::AULI`). Enthält einen Ereignisausgang (E1) und einen Datenausgang (D1) vom Typ ULINT.

## Funktionsweise
Der FB leitet eingehende Ereignisse und Daten vom AUDI_IN-Adapter direkt zum AULI_OUT-Adapter weiter:
- Das Ereignis `E1` von `AUDI_IN` wird auf `E1` von `AULI_OUT` übertragen.
- Der Datenwert `D1` (UDINT) von `AUDI_IN` wird auf `D1` (ULINT) von `AULI_OUT` übertragen. Dabei wird der 32‑Bit‑UDINT-Wert implizit in den 64‑Bit‑ULINT-Wert umgewandelt (null‑extension). Es findet keine zusätzliche Logik statt.

## Technische Besonderheiten
- **Composite FB**: Enthält keine eigene Funktionsbausteinlogik oder Zustandsmaschine, sondern lediglich Verdrahtung zwischen zwei Adaptern.
- **Paket**: `adapter::conversion::unidirectional`
- **Version**: 1.0, erstellt am 2026‑02‑17.
- **Lizenz**: EPL 2.0.

## Zustandsübersicht
Der FB besitzt keinen internen Zustand oder Algorithmus. Er arbeitet streng durchflussorientiert und reagiert auf jedes eingehende Ereignis sofort.

## Anwendungsszenarien
- **Systemintegration**: Wenn ein Systemkomponente Daten über einen AUDI-Adapter (UDINT) bereitstellt, eine andere Komponente jedoch einen AULI-Adapter (ULINT) erwartet, fungiert dieser FB als Brücke.
- **Protokollanpassung**: Einsatz in Steuerungssystemen, die unterschiedliche Integer‑Breiten für Busse oder Schnittstellen verwenden (z. B. 32‑Bit zu 64‑Bit).

## Vergleich mit ähnlichen Bausteinen
- **Einfache Datentypkonverter** (z. B. `UDINT_TO_ULINT`): Diese wandeln nur Daten um, ohne Adapter. Der vorliegende FB arbeitet auf Adapterebene und leitet auch Ereignisse weiter.
- **Adapter‑Transceiver**: Andere Bausteine könnten komplexere Umwandlungen (z. B. skalieren, offset) durchführen. Dieser FB ist minimal gehalten.

## Fazit
`AUDI_TO_AULI` ist ein zweckmäßiger Composite FB zur verlustfreien Konvertierung von UDINT nach ULINT auf Adapterebene. Er ist einfach, leicht verständlich und ideal für saubere Schnittstellentrennung in modularen Systemen.
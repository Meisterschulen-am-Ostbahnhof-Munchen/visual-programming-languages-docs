# AUS_TO_AULI


![AUS_TO_AULI](./AUS_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUS_TO_AULI` ist ein Composite-Baustein zur Konvertierung eines AUS-Adapters (UNSIGNED SHORT INTEGER) in einen AULI-Adapter (UNSIGNED LONG INTEGER). Er ermöglicht die direkte Weiterleitung von Ereignissen und Daten zwischen diesen beiden unidirektionalen Adaptertypen, wobei eine implizite Typumwandlung von USINT nach ULINT stattfindet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **E1** (über `AUS_IN`): Ereigniseingang des angeschlossenen AUS-Adapters. Wird direkt an den Ausgang weitergeleitet.

### **Ereignis-Ausgänge**
- **E1** (über `AULI_OUT`): Ereignisausgang des AULI-Adapters. Entspricht dem eingehenden Ereignis von `AUS_IN.E1`.

### **Daten-Eingänge**
- **D1** (über `AUS_IN`): Dateneingang vom Typ **USINT** (AUS-Adapter). Der Wert wird an den Ausgang übertragen.

### **Daten-Ausgänge**
- **D1** (über `AULI_OUT`): Datenausgang vom Typ **ULINT** (AULI-Adapter). Enthält den konvertierten Wert des Eingangs.

### **Adapter**
- **AUS_IN** (Socket): Aufnahmeschnittstelle für einen AUS-Adapter (Datentyp USINT, Ereignis E1, Daten D1).
- **AULI_OUT** (Plug): Ausgabeschnittstelle für einen AULI-Adapter (Datentyp ULINT, Ereignis E1, Daten D1).

## Funktionsweise
Der Baustein verbindet die Elemente des eingehenden AUS-Adapters direkt mit den korrespondierenden Elementen des ausgehenden AULI-Adapters:
- Ein eingehendes Ereignis am `AUS_IN.E1` wird unverzögert an `AULI_OUT.E1` weitergegeben.
- Der Datenwert `AUS_IN.D1` (USINT) wird ohne zusätzliche Logik auf `AULI_OUT.D1` (ULINT) abgebildet. Die Typkonvertierung erfolgt implizit durch die unterschiedlichen Adapterdefinitionen; ein USINT-Wert wird dabei in den entsprechenden ULINT-Wert erweitert.

## Technische Besonderheiten
- **Composite-Baustein**: Der FB enthält kein eigenes ECC (Execution Control Chart) und keine Zustandslogik, sondern besteht ausschließlich aus einer Ereignis- und Datenverbindung.
- **Implizite Typumwandlung**: Die Konvertierung von USINT nach ULINT wird durch die Adapterdefinitionen der Bibliothek `adapter::types::unidirectional` bereitgestellt. Eine explizite Typumwandlung im FB ist nicht erforderlich.
- **Unidirektionalität**: Der FB unterstützt nur eine Datenflussrichtung (von AUS zu AULI). Eine Rückwärtskonvertierung ist nicht vorgesehen.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Er arbeitet rein ereignisgesteuert und kombinatorisch: Bei jedem eingehenden Ereignis wird der aktuelle Datenwert sofort weitergeleitet. Es werden keine internen Zustände gespeichert.

## Anwendungsszenarien
- **Adapter-Integration**: Wenn ein bestehendes Modul (z. B. ein Sensor) einen AUS-Adapter ausgibt, aber ein nachfolgendes Modul (z. B. eine Steuerung) einen AULI-Adapter erwartet, kann dieser FB als konvertierende Zwischenschicht eingesetzt werden.
- **Systemerweiterung**: Einfaches Upgrade von USINT-basierten Schnittstellen auf ULINT ohne Änderung der umgebenden Logik.
- **Testumgebungen**: Als Platzhalter oder Brücke in Adapter-basierten Teststrukturen.

## Vergleich mit ähnlichen Bausteinen
- **AUS_TO_AULI vs. generische Typkonverter**: Im Gegensatz zu einem universellen Konverter ist dieser FB speziell für die AUS/AULI-Adapter zugeschnitten und benötigt keine zusätzliche Parametrierung. Er ist kompakter und schneller in der Entwicklung.
- **AUS_TO_AULI vs. manuelle Adapter-Programmierung**: Statt selbstständig einen Adapter-zu-Adapter-Konverter zu programmieren, bietet dieser fertige Baustein eine sofort nutzbare, getestete Lösung.

## Fazit
Der FB `AUS_TO_AULI` ist ein einfacher, aber effektiver Composite-Baustein zur Konvertierung eines AUS-Adapters (USINT) in einen AULI-Adapter (ULINT). Durch seine direkte Durchschaltung von Ereignissen und Daten sowie die implizite Typumwandlung stellt er eine saubere und wartbare Lösung für die Integration unterschiedlicher Adapter-Schnittstellen dar.
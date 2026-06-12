# AR_SPLIT_5


![AR_SPLIT_5](./AR_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AR_SPLIT_5 dient dazu, einen eingehenden AR-Adapter in fünf identische AR-Adapter-Ausgänge aufzuteilen. Es handelt sich um einen generischen Baustein, der speziell für die Verteilung von unidirektionalen Adaptern (Typ: `adapter::types::unidirectional::AR`) konzipiert ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine vorhanden.
### **Ereignis-Ausgänge**
Keine vorhanden.
### **Daten-Eingänge**
Keine vorhanden.
### **Daten-Ausgänge**
Keine vorhanden.
### **Adapter**
- **Socket (Eingang)**:
  - `IN`: Typ `adapter::types::unidirectional::AR` – Empfängt einen einzigen AR-Adapter.
- **Plugs (Ausgänge)**:
  - `OUT1`: Typ `adapter::types::unidirectional::AR`
  - `OUT2`: Typ `adapter::types::unidirectional::AR`
  - `OUT3`: Typ `adapter::types::unidirectional::AR`
  - `OUT4`: Typ `adapter::types::unidirectional::AR`
  - `OUT5`: Typ `adapter::types::unidirectional::AR`
    Alle Ausgänge sind identisch aufgebaut und geben den eingehenden AR-Adapter unverändert weiter.

## Funktionsweise
Der Baustein arbeitet als passiver Verteiler: Sobald ein AR-Adapter an den Eingang `IN` angeschlossen wird, wird dieser auf die fünf Ausgänge `OUT1` bis `OUT5` vervielfältigt. Jede Verbindung erhält eine unabhängige, aber identische Kopie des Adapters. Es findet keine Datenverarbeitung oder -änderung statt.

## Technische Besonderheiten
- **Unidirektionalität**: Die Adapter des Typs `AR` sind ausschließlich unidirektional ausgelegt, d.h. Signale fließen nur vom Eingang zu den Ausgängen.
- **Generische Implementierung**: Der FB ist als generischer Typ (`GEN_AR_SPLIT`) realisiert, was eine einfache Wiederverwendung und Anpassung an andere Adapter-Typen ermöglicht.
- **Keine Zustandslogik**: Der Baustein besitzt keine internen Zustände oder Ereignisse; die Aufteilung erfolgt durch reine Verbindungstechnik.

## Zustandsübersicht
Der AR_SPLIT_5 verfügt über keinen eigenen Zustandsautomaten. Sein Verhalten ist statisch und rein strukturell: Der Eingang wird direkt auf alle Ausgänge durchgeschleift.

## Anwendungsszenarien
- **Signalverteilung**: Wenn ein AR-Adapter ein Steuer- oder Datensignal liefert, das an mehrere nachfolgende Komponenten (z.B. Aktoren, Sensoren) weitergegeben werden muss.
- **Module Kaskadierung**: In komplexen Automatisierungssystemen, in denen ein AR-Signal an verschiedene Subsysteme aufgeteilt werden soll.

## Vergleich mit ähnlichen Bausteinen
- **AR_SPLIT_2, AR_SPLIT_3, AR_SPLIT_4**: Diese Bausteine teilen einen AR-Adapter auf zwei, drei bzw. vier Ausgänge auf. Der AR_SPLIT_5 ist die Erweiterung auf fünf Ausgänge.
- **AR_MERGE_***: Im Gegensatz zu Split-Bausteinen führen Merge-Bausteine mehrere AR-Adapter zu einem zusammen.

## Fazit
Der AR_SPLIT_5 ist ein einfacher, aber nützlicher Funktionsblock zur Verteilung eines unidirektionalen AR-Adapters auf fünf unabhängige Ausgänge. Seine generische und ereignislose Struktur macht ihn zu einem grundlegenden Werkzeug für die Adapter-basierte Kommunikation in IEC 61499-Systemen.
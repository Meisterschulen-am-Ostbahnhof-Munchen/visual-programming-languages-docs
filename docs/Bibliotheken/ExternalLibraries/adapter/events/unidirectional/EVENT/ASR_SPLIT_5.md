# ASR_SPLIT_5


![ASR_SPLIT_5](./ASR_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_SPLIT_5** dient der Aufteilung eines einzelnen unidirektionalen ASR-Adapters (Agricultural Standardized Interface) auf fünf gleichartige ASR-Ausgänge. Er ist als generischer Baustein konzipiert und ermöglicht so die einfache Verteilung eines ASR-Signals an mehrere nachgelagerte Komponenten oder Steuerungen.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen Ereignis- oder Datenein-/ausgänge. Die gesamte Kommunikation erfolgt über Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::ASR`.

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Bezeichnung | Typ                        | Richtung |
|-------------|----------------------------|----------|
| `IN`        | `adapter::types::unidirectional::ASR` | Socket (Eingang) |
| `OUT1`      | `adapter::types::unidirectional::ASR` | Plug (Ausgang)   |
| `OUT2`      | `adapter::types::unidirectional::ASR` | Plug (Ausgang)   |
| `OUT3`      | `adapter::types::unidirectional::ASR` | Plug (Ausgang)   |
| `OUT4`      | `adapter::types::unidirectional::ASR` | Plug (Ausgang)   |
| `OUT5`      | `adapter::types::unidirectional::ASR` | Plug (Ausgang)   |

## Funktionsweise

Der Baustein ist ein reiner Multiplexer auf Adapterebene. Das am Socket `IN` anliegende ASR-Signal wird unverändert und ohne Verzögerung auf alle fünf Ausgangs-Plugs (`OUT1` … `OUT5`) durchgeschaltet. Somit empfängt jeder angeschlossene Empfänger das identische Signal des Eingangsadapters. Eine aktive Signalbearbeitung oder -aufbereitung findet nicht statt.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generischer Funktionsblock (`GEN_ASR_SPLIT`) realisiert und kann automatisch an die spezifischen Datentypen des verwendeten ASR-Adapters angepasst werden.
- **Unidirektionale Kommunikation**: Alle Adapter sind unidirektional (`adapter::types::unidirectional::ASR`), d.h. Daten fließen nur vom Eingang zu den Ausgängen, Rückmeldungen sind nicht vorgesehen.
- **Keine Zustandslogik**: Da keine Ereignisse oder Algorithmen vorhanden sind, besitzt der Baustein kein ECC‑Zustandsdiagramm und arbeitet ausschließlich datenflussorientiert.

## Zustandsübersicht

Der Funktionsblock hat keinen internen Zustandsautomaten. Er verhält sich wie eine passive Signalverteilung und benötigt keine Zustandssteuerung.

## Anwendungsszenarien

- **Signalverteilung**: Ein ASR‑Signal (z. B. Sensordaten, Steuerbefehle) muss gleichzeitig an mehrere Verbraucher (z. B. mehrere Aktoren oder übergeordnete Steuerungen) weitergegeben werden.
- **Test- und Simulationsumgebungen**: Paralleles Einspeisen eines Testsignals in mehrere unabhängige Systempfade.
- **Redundanz**: Versorgung mehrerer gleichartiger Steuerungseinheiten mit der gleichen Eingangsinformation.

## Vergleich mit ähnlichen Bausteinen

- **ASR_SPLIT_2 / ASR_SPLIT_3 / ASR_SPLIT_4**: Diese Bausteine teilen ein ASR‑Signal auf zwei, drei bzw. vier Ausgänge auf – je nach Bedarf kann die passende Anzahl gewählt werden.
- **ASR_MERGE**: Im Gegensatz zum Splitter fasst ein MERGE mehrere ASR‑Eingänge zu einem Ausgang zusammen.

## Fazit

Der **ASR_SPLIT_5** ist ein einfacher, aber nützlicher Routing-Baustein zur Vervielfachung eines unidirektionalen ASR-Adapters. Dank seiner generischen Implementierung und der reinen Adapter‑Schnittstelle fügt er sich nahtlos in IEC‑61499‑Anwendungen ein und erleichtert die strukturierte Signalverteilung in komplexen Automatisierungssystemen.
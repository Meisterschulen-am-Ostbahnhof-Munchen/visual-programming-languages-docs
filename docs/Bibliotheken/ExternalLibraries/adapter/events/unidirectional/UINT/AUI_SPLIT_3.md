# AUI_SPLIT_3


![AUI_SPLIT_3](./AUI_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AUI_SPLIT_3** dient als generischer Splitter, der eine einzelne eingehende AUI-Schnittstelle auf drei identische ausgehende AUI-Schnittstellen verteilt. Er ermöglicht die einfache Vervielfachung eines unidirektionalen Adapters (vom Typ `adapter::types::unidirectional::AUI`), ohne dass die darin transportierten Ereignisse oder Daten verändert werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine – der FB besitzt keine eigenständigen Ereignis-Eingänge. Die Ereignisweiterleitung erfolgt ausschließlich über die AUI-Adapter.

### **Ereignis-Ausgänge**
Keine – der FB besitzt keine eigenständigen Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt ausschließlich über die AUI-Adapter.

### **Daten-Eingänge**
Keine – der FB besitzt keine eigenständigen Daten-Eingänge. Daten werden über die AUI-Adapter übertragen.

### **Daten-Ausgänge**
Keine – der FB besitzt keine eigenständigen Daten-Ausgänge. Daten werden über die AUI-Adapter übertragen.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::AUI` | Eingehende AUI-Schnittstelle, die auf drei Ausgänge verteilt wird. |
| Plug (Ausgang) | `OUT1` | `adapter::types::unidirectional::AUI` | Erster ausgehender AUI-Ausgang (identisch zum Eingangssignal). |
| Plug (Ausgang) | `OUT2` | `adapter::types::unidirectional::AUI` | Zweiter ausgehender AUI-Ausgang (identisch zum Eingangssignal). |
| Plug (Ausgang) | `OUT3` | `adapter::types::unidirectional::AUI` | Dritter ausgehender AUI-Ausgang (identisch zum Eingangssignal). |

## Funktionsweise

Der Baustein arbeitet als reiner Signalverteiler. Er nimmt über den Socket `IN` eine AUI-Schnittstelle entgegen und leitet alle über diese Schnittstelle eingehenden Ereignisse und Daten unverändert an die drei Plugs `OUT1`, `OUT2` und `OUT3` weiter. Es findet keinerlei Verarbeitung, Verzögerung oder Zustandsänderung statt. Der FB ist somit **stateless** und verhält sich wie eine einfache Verdrahtungsvervielfachung.

## Technische Besonderheiten

- **Generischer Aufbau**: Der Baustein ist als generischer FB (`GEN_AUI_SPLIT`) gekennzeichnet, sodass er für verschiedene AUI-Adater-Varianten (mit unterschiedlichen Ereignis-/Datensignaturen) eingesetzt werden kann.
- **Unidirektional**: Der Adaptertyp `unidirectional` bedeutet, dass die Daten- und Ereignisflüsse nur in eine Richtung (vom Socket zu den Plugs) erfolgen. Rückwärtige Kommunikation ist nicht vorgesehen.
- **Keine Latenz**: Durch das Fehlen interner Logik tritt keine messbare Verzögerung auf.
- **Keine Konfiguration**: Der FB benötigt keine Parameter – die Anzahl der Ausgänge ist fest auf drei festgelegt.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten. Es gibt nur einen einzigen, durchgängigen Betriebszustand, in dem die Eingangsschnittstelle permanent auf die drei Ausgangsschnittstellen gespiegelt wird.

## Anwendungsszenarien

- **Signalvervielfachung**: Ein AUI-Signal eines Sensors oder einer Steuerung soll an mehrere unabhängige Empfänger (z. B. Aktoren, Anzeigen, andere Steuerungen) weitergeleitet werden.
- **Monitoring**: Ein bestehender AUI-Datenstrom wird an eine Überwachungseinheit kopiert, ohne die Originalsignalpfade zu beeinträchtigen.
- **Test- und Simulationsumgebungen**: Ein Testreiz soll parallel an mehrere zu testende Komponenten verteilt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ausgänge | Eigenschaften |
|----------|----------|---------------|
| `AUI_SPLIT_2` | 2 | Gleiche Funktionsweise, aber nur zwei Ausgänge. |
| `AUI_SPLIT_4` | 4 | Erweiterte Version mit vier Ausgängen. |
| `AUI_MERGE` | – | Führt mehrere AUI-Eingänge zu einem Ausgang zusammen (entgegengesetzte Funktion). |

Der `AUI_SPLIT_3` stellt eine spezifische Konfiguration dar, die genau drei identische Ausgänge bereitstellt. Er kann bei Bedarf durch andere Splitter-Varianten ersetzt werden.

## Fazit

Der `AUI_SPLIT_3` ist ein einfacher, aber nützlicher generischer Funktionsbaustein zur Vervielfachung einer unidirektionalen AUI-Schnittstelle. Dank seiner reinen Durchleitungsfunktion und fehlenden Zustandslogik ist er zuverlässig, performant und leicht in bestehende Automatisierungslösungen integrierbar. Er eignet sich besonders für Anwendungen, in denen ein Signal auf mehrere Pfade aufgeteilt werden muss.
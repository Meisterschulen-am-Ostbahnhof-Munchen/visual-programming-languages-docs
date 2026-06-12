# AD_SPLIT_5


![AD_SPLIT_5](./AD_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AD_SPLIT_5` ist ein generischer Baustein, der einen eingehenden unidirektionalen Adapter (Typ `adapter::types::unidirectional::AD`) auf fünf identische Ausgangsadapter aufteilt. Er dient dazu, ein Adaptersignal parallel an mehrere nachfolgende Bausteine weiterzuleiten, ohne dass der Eingang mehrfach verbunden werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine vorhanden.

### **Ereignis-Ausgänge**

Keine vorhanden.

### **Daten-Eingänge**

Keine vorhanden. Die gesamte Kommunikation erfolgt über den Adapter-Socket.

### **Daten-Ausgänge**

Keine vorhanden. Die Ausgaben erfolgen ausschließlich über die Adapter-Plugs.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AD` | `IN` | Socket (Eingang) | Eingehendes Adaptersignal, welches auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AD` | `OUT1` | Plug (Ausgang) | Erster ausgehender Adapter, identisch zum Eingangssignal. |
| `adapter::types::unidirectional::AD` | `OUT2` | Plug (Ausgang) | Zweiter ausgehender Adapter. |
| `adapter::types::unidirectional::AD` | `OUT3` | Plug (Ausgang) | Dritter ausgehender Adapter. |
| `adapter::types::unidirectional::AD` | `OUT4` | Plug (Ausgang) | Vierter ausgehender Adapter. |
| `adapter::types::unidirectional::AD` | `OUT5` | Plug (Ausgang) | Fünfter ausgehender Adapter. |

## Funktionsweise

Der Baustein besitzt keine Ereignis- oder Datenports im herkömmlichen Sinne. Stattdessen wird ein eingehender Adapter `IN` auf alle fünf ausgehenden Adapter `OUT1` bis `OUT5` durchgeschleift. Das bedeutet, dass Änderungen oder Ereignisse, die über den Eingangsadapter transportiert werden, an alle fünf Ausgänge gleichzeitig weitergegeben werden. Die Vervielfachung erfolgt ohne logische Verarbeitung oder Verzögerung.

## Technische Besonderheiten

- **Generischer Typ**: Der Funktionsblock ist als generischer Baustein implementiert (Attribute `eclipse4diac::core::GenericClassName = 'GEN_AD_SPLIT'`). Dadurch kann er in verschiedenen Kontexten mit dem Adaptertyp `adapter::types::unidirectional::AD` verwendet werden.
- **Keine Zustandsmaschine**: Der Block besitzt kein ECC (Execution Control Chart) und arbeitet rein datenflussgetrieben. Er führt keine speichernden Operationen durch.
- **Unidirektionale Adapter**: Alle Adapter sind unidirektional, d.h. die Daten fließen nur in eine Richtung – vom Socket zu den Plugs.

## Zustandsübersicht

Der Funktionsblock hat keine internen Zustände oder Schritte. Es handelt sich um einen reinen Verteiler (Splitter) ohne eigenes Verhalten. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Signalverteilung**: Wenn ein Adaptersignal mehrfach benötigt wird, z. B. um mehrere parallele Berechnungen oder Ausgaben zu speisen.
- **Modulare Verkettung**: In komplexen Automatisierungssystemen, in denen ein Sensorwert (als Adapter) an verschiedene Subsysteme weitergegeben werden muss.
- **Prototyping**: Schnelles Aufbauen von Testumgebungen, bei denen ein Signal an mehrere Stellen gleichzeitig gelangen soll.

## Vergleich mit ähnlichen Bausteinen

- **AD_SPLIT_2, AD_SPLIT_3, AD_SPLIT_4**: Dieselbe Funktionalität mit zwei, drei bzw. vier Ausgängen. `AD_SPLIT_5` ist die Fünffach-Version.
- **Manuelle Verkabelung**: Ohne diesen Baustein müsste der Ausgang des Quellbausteins mehrfach verbunden werden, was in der 4diac-IDE nicht direkt möglich ist (ein Port kann nur eine Verbindung haben). Der Splitter löst dieses Problem.
- **Ereignisbasierte Splitter**: Es gibt auch Splitter für Ereignisse (z. B. `E_SPLIT`), die jedoch auf Ereignis- und Datenports basieren. `AD_SPLIT_5` arbeitet dagegen ausschließlich auf Adapterebene.

## Fazit

Der Funktionsblock `AD_SPLIT_5` ist ein einfaches, aber nützliches Werkzeug zur Vervielfachung von Adaptersignalen in der 4diac-Entwicklungsumgebung. Durch seine generische Auslegung und den Verzicht auf eine Zustandsmaschine bietet er eine effiziente Möglichkeit, ein Adaptersignal ohne Code-Änderungen auf fünf parallele Pfade zu verteilen. Er ist ideal für modulare und skalierbare Automatisierungsanwendungen.
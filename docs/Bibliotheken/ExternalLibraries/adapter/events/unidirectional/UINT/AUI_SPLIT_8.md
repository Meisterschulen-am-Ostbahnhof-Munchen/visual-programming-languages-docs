# AUI_SPLIT_8


![AUI_SPLIT_8](./AUI_SPLIT_8.svg)

* * * * * * * * * *

## Einleitung

Der Baustein `AUI_SPLIT_8` dient dazu, ein eingehendes AUI-Adapter-Signal (unidirektional) auf acht identische Ausgangsadapter zu verteilen. Er fungiert als passiver Splitter und ermöglicht die einfache Verteilung eines Signalpfades an mehrere nachfolgende Komponenten. Der Funktionsblock ist generisch ausgelegt und nutzt das Adapter-Pattern der IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Adapter | Typ | Richtung |
|---------|-----|----------|
| **IN**  | `adapter::types::unidirectional::AUI` | Socket (Eingang) |
| **OUT1** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT2** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT3** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT4** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT5** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT6** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT7** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |
| **OUT8** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) |

## Funktionsweise

Der Baustein leitet alle über die `IN`-Socket empfangenen Daten und Ereignisse des unidirektionalen AUI-Adapters an alle acht `OUT`-Adapter weiter. Es findet keine logische oder zeitliche Verarbeitung statt; die Weiterleitung erfolgt eins-zu-eins und ohne Latenz. Die Adapter sind vom gleichen Typ (`AUI`), sodass die vollständige Signatur (Daten, Ereignisse, mitgelieferte Schnittstellen) unverändert durchgereicht wird.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist mittels `GenericClassName` (`GEN_AUI_SPLIT`) als generisch deklariert. Er kann daher für verschiedene AUI-Adapter-Varianten (z. B. unterschiedliche Datenbreiten) eingesetzt werden, sofern der Typ `adapter::types::unidirectional::AUI` zugrunde liegt.
- **Unidirektionalität**: Die Adapter sind unidirektional ausgelegt – eine Datenübertragung ist nur in eine Richtung (von IN zu OUT) vorgesehen. Rückkanäle sind nicht enthalten.
- **Keine Zustandslogik**: Der Baustein besitzt keine inneren Zustände, Algorithmen oder Ereignisverarbeitung. Er ist rein strukturell (passive Verdrahtung).

## Zustandsübersicht

Der Baustein besitzt keine Zustände. Er verhält sich statisch und leitet immer alle ankommenden Signale durch.

## Anwendungsszenarien

- **Signalverteilung in Automatisierungsnetzwerken**: Ein Sensor oder Steuergerät liefert ein AUI-konformes Signal, das an mehrere Aktoren oder Subsysteme weitergegeben werden muss.
- **Test- und Simulationsumgebungen**: Verteilen eines Testsignals auf mehrere parallele Prüfpfade.
- **Redundante Signalpfade**: Gleichzeitige Versorgung mehrerer unabhängiger Steuerungen mit derselben Information.

## Vergleich mit ähnlichen Bausteinen

- **`AUI_MERGE_8`** (Gegenstück): Fasst acht AUI-Eingänge zu einem Ausgang zusammen (inverser Operator).
- **`AUI_SPLIT_2`, `AUI_SPLIT_4`**: Gleiche Funktionalität mit geringerer Ausgangsanzahl.
- **Ereignis-Splitter (z. B. `E_SPLIT`)**: Verteilen nur Ereignisse ohne die mitgeführten Daten eines Adapters. `AUI_SPLIT_8` hingegen repliziert den gesamten Adapter-Inhalt.

## Fazit

Der `AUI_SPLIT_8` ist ein einfacher, aber essenzieller Baustein zur Vervielfältigung eines unidirektionalen AUI-Signalpfades. Aufgrund seiner generischen Auslegung und rein passiven Struktur eignet er sich für beliebige AUI-basierte Anwendungen, in denen ein Signal an bis zu acht Empfänger verteilt werden muss. Die Implementierung ist schlank, fehlerarm und benötigt keinerlei Konfiguration.
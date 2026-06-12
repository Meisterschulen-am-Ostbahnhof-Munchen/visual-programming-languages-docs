# AW_SPLIT_7


![AW_SPLIT_7](./AW_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AW_SPLIT_7` dient dazu, einen einzelnen eingehenden AW-Adapter (unidirektional) auf sieben identische AW-Adapter-Ausgänge zu verteilen. Er ist als generischer Baustein ausgelegt und ermöglicht eine einfache Verteilung von Adapterverbindungen ohne Datenverarbeitung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AW` | IN | Socket (Eingang) | Eingehender AW-Adapter, der auf die Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AW` | OUT1 … OUT7 | Plug (Ausgang) | Sieben ausgehende Adapter, die jeweils die gleichen Daten wie der Eingang bereitstellen. |

## Funktionsweise

Der Baustein besitzt keine eigenen Ereignis- oder Datenports. Er wirkt als reine Adaptervervielfältigung: Der eingehende AW-Adapter (`IN`) wird intern ohne Verarbeitung auf alle sieben Ausgangs-Adapter (`OUT1` bis `OUT7`) durchgeschleift. Jeder angeschlossene Baustein an einem der Ausgänge erhält somit exakt die gleiche Instanz des AW-Adapters.

Die Implementierung ist generisch (Generic-FB), sodass der tatsächliche Adaptertyp durch Parameter dynamisch festgelegt werden kann. Dadurch eignet sich der Baustein für beliebige unidirektionale AW-Schnittstellen.

## Technische Besonderheiten

- **Generischer Typ**: Der FB nutzt den Mechanismus generischer Funktionsblöcke, um den konkreten Adaptertyp zur Laufzeit oder beim Kompilieren zu bestimmen. Der Platzhalter `GEN_AW_SPLIT` wird durch den tatsächlichen Adapter ersetzt.
- **Reine Adapter-Verteilung**: Es findet keine Datenkopie oder Serialisierung statt – die Referenzen auf den AW-Adapter werden weitergegeben.
- **Keine Ereignissteuerung** erforderlich: Der Baustein arbeitet asynchron und ohne zeitliche Abhängigkeiten, da Adapter ohnehin datenspezifisch verbunden sind.

## Zustandsübersicht

Der `AW_SPLIT_7` verfügt über keinen internen Zustandsautomaten. Das Verhalten ist deterministisch und besteht ausschließlich aus der Durchleitung des Adapters. Eine Zustandsmaschine ist daher nicht erforderlich.

## Anwendungsszenarien

- **Verteilen von Sensoradaptern** an mehrere Auswerte- oder Steuereinheiten in einer Automatisierungsachse.
- **Aufteilung eines Bus-Signals** in mehrere parallele Verbindungen (z. B. für redundante Überwachung).
- **Kaskadierung von Adaptern** in einem IEC 61499-System, wenn mehrere Funktionsblöcke auf den gleichen Datenstrom zugreifen müssen.

## Vergleich mit ähnlichen Bausteinen

- **SPLIT-Bausteine mit begrenzter Ausgangsanzahl**: Andere Split-FBs (z. B. `SPLIT_2`, `SPLIT_4`) teilen Adapter auf weniger Kanäle auf – hier werden genau sieben Ausgänge bereitgestellt.
- **Adapter-Multiplexer**: Im Gegensatz zu Multiplexern, die zwischen mehreren Eingängen wählen, verteilt der `AW_SPLIT_7` einen Eingang ohne Selektion.
- **Daten-Split-FBs**: Falls der Baustein Daten- und Ereignisports hätte, müsste er Daten kopieren. Adapter-basierte Splits arbeiten effizienter, da nur Referenzen weitergegeben werden.

## Fazit

Der `AW_SPLIT_7` ist ein einfacher, aber nützlicher generischer Funktionsblock zur Vervielfältigung eines unidirektionalen AW-Adapters auf sieben Ausgänge. Seine Stärken liegen in der flexiblen Typanpassung und der effizienten, ereignislosen Weiterleitung. Er eignet sich besonders für modulare Automatisierungssysteme, bei denen ein Adapter mehrfach genutzt werden muss.
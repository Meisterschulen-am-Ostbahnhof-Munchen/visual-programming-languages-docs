# AW_SPLIT_9


![AW_SPLIT_9](./AW_SPLIT_9.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AW_SPLIT_9` dient als generischer Verteiler für einen eingehenden Adapter vom Typ `AW` auf neun identisch ausgelegte Ausgangsadapter. Er ermöglicht die Mehrfachnutzung eines einzelnen Adaptersignals, ohne dass die ursprüngliche Datenquelle dupliziert werden muss. Die Bezeichnung „SPLIT 1 AW into 9 AW“ beschreibt die Kernfunktion: Ein AW-Eingang wird auf neun AW-Ausgänge verteilt.

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

| Typ | Name | Richtung | Beschreibung |
|------|------|----------|-------------|
| `adapter::types::unidirectional::AW` | `IN` | Socket (Eingang) | Eingehender AW‑Adapter, der auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AW` | `OUT1` | Plug (Ausgang) | Erster ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT2` | Plug (Ausgang) | Zweiter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT3` | Plug (Ausgang) | Dritter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT4` | Plug (Ausgang) | Vierter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT5` | Plug (Ausgang) | Fünfter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT6` | Plug (Ausgang) | Sechster ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT7` | Plug (Ausgang) | Siebter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT8` | Plug (Ausgang) | Achter ausgehender AW‑Adapter. |
| `adapter::types::unidirectional::AW` | `OUT9` | Plug (Ausgang) | Neunter ausgehender AW‑Adapter. |

## Funktionsweise

Der Baustein verfügt über keinerlei Verarbeitungslogik (keine ECC, keine Algorithmen). Er fungiert als reiner Verdrahtungshelfer: Das am Socket `IN` anliegende AW‑Signal wird strukturell an alle neun Plug‑Adapter `OUT1` bis `OUT9` weitergeleitet. Im IEC 61499‑Modell bedeutet dies, dass alle Verbindungen, die an die Ausgänge angeschlossen sind, dasselbe Signal erhalten, das am Eingang anliegt. Eine zeitliche Steuerung oder Datenmanipulation findet nicht statt.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generische Klasse (`GEN_AW_SPLIT`) deklariert. Das ermöglicht die Wiederverwendung mit verschiedenen AW‑Adapter‑Typen, sofern die Grundstruktur (unidirektionaler AW‑Adapter) erhalten bleibt.
- **Keine Ereignisse oder Daten**: Die gesamte Kommunikation erfolgt ausschließlich über Adapter‑Schnittstellen. Dies vereinfacht die Handhabung in rein adapterbasierten Architekturen.
- **Keine Zustandslogik**: Der Baustein besitzt kein eigenes Verhalten; er ist ein reines „passives“ Element zur Signalkopierung.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine, da keine Ereignisse oder Algorithmen definiert sind. Sein Verhalten ist rein strukturell: Solange der Eingangsadapter verbunden ist, sind alle Ausgänge stets aktiv – eine Zustandsänderung tritt nicht auf.

## Anwendungsszenarien

- **Signalfächer**: Ein zentrales AW‑Signal (z. B. ein Steuerbefehl oder Sensorwert) muss an mehrere nachgeschaltete Komponenten verteilt werden.
- **Redundante Verbindungen**: In sicherheitskritischen Systemen kann das gleiche AW‑Signal an mehrere parallele Auswerteeinheiten gesendet werden.
- **Verdrahtungsvereinfachung**: Der FB ersetzt manuelle Stern‑Verdrahtungen in der Applikation und verbessert die Übersichtlichkeit des Funktionsplans.

## Vergleich mit ähnlichen Bausteinen

- **AW_SPLIT_N**: Ein generischer Split‑Baustein mit variabler Anzahl von Ausgängen (z. B. `AW_SPLIT_4`, `AW_SPLIT_16`). `AW_SPLIT_9` ist eine spezielle Ausprägung für genau neun Ausgänge.
- **Daten‑Split‑Bausteine**: Bausteine, die Daten‑Eingänge (z. B. `INT`, `REAL`) aufteilen. `AW_SPLIT_9` arbeitet ausschließlich auf Adapterebene und nicht auf einzelnen Datenpunkten.
- **Multiplexer (MUX)**: Ein Multiplexer wählt einen von mehreren Eingängen aus, während dieser Baustein einen Eingang auf viele Ausgänge verteilt (Fan‑Out).

## Fazit

Der `AW_SPLIT_9` ist ein einfacher, aber nützlicher generischer Funktionsblock für die Aufteilung eines unidirektionalen AW‑Adapter‑Signals auf neun parallele Ausgänge. Seine Struktur ist minimalistisch und rein passiv, was ihn zu einem zuverlässigen Werkzeug in adapterorientierten Steuerungsarchitekturen macht. Er benötigt weder Ereignisse noch Daten und kann ohne Nebenwirkungen in bestehende Applikationen integriert werden.
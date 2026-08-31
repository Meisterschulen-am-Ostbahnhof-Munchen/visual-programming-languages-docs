# AB_SPLIT_3_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AB_SPLIT_3`](AB_SPLIT_3.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AB_SPLIT_3_UNGATED](./AB_SPLIT_3_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AB_SPLIT_3_UNGATED** dient dazu, einen eingehenden unidirektionalen Daten-/Signal-Adapter (Typ `AB`) auf drei identische Ausgangs-Adapter aufzuteilen. Er ist als generischer Baustein implementiert und stellt eine einfache 1-zu-3-Verteilung ohne zusätzliche Logik oder Verzögerung dar.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AB` | `IN` | Socket (Eingang) | Empfängt einen unidirektionalen Adapter vom Typ AB. |
| `adapter::types::unidirectional::AB` | `OUT1` | Plug (Ausgang) | Erste Ausgabe des eingehenden Signals. |
| `adapter::types::unidirectional::AB` | `OUT2` | Plug (Ausgang) | Zweite Ausgabe des eingehenden Signals. |
| `adapter::types::unidirectional::AB` | `OUT3` | Plug (Ausgang) | Dritte Ausgabe des eingehenden Signals. |

## Funktionsweise

Der Baustein leitet den am Socket `IN` anliegenden unidirektionalen Adapter **ohne Manipulation** parallel an die drei Plugs `OUT1`, `OUT2` und `OUT3` weiter. Es findet keine Pufferung, Verarbeitung oder zeitliche Steuerung statt. Der Baustein fungiert als reiner **Splitter** (Verteiler) für adapterbasierte Signale.

Da der Adapter `AB` unidirektional ist, erfolgt die Datenübertragung ausschließlich in eine Richtung (vom Socket zu den Plugs). Die drei Ausgänge sind voneinander unabhängig und liefern stets den aktuellen Zustand des Eingangs.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist durch das Attribut `eclipse4diac::core::GenericClassName` als generisch markiert (`'GEN_AB_SPLIT'`). Das bedeutet, der tatsächliche Adapter-Typ kann zur Laufzeit oder beim Instanziieren spezifiziert werden, solange er die Grundstruktur eines unidirektionalen AB-Adapters besitzt.
- **Unidirektionalität**: Sowohl Eingangs- als auch Ausgangs-Adapter sind vom Typ `unidirectional::AB`. Eine Rückwärtskommunikation ist nicht vorgesehen.
- **Keine Zustandshaltung**: Der Baustein besitzt keine interne Zustandsmaschine oder Speicher. Die Weiterleitung erfolgt passiv und kontinuierlich.
- **Copyright**: Der Baustein wurde von der HR Agrartechnik GmbH unter der Eclipse Public License 2.0 veröffentlicht.

## Zustandsübersicht

Der Funktionsblock besitzt **keine explizite Zustandsmaschine**. Das Verhalten ist rein datenflussorientiert: Sobald der Eingangs-Adapter Daten liefert, werden diese unmittelbar an alle Ausgänge propagiert. Eine Zustandsüberwachung oder -steuerung ist nicht erforderlich.

## Anwendungsszenarien

- **Signalverteilung in der Automatisierungstechnik**: Aufteilen eines Sensorsignals (z. B. Temperatur, Druck) an mehrere Verarbeitungseinheiten.
- **Parallelisierung von Steuerungsabläufen**: Bereitstellen desselben Adapter-Streams für verschiedene Funktionsblöcke, die unabhängig voneinander arbeiten.
- **Prototyping und Test**: Verwenden eines simulierten Adapters, um mehrere Systemkomponenten gleichzeitig zu versorgen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Verhalten | Besonderheit |
| ---------- | ----------- | -------------- |
| `SPLIT_2` | 1-zu-2-Verteilung | Analoger Baustein mit zwei Ausgängen. |
| `AB_SPLIT_3_UNGATED` | 1-zu-3-Verteilung | Dieser Baustein. |
| `AB_JOIN` | Zusammenführen mehrerer Adapter | Gegenstück zum Splitter. |

Während `SPLIT_2` nur zwei Ausgänge bietet, deckt `AB_SPLIT_3_UNGATED` den Bedarf für eine dreifache Verteilung ab. Es sind keine weiteren logischen Funktionen wie Filterung oder Verzögerung implementiert.

- **[`AB_SPLIT_3`](AB_SPLIT_3.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **AB_SPLIT_3_UNGATED** ist ein einfacher, aber nützlicher generischer Splitter-Baustein für unidirektionale Adapter. Er ermöglicht eine saubere Strukturierung von Automatisierungsanwendungen, indem ein eingehender Signalpfad auf drei parallele Pfade aufgeteilt wird. Dank seiner generischen Natur kann er für beliebige AB-Adapter-Typen eingesetzt werden und fügt sich nahtlos in die IEC 61499-2-konforme Entwicklungsumgebung 4diac ein.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

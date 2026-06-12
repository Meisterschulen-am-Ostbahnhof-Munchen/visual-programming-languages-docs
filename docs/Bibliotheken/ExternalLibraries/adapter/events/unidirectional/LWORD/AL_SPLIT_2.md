# AL_SPLIT_2


![AL_SPLIT_2](./AL_SPLIT_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AL_SPLIT_2** dient dazu, ein eingehendes unidirektionales Adapter-Signal auf zwei identische Ausgänge aufzuteilen. Er ist als generischer Baustein konzipiert, sodass der konkrete Adaptertyp erst bei der Verwendung festgelegt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine*

### **Ereignis-Ausgänge**
*Keine*

### **Daten-Eingänge**
*Keine*

### **Daten-Ausgänge**
*Keine*

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AL` | **Socket** (Eingang) | `IN` | Eingangssignal, das auf beide Ausgänge verteilt wird |
| `adapter::types::unidirectional::AL` | **Plug** (Ausgang) | `OUT1` | Erster Ausgang mit demselben Adapter-Signal wie `IN` |
| `adapter::types::unidirectional::AL` | **Plug** (Ausgang) | `OUT2` | Zweiter Ausgang mit demselben Adapter-Signal wie `IN` |

## Funktionsweise

Der Baustein leitet das am Socket `IN` anliegende unidirektionale Adapter-Signal unverändert an beide Plugs `OUT1` und `OUT2` weiter. Es findet keine Datenbearbeitung oder -transformation statt – der FB arbeitet rein passiv und durchschleifend. Sobald ein Signal am Eingang anliegt, steht es zeitgleich an beiden Ausgängen zur Verfügung.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Baustein definiert (Attribute `GenericClassName` und `TypeHash`). Dadurch kann er mit unterschiedlichen unidirektionalen Adapter-Instanzen verwendet werden, ohne dass der Quellcode angepasst werden muss.
- **Adapter statt Datenpunkte**: Die Signalübertragung erfolgt ausschließlich über Adapter, nicht über diskrete Ereignis- oder Dateneingänge/-ausgänge. Dies ermöglicht eine strukturierte und wiederverwendbare Kapselung von Kommunikationsschnittstellen.
- **Keine Zustandsabhängigkeit**: Der FB besitzt kein internes Gedächtnis und keine Zustandsmaschine. Die Ausgangssignale folgen direkt dem Eingangssignal.

## Zustandsübersicht

Der Baustein führt keine eigene Zustandsverwaltung. Er kann als **kombinatorischer** Block betrachtet werden, bei dem die Ausgänge stets mit dem aktuellen Eingangswert belegt sind. Ein expliziter Zustandsautomat ist nicht vorhanden.

## Anwendungsszenarien

- **Signalverteilung**: Wenn ein Adapter-Signal von einer Quelle an mehrere unabhängige Empfänger weitergegeben werden muss (z. B. ein Steuerbefehl an zwei Aktoren).
- **Protokollierung / Überwachung**: Ein Adapter-Signal kann auf einen Pfad zur eigentlichen Verarbeitung und gleichzeitig auf einen Überwachungs- oder Logging-Pfad gesplittet werden.
- **Modulare Architekturen**: In komplexen Systemen, die mit Adaptern arbeiten, vereinfacht der `AL_SPLIT_2` die topologische Aufteilung von Signalen, ohne dass manuelle Verbindungen oder Duplikate erstellt werden müssen.

## Vergleich mit ähnlichen Bausteinen

Es existieren in der 4diac-IDE verschiedene Splitter-Bausteine für unterschiedliche Signalarten:

| Baustein | Signalart | Ausgänge | Besonderheit |
|----------|-----------|----------|--------------|
| `AL_SPLIT_2` | Adapter (unidirektional) | 2 | Generisch, keine Daten-/Ereignisse |
| `SPLIT` | Ereignisse | 2 | Verteilt Ereignisse ohne Daten |
| `E_SPLIT` | Ereignisse (mit Daten) | 2 | Verteilt Ereignisse samt begleitender Daten |
| `F_SPLIT` | Daten (beliebiger Typ) | n | Verteilt einen Datenwert auf mehrere Ausgänge |

Der `AL_SPLIT_2` ist speziell für Adapter-Schnittstellen optimiert und bietet damit eine saubere Möglichkeit, komplexe, adapterbasierte Verbindungen aufzutrennen, ohne in die Daten- oder Ereignisebene einzugreifen.

## Fazit

Der `AL_SPLIT_2` ist ein einfacher, aber nützlicher generischer Funktionsblock zur Aufteilung unidirektionaler Adapter-Signale. Er ermöglicht eine flexible und strukturierte Signalverteilung in modularen Automatisierungslösungen, ohne zusätzliche Logik oder Zustandsabhängigkeiten. Sein generischer Charakter macht ihn universell einsetzbar.
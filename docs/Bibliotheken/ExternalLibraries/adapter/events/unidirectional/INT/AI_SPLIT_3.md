# AI_SPLIT_3


![AI_SPLIT_3](./AI_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AI_SPLIT_3** ist ein generischer Baustein zur Vervielfältigung eines analogen Eingangssignals (AI). Er teilt ein eingehendes AI-Signal auf drei separate, identische Ausgangssignale auf. Der Baustein ist vollständig über Adapter vom Typ `AI` definiert und arbeitet rein datenflussorientiert ohne eigene Ereignis- oder Datenpunkt‑Schnittstellen.

## Schnittstellenstruktur

Der Baustein bietet keine direkten Ereignis‑ oder Daten‑Ein‑/Ausgänge. Die gesamte Kommunikation erfolgt über **Adapter**.

### Ereignis-Eingänge

Keine vorhanden.

### Ereignis-Ausgänge

Keine vorhanden.

### Daten-Eingänge

Keine direkten Daten‑Eingänge – das AI‑Signal wird über den Socket‑Adapter `IN` aufgenommen.

### Daten-Ausgänge

Keine direkten Daten‑Ausgänge – die drei identischen AI‑Signale werden über die Plug‑Adapter `OUT1`, `OUT2` und `OUT3` bereitgestellt.

### Adapter

| Richtung | Bezeichnung | Typ          | Beschreibung                                 |
|----------|-------------|--------------|----------------------------------------------|
| Socket   | `IN`        | `ADAPTER_AI` | Eingehendes analoges Signal (Quelle)         |
| Plug     | `OUT1`      | `ADAPTER_AI` | Erster Ausgang – identisch zum Eingangssignal |
| Plug     | `OUT2`      | `ADAPTER_AI` | Zweiter Ausgang – identisch zum Eingangssignal |
| Plug     | `OUT3`      | `ADAPTER_AI` | Dritter Ausgang – identisch zum Eingangssignal |

Die Adapter sind vom Typ `adapter::types::unidirectional::AI`. Der Baustein ist generisch, d. h. die konkrete Datenstruktur des AI‑Signals (z. B. Wert, Einheit, Status) wird erst bei der Instanziierung durch die angebundenen Adapter festgelegt.

## Funktionsweise

Der Funktionsblock leitet das über den Socket `IN` empfangene analoge Signal unverändert und gleichzeitig an alle drei Plug‑Adapter `OUT1`, `OUT2` und `OUT3` weiter. Es findet keine Signalumformung, Verstärkung oder Verzögerung statt. Der Baustein fungiert als reiner **1‑zu‑3‑Splitter**.

Da keine Ereignisse oder Zustandsautomaten vorhanden sind, erfolgt die Weitergabe rein über den Datenfluss. Sobald ein neues AI‑Signal am `IN` anliegt, steht es an allen drei Ausgängen zur Verfügung.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist mithilfe von `eclipse4diac::core::GenericClassName` als `'GEN_AI_SPLIT'` gekennzeichnet. Dadurch kann er in verschiedenen Anwendungen für unterschiedliche AI‑Datentypen verwendet werden, ohne dass der Funktionsblock selbst angepasst werden muss.
- **Reine Adapter‑Schnittstelle:** Es werden keine direkten Ereignis‑ oder Daten‑Ein‑/Ausgänge benötigt. Die gesamte Datenübertragung erfolgt über die Adapter, was eine flexible Kopplung mit anderen Bausteinen ermöglicht.
- **Keine Zustandslogik:** Der Baustein besitzt keinen eigenen Zustandsautomaten (ECC) – die Funktionalität ist rein datenflussbasiert und daher sehr leichtgewichtig.

## Zustandsübersicht

Der Baustein verfügt über **keine** Zustandsmaschine oder internen Zustände. Die Signale werden direkt und ohne Verzögerung weitergeleitet. Eine Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Signalverteilung in Automatisierungssystemen:** Ein analoger Messwert (z. B. Drucksensor, Temperatur) soll an mehrere Steuerungs‑ oder Überwachungseinheiten übergeben werden.
- **Redundanz und Parallelverarbeitung:** Das gleiche AI‑Signal wird für unterschiedliche Algorithmen parallel benötigt (z. B. Regelung, Alarmierung, Protokollierung).
- **Testumgebungen:** Ein simulierte Analogwert kann gleichzeitig an mehrere zu testende Bausteine verteilt werden.

## Vergleich mit ähnlichen Bausteinen

- **AI_SPLIT_2:** Verteilt das Eingangssignal auf zwei statt drei Ausgänge.
- **AI_SPLIT_4 / AI_SPLIT_N:** Erweiterte Versionen mit vier oder mehr Ausgängen (falls vorhanden).
- **AI_SELECT:** Wählt aus mehreren Eingängen einen aus, anstatt ein Signal zu vervielfältigen.
- **AI_MERGE:** Fasst mehrere AI‑Eingänge zu einem Ausgang zusammen (Gegenstück zum Splitter).

Gemeinsam ist allen Split‑Bausteinen, dass sie das Eingangssignal ohne Veränderung an alle Ausgänge weiterleiten. Der AI_SPLIT_3 stellt eine typische 3‑fach‑Ausführung dar.

## Fazit

Der **AI_SPLIT_3** ist ein einfacher, aber effektiver Baustein zur Vervielfältigung eines analogen Signals auf drei Ausgänge. Durch seine generische Natur und die Verwendung von Adaptern fügt er sich nahtlos in Adapter‑basierte 4diac‑Applikationen ein. Er eignet sich ideal für Anwendungen, in denen ein AI‑Wert an mehrere Verbraucher verteilt werden muss, ohne zusätzliche Logik oder Konfiguration.
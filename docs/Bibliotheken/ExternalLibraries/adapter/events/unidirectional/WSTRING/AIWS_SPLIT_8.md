# AIWS_SPLIT_8


![AIWS_SPLIT_8](./AIWS_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung

Der Baustein **AIWS_SPLIT_8** teilt ein eingehendes AIWS-Adapter-Signal auf acht identische Ausgänge auf. Er fungiert als generischer Splitter für unidirektionale Adapterverbindungen und ermöglicht die parallele Weiterleitung eines Signals an mehrere nachfolgende Funktionsbausteine.

## Schnittstellenstruktur

Der Baustein besitzt weder Ereignis- noch Dateneingänge oder -ausgänge. Die gesamte Kommunikation erfolgt ausschließlich über Adapter.

### Ereignis-Eingänge
Keine.

### Ereignis-Ausgänge
Keine.

### Daten-Eingänge
Keine.

### Daten-Ausgänge
Keine.

### Adapter

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Eingang (Socket) | IN | adapater::types::unidirectional::AIWS | Eingehendes AIWS-Signal, das aufgeteilt werden soll. |
| Ausgang (Plug) | OUT1 | adapater::types::unidirectional::AIWS | Erster paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT2 | adapater::types::unidirectional::AIWS | Zweiter paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT3 | adapater::types::unidirectional::AIWS | Dritter paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT4 | adapater::types::unidirectional::AIWS | Vierter paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT5 | adapater::types::unidirectional::AIWS | Fünfter paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT6 | adapater::types::unidirectional::AIWS | Sechster paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT7 | adapater::types::unidirectional::AIWS | Siebter paralleler Ausgang des Signals. |
| Ausgang (Plug) | OUT8 | adapater::types::unidirectional::AIWS | Achter paralleler Ausgang des Signals. |

## Funktionsweise

Der Baustein empfängt über den **IN**-Socket ein Signal des Typs AIWS (Adapter). Dieses Signal wird ohne Verarbeitung oder Verzögerung auf alle acht **OUT**-Plugs dupliziert. Änderungen am Eingangssignal werden sofort an allen Ausgängen widergespiegelt.

## Technische Besonderheiten

- Der Baustein ist generisch und für eine feste Anzahl von acht Ausgängen ausgelegt.
- Es existieren keine ereignisgesteuerten Abläufe – die Signalweitergabe erfolgt rein adapterbasiert und kontinuierlich.
- Die Implementierung ist als reiner Splitter ohne interne Logik oder Zustandsverwaltung realisiert.

## Zustandsübersicht

Der Baustein besitzt keine Zustandsmaschine. Es gibt keine internen Zustände oder Ereignissequenzen – die Ausgabe folgt direkt der Eingabe.

## Anwendungsszenarien

- **Signalverteilung** in Automatisierungsanwendungen: Ein AIWS-Sensorwert soll mehreren unabhängigen Regelungs- oder Überwachungsblöcken gleichzeitig zur Verfügung gestellt werden.
- **Parallelisierung** von Algorithmen: Nachfolgende Bausteine benötigen den gleichen Adapterdatenstrom, arbeiten aber parallel auf verschiedenen Ressourcen.
- **Test- und Simulationsumgebungen**: Ein eingehendes Signal wird auf mehrere Auswertungsinstanzen verteilt, um verschiedene Verarbeitungspfade zu vergleichen.

## Vergleich mit ähnlichen Bausteinen

- **AIWS_SPLIT_4** – Splitter mit vier Ausgängen.
- **AIWS_SPLIT_16** – Splitter mit 16 Ausgängen.
- **AIWS_MERGE** – Zusammenführung mehrerer AIWS-Adapter zu einem Ausgang (Gegenstück).

Gemeinsam ist allen Split-Bausteinen die unveränderte Weitergabe des Signals; sie unterscheiden sich nur in der Anzahl der Ausgänge.

## Fazit

**AIWS_SPLIT_8** ist ein einfacher, aber notwendiger Baustein zur Vervielfachung eines AIWS-Adapter-Signals auf acht parallele Pfade. Seine Implementation ohne Ereignissteuerung oder Zustandslogik macht ihn leichtgewichtig und zuverlässig für den Einsatz in verteilten Automatisierungssystemen.
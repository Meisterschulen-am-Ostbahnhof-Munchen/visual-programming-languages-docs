# AR_SPLIT_4


![AR_SPLIT_4](./AR_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AR_SPLIT_4** dient dazu, einen eingehenden AR-Adapter (unidirektional) auf vier ausgehende AR-Adapter aufzuteilen. Er ist als generischer Baustein (`GenericClassName = 'GEN_AR_SPLIT'`) implementiert und ermöglicht eine einfache Signalvervielfachung für adapterbasierte Kommunikation in Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| (keine) | – | – |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| (keine) | – | – |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AR` | **IN** | Socket (Eingang) | Einzugehender AR-Adaptersignal, das auf die vier Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AR` | **OUT1** | Plug (Ausgang) | Erster ausgehender AR-Kanal. |
| `adapter::types::unidirectional::AR` | **OUT2** | Plug (Ausgang) | Zweiter ausgehender AR-Kanal. |
| `adapter::types::unidirectional::AR` | **OUT3** | Plug (Ausgang) | Dritter ausgehender AR-Kanal. |
| `adapter::types::unidirectional::AR` | **OUT4** | Plug (Ausgang) | Vierter ausgehender AR-Kanal. |

## Funktionsweise

Der Baustein nimmt über den Socket **IN** ein AR-Adaptersignal entgegen und leitet es unverändert an alle vier Plugs **OUT1** bis **OUT4** weiter. Die Aufteilung erfolgt parallel – jedes über **IN** eingehende Ereignis oder jeder Datenwert wird gleichzeitig auf allen Ausgängen bereitgestellt. Der FB selbst führt keine logische Verarbeitung oder Umformung durch; er fungiert als reiner Verteiler (Splitter) für unidirektionale AR-Adapter.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generischer FB (`GenericClassName`) definiert, was bedeutet, dass der konkrete AR-Adaptertyp zur Übersetzungszeit festgelegt wird. Dies erhöht die Wiederverwendbarkeit in verschiedenen Anwendungen.
- **Keine Zustandsmaschine**: Der FB besitzt kein ECC (Execution Control Chart) und keine internen Zustände. Alle Operationen sind rein kombinatorisch bzw. ereignisgetrieben.
- **Unidirektional**: Der Adaptertyp ist als unidirektional spezifiziert; eine Rückmeldung vom Zielbaustein ist nicht vorgesehen.

## Zustandsübersicht

Da der FB keine Zustandsmaschine besitzt, existieren keine expliziten Zustände. Das Verhalten ist deterministisch: Ein eingehender Trigger am Socket **IN** wird sofort an alle Ausgänge weitergeleitet.

## Anwendungsszenarien

- **Signalvervielfachung**: Ein Steuerungssignal (z. B. „Start“ oder „Reset“) soll mehrere parallele Funktionsblöcke gleichzeitig erreichen.
- **Überwachung und Parallelverarbeitung**: Ein Messwert oder ein Alarm wird an mehrere unabhängige Auswerteblöcke verteilt.
- **Test und Simulation**: Während der Entwicklung kann ein Signal aufgezeichnet oder simuliert werden, während es gleichzeitig an den eigentlichen Zielblock geht.

## Vergleich mit ähnlichen Bausteinen

- **AR_SPLIT_2**: Teilt ein AR-Signal auf zwei Ausgänge auf – geeignet für kleinere Verteilungen.
- **AR_SPLIT_N**: Ein nicht standardisierter, konfigurierbarer Splitter (z. B. über Parameter), der für beliebig viele Ausgänge ausgelegt ist.
- **AR_MERGE**: Führt mehrere AR-Signale zu einem zusammen – die Umkehrfunktion des AR_SPLIT_4.

Gegenüber diesen Alternativen bietet AR_SPLIT_4 eine feste Anzahl von vier Ausgängen, was eine kompakte und übersichtliche Implementierung ohne Konfigurationsaufwand ermöglicht.

## Fazit

Der **AR_SPLIT_4** ist ein einfacher, aber nützlicher generischer Funktionsblock zur Verteilung eines unidirektionalen AR-Adaptersignals auf vier parallele Pfade. Aufgrund seines schlanken Designs (keine Ereignis-/Datenschnittstellen, keine Zustandsmaschine) eignet er sich ideal für alle Anwendungen, bei denen ein Signal mehrfach benötigt wird, ohne zusätzliche Logik einzubringen.
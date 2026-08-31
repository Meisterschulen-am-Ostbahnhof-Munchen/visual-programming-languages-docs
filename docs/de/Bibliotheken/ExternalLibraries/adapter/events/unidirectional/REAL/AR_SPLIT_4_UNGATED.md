# AR_SPLIT_4_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AR_SPLIT_4`](AR_SPLIT_4.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AR_SPLIT_4_UNGATED](./AR_SPLIT_4_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AR_SPLIT_4_UNGATED** dient dazu, einen eingehenden AR-Adapter (unidirektional) auf vier ausgehende AR-Adapter aufzuteilen. Er ist als generischer Baustein (`GenericClassName = 'GEN_AR_SPLIT'`) implementiert und ermöglicht eine einfache Signalvervielfachung für adapterbasierte Kommunikation in Steuerungssystemen.

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
| ----- | ------ | ---------- | -------------- |
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
- **AR_MERGE**: Führt mehrere AR-Signale zu einem zusammen – die Umkehrfunktion des AR_SPLIT_4_UNGATED.

Gegenüber diesen Alternativen bietet AR_SPLIT_4_UNGATED eine feste Anzahl von vier Ausgängen, was eine kompakte und übersichtliche Implementierung ohne Konfigurationsaufwand ermöglicht.

- **[`AR_SPLIT_4`](AR_SPLIT_4.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **AR_SPLIT_4_UNGATED** ist ein einfacher, aber nützlicher generischer Funktionsblock zur Verteilung eines unidirektionalen AR-Adaptersignals auf vier parallele Pfade. Aufgrund seines schlanken Designs (keine Ereignis-/Datenschnittstellen, keine Zustandsmaschine) eignet er sich ideal für alle Anwendungen, bei denen ein Signal mehrfach benötigt wird, ohne zusätzliche Logik einzubringen.

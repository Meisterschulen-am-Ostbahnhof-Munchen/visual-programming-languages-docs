# AUDI_DEMUX_4


![AUDI_DEMUX_4](./AUDI_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUDI_DEMUX_4** realisiert einen generischen 1:4-Demultiplexer für den unidirektionalen **AUDI**-Adaptertyp. Er leitet ein an seinem Eingang (Socket) anliegendes Signal wahlweise an einen der vier Ausgänge (Plugs) weiter. Die Auswahl des aktiven Ausgangs erfolgt über einen Indexparameter und wird durch ein Ereignis am Eingang `REQ` ausgelöst. Nach erfolgreicher Umschaltung wird ein Bestätigungsereignis am Ausgang `CNF` gesendet.

Der Baustein ist als generischer Funktionsblock (Generic FB) realisiert und kann daher in verschiedenen Projekten mit dem entsprechenden Adaptertyp verwendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `REQ` | Event | Setzt den Index `K` und löst die Demultiplex-Aktion aus. |

### **Ereignis-Ausgänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `CNF` | Event | Bestätigung der erfolgreichen Index-Setzung und Umschaltung. |

### **Daten-Eingänge**

| Name   | Datentyp | Initialwert | Kommentar |
|--------|----------|-------------|-----------|
| `K`    | UINT     | –           | Index des gewünschten Ausgangs (1..4). |

### **Daten-Ausgänge**

Keine Datenausgänge vorhanden.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AUDI` | `IN`  | Socket (Eingang)  | Eingangssignal, das an den ausgewählten Ausgang weitergeleitet wird. |
| `adapter::types::unidirectional::AUDI` | `OUT1` | Plug (Ausgang) | Erster Ausgang (Index 1). |
| `adapter::types::unidirectional::AUDI` | `OUT2` | Plug (Ausgang) | Zweiter Ausgang (Index 2). |
| `adapter::types::unidirectional::AUDI` | `OUT3` | Plug (Ausgang) | Dritter Ausgang (Index 3). |
| `adapter::types::unidirectional::AUDI` | `OUT4` | Plug (Ausgang) | Vierter Ausgang (Index 4). |

## Funktionsweise

Der FB arbeitet streng ereignisgesteuert:

1. Ein gültiges Ereignis am Eingang `REQ` übernimmt den aktuellen Wert des Daten-Eingangs `K` als Auswahlindex.
2. Der FB verbindet den an `IN` anliegenden Adapter-Datenstrom mit dem durch `K` referenzierten Ausgangsadapter (`OUT1` … `OUT4`).
3. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben.

Nicht verwendete Ausgänge bleiben unverändert (z. B. getrennt von der Quelle). Der Index `K` erwartet Werte im Bereich 1 bis 4; andere Werte führen zu keinem gültigen Durchschalten. Das Verhalten bei ungültigen Indizes ist nicht definiert und sollte durch übergeordnete Logik vermieden werden.

## Technische Besonderheiten

- **Generischer Funktionsblock**: Der FB ist als generischer Typ (`GEN_AUDI_DEMUX`) deklariert. Er kann mit jedem Adapter instanziiert werden, der dem Schema `adapter::types::unidirectional::AUDI` folgt. Die tatsächliche Adapterdefinition wird zur Compile-Zeit festgelegt.
- **Unidirektionale Adapter**: Alle verwendeten Adapter sind unidirektional. Der Signalfluss erfolgt nur vom Socket (`IN`) zu den Plugs (`OUT1` … `OUT4`).
- **Keine internen Zustände**: Der FB besitzt keine explizite Zustandsmaschine. Die Verarbeitung erfolgt rein ereignisgesteuert ohne Zwischenspeicherung von Daten außer dem Index `K`.

## Zustandsübersicht

Der Funktionsblock verfügt über keinen definierten ECC (Execution Control Chart). Sein Verhalten lässt sich auf zwei Phasen reduzieren:

| Phase | Beschreibung |
|-------|--------------|
| **Warten** | Der FB erwartet ein Ereignis an `REQ`. |
| **Verarbeiten** | Nach Empfang von `REQ` wird der Index übernommen, die Durchschaltung aktualisiert und `CNF` gesendet. Danach kehrt der FB sofort in den Wartezustand zurück. |

Eine parallele Verarbeitung mehrerer Ereignisse ist nicht vorgesehen; der FB ist für den strikt sequenziellen Betrieb ausgelegt.

## Anwendungsszenarien

- **Signalweiterleitung** in modularen Automatisierungssystemen, bei denen ein Sensorwert oder eine Steuergröße wahlweise an verschiedene Verbraucher (z. B. Aktoren, Visualisierungen) weitergegeben werden muss.
- **Kanalumschaltung** in Kommunikationsschnittstellen, die auf dem AUDI-Adapterprotokoll basieren.
- **Test- und Simulationsumgebungen**, bei denen ein Datenstrom gezielt auf verschiedene Analyse- oder Logging-Pfade umgeschaltet werden soll.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu konventionellen Demultiplexern (z. B. `MUX`/`DEMUX` auf Signalebene) arbeitet **AUDI_DEMUX_4** auf der Ebene von **Adapterverbindungen**. Statt einzelner Bits oder Werte wird der gesamte über den Adapter definierte Datenverbund (Struktur) umgeschaltet. Dies erleichtert die Handhabung komplexer Datentypen und erhöht die Übersichtlichkeit im Applikationsentwurf.

Ein **generischer MUX-Baustein** für denselben Adaptertyp würde umgekehrt mehrere Eingänge auf einen Ausgang zusammenführen. Der vorliegende FB füllt die entgegengesetzte Rolle – die Verteilung eines Eingangs auf mehrere Ausgänge.

## Fazit

Der **AUDI_DEMUX_4** ist ein kompakter, generischer Funktionsblock für die unidirektionale Demultiplexierung von AUDI-Adapterverbindungen. Durch seine reine Ereignissteuerung, die einfache Indexauswahl und die klare Trennung von Ereignis- und Datenpfaden eignet er sich besonders für applikationsneutrale Verteileraufgaben in IEC 61499-2 konformen Systemen. Die Integration als generischer FB erhöht die Wiederverwendbarkeit über verschiedene Projekte hinweg.
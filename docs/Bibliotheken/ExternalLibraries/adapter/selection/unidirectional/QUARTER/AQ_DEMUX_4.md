# AQ_DEMUX_4


![AQ_DEMUX_4](./AQ_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der **AQ_DEMUX_4** ist ein generischer Demultiplexer für den Adapter-Typ `AQ` (Analoge Quantität). Er verteilt einen eingehenden analogen Wert auf einen von vier Ausgangsadaptern, der durch einen Index `K` ausgewählt wird. Der Baustein wird ereignisgesteuert über den Eingang `REQ` aktiviert und bestätigt die Umschaltung über den Ausgang `CNF`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und leitet den Wert weiter |

**Mit-Variable:** K

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der erfolgten Demultiplexierung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index des Zielausgangs (1…4) |

### **Daten-Ausgänge**

Keine direkt deklarierten Datenausgänge – die Ausgabe erfolgt über die Plugs.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| **Plug** | OUT1 | `adapter::types::unidirectional::AQ` | Zielausgang 1 |
| **Plug** | OUT2 | `adapter::types::unidirectional::AQ` | Zielausgang 2 |
| **Plug** | OUT3 | `adapter::types::unidirectional::AQ` | Zielausgang 3 |
| **Plug** | OUT4 | `adapter::types::unidirectional::AQ` | Zielausgang 4 |
| **Socket**| IN   | `adapter::types::unidirectional::AQ` | Eingangswert, der demultiplext werden soll |

## Funktionsweise

Der Demultiplexer arbeitet ereignisgesteuert:

1. Ein anliegender Wert am Adapter-Socket `IN` wird durch den Baustein an den durch `K` bestimmten Plug (OUT1…OUT4) weitergeleitet.
2. Die Weiterleitung erfolgt bei Eintreffen des Ereignisses `REQ`.
3. Nach erfolgreicher Übertragung wird das Bestätigungsereignis `CNF` gesendet.
4. Der Index `K` muss im Bereich 1 bis 4 liegen; andere Werte führen zu keinem definierten Verhalten (in der Standardimplementierung wird typischerweise auf den ersten Ausgang oder gar keinen umgeschaltet).

Da es sich um einen **generischen FB** handelt (erkennbar am Attribut `GenericClassName`), kann der konkrete Datentyp des Adapters `AQ` durch die Entwicklungsumgebung bei der Instanziierung an den tatsächlichen Anwendungsfall angepasst werden (z. B. Analogwert, Temperatur, Druck o. Ä.).

## Technische Besonderheiten

- **Generischer Typ:** Der FB ist als generisch deklariert (`GEN_AQ_DEMUX`). Bei der Instanziierung kann der Adapter-Typ `AQ` durch einen beliebigen, kompatiblen unidirektionalen Adapter ersetzt werden, sofern die Schnittstelle (Datenrichtung) übereinstimmt.
- **Keine Zustandsspeicherung:** Der Baustein besitzt keine expliziten Zustände oder zeitlichen Verzögerungen – die Umschaltung erfolgt strikt ereignisgesteuert und sofort.
- **Ausgangsauswahl:** Die Auswahl des Ausgangs erfolgt über den ganzzahligen Index `K` (UINT). Die Anzahl der Ausgänge ist fest auf vier begrenzt (OUT1…OUT4).
- **Adapter-Schnittstelle:** Sowohl Eingang als auch Ausgänge verwenden unidirektionale Adapter des Typs `AQ`. Dies ermöglicht eine lose Kopplung an andere Bausteine und eine einfache Wiederverwendung in unterschiedlichen Kontexten.

## Zustandsübersicht

Der Baustein definiert **keine** eigenen Zustandsautomaten (Execution Control Chart). Die interne Logik ist rein ereignisgesteuert und ohne Gedächtnis. Nach Annahme des `REQ`-Ereignisses wird unmittelbar die Weiterleitung und das `CNF`-Ereignis ausgelöst. Ein Fehlerzustand oder eine Überlaufbehandlung ist nicht vorgesehen.

## Anwendungsszenarien

- **Signalverteilung:** Ein von einem Sensor bereitgestellter analoger Wert (z. B. Druck, Temperatur) soll wahlweise an verschiedene Auswerteeinheiten oder Aktoren weitergegeben werden.
- **Kanalumschaltung:** In einer Messkette können mehrere Messstellen nacheinander an eine gemeinsame Auswerteelektronik angeschaltet werden.
- **Parametrierbare Multiplexer:** Zusammen mit einem Index-Geber (z. B. Zähler oder SPS-Auswahl) kann der Demultiplexer dynamisch während des Betriebs umgeschaltet werden.
- **Generischer Austausch:** Da der Adapter-Typ `AQ` generisch ist, eignet sich der FB für beliebige analoge oder skalare Signale in der Automatisierungstechnik (z. B. Strom, Spannung, Füllstand).

## Vergleich mit ähnlichen Bausteinen

- **AQ_MUX_4** (Multiplexer): Führt die entgegengesetzte Funktion aus – mehrere Eingänge werden auf einen Ausgang geschaltet. Beide Bausteine ergänzen sich.
- **E_DEMUX** (Ereignis-Demultiplexer): Verteilt Ereignissignale statt Datenwerte. Der `AQ_DEMUX_4` hingegen verteilt kontinuierliche Daten über Adapter und arbeitet nicht auf Ereignis-, sondern auf Datenebene.
- **Demultiplexer mit fester Anzahl Ausgänge:** Andere Bausteine bieten oft 2, 8 oder 16 Ausgänge. Dieser FB bietet genau vier, was für viele Anwendungen ein guter Kompromiss ist.
- **Generische Implementierung:** Viele Demultiplexer in Bibliotheken sind typspezifisch (z. B. für INT oder REAL). Die generische Natur dieses Bausteins erhöht die Wiederverwendbarkeit.

## Fazit

Der `AQ_DEMUX_4` ist ein kompakter, generischer Demultiplexer für unidirektionale analoge Adapter. Er ermöglicht die flexible Verteilung eines Eingangswerts auf vier Ausgänge unter Kontrolle eines Index. Dank der generischen Typdefinition kann er in verschiedenen Signalumgebungen eingesetzt werden, ohne den Anwendungskern zu ändern. Die einfache ereignisgesteuerte Schnittstelle macht ihn zu einem grundlegenden Baustein für Kanalumschaltungen in verteilten Automatisierungs- und Steuerungssystemen.
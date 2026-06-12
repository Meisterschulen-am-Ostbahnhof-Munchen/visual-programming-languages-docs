# AQ_MUX_3


![AQ_MUX_3](./AQ_MUX_3.svg)

* * * * * * * * * *

## Einleitung

Der **AQ_MUX_3** ist ein generischer Multiplexer für AQ-Adapter. Er ermöglicht die Auswahl eines von drei analogen Eingängen (IN1, IN2, IN3) und leitet den gewählten Eingang an den Ausgang OUT weiter. Die Auswahl erfolgt über den Index K, der durch ein Ereignis gesetzt wird. Der Baustein ist als generischer Funktionsblock (Generic FB) realisiert und eignet sich für Anwendungen, bei denen zwischen verschiedenen Signalquellen umgeschaltet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und löst die Umschaltung aus |

**Mit-Variable:** K

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung, dass der Index K übernommen wurde |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index zur Auswahl des Eingangs (0 → IN1, 1 → IN2, 2 → IN3) |

### **Daten-Ausgänge**

Keine – die Ausgabe erfolgt ausschließlich über den Adapter-Ausgang.

### **Adapter**

| Name | Art | Typ | Kommentar |
|------|-----|-----|-----------|
| OUT  | Plug | `adapter::types::unidirectional::AQ` | Ausgang – liefert den Wert des ausgewählten Eingangs (IN1 für K=0, IN2 für K=1, IN3 für K=2) |
| IN1  | Socket | `adapter::types::unidirectional::AQ` | Erster Eingang (K=0) |
| IN2  | Socket | `adapter::types::unidirectional::AQ` | Zweiter Eingang (K=1) |
| IN3  | Socket | `adapter::types::unidirectional::AQ` | Dritter Eingang (K=2) |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert: Sobald am **REQ**-Eingang ein Ereignis eintrifft, wird der aktuelle Wert des Daten-Eingangs **K** ausgewertet. Je nach Wert des Index wird der entsprechende Adapter-Socket (IN1, IN2 oder IN3) auf den Ausgangs-Adapter **OUT** durchgeschaltet. Nach erfolgreicher Umschaltung wird das Bestätigungsereignis **CNF** ausgegeben.

Es gibt keine innere Zustandsmaschine; die Umschaltung erfolgt unmittelbar bei jedem REQ-Ereignis. Der Baustein ist daher deterministisch und verzögerungsarm.

## Technische Besonderheiten

- **Generischer Funktionsblock** – Der Baustein trägt die generische Klasse `GEN_AQ_MUX` und kann daher in verschiedenen Typkonfigurationen verwendet werden.
- **Adapterbasierte Kommunikation** – Ein- und Ausgänge sind als AQ-Adapter (unidirektional) realisiert, was eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichen Umgebungen ermöglicht.
- **Lizenz** – Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt.
- Keine eigenen Datenausgänge; die Ausgangsdaten werden über den Adapter OUT transportiert.

## Zustandsübersicht

In der bereitgestellten XML ist kein expliziter ECC (Execution Control Chart) definiert. Das Verhalten des Bausteins ist somit rein kombinatorisch: Jedes REQ-Ereignis führt sofort zum Setzen des Ausgangs und zur Ausgabe von CNF. Es gibt keine internen Verzögerungen oder Wartezustände.

## Anwendungsszenarien

- **Signalumschaltung** – Auswahl zwischen verschiedenen analogen Messwerten (z. B. Temperatur, Druck, Füllstand) zur Weiterverarbeitung in einer Steuerung.
- **Parameterwahl** – Umschalten zwischen verschiedenen Sollwerten oder Konfigurationsprofilen, die als AQ-Adapter vorliegen.
- **Redundanz** – Wechsel zwischen mehreren redundanten Sensoren oder Aktoren zur Erhöhung der Ausfallsicherheit.

## Vergleich mit ähnlichen Bausteinen

- **AQ_MUX_2** – Ein Multiplexer mit nur zwei Eingängen (IN1, IN2). Der AQ_MUX_3 erweitert diese Funktionalität auf drei Eingänge.
- **Datenbasierte MUX-Bausteine** – Im Unterschied zu rein datenorientierten Multiplexern (z. B. `MUX` auf Basis von `ANY`-Datentypen) arbeitet der AQ_MUX_3 ausschließlich über Adapter, was eine engere Kopplung an die AQ-Adapter-Schnittstelle bedeutet.

## Fazit

Der AQ_MUX_3 ist ein einfacher, aber wirksamer generischer Multiplexer für AQ-Adapter. Er erlaubt die flexible Umschaltung zwischen drei analogen Eingängen und eignet sich besonders für modulare Steuerungsarchitekturen, bei denen eine lose Kopplung über Adapter gewünscht ist. Seine deterministische Reaktion und die einfache Schnittstelle machen ihn zu einem zuverlässigen Baustein in der 4diac-IDE.
# ATM_DEMUX_3


![ATM_DEMUX_3](./ATM_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ATM_DEMUX_3** ist ein generischer Demultiplexer für unidirektionale ATM-Datenströme. Er leitet einen eingehenden Datenstrom je nach Index auf einen von drei Ausgängen weiter. Der Baustein ist ereignisgesteuert und eignet sich für die bedarfsgerechte Verteilung von Daten in Automatisierungs- oder Kommunikationssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ    | Kommentar                  |
|----------|--------|----------------------------|
| REQ      | Event  | Setzt den Index K und löst die Weiterleitung aus |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | Kommentar                        |
|----------|--------|----------------------------------|
| CNF      | Event  | Bestätigung der Index-Setzung und Weiterleitung |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| K        | UINT  | Index zur Auswahl des Ausgangs (1, 2 oder 3) |

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden; die Datenweitergabe erfolgt über die Adapter.

### **Adapter**
**Plugs (Ausgänge):**

| Name | Typ                                | Kommentar |
|------|------------------------------------|-----------|
| OUT1 | adapter::types::unidirectional::ATM | Erster Ausgang |
| OUT2 | adapter::types::unidirectional::ATM | Zweiter Ausgang |
| OUT3 | adapter::types::unidirectional::ATM | Dritter Ausgang |

**Sockets (Eingänge):**

| Name | Typ                                | Kommentar                 |
|------|------------------------------------|---------------------------|
| IN   | adapter::types::unidirectional::ATM | Eingangsdatenstrom zum Demultiplexen |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert. Bei einem Ereignis am **REQ**-Eingang wird der aktuelle Wert des Daten-Eingangs **K** (Index) ausgelesen. Anschließend werden die am **IN**-Socket anliegenden Daten (ATM-Adapter) an den entsprechenden Ausgangs-Adapter weitergeleitet:

- **K = 1** → Daten fließen zu **OUT1**
- **K = 2** → Daten fließen zu **OUT2**
- **K = 3** → Daten fließen zu **OUT3**

Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben. Für andere Werte von **K** ist kein Verhalten spezifiziert; in der Praxis sollte der Index auf den gültigen Bereich (1–3) beschränkt werden.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_ATM_DEMUX`) definiert und kann mittels `eclipse4diac::core::GenericClassName` und `TypeHash` für verschiedene Zielplattformen konfiguriert werden.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `adapter::types::unidirectional::ATM`, was eine klare Richtung des Datenflusses vorgibt.
- **Keine Zustandsspeicherung**: Der Baustein ist zustandslos – das Verhalten wird ausschließlich durch das REQ-Ereignis und den aktuellen Index K bestimmt.

## Zustandsübersicht

Der **ATM_DEMUX_3** besitzt keine internen Zustände. Er reagiert auf jedes REQ-Ereignis direkt mit der Weiterleitung und einem CNF-Ereignis (sofern der Index gültig ist). Es gibt keine zeitlichen Abhängigkeiten oder sequenziellen Abläufe.

## Anwendungsszenarien

- **Datenverteilung in Feldbussystemen**: Ein ankommender Datenstrom (z. B. von einem Sensor) wird je nach Adressierung an unterschiedliche Aktoren weitergeleitet.
- **Steuerung von Mehrfachausgängen**: In einer Maschinensteuerung kann ein Signal wahlweise auf drei verschiedene Ausgangskanäle geschaltet werden.
- **Prototyp für n‑fach Demultiplexer**: Der Baustein lässt sich als Basis für erweiterte Demultiplexer mit mehr Ausgängen verwenden (durch Anpassung der Adapteranzahl).

## Vergleich mit ähnlichen Bausteinen

| Baustein           | Beschreibung | Unterschied |
|--------------------|--------------|-------------|
| MUX (Multiplexer)  | Fasst mehrere Eingänge zu einem Ausgang zusammen | Gegenteilige Funktion |
| DEMUX_2 / DEMUX_4 | Demultiplexer mit 2 bzw. 4 Ausgängen | **ATM_DEMUX_3** bietet genau drei Ausgänge und ist auf unidirektionale ATM-Adapter spezialisiert |
| SELECT             | Wählt einen von mehreren Datenpfaden aus (oft ohne Adapter) | Arbeitet meist direkt mit Datenvariablen statt mit Adaptern |

## Fazit

Der **ATM_DEMUX_3** ist ein kompakter und klar definierter Demultiplexer für unidirektionale ATM-Adapter. Seine generische Auslegung ermöglicht eine flexible Integration in verschiedene Automatisierungsprojekte, während die ereignisgesteuerte Arbeitsweise eine deterministische Datenverteilung gewährleistet. Durch die Festlegung auf drei Ausgänge eignet er sich besonders für typische 1‑aus‑3‑Schaltaufgaben in der Steuerungstechnik.
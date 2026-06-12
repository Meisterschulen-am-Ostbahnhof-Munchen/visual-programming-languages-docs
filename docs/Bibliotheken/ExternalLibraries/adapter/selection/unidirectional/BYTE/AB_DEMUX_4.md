# AB_DEMUX_4


![AB_DEMUX_4](./AB_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AB_DEMUX_4 ist ein generischer Demultiplexer für den Adapter-Typ `adapter::types::unidirectional::AB`. Er verteilt eingehende Adapterdaten (IN) auf einen von vier Ausgangsadaptern (OUT1–OUT4), gesteuert durch einen Index K. Der Baustein ist als generischer FB (GenericClassName `'GEN_AB_DEMUX'`) ausgelegt und kann für verschiedene konkrete Adapterversionen parametrisiert werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| **REQ** | Setzt den Index K und löst die Verteilung aus. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| **CNF** | Bestätigung der erfolgreichen Indexsetzung und Verteilung. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| **K** | UINT | Index (Wertebereich 1–4), wählt den Zielausgang aus. |

### **Daten-Ausgänge**

Keine separaten Datenausgänge vorhanden; die Ausgabedaten werden über die Adapter-Plugs bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket (Eingang) | **IN** | adapter::types::unidirectional::AB | Eingangsadapter, der die zu verteilenden Daten liefert. |
| Plug (Ausgang) | **OUT1** | adapter::types::unidirectional::AB | Erster Ausgangsadapter (Index 1). |
| Plug (Ausgang) | **OUT2** | adapter::types::unidirectional::AB | Zweiter Ausgangsadapter (Index 2). |
| Plug (Ausgang) | **OUT3** | adapter::types::unidirectional::AB | Dritter Ausgangsadapter (Index 3). |
| Plug (Ausgang) | **OUT4** | adapter::types::unidirectional::AB | Vierter Ausgangsadapter (Index 4). |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert. Sobald am Ereigniseingang **REQ** ein Ereignis eintrifft, wird der am Dateneingang **K** anliegende Index ausgewertet (Werte 1 bis 4). Der Adapter **IN** wird mit dem dem Index entsprechenden Ausgangsadapter verbunden, d.h. die über den Socket eingehenden Daten werden an den ausgewählten Plug (OUT1..OUT4) weitergeleitet. Nach Abschluss der Weiterleitung wird das Ereignis **CNF** ausgegeben. Bei ungültigen Indexwerten erfolgt keine Weiterleitung und es wird dennoch CNF ausgelöst (implizites Verhalten – die genaue Reaktion ist applikationsabhängig).

## Technische Besonderheiten

- Der FB ist als **generischer Funktionsblock** deklariert (`GenericClassName = 'GEN_AB_DEMUX'`). Dadurch kann er für verschiedene konkrete Adapter-Typen (abgeleitet von `adapter::types::unidirectional::AB`) verwendet werden.
- Es werden keine Daten-E/A außerhalb der Adapter genutzt; die gesamte Datenübertragung erfolgt über die Adapterschnittstellen.
- Der Baustein besitzt keinen internen Zustandsspeicher – jedes REQ-Ereignis wird unabhängig verarbeitet.

## Zustandsübersicht

Der AB_DEMUX_4 hat **keine explizite Zustandsmaschine**. Er verhält sich wie eine rein kombinatorische Signalweiche: Auf jedes REQ folgt sofort die entsprechende Weiterleitung und die Ausgabe von CNF. Da kein Zustand erhalten bleibt, ist das Verhalten deterministisch und frei von Memory-Effekten.

## Anwendungsszenarien

- **Datenpfad-Umschaltung**: In einer Produktionsanlage sollen Sensordaten (z.B. über einen AB-Adapter) je nach Betriebsmodus an verschiedene Steuerungseinheiten weitergegeben werden.
- **Routing von Prozesswerten**: Ein zentraler Datenstrom (z.B. Füllstand, Temperatur) wird auf mehrere parallele Verarbeitungszweige verteilt.
- **Test- und Simulationsumgebungen**: Ein simulierter Datenstrom wird wahlweise an verschiedene Testfälle oder visuelle Komponenten geleitet.

## Vergleich mit ähnlichen Bausteinen

- **AB_MUX (Multiplexer)**: Kehrt die Funktion um – mehrere Eingänge werden auf einen Ausgang gemultiplext. AB_DEMUX_4 realisiert den umgekehrten Fall.
- **AB_DEMUX_2 / AB_DEMUX_8**: Varianten mit zwei bzw. acht Ausgängen. Der vorliegende Baustein bietet genau vier Ausgänge und einen Index im Bereich 1..4.
- **Direkte Verbindung via Adapter**: Ohne Demultiplexer müsste pro Ziel ein eigener Adapter-Socket angelegt werden; der Demultiplexer spart Ressourcen und vereinfacht die Konfiguration.

## Fazit

Der AB_DEMUX_4 ist ein kompakter, generischer Demultiplexer für unidirektionale AB-Adapter. Er ermöglicht eine flexible und ressourcenschonende Verteilung von Adapterdaten auf bis zu vier Ausgänge und eignet sich besonders für Anwendungen, in denen ein Datenstrom wahlweise an verschiedene Verbraucher geschaltet werden muss. Die generische Auslegung erhöht die Wiederverwendbarkeit in unterschiedlichen 4diac-Projekten.
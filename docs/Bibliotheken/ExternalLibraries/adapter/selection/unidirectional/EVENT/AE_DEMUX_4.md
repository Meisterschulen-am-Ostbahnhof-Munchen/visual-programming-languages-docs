# AE_DEMUX_4


![AE_DEMUX_4](./AE_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AE_DEMUX_4** ist ein generischer Demultiplexer für Adapter des Typs `AE`. Er leitet einen an seinem Eingang anliegenden Adapter-Wert auf einen von vier Ausgängen weiter. Die Auswahl des Zielausgangs erfolgt über einen Index-Parameter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit Daten |
|----------|--------------|-----------|
| `REQ`    | Setzt den Index K und löst die Weiterleitung aus | `K` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigt die Ausführung der Demultiplexing-Operation |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung       |
|------|-------|--------------------|
| `K`  | UINT  | Index des Zielausgangs (1..4) |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**
- **Plugs (Ausgänge)**  
  - `OUT1` (Typ `AE`) – Adapter-Ausgang 1  
  - `OUT2` (Typ `AE`) – Adapter-Ausgang 2  
  - `OUT3` (Typ `AE`) – Adapter-Ausgang 3  
  - `OUT4` (Typ `AE`) – Adapter-Ausgang 4  

- **Socket (Eingang)**  
  - `IN` (Typ `AE`) – Eingangsadapter, der auf einen der Ausgänge umgeleitet wird

## Funktionsweise
Der Baustein arbeitet als **1-zu-4-Demultiplexer** auf Adapterebene. Bei einem Ereignis am Eingang `REQ` wird der aktuell am Socket `IN` anliegende Adapter-Wert (d. h. das gesamte Daten- und Ereignisinterface des Adapters) auf den durch den Daten-Eingang `K` vorgegebenen Ausgangs-Adapter (`OUT1` … `OUT4`) durchgeschaltet. Die restlichen Ausgänge bleiben dabei inaktiv. Nach erfolgreicher Weiterleitung wird das Ausgangsereignis `CNF` gesendet.

Der Index `K` muss einen gültigen Wert zwischen 1 und 4 annehmen; ungültige Werte führen zu undefiniertem Verhalten.

## Technische Besonderheiten
- Der Baustein ist als **generischer Typ** (`GenericClassName = 'GEN_AE_DEMUX'`) ausgelegt und kann in verschiedenen Kontexten wiederverwendet werden.
- Die Adapter-Schnittstellen sind vom Typ `adapter::types::unidirectional::AE`, d. h. es handelt sich um unidirektionale Ereignis-/Datenadapter.
- Der Baustein enthält einen Typ-Hash (`TypeHash`), der die Identifikation in verteilten Systemen unterstützt.
- Urheberrechtlich geschützt (Eclipse Public License 2.0).

## Zustandsübersicht
Der FB verfügt über keine expliziten Zustände; die Funktionalität ist rein kombinatorisch bzw. ereignisgesteuert. Eine Demultiplexing-Operation wird innerhalb eines einzigen Event-Aufrufs ausgeführt.

## Anwendungsszenarien
- **Signalverteilung** in der Automatisierungstechnik, z. B. Weiterleiten eines Messwerts an verschiedene Verarbeitungsstationen.
- **Steuerungslogiken**, bei denen ein Steuerbefehl wahlweise an unterschiedliche Aktoren gesendet werden muss.
- **Routing von Adapter-verbundenen Komponenten** in modularen 4diac-Anwendungen.

## Vergleich mit ähnlichen Bausteinen
- **`AE_SELECT`** – Ein Multiplexer, der aus mehreren Eingängen einen auswählt. Der Demultiplexer ist die duale Funktion.
- **`E_DEMUX`** – Ein reiner Ereignis-Demultiplexer ohne Daten (nur Event-Weiterleitung). `AE_DEMUX_4` arbeitet dagegen mit vollständigen Adaptern und überträgt sowohl Ereignisse als auch Daten.
- **`DATA_DEMUX_4`** – Demultiplexer für einfache Datentypen (z. B. INT, BOOL). Der hier beschriebene Baustein ist für den komplexen Adaptertyp `AE` spezialisiert.

## Fazit
Der `AE_DEMUX_4` stellt einen kompakten und generischen Demultiplexer für Adapter-basierte Kommunikation dar. Er ermöglicht die dynamische Weiterleitung eines gesamten Adapter-Interfaces an einen von vier Ausgängen und eignet sich besonders für modulare und wiederverwendbare Automatisierungslösungen in der 4diac-IDE.